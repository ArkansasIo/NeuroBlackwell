#include "learning_rules.hpp"
#include <cassert>
int main() {
    nb::STDPParameters p;
    assert(nb::stdp_delta(10.0,p) > 0.0);
    assert(nb::stdp_delta(-10.0,p) < 0.0);
    assert(nb::stdp_delta(0.0,p) == 0.0);
    return 0;
}