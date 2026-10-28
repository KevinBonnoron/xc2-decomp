#include "anm/anm_mirror_animation.h"

#include "anm/anm_binding.h"
#include "anm/anm_mirror_mapper.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"

namespace anm {

MirrorAnimation::MirrorAnimation(const Binding *pOriginal, const MirrorMapper *pMapper, mm::mtl::IAllocator *pAllocator) : Animation(pAllocator), unknown48(pMapper), unknown50(pOriginal) {
  unknown48->addRef();
  unknown50->addRef();
  unknown58 = unknown50->m_pAnimation->unknown18;
  unknown58 += "_mirror";
  const Animation *original = pOriginal->m_pAnimation;
  unknown18 = unknown58.c_str();
  unknown21 = original->unknown21;
  unknown20 = -1;
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

MirrorAnimation::~MirrorAnimation() {
  unknown001(unknown48);
  unknown001(unknown50);
}

s32 MirrorAnimation::getImplType() const { return unknown50->m_pAnimation->getImplType(); }

bool MirrorAnimation::getExtractMotion(f32 time, QsTransform *transform) const {
  QsTransform source;
  if (unknown50->m_pAnimation->getExtractMotion(time, &source)) {
    unknown48->mirrorExtractMotion(source, transform);
    return true;
  }
  return false;
}

bool MirrorAnimation::getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const {
  QsTransform source;
  if (unknown50->m_pAnimation->getDeltaExtractMotion(previousTime, time, looped, &source)) {
    unknown48->mirrorExtractMotion(source, transform);
    return true;
  }
  return false;
}

} // namespace anm
