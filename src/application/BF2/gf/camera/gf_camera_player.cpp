#include "gf/camera/gf_camera_player.h"

#include <math.h>

#include "framework/framework.h"
#include "framework/memory/framework_memory.h"
#include "fw/fw_param_manager.h"
#include "gf/camera/gf_camera_player_target.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "mm_math/mm_vec3.h"

namespace gf {

// Inferred role: camera parameter read from the param list of the camera; original type name unknown.
struct unknown002 {
  f32 unknown00; // Inferred role: field of view in degrees; original member name unknown.
};

PlayerCamera::~PlayerCamera() { ; }

void PlayerCamera::updateViewMatrix() {
  updateCollision2(unknown40, unknown50);
  unknownd0 = m_saveDistance;
  Camera::updateViewMatrix();
}

// __LINE__ must be 233 as in the original file: it is the line argument of the allocation.
mm::mtl::IntrusivePtr<fw::Camera> PlayerCamera::create() {
  const fw::ParamList *paramList = fw::ParamManager::get()->unknown408[19].operator->();
  fw::ParamAdapter adapter;
  adapter.unknown00 = paramList->unknown0c > 0 ? &paramList->unknown10[0] : nullptr;
#line 233
  return new (fw::Framework::getAllocator(), 16, __FILE__, __LINE__) PlayerCamera(adapter);
}

bool PlayerCamera::isResetClimb() {
  f32 yaw = getYaw(PlayerCameraTarget::get()->unknown60, mm::Vec3::unitZ);
  f32 target = unknownb8;
  if (target < 0.0f) {
    target += 6.2831855f;
  }
  f32 diff = fabsf(yaw - target);
  return diff > 1.4835299f && diff < 4.7996554f;
}

void PlayerCamera::setTarget(GF_OBJ_HANDLE *target) {
  if (target != INVALID_HANDLE) {
    GfObjAcc acc(target);
    if (acc.getType() != OBJECT_TYPE_ENEMY) {
      return;
    }
  }
  if (unknowna8 != target) {
    if (unknowna8 == INVALID_HANDLE) {
      if (PlayerCameraTarget::get() == nullptr) {
        return;
      }
    } else {
      unknown5190 = true;
    }
    unknowna8 = target;
  }
}

f32 PlayerCamera::getFov() { return static_cast<const unknown002 *>(fw::ParamManager::get()->unknown408[19]->unknown10->param)->unknown00; }

const mm::mtl::RTTI *PlayerCamera::getRTTI() const { return &m_rtti; }

const char *PlayerCamera::getName() const { return "PlayerCamera"; }

f32 PlayerCamera::getNearClip() { return 0.4f; }

f32 PlayerCamera::getFarClip() { return 80000.0f; }

bool PlayerCamera::isManual() { return m_manual; }

f32 PlayerCamera::getSaveYaw() const { return m_saveYaw; }

f32 PlayerCamera::getSavePitch() const { return m_savePitch; }

f32 PlayerCamera::getSaveDistance() const { return m_saveDistance; }

f32 PlayerCamera::getSaveHeight() const { return m_saveHeight; }

u32 PlayerCamera::getSaveSide() const { return m_saveSide; }

bool PlayerCamera::isSaveFreeMode() const { return m_manual; }

void PlayerCamera::resetClimb(ResetCameraWallTiming timing) {
  unknown124 = true;
  unknown52c4 = timing;
  unknownf0 = timing == RESET_CAMERA_WALL_TIMING_UNDER_GROUND ? 0.6666667f : 0.23333335f;
}

} // namespace gf
