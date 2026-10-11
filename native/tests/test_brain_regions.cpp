#include "brain_regions.hpp"
#include "neuron_population.hpp"
#include <cassert>
#include <cmath>
#include <limits>
#include <stdexcept>

int main() {
    nb::BrainRegionRegistry registry;
    registry.add({1, "Synthetic cortex", "", {}, {1, 1, 1}});
    assert(registry.find(1) != nullptr);
    assert(registry.find(2) == nullptr);
    assert(registry.all().size() == 1);

    bool duplicate = false;
    try {
        registry.add({1, "duplicate", "", {}, {}});
    } catch (const std::invalid_argument&) {
        duplicate = true;
    }
    assert(duplicate);

    bool negative_extent = false;
    try {
        registry.add({2, "invalid extent", "", {}, {-1, 1, 1}});
    } catch (const std::invalid_argument&) {
        negative_extent = true;
    }
    assert(negative_extent);

    bool non_finite_region = false;
    try {
        registry.add({3, "invalid center", "", {std::numeric_limits<double>::quiet_NaN(), 0, 0}, {1, 1, 1}});
    } catch (const std::invalid_argument&) {
        non_finite_region = true;
    }
    assert(non_finite_region);

    nb::NeuronPopulation population({1, nb::NeuronType::Excitatory, 8, {2, 3, 4}, {1, 2, 3}});
    const auto members = population.generate(100);
    assert(members.size() == 8);
    assert(members.front().neuron_id == 100);
    assert(members.back().neuron_id == 107);
    for (const auto& member : members) {
        assert(member.region_id == 1);
        assert(member.type == nb::NeuronType::Excitatory);
        assert(member.position.x >= 1.0 && member.position.x <= 3.0);
        assert(member.position.y >= 1.0 && member.position.y <= 5.0);
        assert(member.position.z >= 1.0 && member.position.z <= 7.0);
    }

    nb::NeuronPopulation empty_population({2, nb::NeuronType::Glial, 0, {}, {}});
    assert(empty_population.generate(500).empty());

    bool negative_spread = false;
    try {
        nb::NeuronPopulation invalid({1, nb::NeuronType::Inhibitory, 1, {}, {-1, 0, 0}});
    } catch (const std::invalid_argument&) {
        negative_spread = true;
    }
    assert(negative_spread);

    bool non_finite_population = false;
    try {
        nb::NeuronPopulation invalid({1, nb::NeuronType::Inhibitory, 1,
            {0, 0, 0}, {std::numeric_limits<double>::infinity(), 0, 0}});
    } catch (const std::invalid_argument&) {
        non_finite_population = true;
    }
    assert(non_finite_population);
    return 0;
}
