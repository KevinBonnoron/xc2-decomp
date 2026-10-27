#include "framework/effect/effect_clip.h"

#include "framework/memory/framework_memory.h"

namespace fw {

EffectResData::EffectResData(mm::mtl::IAllocator *allocator) : unknown10(allocator) {}

EffectResData::~EffectResData() {}

EffectResData *EffectResData::createEffectResData(const SetupInfo &info) {
#line 63
  EffectResData *data = new (info.unknown00, 0x10, __FILE__, __LINE__) EffectResData(info.unknown00);
  if (data != nullptr) {
    data->init(info);
    data->addRef();
  }

  return data;
}

void EffectResData::term() { unknown10.clear(); }

} // namespace fw
