#pragma once
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md).
const f32 DEG_TO_RAD = 0.017453292f;
// Inferred name; kept as an exception to the unknown-name rule (AGENTS.md).
const f32 RAD_TO_DEG = 180.0f / 3.1415927f;

template <typename T> T clamp(T value, T mi, T ma) {
  // __LINE__ must be 819 as in the original header: it is the line argument of the assert.
#line 819
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

inline f32 clamp(const f32 &value, const f32 &mi, const f32 &ma) {
  // __LINE__ must be 819 as in the original header: it is the line argument of the assert.
#line 819
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

template <typename T> const T &min(const T &a, const T &b) { return a < b ? a : b; }

template <typename T> const T &max(const T &a, const T &b) { return a < b ? b : a; }

template <typename T> void clampRef(T &value, const T &mi, const T &ma) {
  // __LINE__ must be 801 as in the original header: it is the line argument of the assert.
#line 801
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    value = mi;
  } else if (value > ma) {
    value = ma;
  }
}

inline f32 fabs(f32 value) { return fabsf(value); }

inline f32 acos(f32 r) {
  // __LINE__ must be 546 as in the original header: it is the line argument of the assert.
#line 546
  MM_ASSERT(mm::fabs(r) < 1.001f);
  if (mm::fabs(r) >= 1.0f) {
    return r > 0.0f ? 0.0f : 3.1415927f;
  }
  return acosf(r);
}

inline f32 asin(f32 r) {
  // __LINE__ must be 581 as in the original header: it is the line argument of the assert.
#line 581
  MM_ASSERT(mm::fabs(r) < 1.001f);
  if (mm::fabs(r) >= 1.0f) {
    return r > 0.0f ? 1.5707964f : -1.5707964f;
  }
  return asinf(r);
}

__attribute__((always_inline)) inline void matrixToEuler(const Mat44 &matrix, Vec3 &euler) {
  f32 r = matrix.rows[2][1];
  // __LINE__ must be 581 as in the original header: it is the line argument of the assert.
#line 581
  MM_ASSERT(mm::fabs(r) < 1.001f);
  if (mm::fabs(r) >= 1.0f) {
    euler.x = -r > 0.0f ? 1.5707964f : -1.5707964f;
  } else {
    euler.x = asinf(-r);
  }
  if (euler.x < 1.5707964f) {
    if (euler.x > -1.5707964f) {
      euler.z = atan2f(matrix.rows[0][1], matrix.rows[1][1]);
      euler.y = atan2f(matrix.rows[2][0], matrix.rows[2][2]);
    } else {
      euler.z = -atan2f(matrix.rows[0][2], matrix.rows[0][0]);
      euler.y = 0.0f;
    }
  } else {
    euler.z = atan2f(matrix.rows[0][2], matrix.rows[0][0]);
    euler.y = 0.0f;
  }
}

__attribute__((always_inline)) inline Vec3 matrixToEuler(const Mat44 &matrix) {
  Vec3 euler;
  matrixToEuler(matrix, euler);
  return euler;
}

// Inferred helper: Euler angles of the rotation of a matrix, with the sign convention opposite to Mat44::setRotXYZ
// (the caller negates them); original name unknown. Evidence: inlined in gf::GfObjSetup::setInitialTransform and
// in the XFRM chunk of gmk::TGmkList::createGmk.
__attribute__((always_inline)) inline void unknown002(const Mat44 &matrix, Vec3 &euler) {
  euler.y = mm::asin(matrix.rows[0][2]);
  if (euler.y < 1.5707964f) {
    if (euler.y > -1.5707964f) {
      euler.z = atan2f(-matrix.rows[0][1], matrix.rows[0][0]);
      euler.x = atan2f(-matrix.rows[1][2], matrix.rows[2][2]);
    } else {
      euler.z = -atan2f(-matrix.rows[1][0], matrix.rows[2][0]);
      euler.x = 0.0f;
    }
  } else {
    euler.z = atan2f(matrix.rows[1][0], -matrix.rows[2][0]);
    euler.x = 0.0f;
  }
}

__attribute__((always_inline)) inline void quatToMatrix(Mat44 &matrix, const Quat &quat) {
  f32 x2 = quat.x + quat.x;
  f32 y2 = quat.y + quat.y;
  f32 z2 = quat.z + quat.z;
  f32 xx = quat.x * x2;
  f32 xy = quat.x * y2;
  f32 xz = quat.x * z2;
  f32 yy = quat.y * y2;
  f32 yz = quat.y * z2;
  f32 zz = quat.z * z2;
  f32 wx = x2 * quat.w;
  f32 wy = y2 * quat.w;
  f32 wz = quat.w * z2;
  matrix.rows[0][0] = 1.0f - (yy + zz);
  matrix.rows[0][1] = xy + wz;
  matrix.rows[0][2] = xz - wy;
  matrix.rows[1][0] = xy - wz;
  matrix.rows[1][1] = 1.0f - (xx + zz);
  matrix.rows[1][2] = yz + wx;
  matrix.rows[2][0] = xz + wy;
  matrix.rows[2][1] = yz - wx;
  matrix.rows[2][2] = 1.0f - (xx + yy);
}

// Inferred helper: the matrix of a quaternion as an affine matrix without translation; original name unknown.
// Evidence: anm::TransformUtil::calcMatrix (1.0.0: 0x710096310c).
inline void unknown001(Mat44 &matrix, const Quat &quat) {
  quatToMatrix(matrix, quat);
  matrix.rows[0][3] = 0.0f;
  matrix.rows[1][3] = 0.0f;
  matrix.rows[2][3] = 0.0f;
  matrix.rows[3][0] = 0.0f;
  matrix.rows[3][1] = 0.0f;
  matrix.rows[3][2] = 0.0f;
  matrix.rows[3][3] = 1.0f;
}

// Inferred helper: quaternion of the rotation of a matrix; original name unknown. Evidence: inlined in fw::PrimCapsule::setup
// (1.0.0: 0x7100197934), whose stack holds the four values and the pointers to the four components below the quaternion of
// the caller, and in gf::GfFieldLodColiAnim::PosInfo::syncGfTransform (0x71002e2728).
// Internal linkage: the game inlines it into the single caller of each unit.
static inline void unknown004(Quat &rotation, const Mat44 &matrix) {
  f32 values[4];
  values[0] = ((matrix.rows[0][0] - matrix.rows[1][1]) - matrix.rows[2][2]) + 1.0f;
  values[1] = ((matrix.rows[1][1] - matrix.rows[0][0]) - matrix.rows[2][2]) + 1.0f;
  values[2] = (-matrix.rows[0][0] - matrix.rows[1][1]) + matrix.rows[2][2] + 1.0f;
  values[3] = matrix.rows[0][0] + matrix.rows[1][1] + matrix.rows[2][2] + 1.0f;
  u32 largest = 0;
  if (values[1] > values[0]) {
    largest = 1;
  }
  if (values[2] > values[largest]) {
    largest = 2;
  }
  if (values[3] > values[largest]) {
    largest = 3;
  }
  if (values[largest] < 0.0f) {
    rotation = mm::Quat::identity;
  } else {
    f32 *components[4] = {&rotation.x, &rotation.y, &rotation.z, &rotation.w};
    f32 root = sqrtf(values[largest]);
    *components[largest] = root * 0.5f;
    f32 scale = 0.25f / (root * 0.5f);
    switch (largest) {
    case 3:
      rotation.x = scale * (matrix.rows[1][2] - matrix.rows[2][1]);
      rotation.y = scale * (matrix.rows[2][0] - matrix.rows[0][2]);
      rotation.z = scale * (matrix.rows[0][1] - matrix.rows[1][0]);
      break;
    case 1:
      rotation.x = scale * (matrix.rows[0][1] + matrix.rows[1][0]);
      rotation.z = scale * (matrix.rows[1][2] + matrix.rows[2][1]);
      rotation.w = scale * (matrix.rows[2][0] - matrix.rows[0][2]);
      break;
    case 2:
      rotation.x = scale * (matrix.rows[2][0] + matrix.rows[0][2]);
      rotation.y = scale * (matrix.rows[1][2] + matrix.rows[2][1]);
      rotation.w = scale * (matrix.rows[0][1] - matrix.rows[1][0]);
      break;
    default:
      rotation.y = scale * (matrix.rows[0][1] + matrix.rows[1][0]);
      rotation.z = scale * (matrix.rows[2][0] + matrix.rows[0][2]);
      rotation.w = scale * (matrix.rows[1][2] - matrix.rows[2][1]);
      break;
    }
  }
}

__attribute__((always_inline)) inline void quatToEuler(const Quat &quat, Vec3 &euler) {
  Mat44 matrix;
  quatToMatrix(matrix, quat);
  matrixToEuler(matrix, euler);
}

__attribute__((always_inline)) inline Vec3 quatToEuler(const Quat &quat) {
  Vec3 euler;
  quatToEuler(quat, euler);
  return euler;
}

inline bool isFinite(f32 r) { return isValidFloat(r); }

// Inferred helper: wraps an angle in radians into [-pi, pi]; original name unknown.
// Evidence: inlined in gf::GfFieldLookIk::isCondMatched, with the assertion "mm::isFinite(r)" of mm_math.h line 1014.
inline f32 unknown003(f32 r) {
  // __LINE__ must be 1014 as in the original header: it is the line argument of the assert.
#line 1014
  MM_ASSERT(mm::isFinite(r));
  if (fabsf(r) > 6.2831855f) {
    r = r - static_cast<int>(r / 6.2831855f) * 6.2831855f;
  }
  if (r > 3.1415927f) {
    r = r - 6.2831855f;
  } else if (r < -3.1415927f) {
    r = r + 6.2831855f;
  }
  return r;
}

} // namespace mm
