#include "brain_model.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace nb {
BrainModel::BrainModel(std::uint64_t seed) : seed_(seed) {}

void BrainModel::reserve(std::size_t n) {
    neurons_.reserve(n);
    input_.reserve(n);
    network_.reserve(n);
    pending_events_.reserve(n);
}

std::uint64_t BrainModel::add_neuron(Vec3 position, NeuronType type, std::uint32_t region_id) {
    const auto id = static_cast<std::uint64_t>(neurons_.size());
    Neuron neuron{id, position, type};
    neuron.region_id = region_id;
    neurons_.push_back(neuron);
    input_.push_back(0.0);
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

void BrainModel::step(double dt_ms) {
    if (!(dt_ms > 0.0) || !std::isfinite(dt_ms)) {
        throw std::invalid_argument("dt must be finite and positive");
    }
    const double end_time_ms = time_ms_ + dt_ms;
    if (!std::isfinite(end_time_ms)) {
        throw std::overflow_error("brain simulation time overflow");
    }

    // Events are quantized to the simulation step: events due by the end of
    // this step contribute during this integration interval.
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
