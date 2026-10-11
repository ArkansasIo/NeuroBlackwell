#include "simulation.hpp"
#include <cassert>
int main(){
    nb::SimulationClock c({0.5,7,1000,true});
    c.advance(4);
    assert(c.time_ms()==2.0);
    assert(c.config().seed==7);
    return 0;
}