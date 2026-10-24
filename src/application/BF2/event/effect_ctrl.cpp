#include "event/effect_ctrl.h"

#include "event/effect_manager.h"
#include "event/i_attach_actor.h"
#include "framework/effect/effect_manager.h"
#include "mm_mtl/singleton.h"

namespace fw {
enum EF_CATEGORY : int;
} // namespace fw

namespace event {

EffectCtrl::EffectCtrl() {
  unknown15c = 0;
  reset();
}

void EffectCtrl::create(const char *name, u32 attribute) {
  destroy();
  unknown118 = name;
  unknown15c = attribute;
  reset();
}

void EffectCtrl::destroy() {
  if (unknown1b0 != nullptr) {
    for (size_t i = 0; i < unknown10.size(); i++) {
      unknown1b0->setEffectCaster(false, unknown10[i]);
    }
  }
  if (unknown1c0 != nullptr) {
    for (size_t i = 0; i < unknown10.size(); i++) {
      unknown1c0->setEffectMount(false, unknown10[i], "", mm::Vec3::zero, false, static_cast<ATTACH_TYPE>(0));
    }
  }
  unknown1b0 = nullptr;
  unknown1c0 = nullptr;
  unknown10.clear();
}

void EffectCtrl::genelate() {
  unknown08 = fw::EffectManager::get()->create(unknown118.c_str(), mm::mtl::Singleton<EffectManager>::getPtr()->getResPack(), true);
  fw::EffectManager::get()->setCategory(unknown08, static_cast<fw::EF_CATEGORY>(3));
}

void EffectCtrl::dead() {
  if (unknown08 != 0) {
    fw::EffectManager::get()->dead(unknown08);
  }
  for (size_t i = 0; i < unknown10.size(); i++) {
    fw::EffectManager::get()->dead(unknown10[i]);
  }
}

void EffectCtrl::kill() {
  detach();
  if (unknown08 != 0) {
    fw::EffectManager::get()->remove(unknown08);
  }
  for (size_t i = 0; i < unknown10.size(); i++) {
    fw::EffectManager::get()->remove(unknown10[i]);
  }
}

void EffectCtrl::setSpeed(f32 speed) { m_speed = speed; }

void EffectCtrl::setSkip(f32 skip) { m_skip = skip; }

void EffectCtrl::setPrio(int prio) { m_prio = prio; }

void EffectCtrl::setPos(const mm::Vec3 &pos) { m_pos = pos; }

const mm::Vec3 &EffectCtrl::getPos() const { return m_pos; }

void EffectCtrl::setRot(const mm::Vec3 &rot) { m_rot = rot; }

const mm::Vec3 &EffectCtrl::getRot() const { return m_rot; }

void EffectCtrl::setScale(const mm::Vec3 &scale) { m_scale = scale; }

const mm::Vec3 &EffectCtrl::getScale() const { return m_scale; }

void EffectCtrl::setColor(const mm::Col4 &color) { m_color = color; }

const mm::Col4 &EffectCtrl::getColor() const { return m_color; }

void EffectCtrl::setCaster(IAttachActor *caster) {
  detach();
  unknown1b0 = caster;
  unknown1c0 = nullptr;
  if (unknown1b0 != nullptr) {
    for (size_t i = 0; i < unknown10.size(); i++) {
      unknown1b0->setEffectCaster(true, unknown10[i]);
    }
  }
}

void EffectCtrl::setMount(IAttachActor *mount, const char *bone, const mm::Vec3 &offset, bool isRotate, ATTACH_TYPE type) {
  detach();
  unknown1b0 = nullptr;
  unknown1c0 = mount;
  unknown1c8 = bone;
  unknown1f0 = offset;
  unknown200 = isRotate;
  unknown204 = type;
  if (unknown1c0 != nullptr) {
    for (size_t i = 0; i < unknown10.size(); i++) {
      unknown1c0->setEffectMount(true, unknown10[i], unknown1c8.c_str(), unknown1f0, unknown200, static_cast<ATTACH_TYPE>(unknown204));
    }
  }
}

size_t EffectCtrl::getEffCount() const { return unknown10.size(); }

} // namespace event
