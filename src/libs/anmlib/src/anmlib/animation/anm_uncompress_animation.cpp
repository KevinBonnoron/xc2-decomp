#include "anm/anm_uncompress_animation.h"

namespace anm {
struct SerialiseArg;

UncompressAnimation::UncompressAnimation(mm::mtl::IAllocator *pAllocator) : Animation(pAllocator) {}

UncompressAnimation::UncompressAnimation(const SerialiseArg &arg) : Animation(arg), unknown48(arg) {}

s32 UncompressAnimation::getImplType() const { return 0; }

} // namespace anm
