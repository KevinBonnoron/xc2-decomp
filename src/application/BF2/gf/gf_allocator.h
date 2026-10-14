#pragma once
#include "mtl/alloc_handle.h"
#include <stddef.h>

namespace gf {

class GfAllocator {
public:
  mtl::ALLOC_HANDLE getMemHandle() const;
};

enum ALLOCATOR {
  ALLOCATOR_SYSTEM = 1,
  ALLOCATOR_BDAT = 4,
};

GfAllocator *getAllocator(ALLOCATOR allocator);

} // namespace gf

void *operator new(size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment);
