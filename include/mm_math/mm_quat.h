#pragma once
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

struct alignas(16) Quat {
  static const Quat zero;     // Name from the game symbol _ZN2mm4Quat4zeroE; also in torna and xc1de.
  static const Quat identity; // Name from the game symbol _ZN2mm4Quat8identityE; also in torna and xc1de.
  bool isValid() const;
  bool isZero() const;
  bool isNormalized() const;
  Vec3 rotate(const Vec3 &vector) const;
  static Quat mul(const Quat &qa, const Quat &qb);
  static void inverse(Quat &qa);
  // Inferred role: sets the rotation about the y axis of half the angle; original name unknown. Evidence: the same four stores in the order y, w, x, z are in
  // gf::GfComBehaviorMob::moveToGoal (0x710052cc40), gf::AIAgentField::procMsgPcFieldHighJump, procMsgPcFieldNotifyWaterWarp and procMsgPcFieldNotifyWaterWarpBuddy,
  // gf_pc_state_field_big_jump.cpp (unknown50 and target) and gf_field_exec_cmd_turn.cpp (rotation and half).
  void unknown001(f32 half) {
    y = sinf(half);
    w = cosf(half);
    x = 0.0f;
    z = 0.0f;
  }

  f32 x;
  f32 y;
  f32 z;
  f32 w;
};

inline bool Quat::isValid() const { return isValidFloat(x) && isValidFloat(y) && isValidFloat(z) && isValidFloat(w); }

inline bool Quat::isZero() const { return fabsf(zero.x - x) <= 0.000001f && fabsf(zero.y - y) <= 0.000001f && fabsf(zero.z - z) <= 0.000001f && fabsf(zero.w - w) <= 0.000001f; }

inline bool Quat::isNormalized() const { return fabsf(x * x + y * y + z * z + w * w - 1.0f) < 0.000001f; }

inline Vec3 Quat::rotate(const Vec3 &vector) const {
  f32 tx = y * vector.z - z * vector.y + w * vector.x;
  f32 ty = z * vector.x - vector.z * x + vector.y * w;
  f32 tz = vector.y * x - y * vector.x + vector.z * w;
  f32 tw = -vector.x * x - y * vector.y - vector.z * z;
  Vec3 result;
  result.x = -(z * ty) + y * tz - x * tw + w * tx;
  result.y = -(x * tz) + z * tx - y * tw + w * ty;
  result.z = -(y * tx) + x * ty - z * tw + w * tz;
  return result;
}

__attribute__((always_inline)) inline Quat Quat::mul(const Quat &qa, const Quat &qb) {
  if (!qa.isValid()) {
    MMStdBase::mmPrint("qa[%f %f %f %f]\n", qa.x, qa.y, qa.z, qa.w);
  }

  if (!qb.isValid()) {
    MMStdBase::mmPrint("qb[%f %f %f %f]\n", qb.x, qb.y, qb.z, qb.w);
  }

  Quat result;
  result.x = qb.y * qa.z - qb.z * qa.y + qa.x * qb.w + qb.x * qa.w;
  result.y = qb.z * qa.x - qb.x * qa.z + qa.y * qb.w + qb.y * qa.w;
  result.z = qb.x * qa.y - qb.y * qa.x + qa.z * qb.w + qb.z * qa.w;
  result.w = qb.w * qa.w - qb.x * qa.x - qb.y * qa.y - qb.z * qa.z;
  return result;
}

// Defined in mm_math.h, which includes this header.
inline f32 acos(f32 r);

// Internal linkage: the game inlines it into the single caller of each unit only (an external linkage function with
// this body is over the -O3 inline threshold: always_inline would be needed).
// Name from the shape (interpolation of two normalized quaternions along the shortest arc); original name unknown.
static inline Quat slerp(const Quat &qs, const Quat &qe, f32 t) {
  // __LINE__ must be 0x57f and 0x580 as in the original header: they are the line arguments of the asserts.
#line 1407
  MM_ASSERT(qs.isNormalized());
  MM_ASSERT(qe.isNormalized());
  Quat end = qe;
  f32 cosine = qs.x * end.x + qs.y * end.y + qs.z * end.z + qs.w * end.w;
  if (cosine < 0.0f) {
    end.x = -end.x;
    end.y = -end.y;
    end.z = -end.z;
    end.w = -end.w;
    cosine = -cosine;
  }
  if (cosine > 1.0f) {
    cosine = 1.0f;
  }
  f32 angle = mm::acos(cosine);
  if (fabsf(angle) < 0.000001f) {
    return end;
  }
  f32 inverseSine = 1.0f / sinf(angle);
  f32 startWeight = sinf((1.0f - t) * angle) * inverseSine;
  f32 endWeight = inverseSine * sinf(t * angle);
  end.x = qs.x * startWeight + end.x * endWeight;
  end.y = qs.y * startWeight + end.y * endWeight;
  end.z = qs.z * startWeight + end.z * endWeight;
  end.w = qs.w * startWeight + end.w * endWeight;
  return end;
}

// Inferred helper: quaternion of Euler angles, the products of the sines and cosines of the half angles (the three half angles are computed before
// the first sinf call); original name unknown. Evidence: the same statements are inlined in event::CharaEvaPlayer::update (0x71000c98c4),
// fw::FootPlacementIKSolver::setGroundAngle, gf::npc::StateWalk::seqWaitMoveEnd and, stored into a quaternion of the caller,
// gf::GfRelSmnEnemy::validatePopPos (0x710038ae80). Not the helper of gf_camera_utilities.h (w with the sines first) nor unknown009 below
// (the sign of the second product differs).
// Internal linkage: as a member function (external linkage) or with always_inline, CharaEvaPlayer::update loads its 0.5 constant into another register.
static inline void unknown005(Quat &quat, const Vec3 &rotation) {
  f32 halfX = rotation.x * 0.5f;
  f32 halfY = rotation.y * 0.5f;
  f32 halfZ = rotation.z * 0.5f;
  f32 sinX = sinf(halfX);
  f32 cosX = cosf(halfX);
  f32 sinY = sinf(halfY);
  f32 cosY = cosf(halfY);
  f32 sinZ = sinf(halfZ);
  f32 cosZ = cosf(halfZ);
  quat.x = sinX * cosY * cosZ - cosX * sinY * sinZ;
  quat.y = cosX * sinY * cosZ + sinX * cosY * sinZ;
  quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
  quat.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

static inline Quat unknown005(const Vec3 &rotation) {
  Quat quat;
  unknown005(quat, rotation);
  return quat;
}

// Inferred helper: quaternion of Euler angles, each half angle multiplied inside its sinf and cosf call (x and w sums, y and z differences); original
// name unknown. Evidence: the same statements are inlined in event::CharaSetRot::update (1.0.0: 0x71000cbb54), gf::GfGameUtil::setTransformPreEnemy (0x710034f47c)
// and both SCOM_OBJ_WARP_POS::create overloads that take a rotation (0x71005c2308, 0x71005c253c); the three of them match through it. Not mm::unknown005
// (the sign of the second product differs) nor the helper of gf_camera_utilities.h.
// The rotation is a copy and the result goes through a reference: with a const reference setTransformPreEnemy reloads the components after each sinf call (94
// instructions against the game's 93), and with a returned Quat it schedules the w product after the stores of x and y.
static inline void unknown009(Quat &quat, Vec3 rotation) {
  f32 sinX = sinf(rotation.x * 0.5f);
  f32 cosX = cosf(rotation.x * 0.5f);
  f32 sinY = sinf(rotation.y * 0.5f);
  f32 cosY = cosf(rotation.y * 0.5f);
  f32 sinZ = sinf(rotation.z * 0.5f);
  f32 cosZ = cosf(rotation.z * 0.5f);
  quat.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
  quat.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
  quat.z = cosX * cosY * sinZ - sinX * sinY * cosZ;
  quat.w = cosX * cosY * cosZ + sinX * sinY * sinZ;
}

// Inferred helper: rotates a vector in place by a quaternion, each component stored before the next one is computed; original name unknown. Same statements as
// Quat::rotate (`v = q.rotate(v)` stores the three components at the end). Six functions inline these statements, each matching through the helper: gf::GfMenuBladeCreateCamera::updateLookAt
// (0x71003fe114: with `target = quat.rotate(target)` the function has the game's 210 instructions but adds `position` first in the x and y sums, where the game has the rotated
// component first), gf::GfMenuModelViewCamera::updateLookAt (0x71003e6914, the same recipe), gf::ChainAttackCamera::updateParam (0x71001d3ce8: 237 instructions against the game's
// 260 with `v = q.rotate(v)`; the quaternion and the vector are references there, so the game reloads the quaternion after each store), mm::Aabb::transform(const Quat &)
// (0x71006fc700, loop body, 112 instructions), gf::FusionComboCamera::getYaw(const Quat &) (0x71001d60e0, the negated unit axis rotated in place, 63 instructions) and
// gf::PlayerCamera::reset (0x71001dd84c, the negated unit axis, with the quaternion copied into a local first).
// The statements are also written out in gf::GfComSound::flush (0x710057edc0: through the helper 194 instructions but 22 differing lines, the rotated offset goes into a result declared
// before the temporaries) and in two functions of anm::TransformUtil (anmlib is reserved, left as it is).
// Internal linkage: like unknown005, so that no out-of-line copy exists.
static inline void unknown010(const Quat &quat, Vec3 &vector) {
  f32 tx = quat.y * vector.z - quat.z * vector.y + quat.w * vector.x;
  f32 ty = quat.z * vector.x - vector.z * quat.x + vector.y * quat.w;
  f32 tz = vector.y * quat.x - quat.y * vector.x + vector.z * quat.w;
  f32 tw = -vector.x * quat.x - quat.y * vector.y - vector.z * quat.z;
  vector.x = -(quat.z * ty) + quat.y * tz - quat.x * tw + quat.w * tx;
  vector.y = -(quat.x * tz) + quat.z * tx - quat.y * tw + quat.w * ty;
  vector.z = -(quat.y * tx) + quat.x * ty - quat.z * tw + quat.w * tz;
}

// Inferred helper: rotates a vector by a quaternion into a result that is declared before the quaternion and the vector are read, each component stored by the last three statements; original
// name unknown. Same statements as Quat::rotate, but `result = q.rotate(v)` and the in-place unknown010 give other operand orders where the result is a member or a field of a packet:
// gf::GfComBehaviorPc::warpWall (0x7100567750: the search direction of the horizontal packet, 259 instructions; Quat::rotate gives 56 differing lines, unknown010 on a copy of the
// axis 16, the vector loaded before the quaternion component of its first product) and fw::Transform::invert (0x710017e174, the negated translation into the result, 120 instructions; the
// same two forms give 86 differing lines). Used by: warpWall, Transform::invert.
// The body repeats the one of unknown010 on purpose: unknown010 written as `unknown011(quat, vector, vector)` breaks five functions that match through it (a helper is simplified before it is
// inlined: ChainAttackCamera::updateParam, GfMenuModelViewCamera::updateLookAt, GfMenuBladeCreateCamera::updateLookAt, Aabb::transform(const Quat &), GfMoveRunControler::update), and
// unknown011 written as a copy plus unknown010 gives warpWall's 16 differing lines.
// Internal linkage: like unknown010.
static inline void unknown011(const Quat &quat, const Vec3 &vector, Vec3 &result) {
  f32 tx = quat.y * vector.z - quat.z * vector.y + quat.w * vector.x;
  f32 ty = quat.z * vector.x - vector.z * quat.x + vector.y * quat.w;
  f32 tz = vector.y * quat.x - quat.y * vector.x + vector.z * quat.w;
  f32 tw = -vector.x * quat.x - quat.y * vector.y - vector.z * quat.z;
  result.x = -(quat.z * ty) + quat.y * tz - quat.x * tw + quat.w * tx;
  result.y = -(quat.x * tz) + quat.z * tx - quat.y * tw + quat.w * ty;
  result.z = -(quat.y * tx) + quat.x * ty - quat.z * tw + quat.w * tz;
}

} // namespace mm
