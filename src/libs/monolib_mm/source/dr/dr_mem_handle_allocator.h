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

  mtl::ALLOC_HANDLE unknown08; // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(DrMemHandleAllocator, unknown08) == 0x08, "");

} // namespace ml
