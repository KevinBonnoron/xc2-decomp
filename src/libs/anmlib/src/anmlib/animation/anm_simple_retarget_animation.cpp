#include "anm/anm_simple_retarget_animation.h"

#include "anm/anm_binding.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_simple_mapper.h"
#include "mm_mtl/allocator.h"

namespace anm {

SimpleRetargetAnimation::~SimpleRetargetAnimation() {
  unknown001(m_pMapper);
  unknown001(m_pOriginal);
  if (m_pAllocator != nullptr && unknowna0 != nullptr) {
    m_pAllocator->deallocate(unknowna0);
  }
}

s32 SimpleRetargetAnimation::getImplType() const { return m_pOriginal->m_pAnimation->getImplType(); }

void SimpleRetargetAnimation::sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const { m_pOriginal->m_pAnimation->sampleTrucks(time, binding, transforms); }

bool SimpleRetargetAnimation::getExtractMotion(f32 time, QsTransform *transform) const { return m_pOriginal->m_pAnimation->getExtractMotion(time, transform); }

bool SimpleRetargetAnimation::getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const {
  return m_pOriginal->m_pAnimation->getDeltaExtractMotion(previousTime, time, looped, transform);
}

} // namespace anm
