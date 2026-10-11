#include "brain_model.hpp"
#include <cassert>
#include <cmath>
#include <stdexcept>

int main() {
    nb::BrainModel brain(7);
    brain.reserve(2);
    const auto source = brain.add_neuron({0, 0, 0}, nb::NeuronType::Excitatory, 11);
    const auto target = brain.add_neuron({1, 0, 0}, nb::NeuronType::Inhibitory, 12);
    assert(brain.neurons()[source].region_id == 11);
    assert(brain.neurons()[target].region_id == 12);
    brain.connect(source, target, 25.0, 2.0);

    brain.stimulate(source, 25.0);
    brain.step(1.0);
    assert(brain.neurons().size() == 2 && brain.synapses().size() == 1);
    assert(brain.neurons()[source].spiked);
    assert(!brain.neurons()[target].spiked);
    assert(brain.pending_event_count() == 1);
    assert(std::abs(brain.time_ms() - 1.0) < 1e-12);

    brain.step(1.0);
    assert(!brain.neurons()[target].spiked);
    assert(brain.pending_event_count() == 1);

    brain.step(1.0);
    assert(brain.neurons()[target].spiked);
    assert(brain.pending_event_count() == 0);
    assert(std::abs(brain.time_ms() - 3.0) < 1e-12);

    bool rejects_invalid_dt = false;
    try {
        brain.step(0.0);
    } catch (const std::invalid_argument&) {
        rejects_invalid_dt = true;
    }
    assert(rejects_invalid_dt);

    nb::BrainModel population_brain(42);
    const nb::NeuronPopulation population({
        77, nb::NeuronType::Glial, 4, {10, 20, 30}, {2, 3, 4}
    });
    const auto ids = population_brain.add_population(population);
    assert(ids.size() == 4);
    assert(ids.front() == 0 && ids.back() == 3);
    for (const auto id : ids) {
        assert(population_brain.neurons()[id].region_id == 77);
        assert(population_brain.neurons()[id].type == nb::NeuronType::Glial);
    }
    return 0;
}
