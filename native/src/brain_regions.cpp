#include "brain_regions.hpp"
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <utility>

namespace nb {
void BrainRegionRegistry::add(BrainRegion region) {
    if (region.name.empty()) {
        throw std::invalid_argument("region name must not be empty");
    }
    if (find(region.id)) {
        throw std::invalid_argument("duplicate brain region id");
    }
    const auto finite = [](double value) { return std::isfinite(value); };
    if (!finite(region.center.x) || !finite(region.center.y) || !finite(region.center.z) ||
        !finite(region.extent.x) || !finite(region.extent.y) || !finite(region.extent.z)) {
        throw std::invalid_argument("region geometry must be finite");
    }
    if (region.extent.x < 0.0 || region.extent.y < 0.0 || region.extent.z < 0.0) {
        throw std::invalid_argument("region extents must be non-negative");
    }
    regions_.push_back(std::move(region));
}

const BrainRegion* BrainRegionRegistry::find(std::uint32_t id) const noexcept {
    const auto it = std::find_if(regions_.begin(), regions_.end(),
        [id](const auto& region) { return region.id == id; });
    return it == regions_.end() ? nullptr : &*it;
}
} // namespace nb
