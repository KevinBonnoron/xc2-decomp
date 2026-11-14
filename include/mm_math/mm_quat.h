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

} // namespace mm
