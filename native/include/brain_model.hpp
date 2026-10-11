#pragma once
#include "learning_rules.hpp"
#include "neural_types.hpp"
#include "neuron_population.hpp"
#include "synapse_network.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace nb {
struct Neuron {
    std::uint64_t id{};
    Vec3 position{};
    NeuronType type{NeuronType::Excitatory};
    double membrane_mv{-70.0};
    double threshold_mv{-50.0};
    double leak_tau_ms{20.0};
    bool spiked{false};
    std::uint32_t region_id{};
};

struct PendingSynapticEvent {
    double delivery_time_ms{};
    std::uint64_t target{};
    double weight{};
};

class BrainModel {
public:
    explicit BrainModel(std::uint64_t seed = 1);
    void reserve(std::size_t n);
    std::uint64_t add_neuron(Vec3 position, NeuronType type, std::uint32_t region_id = 0);
    std::vector<std::uint64_t> add_population(const NeuronPopulation& population);
    void connect(std::uint64_t source, std::uint64_t target, double weight, double delay_ms = 1.0);
    void step(double dt_ms);
    void stimulate(std::uint64_t neuron_id, double current);
    void set_plasticity_enabled(bool enabled) noexcept { plasticity_enabled_ = enabled; }
    [[nodiscard]] bool plasticity_enabled() const noexcept { return plasticity_enabled_; }
    void set_stdp_parameters(const STDPParameters& parameters);
    const std::vector<Neuron>& neurons() const noexcept { return neurons_; }
    const std::vector<Synapse>& synapses() const noexcept { return network_.edges(); }
    double time_ms() const noexcept { return time_ms_; }
    std::size_t pending_event_count() const noexcept { return pending_events_.size(); }

private:
    std::vector<Neuron> neurons_;
    SynapseNetwork network_;
    std::vector<double> input_;
    std::vector<double> last_spike_ms_;
    std::vector<PendingSynapticEvent> pending_events_;
    STDPParameters stdp_parameters_{};
    bool plasticity_enabled_{false};
    double time_ms_{};
    std::uint64_t seed_{};
};
} // namespace nb
