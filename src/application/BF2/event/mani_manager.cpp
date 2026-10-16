#include "event/mani_manager.h"

namespace event {

bool ManiManager::exist(mm::mtl::FixedVector<Item, ITEM_COUNT> &items, IManiCallback *callback) {
  for (u32 i = 0; i < items.size(); i++) {
    if (items[i].callback == callback) {
      return true;
    }
  }
  return false;
}

void ManiManager::setAdjestPosEnable(bool isEnable) { flags.set(FLAG_ADJEST_POS, isEnable); }

bool ManiManager::isAdjestPosEnable() const { return flags.test(FLAG_ADJEST_POS); }

void ManiManager::setDebugEnable(bool isEnable) { mDebugFlags.set(DEBUG_FLAG_ENABLE, isEnable); }

bool ManiManager::OnMouseButtonDown(ml::EventView *view) { return false; }

} // namespace event
