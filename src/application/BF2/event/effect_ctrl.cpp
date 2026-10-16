#include "event/effect_ctrl.h"

namespace event {

EffectCtrl::EffectCtrl() {
  mAttribute = 0;
  reset();
}

void EffectCtrl::setSpeed(f32 speed) { mSpeed = speed; }

void EffectCtrl::setSkip(f32 skip) { mSkip = skip; }

void EffectCtrl::setPrio(int prio) { mPrio = prio; }

void EffectCtrl::setPos(const mm::Vec3 &pos) { mPos = pos; }

const mm::Vec3 &EffectCtrl::getPos() const { return mPos; }

void EffectCtrl::setRot(const mm::Vec3 &rot) { mRot = rot; }

const mm::Vec3 &EffectCtrl::getRot() const { return mRot; }

void EffectCtrl::setScale(const mm::Vec3 &scale) { mScale = scale; }

const mm::Vec3 &EffectCtrl::getScale() const { return mScale; }

void EffectCtrl::setColor(const mm::Col4 &color) { mColor = color; }

const mm::Col4 &EffectCtrl::getColor() const { return mColor; }

size_t EffectCtrl::getEffCount() const { return mHandles.size(); }

} // namespace event
