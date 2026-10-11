cmake_minimum_required(VERSION 3.20)
project(synthetic_human_brain_native LANGUAGES C CXX)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(synthetic_human_brain STATIC
    src/brain_model.cpp
    src/synapse_network.cpp
    src/learning_rules.cpp
    src/brain_c_api.cpp
    src/neural_address.c
    src/simulation.cpp
)
target_include_directories(synthetic_human_brain PUBLIC include)
add_library(neuroblackwell_brain ALIAS synthetic_human_brain)

add_executable(shb_brain_demo src/main.cpp)
target_link_libraries(shb_brain_demo PRIVATE synthetic_human_brain)

enable_testing()
add_executable(shb_brain_test tests/test_brain.cpp)
target_link_libraries(shb_brain_test PRIVATE synthetic_human_brain)
add_test(NAME shb_brain_test COMMAND shb_brain_test)

add_executable(shb_learning_rules_test tests/test_learning_rules.cpp)
target_link_libraries(shb_learning_rules_test PRIVATE synthetic_human_brain)
add_test(NAME shb_learning_rules_test COMMAND shb_learning_rules_test)

add_executable(shb_c_api_test tests/test_c_api.cpp)
target_link_libraries(shb_c_api_test PRIVATE synthetic_human_brain)
add_test(NAME shb_c_api_test COMMAND shb_c_api_test)

add_executable(shb_neural_address_test tests/test_neural_address.c)
target_link_libraries(shb_neural_address_test PRIVATE synthetic_human_brain)
add_test(NAME shb_neural_address_test COMMAND shb_neural_address_test)

add_executable(shb_simulation_test tests/test_simulation.cpp)
target_link_libraries(shb_simulation_test PRIVATE synthetic_human_brain)
add_test(NAME shb_simulation_test COMMAND shb_simulation_test)
