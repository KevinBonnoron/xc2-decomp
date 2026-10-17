#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace mtl {

enum AllocatorType {
  ALLOCATOR_TYPE_PROGRAM = 1,
  ALLOCATOR_TYPE_RESOURCE = 2,
};

class MemManager {
public:
  static ALLOC_HANDLE create(void *buffer, size_t size, const char *name, bool);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, const char *file = "no name", int line = 0);
  static ALLOC_HANDLE create(ALLOC_HANDLE parent, size_t size, const char *name, bool, AllocatorType type, size_t alignment,
                             const char *file = "no name", int line = 0);
  static void erase(ALLOC_HANDLE handle);
  static mm::mtl::IAllocator *getAllocator(const ALLOC_HANDLE &handle);
  static void *allocate(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void deallocate(void *pointer, size_t size, bool isBack);
  static void *reallocate(void *pointer, size_t size, bool isBack);
  static size_t maxAllocSize(ALLOC_HANDLE handle);
  static bool isArea(ALLOC_HANDLE handle, const void *pointer);
  static u64 getTopAdr(const ALLOC_HANDLE &handle);
  static size_t getTotalSize(ALLOC_HANDLE handle);
};

} // namespace mtl
