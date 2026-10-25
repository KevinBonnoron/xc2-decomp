#include "dr/dr_irr_vol_allocator.h"

#include "mtl/mem_manager.h"

namespace ml {
namespace irrvol {

float frac(float value) { return value - static_cast<int>(value); }

MemHandlebaseAllocator::MemHandlebaseAllocator() {}

MemHandlebaseAllocator::MemHandlebaseAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void MemHandlebaseAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE MemHandlebaseAllocator::getMemHandle() const { return unknown08; }

void *MemHandlebaseAllocator::allocate(size_t size, size_t alignment) { return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0); }

void MemHandlebaseAllocator::deallocate(void *pointer) {
  if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

} // namespace irrvol
} // namespace ml
