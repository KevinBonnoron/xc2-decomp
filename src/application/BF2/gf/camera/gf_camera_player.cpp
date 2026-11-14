#include "gf/camera/gf_camera_player.h"

#include <math.h>

#include "framework/framework.h"
#include "framework/memory/allocator.h"
#include "framework/memory/framework_memory.h"
#include "framework/reflection.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "gf/camera/gf_camera_player_target.h"
#include "gf/camera/gf_camera_utilities.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/dev_graph.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

void PlayerCamera::createReflection(fw::Reflection *reflection, const char *name, u32 index) {
#line 45
  fw::ReflectionValueStruct *value = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueStruct(name, sizeof(unknown002));
#line 46
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("fov", offsetof(unknown002, fov), 1.0f, 90.0f, 40.0f));
#line 47
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("collision_size", offsetof(unknown002, collision_size), 0.01f, 1.0f, 0.25f));
#line 48
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distance_minimum", offsetof(unknown002, distance_minimum), 0.01f, 100.0f, 2.0f));
#line 49
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distance_maximum", offsetof(unknown002, distance_maximum), 0.01f, 100.0f, 15.0f));
#line 50
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distance_default", offsetof(unknown002, distance_default), 0.01f, 100.0f, 7.0f));
#line 51
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("camera_height", offsetof(unknown002, camera_height), 0.0f, 100.0f, 1.7f));
#line 52
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("look_height", offsetof(unknown002, look_height), 0.0f, 100.0f, 1.5f));
#line 53
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("height_min", offsetof(unknown002, height_min), -5.0f, 0.0f, -0.5f));
#line 54
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("height_max", offsetof(unknown002, height_max), 0.0f, 5.0f, 0.5f));
#line 55
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("pitch_limit_upper", offsetof(unknown002, pitch_limit_upper), 0.0f, 89.0f, 75.0f));
#line 56
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("pitch_limit_lower", offsetof(unknown002, pitch_limit_lower), 0.0f, 89.0f, 75.0f));
#line 57
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("damp_horizontal_revise", offsetof(unknown002, damp_horizontal_revise), 0.01f, 1.0f, 0.1f));
#line 58
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("damp_vertical_revise", offsetof(unknown002, damp_vertical_revise), 0.01f, 1.0f, 0.1f));
#line 59
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("zoom_speed", offsetof(unknown002, zoom_speed), 0.01f, 100.0f, 0.8f));
#line 60
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("yaw_speed", offsetof(unknown002, yaw_speed), 0.01f, 10.0f, 4.0f));
#line 61
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("pitch_speed", offsetof(unknown002, pitch_speed), 0.01f, 10.0f, 4.0f));
#line 62
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("height_speed", offsetof(unknown002, height_speed), 0.01f, 0.1f, 0.1f));
#line 63
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotate_revise", offsetof(unknown002, rotate_revise), 0.01f, 1.0f, 0.07f));
#line 64
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotate_revise_at_manual", offsetof(unknown002, rotate_revise_at_manual), 0.01f, 1.0f, 0.2f));
#line 65
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotate_revise_at_reset", offsetof(unknown002, rotate_revise_at_reset), 0.01f, 1.0f, 0.2f));
#line 66
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("rotate_revise_at_slope", offsetof(unknown002, rotate_revise_at_slope), 0.01f, 1.0f, 0.03f));
#line 67
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("distance_revise", offsetof(unknown002, distance_revise), 0.01f, 1.0f, 0.2f));
#line 68
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                 fw::ReflectionValueF32("target_range_width", offsetof(unknown002, target_range_width), 0.0f, static_cast<f32>(ml::DevGraph::getRootWidth()), 100.0f));
#line 69
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__)
                 fw::ReflectionValueF32("target_range_height", offsetof(unknown002, target_range_height), 0.0f, static_cast<f32>(ml::DevGraph::getRootHeight()), 100.0f));
#line 71
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32(
      "target_range_offset_y", offsetof(unknown002, target_range_offset_y), static_cast<f32>(ml::DevGraph::getRootHeight()) * -0.5f, static_cast<f32>(ml::DevGraph::getRootHeight()) * 0.5f, 0.0f));
#line 72
  fw::ReflectionValueBitset32 *flags = new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueBitset32("flags", offsetof(unknown002, flags));
#line 73
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("slope_revise_enable", 0x10, true));
#line 74
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("horizontal_reverse_enable", 0x20, false));
#line 75
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("vertical_reverse_enable", 0x40, false));
#line 76
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("semimanual_enable", 0x80, false));
#line 77
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("ship_curve", 0x100, false));
#line 78
  flags->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueFlag("ship_random", 0x200, false));
  value->add(flags);
#line 80
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueU32("camera_type", offsetof(unknown002, camera_type), 0u, 1u, 0u));
#line 81
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_roll_min", offsetof(unknown002, ship_roll_min), 1.0f, 90.0f, 2.0f));
#line 82
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_roll_max", offsetof(unknown002, ship_roll_max), 1.0f, 90.0f, 5.0f));
#line 83
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_roll_move", offsetof(unknown002, ship_roll_move), 0.001f, 1.0f, 0.04f));
#line 84
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_pitch_min", offsetof(unknown002, ship_pitch_min), 0.01f, 5.0f, 0.2f));
#line 85
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_pitch_max", offsetof(unknown002, ship_pitch_max), 0.01f, 5.0f, 0.5f));
#line 86
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("ship_pitch_move", offsetof(unknown002, ship_pitch_move), 0.001f, 1.0f, 0.005f));
#line 87
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueS32("look_bone", offsetof(unknown002, look_bone), 0, 1, 0));
#line 88
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("side_distance_min", offsetof(unknown002, side_distance_min), -5.0f, 0.0f, -1.0f));
#line 89
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("side_distance_max", offsetof(unknown002, side_distance_max), 0.0f, 5.0f, 1.0f));
#line 90
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("side_distance1", offsetof(unknown002, side_distance[0]), -5.0f, 5.0f, -0.5f));
#line 91
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("side_distance2", offsetof(unknown002, side_distance[1]), -5.0f, 5.0f, 0.0f));
#line 92
  value->add(new (fw::Allocator::getDebAllocator(), 16, __FILE__, __LINE__) fw::ReflectionValueF32("side_distance3", offsetof(unknown002, side_distance[2]), -5.0f, 5.0f, 0.5f));
  reflection->setReflectionStruct(index, value);
}

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
  if (target != unknown020) {
    GfObjAcc acc(target);
    if (acc.getType() != OBJECT_TYPE_ENEMY) {
      return;
    }
  }
  if (unknowna8 != target) {
    if (unknowna8 == unknown020) {
      if (PlayerCameraTarget::get() == nullptr) {
        return;
      }
    } else {
      unknown5190 = true;
    }
    unknowna8 = target;
  }
}

f32 PlayerCamera::getFov() { return static_cast<const unknown002 *>(fw::ParamManager::get()->unknown408[19]->unknown10->param)->fov; }

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
  unknownf0 = timing == RESET_CAMERA_WALL_TIMING_UNKNOWN_0 ? 0.6666667f : 0.23333335f;
}

f32 PlayerCamera::getYaw(const mm::Vec3 &position, const mm::Vec3 &target) {
  mm::Vec3 from(position.x, 0.0f, position.z);
  mm::Vec3 to(target.x, 0.0f, target.z);
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return m_saveYaw;
  }
  from.unknown001();
  to.unknown001();
  f32 cosine = to.x * from.x + to.y * from.y + to.z * from.z;
  mm::clampRef(cosine, -1.0f, 1.0f);
  f32 angle = mm::acos(cosine);
  mm::Vec3 axis;
  CameraUtilities::getRotateAxis(from, to, axis);
  return axis.y < 0.0f ? 6.2831855f - angle : angle;
}

f32 PlayerCamera::getPitch(const mm::Vec3 &position, const mm::Vec3 &target) {
  f32 yaw = getYaw(position, target);
  mm::Vec3 from = position;
  mm::Vec3 to = target;
  if ((fabsf(from.x) <= 0.000001f && fabsf(from.y) <= 0.000001f && fabsf(from.z) <= 0.000001f) || (fabsf(to.x) <= 0.000001f && fabsf(to.y) <= 0.000001f && fabsf(to.z) <= 0.000001f)) {
    return m_savePitch;
  }
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
  mm::Vec3 axis;
  CameraUtilities::getRotateAxis(from, to, axis);
  return axis.x < 0.0f ? -angle : angle;
}

bool PlayerCamera::getHitPosition(const fw::ColiCheckConfig &config, const mm::Vec3 &start, const mm::Vec3 &end, mm::Vec3 &hitPosition) {
  hitPosition = mm::Vec3::zero;
  unknown160.clear();
  if (!fw::ColiCheck::testLineChara(unknown160, start, end, config)) {
    return false;
  }
  mm::Vec3 position = unknown160.getPosition(0);
  mm::Vec3 normal = unknown160.getNormal(0);
  mm::Vec3 direction = end - start;
  direction.unknown001();
  if (normal.x * direction.x + normal.y * direction.y + normal.z * direction.z < 0.0f) {
    hitPosition = position;
    return true;
  }
  return false;
}

void PlayerCamera::resetBattleWarp() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknown110 = target->unknown20.unknown00;
    unknown100 = unknown110;
    unknown51a0 = unknown100;
  }
}

} // namespace gf

#include "gf/camera/gf_camera_utilities.cpp"
