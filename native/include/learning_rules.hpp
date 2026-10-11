#pragma once
namespace nb {
struct STDPParameters {
    double potentiation{0.005};
    double depression{0.005};
    double tau_plus_ms{20.0};
    double tau_minus_ms{20.0};
    double minimum_weight{0.0};
    double maximum_weight{10.0};
};
double stdp_delta(double dt_ms, const STDPParameters& p) noexcept;
}