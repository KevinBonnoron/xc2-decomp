#include "gf/camera/gimmick/gf_camera_gimmick.h"

namespace gf {

void GimmickCamera::onActivate() {}

bool GimmickCamera::isPlayEnd() const {
  if (unknown100f9) {
    return !unknown100f8;
  }

  return false;
}

bool GimmickCamera::isLoaded() const { return true; }

void GimmickCamera::setAuto(bool isAuto) { unknown100fa = isAuto; }

void GimmickCamera::setCollision(bool isCollision) { unknown100fb = isCollision; }

void GimmickCamera::setSpeedFlag(bool isEnable) { unknown100fc = isEnable; }

void GimmickCamera::setPause(bool isPause) { unknown100fd = isPause; }

bool GimmickCamera::isPause() const { return unknown100fd; }

void GimmickCamera::setNearClip(f32 nearClip) { unknown30 = nearClip; }

void GimmickCamera::setFarClip(f32 farClip) { unknown34 = farClip; }

void GimmickCamera::setLookUnlock() { unknown10154 = false; }

const mm::Vec3 &GimmickCamera::getPos() const { return unknownb0; }

void GimmickCamera::setPos(const mm::Vec3 &position) {
  if (!unknown100f8) {
    unknownb0 = position;
  }
}

const mm::Vec3 &GimmickCamera::getRot() const { return unknownc0; }

void GimmickCamera::setRot(const mm::Vec3 &rotation) {
  if (!unknown100f8) {
    unknownc0 = rotation;
  }
}

const f32 &GimmickCamera::getFov() const { return unknownd0; }

const s32 &GimmickCamera::getIndex() const { return unknown10100; }

const s32 &GimmickCamera::getFrame() const { return unknown10104; }

const f32 &GimmickCamera::getSpeed() const { return unknown10108; }

const f32 &GimmickCamera::getControlSpeed() const { return unknown10138; }

void GimmickCamera::clear() {
  if (!unknown100f8) {
    unknown00e0.clear();
  }
}

const mm::mtl::RTTI *GimmickCamera::getRTTI() const { return &m_rtti; }

const char *GimmickCamera::getName() const { return "GimmickCamera"; }

} // namespace gf
