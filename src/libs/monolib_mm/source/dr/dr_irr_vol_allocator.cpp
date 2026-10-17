#include "dr/dr_irr_vol_allocator.h"

#include "mtl/mem_manager.h"

namespace ml {
namespace irrvol {

MemHandlebaseAllocator::MemHandlebaseAllocator() {}

MemHandlebaseAllocator::MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle) : m_handle(handle) {}

void MemHandlebaseAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { m_handle = handle; }

mtl::ALLOC_HANDLE MemHandlebaseAllocator::getMemHandle() const { return m_handle; }

void *MemHandlebaseAllocator::allocate(size_t size, size_t alignment) {
  return mtl::MemManager::allocate(m_handle, size, alignment, false, "no name", 0);
}

void MemHandlebaseAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

} // namespace irrvol
} // namespace ml
