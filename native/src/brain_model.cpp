#include "brain_model.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
#include <map>
#include <stdexcept>
#include <utility>

namespace nb {
BrainModel::BrainModel(std::uint64_t seed) : seed_(seed) {}

void BrainModel::reserve(std::size_t n) {
    neurons_.reserve(n);
    input_.reserve(n);
    last_spike_ms_.reserve(n);
    network_.reserve(n);
    pending_events_.reserve(n);
}

std::uint64_t BrainModel::add_neuron(Vec3 position, NeuronType type, std::uint32_t region_id) {
    const auto id = static_cast<std::uint64_t>(neurons_.size());
    Neuron neuron{id, position, type};
    neuron.region_id = region_id;
    neurons_.push_back(neuron);
    input_.push_back(0.0);
    last_spike_ms_.push_back(-std::numeric_limits<double>::infinity());
    return id;
}

std::vector<std::uint64_t> BrainModel::add_population(const NeuronPopulation& population) {
    const auto first_id = static_cast<std::uint64_t>(neurons_.size());
    const auto members = population.generate(first_id);
    std::vector<std::uint64_t> ids;
    ids.reserve(members.size());
    for (const auto& member : members) {
        ids.push_back(add_neuron(member.position, member.type, member.region_id));
    }
    return ids;
}

void BrainModel::connect(std::uint64_t source, std::uint64_t target, double weight, double delay_ms) {
    if (source >= neurons_.size() || target >= neurons_.size()) {
        throw std::out_of_range("synapse neuron id");
    }
    network_.connect(source, target, weight, delay_ms);
}

void BrainModel::stimulate(std::uint64_t neuron_id, double current) {
    if (neuron_id >= input_.size()) {
        throw std::out_of_range("stimulus neuron id");
    }
    if (!std::isfinite(current)) {
        throw std::invalid_argument("non-finite stimulus");
    }
    input_[neuron_id] += current;
}

void BrainModel::set_stdp_parameters(const STDPParameters& parameters) {
    if (!std::isfinite(parameters.potentiation) || parameters.potentiation < 0.0 ||
        !std::isfinite(parameters.depression) || parameters.depression < 0.0 ||
        !std::isfinite(parameters.tau_plus_ms) || parameters.tau_plus_ms <= 0.0 ||
        !std::isfinite(parameters.tau_minus_ms) || parameters.tau_minus_ms <= 0.0 ||
        !std::isfinite(parameters.minimum_weight) || !std::isfinite(parameters.maximum_weight) ||
        parameters.minimum_weight > parameters.maximum_weight) {
        throw std::invalid_argument("invalid STDP parameters");
    }
    stdp_parameters_ = parameters;
}

void BrainModel::step(double dt_ms) {
    if (!(dt_ms > 0.0) || !std::isfinite(dt_ms)) {
        throw std::invalid_argument("dt must be finite and positive");
    }
    const double end_time_ms = time_ms_ + dt_ms;
    if (!std::isfinite(end_time_ms)) {
        throw std::overflow_error("brain simulation time overflow");
    }

    // Event times are quantized to this step: events due by its end contribute
    // during the current integration interval.
    std::vector<PendingSynapticEvent> future_events;
    future_events.reserve(pending_events_.size());
    for (const auto& event : pending_events_) {
        if (event.delivery_time_ms <= end_time_ms) {
            input_[event.target] += event.weight;
        } else {
            future_events.push_back(event);
        }
    }
    pending_events_.swap(future_events);

    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        auto& neuron = neurons_[i];
        const double tau = std::max(1e-9, neuron.leak_tau_ms);
        neuron.membrane_mv += dt_ms * ((-70.0 - neuron.membrane_mv) / tau + input_[i]);
        neuron.spiked = neuron.membrane_mv >= neuron.threshold_mv;
        if (neuron.spiked) {
            neuron.membrane_mv = -70.0;
        }
    }

    // Pair-based STDP uses only spike times from earlier steps. The helper's
    // positive interval means potentiation (post after pre); negative means
    // depression (pre after post). Plasticity is opt-in and weights are clamped.
    if (plasticity_enabled_) {
        std::map<std::pair<std::uint64_t, std::uint64_t>, double> weight_deltas;
        for (const auto& synapse : network_.edges()) {
            const bool pre_spiked = neurons_[synapse.source].spiked;
            const bool post_spiked = neurons_[synapse.target].spiked;
            double delta = 0.0;
            if (pre_spiked && std::isfinite(last_spike_ms_[synapse.target])) {
                delta += stdp_delta(last_spike_ms_[synapse.target] - end_time_ms, stdp_parameters_);
            }
            if (post_spiked && std::isfinite(last_spike_ms_[synapse.source])) {
                delta += stdp_delta(end_time_ms - last_spike_ms_[synapse.source], stdp_parameters_);
            }
            if (delta != 0.0) {
                weight_deltas[{synapse.source, synapse.target}] += delta;
            }
        }
        for (const auto& [pair, delta] : weight_deltas) {
            network_.apply_stdp(pair.first, pair.second, delta,
                                 stdp_parameters_.minimum_weight,
                                 stdp_parameters_.maximum_weight);
        }
    }

    for (std::size_t i = 0; i < neurons_.size(); ++i) {
        if (neurons_[i].spiked) {
            last_spike_ms_[i] = end_time_ms;
        }
    }

    for (const auto& synapse : network_.edges()) {
        if (neurons_[synapse.source].spiked) {
            pending_events_.push_back({
                end_time_ms + synapse.delay_ms,
                synapse.target,
                synapse.weight
            });
        }
    }

    std::fill(input_.begin(), input_.end(), 0.0);
    time_ms_ = end_time_ms;
}
} // namespace nb
