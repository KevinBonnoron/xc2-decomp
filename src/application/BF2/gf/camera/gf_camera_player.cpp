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
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_option.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "ml/dev_graph.h"
#include "ml/scn_cam_util.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {

class GfObj;

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

// Inferred helper: position of the camera on the player target in the frame of the camera, at the default distance and the look height above the camera height; original name unknown.
// The game repeats it inline in resetClimb(), reset() and resetLoad() (1.0.0: 0x71001dc168, 0x71001dd84c, 0x71001ddbb0; no call). Evidence for the forms, measured against the game:
// - `cameraHeight` places the load of camera_height before the load of look_height (0x71001dc1bc: ldp of distance_default and camera_height, then ldr of look_height); with the
//   subtraction written out the order is look_height, camera_height and the ldp pairs the other two (5 differing lines).
// - `+ 0.0f` is the fadd of distance_default with zero (0x71001dc1cc).
// The helper returns the vector and the callers keep `pitchPosition` and `forward`: a helper that also calls getPitch ends its locals before the last call of resetClimb() and
// reset(), which then becomes a tail call (159 instructions against the game's 153 and 212 against 206; resetLoad() matches either way).
static mm::Vec3 unknown003(PlayerCamera *camera) {
  const PlayerCamera::unknown002 *param = static_cast<const PlayerCamera::unknown002 *>(camera->m_paramAdapter.unknown00->param);
  f32 cameraHeight = param->camera_height;
  return mm::Vec3(0.0f, param->look_height - cameraHeight, param->distance_default + 0.0f);
}

// Inferred helper: sets the position of the player target and the previous one, and clears the flag of the changed target, before the tracked position; original name unknown. The game
// repeats these stores inline in resetClimb(), reset() and resetLoad() (1.0.0: 0x71001dc168, 0x71001dd84c, 0x71001ddbb0); resetBattleWarp() (0x71001dde34) has the same without the flag.
static void unknown004(PlayerCamera *camera, PlayerCameraTarget *target) {
  camera->unknown110 = target->m_transform.unknown00;
  camera->unknown100 = camera->unknown110;
  camera->unknown5190 = false;
  camera->unknown51a0 = camera->unknown100;
}

// The camera position of resetClimb(), reset() and resetLoad() is the product of unitZ * unknownd0 rotated by the yaw quaternion, stored in unknown5180 and then added to unknown100
// (1.0.0: 0x71001dc364 is the first of the three final fadd of resetClimb(), with the sum in the game's operand order). Measured on resetClimb(): the sum in one expression
// (`unknown5180 = rotation.rotate(...) + unknown100`) gives 17 differing lines, the sum through the member as written here matches. A helper for the three statements keeps the 153
// instructions but swaps the operands of the three final fadd (3 differing lines; with the sum in one expression 17), because a helper is simplified before it is inlined. Ruling 8: the
// block stays written out in resetClimb(), reset() and resetLoad(), the call form being the measured one above.
void PlayerCamera::resetClimb() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    unknownb8 = m_saveYaw = getYaw(target->unknown60, mm::Vec3::unitZ);
    mm::Vec3 pitchPosition = unknown003(this);
    mm::Vec3 forward = mm::Vec3::unitZ;
    unknownc8 = getPitch(pitchPosition, forward);
    unknownd0 = m_saveDistance;
    unknownc0 = 0.0f;
    m_savePitch = 0.0f;
    unknownd8 = m_saveHeight;
    unknown004(this, target);
    unknown121 = false;
    unknown122 = false;
    mm::Quat rotation = unknown169(0.0f, unknownb8, 0.0f);
    unknown5180 = rotation.rotate(mm::Vec3::unitZ * unknownd0);
    unknown5180 += unknown100;
    GfDataUtil::setCameraYaw(m_saveYaw);
    GfDataUtil::setCameraPitch(m_savePitch);
  }
}

void PlayerCamera::setTarget(GF_OBJ_HANDLE *target) {
  if (target != unknown020) {
    GfObjAcc acc(target);
    if (acc.getType() != OBJECT_TYPE_ENEMY) {
      return;
    }
  }
  if (m_GF_OBJ_HANDLE != target) {
    if (m_GF_OBJ_HANDLE == unknown020) {
      if (PlayerCameraTarget::get() == nullptr) {
        return;
      }
    } else {
      unknown5190 = true;
    }
    m_GF_OBJ_HANDLE = target;
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

// Forms of reset() (1.0.0: 0x71001dd84c, 206 instructions), each measured against the game:
// - `targetRotation`: the game copies the unit axis (0x71001dd884) before it loads the rotation of the target (0x71001dd8a0); with `mm::unknown010(target->m_transform.unknown10, direction)`
//   the nine products and sums that use the quaternion come out with their operands swapped (9 differing lines, same size). A copy of the quaternion in a local places its loads there.
// - the block holds `direction` and `reference`: their slots are the ones that `forward` (sp+0) and `pitchPosition` (sp+0x10) use afterwards (0x71001dd954 `mov x2, sp`, 0x71001dd950
//   `add x1, sp, #0x10`), and the game's frame is 0x60 bytes. Without the block the frame is 0x80 (19 differing lines, same instruction count), ruling 3.
// The rest is as resetClimb(), see there.
void PlayerCamera::reset() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    {
      mm::Vec3 direction;
      mm::Vec3 reference = mm::Vec3::unitZ;
      direction = mm::Vec3(-reference.x, -reference.y, -reference.z);
      const mm::Quat targetRotation = target->m_transform.unknown10;
      mm::unknown010(targetRotation, direction);
      unknownb8 = m_saveYaw = getYaw(direction, reference);
    }
    mm::Vec3 pitchPosition = unknown003(this);
    mm::Vec3 forward = mm::Vec3::unitZ;
    unknownc8 = getPitch(pitchPosition, forward);
    unknownd0 = m_saveDistance;
    unknownc0 = 0.0f;
    m_savePitch = 0.0f;
    unknownd8 = m_saveHeight;
    unknown004(this, target);
    m_manual = false;
    unknown121 = false;
    unknown122 = false;
    mm::Quat rotation = unknown169(0.0f, unknownb8, 0.0f);
    unknown5180 = rotation.rotate(mm::Vec3::unitZ * unknownd0);
    unknown5180 += unknown100;
    GfDataUtil::setCameraYaw(m_saveYaw);
    GfDataUtil::setCameraPitch(m_savePitch);
  }
}

void PlayerCamera::resetClimb(ResetCameraWallTiming timing) {
  unknown124 = true;
  unknown52c4 = timing;
  unknownf0 = timing == RESET_CAMERA_WALL_TIMING_UNKNOWN_0 ? 0.6666667f : 0.23333335f;
}

// Forms of resetLoad() (1.0.0: 0x71001ddbb0, 161 instructions): the game reads the parameter record (0x71001ddbe0-0x71001ddbec, kept in x22) before the call of getCameraYaw
// (0x71001ddbf4), which is what the single-use `side` local places (ruling 2). With `m_paramAdapter.get<unknown002>()->side_distance[m_saveSide]` in the use the function has 158
// instructions and a frame of 0x60 bytes against 0x70 (38 differing lines). The rest is as resetClimb().
void PlayerCamera::resetLoad() {
  PlayerCameraTarget *target = PlayerCameraTarget::get();
  if (target != nullptr) {
    const unknown002 *side = m_paramAdapter.get<unknown002>();
    unknownb8 = m_saveYaw = GfDataUtil::getCameraYaw();
    mm::Vec3 pitchPosition = unknown003(this);
    mm::Vec3 forward = mm::Vec3::unitZ;
    unknownc8 = getPitch(pitchPosition, forward);
    unknownc0 = m_savePitch = GfDataUtil::getCameraPitch();
    unknownd0 = m_saveDistance = GfDataUtil::getPlayerCameraDistance();
    unknownd8 = m_saveHeight = GfDataUtil::getCameraHeight();
    m_saveSide = GfDataUtil::getCameraSide();
    unknowne0 = unknowne4 = side->side_distance[m_saveSide];
    unknown004(this, target);
    m_manual = GfDataUtil::isCameraFreeMode();
    unknown121 = false;
    unknown122 = false;
    mm::Quat rotation = unknown169(0.0f, unknownb8, 0.0f);
    unknown5180 = rotation.rotate(mm::Vec3::unitZ * unknownd0);
    unknown5180 += unknown100;
  }
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
    unknown110 = target->m_transform.unknown00;
    unknown100 = unknown110;
    unknown51a0 = unknown100;
  }
}

void PlayerCamera::updateTarget(const fw::Transform &transform, bool param2) {
  unknown122 = false;
  if (!param2 && m_manual) {
    return;
  }
  if (m_GF_OBJ_HANDLE == unknown020) {
    return;
  }
  if (!PlayerCameraTarget::get()->unknown45) {
    return;
  }
  GfObj *obj = GfObjUtil::getObj(m_GF_OBJ_HANDLE);
  if (obj == nullptr) {
    return;
  }
  GfObjAcc acc(obj);
  if (acc.getType() != OBJECT_TYPE_ENEMY) {
    return;
  }
  const unknown002 *param = m_paramAdapter.get<unknown002>();
  const unknown002 *base = static_cast<const unknown002 *>(m_paramAdapter.unknown00->param);
  f32 height = ((unknownd0 - base->distance_minimum) / (base->distance_maximum - base->distance_minimum)) * base->height_max;
  mm::Vec3 look = acc.getWorldTransform().unknown00;
  if (param->look_bone == 0) {
    look.y = look.y + fminf(height + param->look_height + unknownd8, 2.0f);
  } else {
    CameraUtilities::getCameraLookBonePosition(m_GF_OBJ_HANDLE, look);
  }
  // The game adds look_height and unknownd8 to the height before it loads the position of the target (the two fadd at 0x71001dafa8, before the loads at 0x71001dafb4): the local
  // places that sum first; written inline in the y component (as one sum or as a chain of subtractions) the order of the fadd and the loads differs (measured).
  f32 offset = height + param->look_height + unknownd8;
  mm::Vec3 position(look.x - transform.unknown00.x, look.y - transform.unknown00.y - offset, look.z - transform.unknown00.z);
  mm::Vec3 forward = mm::Vec3::unitZ;
  m_saveYaw = getYaw(mm::Vec3(-position.x, -position.y, -position.z), forward);
  m_savePitch = getPitch(position, forward);
  // The game reads the pitch limits through m_paramAdapter again here (the calls on `this` above force the reload) and computes both products before it loads unknownc8: with the
  // subtraction in the initialisers the load comes between the two products (measured, same size, different order).
  f32 lower = static_cast<const unknown002 *>(m_paramAdapter.unknown00->param)->pitch_limit_lower * -mm::DEG_TO_RAD;
  f32 upper = static_cast<const unknown002 *>(m_paramAdapter.unknown00->param)->pitch_limit_upper * mm::DEG_TO_RAD;
  lower -= unknownc8;
  upper -= unknownc8;
  mm::clampRef(m_savePitch, lower, upper);
  mm::Vec3 screen;
  if (!ml::ScnCamUtil::getScreenPos(screen, unknown20, look)) {
    unknownec = param->rotate_revise_at_reset;
  } else {
    f32 centerX = ml::DevGraph::getRootWidth() * 0.5f;
    s32 rootHeight = ml::DevGraph::getRootHeight();
    // Locals placing member loads and calls (rulings of 2026-11-13): the game calls getRootHeight right after getRootWidth, loads the three target range members before the
    // first sqrt (0x71001db0e0) and computes both distances before it tests them; each of these written at its use gives another order (measured).
    f32 rangeOffsetY = param->target_range_offset_y;
    f32 rangeHeight = param->target_range_height;
    f32 rangeWidth = param->target_range_width * 0.5f;
    f32 lookDistance = sqrtf((look.x - unknown40.x) * (look.x - unknown40.x) + (look.z - unknown40.z) * (look.z - unknown40.z));
    f32 transformDistance = sqrtf((transform.unknown00.x - unknown40.x) * (transform.unknown00.x - unknown40.x) + (transform.unknown00.z - unknown40.z) * (transform.unknown00.z - unknown40.z));
    f32 left = centerX - rangeWidth;
    if (lookDistance - 1.0f <= transformDistance) {
      screen.x = 0.0f;
    }
    unknownec = 0.0f;
    f32 rate = 0.0f;
    if (left > screen.x) {
      f32 diff = left - screen.x;
      if (diff != 0.0f) {
        rate = diff / rangeWidth;
      }
    } else {
      f32 right = centerX + rangeWidth;
      if (right < screen.x) {
        f32 diff = screen.x - right;
        if (diff != 0.0f) {
          rate = diff / rangeWidth;
        }
      } else {
        f32 center = rangeOffsetY + rootHeight * 0.5f;
        f32 half = rangeHeight * 0.5f;
        f32 top = center - half;
        if (top > screen.y) {
          f32 diff = top - screen.y;
          if (diff != 0.0f) {
            rate = diff / half;
          }
        } else {
          f32 bottom = center + half;
          if (bottom < screen.y) {
            f32 diff = screen.y - bottom;
            if (diff != 0.0f) {
              rate = diff / half;
            }
          }
        }
      }
    }
    u32 index = GfDataManager::getDataOption()->unknown04[4];
    if (unknown52d7 <= index) {
      index = 0;
    }
    unknownec = rate * unknown52d8[index].unknown10;
  }
  unknown122 = true;
}

} // namespace gf

// The game builds the target and the sub view cameras between the player camera and the camera utilities, in one contiguous range with no other unit
// between (PlayerCamera 0x71001d7360 to 0x71001def8c, PlayerCameraTarget 0x71001dfd14 to 0x71001e0344, SubViewCamera 0x71001e03c8 to 0x71001e0518,
// CameraUtilities 0x71001e0574 to 0x71001e0d24). CameraPadData (0x71001defd0 to 0x71001df48c) sits in the same range but cannot join: with it ~PlayerCamera
// inlines a destructor the game calls (21 instructions against 18).
#include "gf/camera/gf_camera_player_target.cpp"
#include "gf/camera/gf_camera_subview.cpp"

#include "gf/camera/gf_camera_utilities.cpp"
