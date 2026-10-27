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
struct Cubic3Curve;
struct Cubic4Curve;

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
