#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"

namespace ml {

class DrMemHandleAllocator : public mm::mtl::IAllocator {
public:
  ~DrMemHandleAllocator() override {}
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;

  mtl::ALLOC_HANDLE m_ALLOC_HANDLE; // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(DrMemHandleAllocator, m_ALLOC_HANDLE) == 0x08, "");

} // namespace ml
