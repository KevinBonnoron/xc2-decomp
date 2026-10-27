#pragma once
#include <stddef.h>

#include "anm/anm_animation.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Skeleton;
class Binding;

class ReferencePoseAnimation : public Animation {
public:
  ReferencePoseAnimation(const Skeleton *skeleton, mm::mtl::IAllocator *pAllocator);
  ~ReferencePoseAnimation() override;
  Binding *createBinding();
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  s32 getImplType() const override;

  const Skeleton *unknown48; // Inferred role: p skeleton; original member name unknown.
};

static_assert(offsetof(ReferencePoseAnimation, unknown48) == 0x48, "");
static_assert(sizeof(ReferencePoseAnimation) == 0x50, "");

} // namespace anm
