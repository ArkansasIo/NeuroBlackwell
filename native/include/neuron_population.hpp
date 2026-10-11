#pragma once
#include "brain_regions.hpp"
#include "neural_types.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
namespace nb {
struct PopulationConfig {
    std::uint32_t region_id{};
    NeuronType type{NeuronType::Excitatory};
    std::size_t count{};
    Vec3 center{};
    Vec3 spread{0.1,0.1,0.1};
};
struct PopulationMember { std::uint64_t neuron_id{}; std::uint32_t region_id{}; NeuronType type{}; Vec3 position{}; };
class NeuronPopulation {
public:
    explicit NeuronPopulation(PopulationConfig config);
    [[nodiscard]] const PopulationConfig& config() const noexcept { return config_; }
    [[nodiscard]] std::vector<PopulationMember> generate(std::uint64_t first_id) const;
private:
    PopulationConfig config_;
};
}