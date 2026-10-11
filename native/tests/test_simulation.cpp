#include "simulation.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

int main() {
    nb::SimulationClock clock({0.5, 7, 1000, true});
    clock.advance(4);
    assert(std::abs(clock.time_ms() - 2.0) < 1e-12);
    assert(clock.config().seed == 7);
    clock.advance();
    assert(std::abs(clock.time_ms() - 2.5) < 1e-12);

    bool rejects_zero = false;
    try {
        nb::SimulationClock invalid({0.0, 1, 10, false});
    } catch (const std::invalid_argument&) {
        rejects_zero = true;
    }
    assert(rejects_zero);

    bool rejects_nan = false;
    try {
        nb::SimulationClock invalid({std::numeric_limits<double>::quiet_NaN(), 1, 10, false});
    } catch (const std::invalid_argument&) {
        rejects_nan = true;
    }
    assert(rejects_nan);
    return 0;
}
