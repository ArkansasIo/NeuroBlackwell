#pragma once
#include "neural_types.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
namespace nb {
struct Synapse {
    std::uint64_t source{}, target{};
    double weight{};
    double delay_ms{1.0};
    double eligibility{};
};
class SynapseNetwork {
public:
    void reserve(std::size_t n);
    void connect(std::uint64_t source, std::uint64_t target, double weight, double delay_ms);
    void clear();
    [[nodiscard]] const std::vector<Synapse>& edges() const noexcept { return edges_; }
    void apply_stdp(std::uint64_t source, std::uint64_t target, double delta,
                    double minimum_weight = 0.0, double maximum_weight = 10.0);
private:
    std::vector<Synapse> edges_;
};
}