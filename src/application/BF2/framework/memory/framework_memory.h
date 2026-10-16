#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace fw {

class FrameworkMemory {
public:
  static mtl::ALLOC_HANDLE getMem(u32 section);
  static mm::mtl::IAllocator *getAllocator(u32 section);
};

} // namespace fw

void *operator new(size_t size, mm::mtl::IAllocator *allocator, int alignment, const char *file, size_t line);
