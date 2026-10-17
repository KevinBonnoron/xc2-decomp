#pragma once
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace fw {

class EffectPack : public mm::mtl::ReferenceObject {
public:
  static EffectPack *createFromMemory(void *data, u32 size, const char *name, bool isCopy);
};

} // namespace fw
