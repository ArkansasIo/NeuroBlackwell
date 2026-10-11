#pragma once
#include <cstddef>
#include <cstdint>
namespace nb {
struct SimulationConfig {
    double dt_ms{0.1};
    std::uint64_t seed{1};
    std::size_t max_neurons{100000};
    bool plasticity_enabled{true};
};
class SimulationClock {
public:
    explicit SimulationClock(SimulationConfig config = {});
    void advance();
    void advance(std::size_t steps);
    [[nodiscard]] double time_ms() const noexcept { return time_ms_; }
    [[nodiscard]] const SimulationConfig& config() const noexcept { return config_; }
private:
    SimulationConfig config_;
    double time_ms_{};
};
}