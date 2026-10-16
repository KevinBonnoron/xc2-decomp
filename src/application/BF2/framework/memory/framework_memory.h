#pragma once
#include "mtl/alloc_handle.h"
#include "types.h"

namespace fw {

class FrameworkMemory {
public:
  static mtl::ALLOC_HANDLE getMem(u32 section);
};

} // namespace fw
