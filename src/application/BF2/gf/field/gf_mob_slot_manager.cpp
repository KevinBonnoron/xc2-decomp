#include "gf/field/gf_mob_slot_manager.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMobSlotManager::GfMobSlotManager() : unknown528(1e12f) { unknown408.setAllocator(getAllocator(ALLOCATOR_UNKNOWN_0)); }

bool GfMobSlotManager::addFailedPopDistSq(f32 distSq) {
  if (unknown420.size() == unknown420.capacity()) {
    return false;
  }
  for (f32 *it = unknown420.begin(); it != unknown420.end(); it++) {
    if (!(*it < distSq)) {
      unknown420.insert(it, distSq);
      return true;
    }
  }
  unknown420.push_back(distSq);
  return true;
}

void GfMobSlotManager::disposeMobInfos() { unknown000.clear(); }

} // namespace gf
