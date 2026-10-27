#include "anm/anm_dynamic_animation.h"

namespace anm {

s32 DynamicAnimation::getImplType() const { return unknown48->getImplType(); }

void DynamicAnimation::sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const { unknown48->sampleTrucks(time, binding, transforms); }

bool DynamicAnimation::getExtractMotion(f32 time, QsTransform *transform) const { return unknown48->getExtractMotion(time, transform); }

bool DynamicAnimation::getDeltaExtractMotion(f32 previousTime, f32 time, bool looped, QsTransform *transform) const { return unknown48->getDeltaExtractMotion(previousTime, time, looped, transform); }

} // namespace anm
