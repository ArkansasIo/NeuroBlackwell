#include "learning_rules.hpp"
#include <cmath>
namespace nb {
double stdp_delta(double dt,const STDPParameters& p) noexcept {
    if (dt > 0.0) return p.potentiation * std::exp(-dt / p.tau_plus_ms);
    if (dt < 0.0) return -p.depression * std::exp(dt / p.tau_minus_ms);
    return 0.0;
}
}