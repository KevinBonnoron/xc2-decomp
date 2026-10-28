#pragma once
#include <stddef.h>

#include "anm/anm_animation.h"
#include "anm/anm_array-inl.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {
struct SerialiseArg;
struct Cubic4Curve;

// Cubic polynomial pieces: the start time, then for each axis the cubic, quadratic, linear and constant terms.
struct Cubic3Curve {
  f32 unknown00;
  f32 unknown04[12];
};

static_assert(sizeof(Cubic3Curve) == 0x34, "");

// Orders a time against the start of a cubic piece; shared with the extra truck curves.
struct CmpCubic {
  template <typename Curve> bool operator()(f32 time, const Curve &curve) const { return time < curve.unknown00; }
};

void calcVec3(const Array<Cubic3Curve> &curves, f32 time, f32 *pOut);

// Inferred per-bone curve set of CubicAnimation; original name unknown.
struct unknown004 {
  Array<Cubic3Curve> unknown00; // Inferred role: translation curves; original member name unknown.
  Array<Cubic4Curve> unknown10; // Inferred role: rotation curves; original member name unknown.
  Array<Cubic3Curve> unknown20; // Inferred role: scale curves; original member name unknown.
};

static_assert(sizeof(unknown004) == 0x30, "");

class CubicAnimation : public Animation {
public:
  explicit CubicAnimation(mm::mtl::IAllocator *pAllocator);
  explicit CubicAnimation(const SerialiseArg &arg);
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;

  Array<unknown004> unknown48; // Inferred role: bone curves; original member name unknown.
};

static_assert(offsetof(CubicAnimation, unknown48) == 0x48, "");

} // namespace anm
