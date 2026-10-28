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
template void mm::mtl::Vector<fw::EffectAnnotationData>::expand(size_t, size_t);
template void mm::mtl::Vector<fw::EffectAnnotationData>::push_back(const fw::EffectAnnotationData &);
