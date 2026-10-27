#include "anm/anm_cubic_animation.h"

namespace anm {
struct SerialiseArg;

CubicAnimation::CubicAnimation(mm::mtl::IAllocator *pAllocator) : Animation(pAllocator) {}

CubicAnimation::CubicAnimation(const SerialiseArg &arg) : Animation(arg), unknown48(arg) {}

s32 CubicAnimation::getImplType() const { return 1; }

} // namespace anm
