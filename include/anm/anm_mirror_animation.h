#pragma once
#include <stddef.h>

#include "anm/anm_animation.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace anm {

class Binding;
class MirrorMapper;

class MirrorAnimation : public Animation {
public:
  MirrorAnimation(const Binding *pOriginal, const MirrorMapper *pMapper, mm::mtl::IAllocator *pAllocator);
  ~MirrorAnimation() override;
  Binding *createBinding();
  s32 getImplType() const override;
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  bool getExtractMotion(f32 time, QsTransform *transform) const override;
  bool getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const override;

  const MirrorMapper *unknown48; // Inferred role: p mirror mapper; original member name unknown.
  const Binding *unknown50;      // Inferred role: p binding of the mirrored animation; original member name unknown.
  mm::mtl::FixStr<64> unknown58; // Inferred role: animation name; original member name unknown.
};

static_assert(offsetof(MirrorAnimation, unknown48) == 0x48, "");
static_assert(offsetof(MirrorAnimation, unknown50) == 0x50, "");
static_assert(offsetof(MirrorAnimation, unknown58) == 0x58, "");
static_assert(sizeof(MirrorAnimation) == 0xa0, "");

} // namespace anm
