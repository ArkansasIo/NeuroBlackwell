#include "neuron_population.hpp"
#include <stdexcept>
namespace nb {
NeuronPopulation::NeuronPopulation(PopulationConfig c):config_(c) {
    if(c.spread.x<0||c.spread.y<0||c.spread.z<0) throw std::invalid_argument("population spread must be non-negative");
}
std::vector<PopulationMember> NeuronPopulation::generate(std::uint64_t first_id) const {
    std::vector<PopulationMember> out; out.reserve(config_.count);
    if(config_.count==0) return out;
    for(std::size_t i=0;i<config_.count;++i) {
        const double u=(static_cast<double>(i)+0.5)/static_cast<double>(config_.count);
        const double x=2.0*u-1.0;
        const double y=(i%2==0?1.0:-1.0)*config_.spread.y*(1.0-u);
        const double z=(static_cast<double>((i*37)%config_.count)/static_cast<double>(config_.count)*2.0-1.0);
        out.push_back({first_id+i,config_.region_id,config_.type,
            {config_.center.x+x*config_.spread.x,config_.center.y+y,config_.center.z+z*config_.spread.z}});
    }
    return out;
}
}