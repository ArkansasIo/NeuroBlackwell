#include "brain_c_api.h"
#include "brain_model.hpp"
#include <new>
struct SHBBrain { nb::BrainModel model; explicit SHBBrain(uint64_t seed):model(seed){} };
extern "C" {
SHBBrain* shb_brain_create(uint64_t seed) { try { return new SHBBrain(seed); } catch (...) { return nullptr; } }
void shb_brain_destroy(SHBBrain* b) { delete b; }
uint64_t shb_brain_add_neuron(SHBBrain* b, SHBVec3 p, SHBNeuronType t) {
    if (!b) return UINT64_MAX;
    try { return b->model.add_neuron({p.x,p.y,p.z}, static_cast<nb::NeuronType>(t)); } catch (...) { return UINT64_MAX; }
}
int shb_brain_connect(SHBBrain* b,uint64_t s,uint64_t t,double w,double d) {
    if (!b) return -1;
    try { b->model.connect(s,t,w,d); return 0; } catch (...) { return -1; }
}
int shb_brain_stimulate(SHBBrain* b,uint64_t id,double current) {
    if (!b) return -1;
    try { b->model.stimulate(id,current); return 0; } catch (...) { return -1; }
}
int shb_brain_step(SHBBrain* b,double dt) {
    if (!b) return -1;
    try { b->model.step(dt); return 0; } catch (...) { return -1; }
}
size_t shb_brain_neuron_count(const SHBBrain* b) { return b ? b->model.neurons().size() : 0; }
size_t shb_brain_synapse_count(const SHBBrain* b) { return b ? b->model.synapses().size() : 0; }
double shb_brain_time_ms(const SHBBrain* b) { return b ? b->model.time_ms() : 0.0; }
}