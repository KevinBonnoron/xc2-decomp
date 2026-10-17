#include "anm/anm_uncompress_animation.h"

namespace anm {
struct SerialiseArg;

UncompressAnimation::UncompressAnimation(const SerialiseArg &arg) : Animation(arg) {}

s32 UncompressAnimation::getImplType() const { return 0; }

} // namespace anm
