#include "simulation.hpp"
#include <stdexcept>
namespace nb {
SimulationClock::SimulationClock(SimulationConfig c):config_(c){
    if(!(config_.dt_ms>0.0)) throw std::invalid_argument("dt_ms must be positive");
}
void SimulationClock::advance(){time_ms_+=config_.dt_ms;}
void SimulationClock::advance(std::size_t steps){time_ms_+=config_.dt_ms*static_cast<double>(steps);}
}