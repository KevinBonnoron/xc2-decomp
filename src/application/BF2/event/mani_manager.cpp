#include "event/mani_manager.h"

#include "fw/fw_coli_check.h"
#include "mm_math/mm_vec3.h"

namespace event {

void ManiManager::adjestPosY(mm::Vec3 &position) {
  mm::Vec3 result = position;
  mm::Vec3 start;
  start.x = position.x;
  start.y = position.y + 1.0f;
  start.z = position.z;
  if (fw::ColiCheck::getSnapPos(result, start, 6.0f, 0xffffffff)) {
    position = result;
  }
}

bool ManiManager::exist(mm::mtl::FixedVector<Item, ITEM_COUNT> &items, IManiCallback *callback) {
  for (u32 i = 0; i < items.size(); i++) {
    if (items[i].unknown00 == callback) {
      return true;
    }
  }
  return false;
}

void ManiManager::setAdjestPosEnable(bool isEnable) { unknown18.set(FLAG_ADJEST_POS, isEnable); }

bool ManiManager::isAdjestPosEnable() const { return unknown18.test(FLAG_ADJEST_POS); }

void ManiManager::setDebugEnable(bool isEnable) { unknown1c.set(DEBUG_FLAG_ENABLE, isEnable); }

bool ManiManager::OnMouseButtonDown(ml::EventView *view) { return false; }

} // namespace event
