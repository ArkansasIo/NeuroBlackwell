#include "synapse_network.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
namespace nb {
void SynapseNetwork::reserve(std::size_t n) { edges_.reserve(n); }
void SynapseNetwork::connect(std::uint64_t s,std::uint64_t t,double w,double d) {
    if (!std::isfinite(w) || !std::isfinite(d) || d < 0.0) throw std::invalid_argument("invalid synapse");
    edges_.push_back(Synapse{s,t,w,d,0.0});
}
void SynapseNetwork::clear() { edges_.clear(); }
void SynapseNetwork::apply_stdp(std::uint64_t s,std::uint64_t t,double delta) {
    for (auto& e : edges_) if (e.source==s && e.target==t) e.weight += delta;
}
}