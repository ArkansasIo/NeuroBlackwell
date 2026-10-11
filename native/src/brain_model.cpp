#include "brain_model.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace nb {
BrainModel::BrainModel(std::uint64_t seed): seed_(seed) {}
void BrainModel::reserve(std::size_t n){ neurons_.reserve(n); input_.reserve(n); }
std::uint64_t BrainModel::add_neuron(Vec3 p, NeuronType type){
    auto id=static_cast<std::uint64_t>(neurons_.size());
    neurons_.push_back(Neuron{id,p,type});
    input_.push_back(0.0);
    return id;
}
void BrainModel::connect(std::uint64_t s,std::uint64_t t,double w,double d){
    if(s>=neurons_.size()||t>=neurons_.size()) throw std::out_of_range("synapse neuron id");
    if(!std::isfinite(w)||!std::isfinite(d)||d<0.0) throw std::invalid_argument("invalid synapse");
    synapses_.push_back(Synapse{s,t,w,d});
}
void BrainModel::stimulate(std::uint64_t id,double current){
    if(id>=input_.size()) throw std::out_of_range("stimulus neuron id");
    if(!std::isfinite(current)) throw std::invalid_argument("non-finite stimulus");
    input_[id]+=current;
}
void BrainModel::step(double dt){
    if(!(dt>0.0)||!std::isfinite(dt)) throw std::invalid_argument("dt must be finite and positive");
    std::vector<double> next_input(input_.size(),0.0);
    for(std::size_t i=0;i<neurons_.size();++i){
        auto &n=neurons_[i];
        const double tau=std::max(1e-9,n.leak_tau_ms);
        n.membrane_mv += dt*((-70.0-n.membrane_mv)/tau + input_[i]);
        n.spiked=n.membrane_mv>=n.threshold_mv;
        if(n.spiked) n.membrane_mv=-70.0;
    }
    for(const auto &s:synapses_) if(neurons_[s.source].spiked) next_input[s.target]+=s.weight;
    input_.swap(next_input);
    time_ms_+=dt;
}
}