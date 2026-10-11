#include "synapse_network.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace nb {
void SynapseNetwork::reserve(std::size_t n) {
    edges_.reserve(n);
}

void SynapseNetwork::connect(std::uint64_t source, std::uint64_t target, double weight, double delay_ms) {
    if (!std::isfinite(weight) || !std::isfinite(delay_ms) || delay_ms < 0.0) {
        throw std::invalid_argument("invalid synapse");
    }
    edges_.push_back(Synapse{source, target, weight, delay_ms, 0.0});
}

void SynapseNetwork::clear() {
    edges_.clear();
}

void SynapseNetwork::apply_stdp(std::uint64_t source, std::uint64_t target, double delta,
                                double minimum_weight, double maximum_weight) {
    if (!std::isfinite(delta) || !std::isfinite(minimum_weight) ||
        !std::isfinite(maximum_weight) || minimum_weight > maximum_weight) {
        throw std::invalid_argument("invalid STDP weight update");
    }
    for (auto& edge : edges_) {
        if (edge.source == source && edge.target == target) {
            edge.weight = std::clamp(edge.weight + delta, minimum_weight, maximum_weight);
        }
    }
}
} // namespace nb
