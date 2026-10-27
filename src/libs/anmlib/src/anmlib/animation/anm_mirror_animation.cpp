#include "anm/anm_mirror_animation.h"

#include "anm/anm_binding.h"
#include "anm/anm_mirror_mapper.h"
#include "anm/anm_qs_transform.h"
#include "anm/anm_reference_object.h"

namespace anm {

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
