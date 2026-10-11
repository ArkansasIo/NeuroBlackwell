#include "brain_model.hpp"
#include <cassert>
#include <cmath>
int main(){
    nb::BrainModel b(7); b.reserve(2);
    auto a=b.add_neuron({0,0,0},nb::NeuronType::Excitatory);
    auto c=b.add_neuron({1,0,0},nb::NeuronType::Inhibitory);
    b.connect(a,c,5.0);
    b.stimulate(a,25.0); b.step(1.0);
    assert(b.neurons().size()==2 && b.synapses().size()==1);
    assert(std::abs(b.time_ms()-1.0)<1e-12);
    return 0;
}