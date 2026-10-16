#pragma once
#include <stddef.h>

namespace mtl {
class ALLOC_HANDLE;

class MemManager {
public:
  static void *allocate(ALLOC_HANDLE handle, size_t size, size_t alignment, bool isBack, const char *name, int line);
  static void deallocate(void *pointer, size_t size, bool isBack);
};

} // namespace mtl
