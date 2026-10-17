#include "anm/anm_empty_animation.h"

namespace anm {
struct SerialiseArg;

EmptyAnimation::EmptyAnimation(const SerialiseArg &arg) : Animation(arg) {}

void EmptyAnimation::sampleTrucks(f32 time, const Binding &binding, QsTransform *transforms) const {}

s32 EmptyAnimation::getImplType() const { return 2; }

} // namespace anm
