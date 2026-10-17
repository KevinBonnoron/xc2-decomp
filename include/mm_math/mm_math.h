#pragma once
#include "math.h"
#include "mm/mm_std_base.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

const f32 DEG_TO_RAD = 0.017453292f;
const f32 RAD_TO_DEG = 57.29578f;

template <typename T> T clamp(T value, T mi, T ma) {
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

__attribute__((always_inline)) inline Vec3 quatToEuler(const Quat &quat) {
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
  f32 m00 = 1.0f - (yy + zz);
  f32 m01 = xy + wz;
  f32 m02 = xz - wy;
  f32 m11 = 1.0f - (xx + zz);
  f32 m20 = xz + wy;
  f32 m22 = 1.0f - (xx + yy);
  f32 r = yz - wx;
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
      euler.z = atan2f(m01, m11);
      euler.y = atan2f(m20, m22);
    } else {
      euler.y = 0.0f;
      euler.z = -atan2f(m02, m00);
    }
  } else {
    euler.y = 0.0f;
    euler.z = atan2f(m02, m00);
  }
  return euler;
}

} // namespace mm
