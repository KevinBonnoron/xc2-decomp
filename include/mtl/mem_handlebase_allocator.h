#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"

namespace mtl {

class MemHandlebaseAllocator : public mm::mtl::IAllocator {
public:
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;
  const char *getName() const override;

  ALLOC_HANDLE unknown08; // Inferred role: handle of the region the allocator serves; original member name unknown.
};

static_assert(sizeof(MemHandlebaseAllocator) == 0x10, "");

} // namespace mtl
