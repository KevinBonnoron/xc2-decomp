#include "gf/camera/gimmick/gf_camera_gimmick.h"

#include <math.h>

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_update_info.h"
#include "gf/camera/gf_camera_utilities.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

void GimmickCamera::updateParams() {
  mm::Vec3 target = unknown171(unknownc0.x, unknownc0.y, 0.0f);
  target += unknownb0;
  m_fov = unknownd0;
  setLookAt(unknownb0, target, unknownc0.z);
}

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55); // Inferred role: camera prio gimmick; original name unknown.

GimmickCamera::GimmickCamera() : GimmickCamera(CAMERA_PRIO_UNKNOWN_55) {}

f32 GimmickCamera::getPitch(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  f32 yaw = getYaw(direction, reference);
  mm::Vec3 from = direction;
  mm::Vec3 to = reference;
  mm::Quat rotation;
  rotation.x = 0.0f;
  rotation.y = sinf(yaw * -0.5f);
  rotation.z = 0.0f;
  rotation.w = cosf(yaw * -0.5f);
  from = rotation.rotate(from);
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.z * to.y - from.y * to.z < 0.0f ? -angle : angle;
}

f32 GimmickCamera::getYaw(const mm::Vec3 &direction, const mm::Vec3 &reference) {
  mm::Vec3 from(direction.x, 0.0f, direction.z);
  mm::Vec3 to(reference.x, 0.0f, reference.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return 0.0f;
  }
  from.unknown002();
  to.unknown002();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  return from.x * to.z - from.z * to.x < 0.0f ? 6.2831855f - angle : angle;
}

// __LINE__ must be 110, 117, 128 and 140 as in the original file: they are the line arguments of the allocations.
mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create() {
#line 110
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera;
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(fw::CAMERA_PRIO prio) {
#line 110
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera(prio);
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char *name) {
#line 117
  GimmickCamera *camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera;
  camera->unknown100f0 = 1;
  camera->unknown100f4 = 0;
  camera->setReadFile(name);
  return camera;
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char *name, GF_OBJ_HANDLE *handle) {
#line 128
  GimmickCamera *camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera;
  camera->unknown100f0 = 1;
  camera->unknown100f4 = 1;
  camera->m_handle = handle;
  camera->setReadFile(name);
  return camera;
}

mm::mtl::IntrusivePtr<fw::Camera> GimmickCamera::create(const char *name, const mm::Vec3 &position, f32 rotation) {
#line 140
  GimmickCamera *camera = new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) GimmickCamera;
  camera->unknown100f0 = 1;
  camera->unknown100f4 = 2;
  camera->unknown10110 = position;
  camera->unknown10120 = rotation;
  camera->setReadFile(name);
  return camera;
}

void GimmickCamera::setHandle(GF_OBJ_HANDLE *handle) {
  m_handle = handle;
  fw::UpdateInfo info;
  info.unknown04 = 0.0f;
  updatePlayCamera(info);
  updateParams();
}

void GimmickCamera::setLookLock(const mm::Vec3 &position) {
  unknown10154 = true;
  unknown10160 = position;
  mm::Vec3 delta = unknown10160 - unknownb0;
  f32 distance = sqrtf(delta.x * delta.x + delta.y * delta.y + delta.z * delta.z);
  if (distance <= 1.0f) {
    distance = 1.0f;
  }
  mm::Vec3 direction = unknown10160 - unknownb0;
  mm::Vec3 reference = mm::Vec3::unitZ;
  unknownc0.x = getPitch(direction, reference);
  unknownc0.y = getYaw(direction, reference);
  mm::Quat quat = unknown169(unknownc0.x, unknownc0.y, 0.0f);
  mm::Vec3 offset = mm::Vec3::unitZ * distance;
  unknownb0 = unknown10160 + quat.rotate(mm::Vec3(-offset.x, -offset.y, -offset.z));
}

void GimmickCamera::add(const Param &param) {
  if (!unknown100f8) {
    unknown00e0.push_back(param);
  }
}

void GimmickCamera::onActivate() {}

bool GimmickCamera::isPlayEnd() const {
  if (unknown100f9) {
    return !unknown100f8;
  }

  return false;
}

void GimmickCamera::calcSpeedTypeLinearSpacing(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov) {
  f32 rate = unknown10104 / from.unknown30;
  position = from.unknown00 + (to.unknown00 - from.unknown00) * rate;
  rotation = from.unknown10 + (to.unknown10 - from.unknown10) * rate;
  fov = from.unknown20 + (to.unknown20 - from.unknown20) * rate;
}

void GimmickCamera::calcSpeedTypeSlowOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov) {
  f32 rate = slowOut(unknown10104 / from.unknown30);
  position = from.unknown00 + (to.unknown00 - from.unknown00) * rate;
  rotation = from.unknown10 + (to.unknown10 - from.unknown10) * rate;
  fov = from.unknown20 + (to.unknown20 - from.unknown20) * rate;
}

void GimmickCamera::calcSpeedTypeFastOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov) {
  f32 rate = fastOut(unknown10104 / from.unknown30);
  position = from.unknown00 + (to.unknown00 - from.unknown00) * rate;
  rotation = from.unknown10 + (to.unknown10 - from.unknown10) * rate;
  fov = from.unknown20 + (to.unknown20 - from.unknown20) * rate;
}

void GimmickCamera::calcSpeedTypeFastInFastOut(const Param &from, const Param &to, f32 time, mm::Vec3 &position, mm::Vec3 &rotation, f32 &fov) {
  f32 rate = fastInFastOut(unknown10104 / from.unknown30);
  position = from.unknown00 + (to.unknown00 - from.unknown00) * rate;
  rotation = from.unknown10 + (to.unknown10 - from.unknown10) * rate;
  fov = from.unknown20 + (to.unknown20 - from.unknown20) * rate;
}

bool GimmickCamera::isLoaded() const { return true; }

void GimmickCamera::play() {
  if (!unknown100f8 && !unknown00e0.empty()) {
    unknown100f8 = true;
    unknown100f9 = true;
    unknown10100 = 0;
    unknown10104 = 0.0f;
    Param first = unknown00e0.front();
    unknownb0 = first.unknown00;
    unknownc0 = first.unknown10;
    unknownd0 = first.unknown20;
  }
}

void GimmickCamera::update(const fw::UpdateInfo &info) {
  if (unknown10130 != nullptr) {
    if (unknown100fa) {
      play();
    }
    unknown10130 = nullptr;
  }
  if (unknown100f8) {
    updatePlayCamera(info);
  }
  updateParams();
}

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

void GimmickCamera::setFov(const f32 &fov) {
  if (!unknown100f8) {
    unknownd0 = fov;
  }
}

f32 GimmickCamera::curve(f32 a, f32 b, f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return (1.0f - x) * a + x * b;
}

f32 GimmickCamera::slowOut(f32 t) {
  f32 x = sinf((1.0f - t) * 1.5707964f + 4.712389f) + 1.0f;
  return 1.0f - (x + (1.0f - x) * 0.0f);
}

f32 GimmickCamera::fastOut(f32 t) {
  f32 x = sinf(t * 1.5707964f + 4.712389f) + 1.0f;
  return x + (1.0f - x) * 0.0f;
}

f32 GimmickCamera::fastInFastOut(f32 t) { return (tanf(t * 1.8849556f + 2.1991148f) + 1.38f) / 2.76f; }

mm::Vec3 GimmickCamera::calcAxisRotatePosition(const mm::Vec3 &from, const mm::Vec3 &to, f32 rate, f32 scale, f32 offset) {
  mm::Vec3 fromDelta = mm::Vec3(0.0f, from.y, 0.0f) - from;
  f32 fromRadius = sqrtf(fromDelta.x * fromDelta.x + fromDelta.y * fromDelta.y + fromDelta.z * fromDelta.z);
  mm::Vec3 toDelta = mm::Vec3(0.0f, to.y, 0.0f) - to;
  f32 toRadius = sqrtf(toDelta.x * toDelta.x + toDelta.y * toDelta.y + toDelta.z * toDelta.z);
  f32 radius = fromRadius + (toRadius - fromRadius) * offset + (toRadius - fromRadius) * scale * rate;
  mm::Vec3 position = from + (to - from) * offset + (to - from) * scale * rate;
  mm::Vec3 center(0.0f, position.y, 0.0f);
  mm::Vec3 direction = position - center;
  direction.unknown001();
  return center + direction * radius;
}

const s32 &GimmickCamera::getIndex() const { return unknown10100; }

const f32 &GimmickCamera::getFrame() const { return unknown10104; }

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
