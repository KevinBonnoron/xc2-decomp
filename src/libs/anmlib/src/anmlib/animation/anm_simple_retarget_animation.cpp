#include "anm/anm_simple_retarget_animation.h"

#include "anm/anm_array-inl.h"
#include "anm/anm_binding.h"
#include "anm/anm_reference_object.h"
#include "anm/anm_simple_mapper.h"
#include "anm/anm_skeleton.h"
#include "mm/mm_std_base.h"
#include "mm_mtl/allocator.h"

namespace anm {

SimpleRetargetAnimation::SimpleRetargetAnimation(const Binding *pOriginal, const SimpleMapper *pMapper, mm::mtl::IAllocator *pAllocator)
    : Animation(pAllocator), m_pMapper(pMapper), m_pOriginal(pOriginal), unknowna0(nullptr) {
  MM_ASSERT(m_pMapper->m_pSkeletonA->getBoneCount() == m_pOriginal->m_indexTable.size());
  m_pMapper->addRef();
  m_pOriginal->addRef();
  unknown58 = m_pOriginal->m_pAnimation->unknown18;
  unknown58 += "_simple_map";
  const Animation *original = pOriginal->m_pAnimation;
  unknown18 = unknown58.c_str();
  unknown21 = original->unknown21;
  unknown20 = -3;
  unknown22 = original->unknown22;
  unknown23 = original->unknown23;
  unknown24 = original->unknown24;
  unknown28 = original->unknown28;
  unknown2c = original->unknown2c;
  const void *annotations = original->unknown30;
  u32 annotationNum = original->unknown38;
  unknown30 = annotations;
  unknown38 = annotationNum;
}

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
