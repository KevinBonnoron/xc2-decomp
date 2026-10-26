#include "event/mani_manager.h"

#include "event/manager.h"
#include "fw/fw_coli_check.h"
#include "ml/scn.h"
#include "ml/win_view.h"
#include "mm_math/mm_vec3.h"
#include "scn/scn_debug.h"

namespace event {

ManiManager::ManiManager()
    : unknown22030(MANI_TYPE_POS), unknown22040(mm::Mat44::identity), unknown22080(mm::Mat44::identity), unknown220c0(mm::Mat44::identity), unknown22100(mm::Mat44::identity),
      unknown22140(mm::Mat44::identity) {}

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

void ManiManager::create() {
  if (!unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->attachWorkEvent(this, false);
    unknown18.set(FLAG_ATTACHED);
  }
  unknown20.clear();
}

void ManiManager::clear() {
  clearManipulate();
  if (unknown18.test(FLAG_ATTACHED)) {
    Manager::get()->getScn()->getView(-1)->detachWorkEvent(this);
    unknown18.set(FLAG_ATTACHED, false);
  }
  unknown20.clear();
  unknown18.clear();
}

void ManiManager::clearManipulate() {
  unknown20.clear();
  unknown22030 = MANI_TYPE_POS;
  Manager::get()->getScn()->unknown30->clrManipulator();
  unknown18.set(FLAG_ACTIVE, false);
}

void ManiManager::setEnable(bool isEnable) {
  if (isEnable) {
    unknown18.set(FLAG_ENABLE, true);
  } else {
    clearManipulate();
    unknown18.set(FLAG_ENABLE, false);
  }
}

void ManiManager::setAdjestPosEnable(bool isEnable) { unknown18.set(FLAG_ADJEST_POS, isEnable); }

bool ManiManager::isAdjestPosEnable() const { return unknown18.test(FLAG_ADJEST_POS); }

void ManiManager::setDebugEnable(bool isEnable) { unknown1c.set(DEBUG_FLAG_ENABLE, isEnable); }

bool ManiManager::OnMouseButtonDown(ml::EventView *view) { return false; }

} // namespace event
