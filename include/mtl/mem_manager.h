#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"

namespace mtl {

enum AllocatorType {
  ALLOCATOR_TYPE_PROGRAM = 1,
  ALLOCATOR_TYPE_RESOURCE = 2,
};

class MemManager {
public:
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, AllocatorType type, size_t alignment,
                             const char *file = "no name", int line = 0);
  static void erase(ALLOC_HANDLE handle);
  static void *allocate(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void deallocate(void *pointer, size_t size, bool isBack);
};

} // namespace mtl
