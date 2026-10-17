#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"

namespace ml {

class DevFileDicAllocator {
public:
  DevFileDicAllocator(mtl::ALLOC_HANDLE mem);
  void setMemHandle(mtl::ALLOC_HANDLE mem);
  void *allocate(size_t size, size_t alignment);
  void deallocate(void *pointer);
  void *reallocate(void *pointer, size_t size);

  mtl::ALLOC_HANDLE m_mem;
};

} // namespace ml
