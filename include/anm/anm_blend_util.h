#pragma once
#include <stddef.h>

#include "anm/anm_array-inl.h"
#include "types.h"

namespace anm {

class ExtraTruckSlot;
class Skeleton;
struct QsTransform;

struct BlendSrc {
  u32 unknown00;                // Inferred role: bone count; original member name unknown.
  const QsTransform *unknown08; // Inferred role: poses; original member name unknown.
  const f32 *unknown10;         // Inferred role: bone weights; original member name unknown.
  f32 unknown18;                // Inferred role: weight; original member name unknown.
};

struct BlendNormalDst {
  QsTransform *unknown00; // Inferred role: weighted poses; original member name unknown.
  f32 *unknown08;         // Inferred role: weight sums; original member name unknown.
};

struct NormalizeSrc {
  u32 unknown00;                // Inferred role: bone count; original member name unknown.
  const QsTransform *unknown08; // Inferred role: reference poses; original member name unknown.
  const f32 *unknown10;         // Inferred role: weight sums; original member name unknown.
};

struct NormalizeMSSrc {
  const Skeleton *unknown00; // Inferred role: p skeleton; original member name unknown.
  const f32 *unknown08;      // Inferred role: weight sums; original member name unknown.
};

struct BlendExtraTruckSrc {
  u32 unknown00;               // Inferred role: truck count; original member name unknown.
  const f32 *unknown08;        // Inferred role: truck values; original member name unknown.
  const Array<s16> *unknown10; // Inferred role: truck index table; original member name unknown.
  f32 unknown18;               // Inferred role: weight; original member name unknown.
};

struct BlendNormalExtraTruckDst {
  f32 *unknown00; // Inferred role: weighted sums; original member name unknown.
  f32 *unknown08; // Inferred role: weight sums; original member name unknown.
};

struct BlendAddExtraTruckDst {
  f32 *unknown00; // Inferred role: weighted sums; original member name unknown.
};

struct NormalizeExtraTruckSrc {
  u32 unknown00;               // Inferred role: truck count; original member name unknown.
  const Array<f32> *unknown08; // Inferred role: reference values; original member name unknown.
  const f32 *unknown10;        // Inferred role: weight sums; original member name unknown.
  const ExtraTruckSlot *pSlot;
};

static_assert(offsetof(BlendExtraTruckSrc, unknown10) == 0x10, "");
static_assert(offsetof(BlendExtraTruckSrc, unknown18) == 0x18, "");
static_assert(offsetof(NormalizeExtraTruckSrc, pSlot) == 0x18, "");

class BlendUtil {
public:
  static void blendNormal(const BlendSrc &src, BlendNormalDst *dst);
  static void normalizePose(const NormalizeSrc &src, QsTransform *poses);
  static void normalizePoseMS(const NormalizeMSSrc &src, QsTransform *poses);
  static void blendNormalExtraTruck(const BlendExtraTruckSrc &src, BlendNormalExtraTruckDst *dst);
  static void blendAddExtraTruck(const BlendExtraTruckSrc &src, BlendAddExtraTruckDst *dst);
  static void normalizeExtraTruck(const NormalizeExtraTruckSrc &src, f32 *values);
};

} // namespace anm
