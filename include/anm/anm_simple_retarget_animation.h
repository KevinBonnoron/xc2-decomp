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
class SimpleMapper;

class SimpleRetargetAnimation : public Animation {
public:
  SimpleRetargetAnimation(const Binding *pOriginal, const SimpleMapper *pMapper, mm::mtl::IAllocator *pAllocator);
  ~SimpleRetargetAnimation() override;
  Binding *createBinding();
  s32 getImplType() const override;
  void sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const override;
  bool getExtractMotion(f32 time, QsTransform *transform) const override;
  bool getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const override;

  const SimpleMapper *m_pMapper;
  const Binding *m_pOriginal;
  mm::mtl::FixStr<64> unknown58; // Inferred role: animation name; original member name unknown.
  void *unknowna0;               // Inferred role: allocation released with the allocator; original member name unknown.
};

static_assert(offsetof(SimpleRetargetAnimation, m_pMapper) == 0x48, "");
static_assert(offsetof(SimpleRetargetAnimation, m_pOriginal) == 0x50, "");
static_assert(offsetof(SimpleRetargetAnimation, unknown58) == 0x58, "");
static_assert(offsetof(SimpleRetargetAnimation, unknowna0) == 0xa0, "");
static_assert(sizeof(SimpleRetargetAnimation) == 0xa8, "");

} // namespace anm
