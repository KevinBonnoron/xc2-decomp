#pragma once
#include "mm/mm_std_base.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {

inline bool isValidFloat(f32 value) {
  u32 bits = *reinterpret_cast<u32 *>(&value);
  return bits != 0xcccccccc && (bits & 0x7f800000) != 0x7f800000;
}

struct alignas(16) Quat {
  static const Quat zero;
  static const Quat identity;

  bool isValid() const;
  Vec3 rotate(const Vec3 &vector) const;
  static Quat mul(const Quat &qa, const Quat &qb);

  f32 x;
  f32 y;
  f32 z;
  f32 w;
};

inline bool Quat::isValid() const { return isValidFloat(x) && isValidFloat(y) && isValidFloat(z) && isValidFloat(w); }

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

} // namespace mm
