#ifndef SYNTHETIC_HUMAN_BRAIN_C_API_H
#define SYNTHETIC_HUMAN_BRAIN_C_API_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
typedef struct SHBBrain SHBBrain;
typedef struct { double x, y, z; } SHBVec3;
typedef enum { SHB_EXCITATORY=0, SHB_INHIBITORY=1, SHB_GLIAL=2 } SHBNeuronType;
SHBBrain* shb_brain_create(uint64_t seed);
void shb_brain_destroy(SHBBrain* brain);
uint64_t shb_brain_add_neuron(SHBBrain* brain, SHBVec3 position, SHBNeuronType type);
int shb_brain_connect(SHBBrain* brain, uint64_t source, uint64_t target, double weight, double delay_ms);
int shb_brain_stimulate(SHBBrain* brain, uint64_t neuron_id, double current);
int shb_brain_step(SHBBrain* brain, double dt_ms);
size_t shb_brain_neuron_count(const SHBBrain* brain);
size_t shb_brain_synapse_count(const SHBBrain* brain);
double shb_brain_time_ms(const SHBBrain* brain);
#ifdef __cplusplus
}
#endif
#endif