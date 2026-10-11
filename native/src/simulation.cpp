#include "simulation.hpp"
#include <cmath>
#include <limits>
#include <stdexcept>

namespace nb {
SimulationClock::SimulationClock(SimulationConfig config) : config_(config) {
    if (!(config_.dt_ms > 0.0) || !std::isfinite(config_.dt_ms)) {
        throw std::invalid_argument("dt_ms must be finite and positive");
    }
}

void SimulationClock::advance() {
    advance(1);
}

void SimulationClock::advance(std::size_t steps) {
    const double increment = config_.dt_ms * static_cast<double>(steps);
    if (!std::isfinite(increment) || !std::isfinite(time_ms_ + increment)) {
        throw std::overflow_error("simulation clock exceeded finite time range");
    }
    time_ms_ += increment;
}
} // namespace nb
