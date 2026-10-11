#ifndef SYNTHETIC_HUMAN_BRAIN_NEURAL_ADDRESS_H
#define SYNTHETIC_HUMAN_BRAIN_NEURAL_ADDRESS_H
#include <stddef.h>
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif
#define SHB_NEURAL_ADDRESS_MAX_BYTES 128
typedef struct { uint16_t bit_width; uint8_t bytes[SHB_NEURAL_ADDRESS_MAX_BYTES]; } SHBNeuralAddress;
int shb_address_init(SHBNeuralAddress* address, uint16_t bit_width);
int shb_address_set_bit(SHBNeuralAddress* address, uint16_t bit_index, int value);
int shb_address_get_bit(const SHBNeuralAddress* address, uint16_t bit_index);
int shb_address_equal(const SHBNeuralAddress* a, const SHBNeuralAddress* b);
size_t shb_address_hex(const SHBNeuralAddress* address, char* out, size_t out_size);
#ifdef __cplusplus
}
#endif
#endif