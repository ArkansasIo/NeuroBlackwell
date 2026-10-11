# Synthetic Human Brain Program — Native Engine

## Build
```sh
cmake -S native -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --parallel
ctest --test-dir build/native --output-on-failure
```

Requires CMake 3.20+, a C17 compiler, and a C++20 compiler.

## Modules
- `brain_model.*`: neuron state and simulation step.
- `synapse_network.*`: directed connections.
- `learning_rules.*`: illustrative STDP update curve.
- `brain_c_api.*`: stable C ABI for external front ends.
- `neural_address.*`: fixed-width address utility for 128/256/512/1024-bit IDs.
- `simulation.*`: deterministic simulation clock configuration.
- `brain_regions.*`: region registry.
- `neuron_population.*`: reproducible synthetic population coordinates.

This is a small research simulator, not a biologically complete brain. Synthetic atlas coordinates are not MRI data. The current stepper is simplified and does not model conduction delays or full Hodgkin–Huxley dynamics.
