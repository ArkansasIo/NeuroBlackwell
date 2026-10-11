# Native tests

CMake registers test executables for the brain model, learning-rule math, C API, neural-address bit operations, simulation clock, and region/population registry.

Run from the repository root:
```sh
cmake -S native -B build/native
cmake --build build/native --parallel
ctest --test-dir build/native --output-on-failure
```

A test is considered verified only after the compiler and CTest actually execute it; adding a test source file alone is not proof of a passing build.
