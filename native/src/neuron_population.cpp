#include "neuron_population.hpp"
#include <cmath>
#include <stdexcept>

namespace nb {
NeuronPopulation::NeuronPopulation(PopulationConfig config) : config_(config) {
    const auto finite = [](double value) { return std::isfinite(value); };
    if (!finite(config.center.x) || !finite(config.center.y) || !finite(config.center.z) ||
        !finite(config.spread.x) || !finite(config.spread.y) || !finite(config.spread.z)) {
        throw std::invalid_argument("population geometry must be finite");
    }
    if (config.spread.x < 0.0 || config.spread.y < 0.0 || config.spread.z < 0.0) {
        throw std::invalid_argument("population spread must be non-negative");
    }
}

std::vector<PopulationMember> NeuronPopulation::generate(std::uint64_t first_id) const {
    std::vector<PopulationMember> members;
    members.reserve(config_.count);
    if (config_.count == 0) {
        return members;
    }

    for (std::size_t i = 0; i < config_.count; ++i) {
        const double u = (static_cast<double>(i) + 0.5) / static_cast<double>(config_.count);
        const double x = 2.0 * u - 1.0;
        const double y = (i % 2 == 0 ? 1.0 : -1.0) * config_.spread.y * (1.0 - u);
        const double z = (static_cast<double>((i * 37U) % config_.count) /
                          static_cast<double>(config_.count)) * 2.0 - 1.0;
        members.push_back({
            first_id + static_cast<std::uint64_t>(i),
            config_.region_id,
            config_.type,
            {config_.center.x + x * config_.spread.x,
             config_.center.y + y,
             config_.center.z + z * config_.spread.z}
        });
    }
    return members;
}
} // namespace nb
