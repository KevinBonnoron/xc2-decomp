#pragma once
#include <stddef.h>

namespace gf {

class GfAllocator;

enum ALLOCATOR {
  ALLOCATOR_SYSTEM = 1,
};

GfAllocator *getAllocator(ALLOCATOR allocator);

} // namespace gf

void *operator new(size_t size, gf::GfAllocator *allocator, const char *file, size_t line, int alignment);
