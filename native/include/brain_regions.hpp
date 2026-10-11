#pragma once
#include "neural_types.hpp"
#include <cstdint>
#include <string>
#include <vector>
namespace nb {
struct BrainRegion {
    std::uint32_t id{};
    std::string name;
    std::string parent_id;
    Vec3 center{};
    Vec3 extent{};
};
class BrainRegionRegistry {
public:
    void add(BrainRegion region);
    [[nodiscard]] const BrainRegion* find(std::uint32_t id) const noexcept;
    [[nodiscard]] const std::vector<BrainRegion>& all() const noexcept { return regions_; }
private:
    std::vector<BrainRegion> regions_;
};
}