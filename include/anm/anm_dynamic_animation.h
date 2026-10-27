#pragma once
#include <stddef.h>

#include "anm/anm_animation.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace anm {

class DynamicAnimation : public Animation {
public:
  ~DynamicAnimation() override {
    mm::mtl::IAllocator *allocator = m_pAllocator;
    for (u32 i = 0; i < unknown50.size(); i++) {
      allocator->deallocate(unknown50[i]);
    }
  }
  s32 getImplType() const override;
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  bool getExtractMotion(f32 time, QsTransform *transform) const override;
  bool getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const override;

  const Animation *unknown48;        // Inferred role: p animation the calls are forwarded to; original member name unknown.
  mm::mtl::Vector<void *> unknown50; // Inferred role: allocations released with the allocator; original member name unknown.
};

static_assert(offsetof(DynamicAnimation, unknown48) == 0x48, "");
static_assert(offsetof(DynamicAnimation, unknown50) == 0x50, "");
static_assert(sizeof(DynamicAnimation) == 0x78, "");

} // namespace anm
