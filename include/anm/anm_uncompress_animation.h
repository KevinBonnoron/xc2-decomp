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

class UncompressAnimation : public Animation {
public:
  explicit UncompressAnimation(mm::mtl::IAllocator *pAllocator);
  explicit UncompressAnimation(const SerialiseArg &arg);
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;

  Array<f32> unknown48; // Inferred role: uncompressed bone values; original member name unknown.
};

static_assert(offsetof(UncompressAnimation, unknown48) == 0x48, "");

} // namespace anm
