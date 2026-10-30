#pragma once
#include <math.h>

#include "mm/mm_std_base.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

const f32 DEG_TO_RAD = 0.017453292f;
const f32 RAD_TO_DEG = 180.0f / 3.1415927f;

template <typename T> T clamp(T value, T mi, T ma) {
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

inline f32 clamp(const f32 &value, const f32 &mi, const f32 &ma) {
  MM_ASSERT(mi <= ma);
  if (value < mi) {
    return mi;
  }

  return value > ma ? ma : value;
}

template <typename T> const T &min(const T &a, const T &b) { return a < b ? a : b; }

template <typename T> const T &max(const T &a, const T &b) { return a < b ? b : a; }

template <typename T> void clampRef(T &value, const T &mi, const T &ma) {
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

__attribute__((always_inline)) inline Vec3 matrixToEuler(const Mat44 &matrix) {
  f32 r = matrix.rows[2][1];
  // __LINE__ must be 581 as in the original header: it is the line argument of the assert.
#line 581
  MM_ASSERT(mm::fabs(r) < 1.001f);
  Vec3 euler;
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
      euler.y = 0.0f;
      euler.z = -atan2f(matrix.rows[0][2], matrix.rows[0][0]);
    }
  } else {
    euler.y = 0.0f;
    euler.z = atan2f(matrix.rows[0][2], matrix.rows[0][0]);
  }
  return euler;
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

__attribute__((always_inline)) inline Vec3 quatToEuler(const Quat &quat) {
  Mat44 matrix;
  quatToMatrix(matrix, quat);
  return matrixToEuler(matrix);
}

} // namespace mm
