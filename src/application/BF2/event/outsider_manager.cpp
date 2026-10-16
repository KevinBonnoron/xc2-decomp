#include "event/outsider_manager.h"

namespace event {

OutsiderManager::OutsiderManager() : dispFlags(0), flags(0), mTargets(OBJ_TYPE_NONE) {}

void OutsiderManager::clear() {
  if (flags & FLAG_ACTIVE) {
    update(false);
  }
  mField.clear();
  mTargets = OBJ_TYPE_NONE;
  flags = 0;
}

void OutsiderManager::update(bool isHide) {
  if (mField.getType() < OutsiderField::TYPE_CIRCLE) {
    return;
  }
  if (mTargets & OBJ_TYPE_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_NPC);
  }
  if (mTargets & OBJ_TYPE_ROUTED_NPC) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_NPC);
  }
  if (mTargets & OBJ_TYPE_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ENEMY);
  }
  if (mTargets & OBJ_TYPE_ROUTED_ENEMY) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_ENEMY);
  }
  if (mTargets & OBJ_TYPE_ROUTED_MAP_OBJ) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MAP_OBJ);
  }
  if (mTargets & OBJ_TYPE_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_MOB);
  }
  if (mTargets & OBJ_TYPE_ROUTED_MOB) {
    updateSub(isHide, gmk::GMK_TYPE_ROUTED_MOB);
  }
}

void OutsiderManager::update() {
  if (flags & FLAG_ACTIVE) {
    mField.update();
    if (mField.getRadius() > 0.0f) {
      update(true);
    }
  }
}

void OutsiderManager::defineTgt(OBJ_TYPE targets) { mTargets = targets; }

void OutsiderManager::defineFld(OutsiderField::TYPE type, const mm::Vec3 &pos, f32 radius) { mField.setField(type, pos, radius); }

void OutsiderManager::setActive(bool isActive) {
  if (isActive) {
    flags |= FLAG_ACTIVE;
  } else {
    clear();
  }
}

void OutsiderManager::setDisp(bool isDisp) {
  if (isDisp) {
    dispFlags |= DISP_FLAG_DISP;
  } else {
    dispFlags &= ~DISP_FLAG_DISP;
  }
}

bool OutsiderManager::isDisp() const { return (dispFlags & DISP_FLAG_DISP) != 0; }

} // namespace event
