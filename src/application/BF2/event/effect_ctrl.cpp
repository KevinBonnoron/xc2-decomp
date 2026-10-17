#include "event/effect_ctrl.h"

#include "event/effect_manager.h"
#include "event/i_attach_actor.h"
#include "framework/effect/effect_manager.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace event {
enum ATTACH_TYPE : int;

EffectCtrl::EffectCtrl() {
  mAttribute = 0;
  reset();
}

void EffectCtrl::create(const char *name, u32 attribute) {
  destroy();
  mName = name;
  mAttribute = attribute;
  reset();
}

void EffectCtrl::destroy() {
  if (mCaster != nullptr) {
    for (size_t i = 0; i < mHandles.size(); i++) {
      mCaster->setEffectCaster(false, mHandles[i]);
    }
  }
  if (mMount != nullptr) {
    for (size_t i = 0; i < mHandles.size(); i++) {
      mMount->setEffectMount(false, mHandles[i], "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
    }
  }
  mCaster = nullptr;
  mMount = nullptr;
  mHandles.clear();
}

void EffectCtrl::genelate() {
  handle = fw::EffectManager::get()->create(mName.c_str(), mm::mtl::Singleton<EffectManager>::getPtr()->getResPack(), true);
  fw::EffectManager::get()->setCategory(handle, static_cast<fw::EF_CATEGORY>(3));
}

void EffectCtrl::dead() {
  if (handle != 0) {
    fw::EffectManager::get()->dead(handle);
  }
  for (size_t i = 0; i < mHandles.size(); i++) {
    fw::EffectManager::get()->dead(mHandles[i]);
  }
}

void EffectCtrl::kill() {
  if (mCaster != nullptr) {
    for (size_t i = 0; i < mHandles.size(); i++) {
      mCaster->setEffectCaster(false, mHandles[i]);
    }
  }
  if (mMount != nullptr) {
    for (size_t i = 0; i < mHandles.size(); i++) {
      mMount->setEffectMount(false, mHandles[i], "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
    }
  }
  if (handle != 0) {
    fw::EffectManager::get()->remove(handle);
  }
  for (size_t i = 0; i < mHandles.size(); i++) {
    fw::EffectManager::get()->remove(mHandles[i]);
  }
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
