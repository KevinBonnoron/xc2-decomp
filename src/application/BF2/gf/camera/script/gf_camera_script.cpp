#include "gf/camera/script/gf_camera_script.h"

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_update_info.h"
#include "gf/camera/gf_camera_utilities.h"

namespace fw {
enum CAMERA_PRIO : int;
} // namespace fw

namespace gf {

mm::mtl::IntrusivePtr<fw::Camera> ScriptCameraEntity::create(const mm::Vec3 &position, const mm::Vec3 &rotation) {
  // __LINE__ must be 47 as in the original file: it is the line argument of the allocation.
#line 47
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) ScriptCameraEntity(position, rotation);
}

static constexpr fw::CAMERA_PRIO CAMERA_PRIO_UNKNOWN_55 = static_cast<fw::CAMERA_PRIO>(55); // Inferred role: camera prio script; original name unknown.

ScriptCameraEntity::ScriptCameraEntity(const mm::Vec3 &position, const mm::Vec3 &rotation)
    : fw::Camera(CAMERA_PRIO_UNKNOWN_55), unknownb0(position), unknownc0(rotation), unknownd0(position), unknowne0(rotation), unknownf0(position), unknown100(rotation), unknown110(0.0f),
      unknown114(0.0f) {
  m_fov = 45.0f;
  unknown30 = 0.4f;
  unknown34 = 80000.0f;
  mm::Vec3 target = unknown171(unknown100.x, unknown100.y, 0.0f);
  target += unknownf0;
  setLookAt(unknownf0, target, unknown100.z);
}

ScriptCameraEntity::~ScriptCameraEntity() {}

void ScriptCameraEntity::onActivate() {}

void ScriptCameraEntity::update(const fw::UpdateInfo &info) {
  if (unknown110 > 0.0f) {
    calcSpeedTypeLinearSpacing();
    unknown114 += info.unknown04 / (1.0f / 30.0f);
    if (unknown110 < unknown114) {
      unknown114 = unknown110;
    }
  }
  mm::Vec3 target = unknown171(unknown100.x, unknown100.y, 0.0f);
  target += unknownf0;
  setLookAt(unknownf0, target, unknown100.z);
}

void ScriptCameraEntity::calcSpeedTypeLinearSpacing() {
  f32 rate = unknown114 / unknown110;
  unknownf0 = unknownb0 + (unknownd0 - unknownb0) * rate;
  unknown100 = unknownc0 + (unknowne0 - unknownc0) * rate;
}

void ScriptCameraEntity::move(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time) {
  unknown110 = time;
  unknown114 = 0.0f;
  if (time <= 0.0f) {
    unknownf0 = position;
    unknown100 = rotation;
  } else {
    unknownb0 = unknownf0;
    unknownc0 = unknown100;
    unknownd0 = position;
    unknowne0 = rotation;
  }
}

const mm::mtl::RTTI *ScriptCameraEntity::getRTTI() const { return &m_rtti; }

const char *ScriptCameraEntity::getName() const { return "ScriptCameraEntity"; }

ScriptCamera::ScriptCamera() {}

ScriptCamera::~ScriptCamera() {}

void ScriptCamera::start(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time) {
  if (unknown08.get() == nullptr) {
    unknown08 = ScriptCameraEntity::create(position, rotation);
    // The frame count is converted in place, as in end: with time / 30.0f written in the call the address of the layer (add x0, x8, #0x20) comes before the fdiv of 1.0.0: 0x71001e6260.
    time /= 30.0f;
    fw::CameraManager::get()->unknown20[0].push(unknown08, time);
  }
}

void ScriptCamera::end(f32 time) {
  if (unknown08.get() != nullptr) {
    if (unknown08->unknowna0) {
      time /= 30.0f;
      fw::CameraManager::get()->unknown20[0].pop(unknown08, time);
    }
    unknown08 = nullptr;
  }
}

void ScriptCamera::move(const mm::Vec3 &position, const mm::Vec3 &rotation, f32 time) {
  if (unknown08.get() != nullptr) {
    static_cast<ScriptCameraEntity *>(unknown08.get())->move(position, rotation, time);
  }
}

} // namespace gf
