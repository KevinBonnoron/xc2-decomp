#include "gf/field/gf_mob_slot_manager.h"

#include "gf/gf_allocator.h"

namespace gf {

GfMobSlotManager::GfMobSlotManager() : unknown528(1e12f) { unknown408.setAllocator(getAllocator(ALLOCATOR_DEFAULT)); }

void GfMobSlotManager::disposeMobInfos() { unknown000.clear(); }

} // namespace gf
