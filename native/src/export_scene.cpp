#include "brain_model.hpp"

#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

namespace {
const char* type_name(nb::NeuronType type) {
    return nb::neuron_type_name(type).data();
}
}

int main(int argc, char** argv) {
    const std::string output_path = argc > 1 ? argv[1] : "brain3d/data/native_snapshot.json";
    nb::BrainModel brain(20261011);
    constexpr std::uint32_t region_count = 4;
    constexpr std::uint64_t neuron_count = 96;
    brain.reserve(neuron_count);

    for (std::uint64_t i = 0; i < neuron_count; ++i) {
        const double angle = 6.283185307179586 * static_cast<double>(i) / neuron_count;
        const double ring = 0.55 + 0.08 * std::sin(angle * 7.0);
        const nb::Vec3 position{
            0.82 * ring * std::cos(angle),
            0.70 * ring * std::sin(angle),
            0.24 * std::sin(angle * 3.0) + 0.10 * std::cos(angle * 5.0)
        };
        const auto type = (i % 7 == 0) ? nb::NeuronType::Inhibitory : nb::NeuronType::Excitatory;
        brain.add_neuron(position, type, static_cast<std::uint32_t>(1 + (i % region_count)));
    }

    for (std::uint64_t i = 0; i < neuron_count; ++i) {
        const auto next = (i + 1) % neuron_count;
        const auto skip = (i + 7) % neuron_count;
        brain.connect(i, next, 0.35 + 0.05 * static_cast<double>(i % 5), 1.0 + 0.25 * static_cast<double>(i % 4));
        brain.connect(i, skip, 0.18 + 0.03 * static_cast<double>(i % 3), 2.0);
    }

    for (std::uint64_t i = 0; i < neuron_count; i += 12) {
        brain.stimulate(i, 25.0);
    }
    for (int step = 0; step < 8; ++step) {
        brain.step(1.0);
    }

    std::ofstream out(output_path);
    if (!out) {
        std::cerr << "Unable to open output file: " << output_path << '\n';
        return 1;
    }
    out << std::setprecision(12);
    out << "{\n"
        << "  \"version\": \"1.0\",\n"
        << "  \"dataset_id\": \"NB-NATIVE-SNAPSHOT-001\",\n"
        << "  \"status\": \"synthetic_native_simulation\",\n"
        << "  \"coordinate_system\": \"normalized_brain_xyz\",\n"
        << "  \"simulation_time_ms\": " << brain.time_ms() << ",\n"
        << "  \"regions\": [\n"
        << "    {\"id\":1,\"name\":\"Frontal synthetic region\",\"center\":[-0.35,0.25,0.05]},\n"
        << "    {\"id\":2,\"name\":\"Temporal synthetic region\",\"center\":[0.45,0.05,-0.02]},\n"
        << "    {\"id\":3,\"name\":\"Parietal synthetic region\",\"center\":[0.0,0.45,0.08]},\n"
        << "    {\"id\":4,\"name\":\"Occipital synthetic region\",\"center\":[0.0,-0.45,-0.03]}\n"
        << "  ],\n  \"neurons\": [\n";
    const auto& neurons = brain.neurons();
    for (std::size_t i = 0; i < neurons.size(); ++i) {
        const auto& n = neurons[i];
        out << "    {\"id\":" << n.id
            << ",\"region_id\":" << n.region_id
            << ",\"type\":\"" << type_name(n.type) << "\""
            << ",\"x\":" << n.position.x << ",\"y\":" << n.position.y
            << ",\"z\":" << n.position.z << ",\"membrane_mv\":" << n.membrane_mv
            << ",\"spiked\":" << (n.spiked ? "true" : "false") << "}";
        out << (i + 1 == neurons.size() ? "\n" : ",\n");
    }
    out << "  ],\n  \"connections\": [\n";
    const auto& edges = brain.synapses();
    for (std::size_t i = 0; i < edges.size(); ++i) {
        const auto& e = edges[i];
        out << "    {\"source\":" << e.source << ",\"target\":" << e.target
            << ",\"weight\":" << e.weight << ",\"delay_ms\":" << e.delay_ms << "}";
        out << (i + 1 == edges.size() ? "\n" : ",\n");
    }
    out << "  ],\n"
        << "  \"provenance\": [{\"kind\":\"generated\",\"description\":\"Deterministic demonstration from the native C++ engine; not biological measurements.\"}]\n"
        << "}\n";
    if (!out) {
        std::cerr << "Failed while writing output file: " << output_path << '\n';
        return 1;
    }
    std::cout << "Wrote " << neurons.size() << " neurons and " << edges.size()
              << " connections at t=" << brain.time_ms() << " ms to " << output_path << '\n';
    return 0;
}
