#include "brain_model.hpp"
#include <iostream>
int main(){
    nb::BrainModel brain(42); brain.reserve(2);
    auto a=brain.add_neuron({-0.1,0,0},nb::NeuronType::Excitatory);
    auto b=brain.add_neuron({0.1,0,0},nb::NeuronType::Inhibitory);
    brain.connect(a,b,2.0);
    brain.stimulate(a,25.0); brain.step(1.0);
    std::cout<<"NeuroBlackwell native demo: neurons="<<brain.neurons().size()
             <<" synapses="<<brain.synapses().size()<<" time_ms="<<brain.time_ms()<<"
";
    return 0;
}