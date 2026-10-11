#include "brain_c_api.h"
#include <cassert>
int main() {
    SHBBrain* b=shb_brain_create(7);
    assert(b);
    assert(shb_brain_add_neuron(b,{0,0,0},SHB_EXCITATORY)==0);
    assert(shb_brain_add_neuron(b,{1,0,0},SHB_INHIBITORY)==1);
    assert(shb_brain_connect(b,0,1,2.0,1.0)==0);
    assert(shb_brain_stimulate(b,0,25.0)==0);
    assert(shb_brain_step(b,1.0)==0);
    assert(shb_brain_neuron_count(b)==2);
    assert(shb_brain_synapse_count(b)==1);
    assert(shb_brain_time_ms(b)==1.0);
    shb_brain_destroy(b);
    return 0;
}