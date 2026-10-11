#include "brain_regions.hpp"
#include <algorithm>
#include <stdexcept>
namespace nb {
void BrainRegionRegistry::add(BrainRegion region) {
    if (region.name.empty()) throw std::invalid_argument("region name must not be empty");
    if (find(region.id)) throw std::invalid_argument("duplicate brain region id");
    regions_.push_back(std::move(region));
}
const BrainRegion* BrainRegionRegistry::find(std::uint32_t id) const noexcept {
    const auto it=std::find_if(regions_.begin(),regions_.end(),[id](const auto& r){return r.id==id;});
    return it==regions_.end()?nullptr:&*it;
}
}