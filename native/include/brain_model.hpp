#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace nb {
struct Vec3 { double x{}, y{}, z{}; };
enum class NeuronType : std::uint8_t { Excitatory, Inhibitory, Glial };

struct Neuron {
    std::uint64_t id{};
    Vec3 position{};
    NeuronType type{NeuronType::Excitatory};
    double membrane_mv{-70.0};
    double threshold_mv{-50.0};
    double leak_tau_ms{20.0};
    bool spiked{false};
};

struct Synapse {
    std::uint64_t source{}, target{};
    double weight{};
    double delay_ms{1.0};
};

class BrainModel {
public:
    explicit BrainModel(std::uint64_t seed = 1);
    void reserve(std::size_t n);
    std::uint64_t add_neuron(Vec3 position, NeuronType type);
    void connect(std::uint64_t source, std::uint64_t target, double weight, double delay_ms = 1.0);
    void step(double dt_ms);
    void stimulate(std::uint64_t neuron_id, double current);
    const std::vector<Neuron>& neurons() const noexcept { return neurons_; }
    const std::vector<Synapse>& synapses() const noexcept { return synapses_; }
    double time_ms() const noexcept { return time_ms_; }
private:
    std::vector<Neuron> neurons_;
    std::vector<Synapse> synapses_;
    std::vector<double> input_;
    double time_ms_{};
    std::uint64_t seed_{};
};
}