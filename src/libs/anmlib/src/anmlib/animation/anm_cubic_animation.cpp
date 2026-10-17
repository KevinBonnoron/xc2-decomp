#include "anm/anm_cubic_animation.h"

namespace anm {
struct SerialiseArg;

CubicAnimation::CubicAnimation(const SerialiseArg &arg) : Animation(arg) {}

s32 CubicAnimation::getImplType() const { return 1; }

} // namespace anm
