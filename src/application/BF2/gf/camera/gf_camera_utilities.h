#pragma once
#include <math.h>

#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace fw {
struct ColiCheckConfig;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;

class CameraUtilities {
public:
  static void getCameraLookBonePosition(GF_OBJ_HANDLE *handle, mm::Vec3 &position);
  static bool getRotateAxis(const mm::Vec3 &from, const mm::Vec3 &to, mm::Vec3 &axis);
  static bool updateCollision(const fw::ColiCheckConfig &config, mm::Vec3 &position, const mm::Vec3 &target, const f32 &fov, const f32 &collisionSize);
};

// Inferred role: quaternion of the Euler angles (half-angle products); original name unknown. Evidence: inlined in
// gf::GimmickCamera::updateParams (1.0.0: 0x71001e2598), gf::GimmickCamera::setLookLock,
// gf::ScriptCameraEntity::ScriptCameraEntity (0x71001e5960) and gf::ScriptCameraEntity::update (0x71001e5c68).
// Not mm::unknown005 (mm_quat.h, shared by fw::FootPlacementIKSolver, gf::npc::StateWalk and event::CharaEvaPlayer): here w is sin * sin * sin +
// cos * cos * cos (operand order of the fadd at 0x71001e264c); with cos * cos * cos + sin * sin * sin the three camera functions stop matching,
// while ik_foot_placement_solver.cpp, gf_npc_state_walk.cpp and chara_eva_player.cpp need that other order.
// Internal linkage: with external linkage (plain inline) one fmul has its operands swapped in GimmickCamera::updateParams
// (0x71001e2658) and ScriptCameraEntity::update (0x71001e5e00).
static inline mm::Quat unknown169(f32 pitch, f32 yaw, f32 roll) {
  f32 halfX = pitch * 0.5f;
  f32 halfY = yaw * 0.5f;
  f32 halfZ = roll * 0.5f;
  f32 sinX = sinf(halfX);
  f32 cosX = cosf(halfX);
  f32 sinY = sinf(halfY);
  f32 cosY = cosf(halfY);
  f32 sinZ = sinf(halfZ);
  f32 cosZ = cosf(halfZ);
  mm::Quat quat;
  quat.x = sinX * cosY * cosZ - cosX * sinY * sinZ;
  quat.y = cosX * sinY * cosZ + sinX * cosY * sinZ;
  quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
  quat.w = sinX * sinY * sinZ + cosX * cosY * cosZ;
  return quat;
}

// Inferred role: direction of a camera rotation, the unitZ rotated by the quaternion of the Euler angles; original name unknown.
// Evidence and linkage: see unknown169.
static inline mm::Vec3 unknown171(f32 pitch, f32 yaw, f32 roll) {
  mm::Quat quat = unknown169(pitch, yaw, roll);
  return quat.rotate(mm::Vec3::unitZ);
}

} // namespace gf
