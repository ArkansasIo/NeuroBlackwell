#pragma once
#include <cstdint>
#include <string_view>
namespace nb {
struct Vec3 { double x{}, y{}, z{}; };
enum class NeuronType : std::uint8_t { Excitatory, Inhibitory, Glial };
constexpr std::string_view neuron_type_name(NeuronType t) noexcept {
    switch (t) {
        case NeuronType::Excitatory: return "excitatory";
        case NeuronType::Inhibitory: return "inhibitory";
        case NeuronType::Glial: return "glial";
    }
    return "unknown";
}
}