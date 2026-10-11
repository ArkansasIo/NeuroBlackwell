#include "brain_regions.hpp"
#include "neuron_population.hpp"
#include <cassert>
#include <stdexcept>
int main() {
    nb::BrainRegionRegistry registry;
    registry.add({1,"Synthetic cortex","",{}, {1,1,1}});
    assert(registry.find(1)!=nullptr);
    assert(registry.find(2)==nullptr);
    bool duplicate=false;
    try { registry.add({1,"duplicate","",{}, {}}); } catch(const std::invalid_argument&) { duplicate=true; }
    assert(duplicate);
    nb::NeuronPopulation pop({1,nb::NeuronType::Excitatory,8,{0,0,0},{1,1,1}});
    auto members=pop.generate(100);
    assert(members.size()==8 && members.front().neuron_id==100 && members.back().neuron_id==107);
    return 0;
}