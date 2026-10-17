#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"

namespace layer {

class LayerMemHandleAllocator : public mm::mtl::IAllocator {
public:
  LayerMemHandleAllocator();
  LayerMemHandleAllocator(mtl::ALLOC_HANDLE handle);
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  mtl::ALLOC_HANDLE getMemHandle() const;
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;

  mtl::ALLOC_HANDLE m_handle;
};

static_assert(offsetof(LayerMemHandleAllocator, m_handle) == 0x08, "");

} // namespace layer
