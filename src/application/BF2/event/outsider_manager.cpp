#include "event/outsider_manager.h"

namespace event {

OutsiderManager::OutsiderManager() : unknown10(0), unknown14(0), unknown18(OBJ_TYPE_NONE) {}

void OutsiderManager::clear() {
  if (unknown14 & FLAG_ACTIVE) {
    update(false);
  }
  unknown20.clear();
  unknown18 = OBJ_TYPE_NONE;
  unknown14 = 0;
}

void OutsiderManager::update(bool isHide) {
  if (unknown20.getType() < OutsiderField::TYPE_CIRCLE) {
    return;
  }
  if (unknown18 & OBJ_TYPE_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_NPC);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_NPC);
  }
  if (unknown18 & OBJ_TYPE_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_ENEMY);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_MAP_OBJ) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MAP_OBJ);
  }
  if (unknown18 & OBJ_TYPE_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_MOB);
  }
  if (unknown18 & OBJ_TYPE_ROUTED_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MOB);
  }
}

void OutsiderManager::update() {
  if (unknown14 & FLAG_ACTIVE) {
    unknown20.update();
    if (unknown20.getRadius() > 0.0f) {
      update(true);
    }
  }
}

void OutsiderManager::defineTgt(OBJ_TYPE targets) { unknown18 = targets; }

void OutsiderManager::defineFld(OutsiderField::TYPE type, const mm::Vec3 &pos, f32 radius) { unknown20.setField(type, pos, radius); }

void OutsiderManager::setActive(bool isActive) {
  if (isActive) {
    unknown14 |= FLAG_ACTIVE;
  } else {
    clear();
  }
}

void OutsiderManager::setDisp(bool isDisp) {
  if (isDisp) {
    unknown10 |= DISP_FLAG_DISP;
  } else {
    unknown10 &= ~DISP_FLAG_DISP;
  }
}

bool OutsiderManager::isDisp() const { return (unknown10 & DISP_FLAG_DISP) != 0; }

} // namespace event
