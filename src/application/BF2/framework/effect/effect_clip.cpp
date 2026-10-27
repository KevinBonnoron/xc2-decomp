#include "framework/effect/effect_clip.h"

namespace fw {

EffectResData::EffectResData(mm::mtl::IAllocator *allocator) : unknown10(allocator) {}

void EffectResData::term() { unknown10.clear(); }

} // namespace fw
