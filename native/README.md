# Synthetic Human Brain Program — Native Engine

## Build
```sh
cmake -S native -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --parallel
ctest --test-dir build/native --output-on-failure
```

Requires CMake 3.20+, a C17 compiler, and a C++20 compiler.

## Modules
- `brain_model.*`: neuron state, simulation stepping, event delivery, and population instantiation.
- `synapse_network.*`: directed connections with weights and delay metadata.
- `learning_rules.*`: pair-based STDP update curve, optionally coupled to observed spike history.
- `brain_c_api.*`: stable C ABI for external front ends.
- `neural_address.*`: fixed-width address utility for 128/256/512/1024-bit IDs.
- `simulation.*`: deterministic simulation clock configuration.
- `brain_regions.*`: validated region registry.
- `neuron_population.*`: deterministic synthetic population coordinates and region labels.

## Event timing and limitations
When a neuron spikes, each outgoing synapse schedules a weighted event at
`simulation_time + delay_ms`. Events due by the end of a simulation step are
applied during that integration interval, so event timing is quantized to the
configured timestep. The current neuron integrator is a simplified leaky
integrate-and-fire model; it is not a conductance-based or Hodgkin–Huxley model.
Pair-based STDP can be enabled with `BrainModel::set_plasticity_enabled(true)`;
updates use prior-step spike timestamps and clamp weights to configured limits via
`set_stdp_parameters`. Plasticity is disabled by default. This is a simplified
learning rule, not a validated model of biological synaptic plasticity. The
synthetic atlas is illustrative and is not derived from MRI data.
