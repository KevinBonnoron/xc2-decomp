#pragma once
#include <stddef.h>

#include "mm_mtl/allocator.h"
#include "mtl/alloc_handle.h"

namespace layer {

class LayerHandleAllocator : public mm::mtl::IAllocator {
public:
  LayerHandleAllocator();
  LayerHandleAllocator(mtl::ALLOC_HANDLE handle);
  void setMemHandle(mtl::ALLOC_HANDLE handle);
  mtl::ALLOC_HANDLE getMemHandle() const;
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;

  mtl::ALLOC_HANDLE m_memHandle; // Inferred role: handle; named after the game accessor layer::LayerHandleAllocator::getMemHandle.
};

static_assert(offsetof(LayerHandleAllocator, m_memHandle) == 0x08, "");

} // namespace layer
