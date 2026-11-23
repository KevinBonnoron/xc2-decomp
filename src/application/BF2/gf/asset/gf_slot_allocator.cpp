#include "gf/asset/gf_slot_allocator.h"

#include "gf/gf_allocator.h"

namespace gf {

constexpr u32 SIZE_UNKNOWN_8192 = 0x2000; // Inferred role: size alloc block size; original name unknown.

GfSlotAllocator::GfSlotAllocator() : unknown08(nullptr), unknown10(nullptr), unknown2ec(true) {}

GfSlotAllocator::~GfSlotAllocator() { destroy(); }

void GfSlotAllocator::destroy() {
  if (unknown10 != nullptr) {
    unknown08->deallocate(unknown10);
    unknown10 = nullptr;
  }
  m_sizeAlloc.destroy();
  unknown08 = nullptr;
}

size_t GfSlotAllocator::getBlockSize() const { return m_sizeAlloc.m_blockSize; }

void GfSlotAllocator::setupSizeAlloc(const char *name, mm::mtl::IAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) {
  this->m_name = name;
  unknown08 = allocator;
  this->unknown2ec = useDebugMemory;
  unknown10 = unknown08->allocate(size, alignment);
  if (unknown10 != nullptr) {
    m_sizeAlloc.setup(getAllocator(ALLOCATOR_UNKNOWN_0), SIZE_UNKNOWN_8192, unknown10, size);
  }
}

void GfSlotAllocator::setup(const char *name, GfSlotAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) { setupSizeAlloc(name, allocator, size, alignment, useDebugMemory); }

void GfSlotAllocator::resize(size_t size) { m_sizeAlloc.resize(size); }

void *GfSlotAllocator::allocate(size_t size, size_t alignment) {
  void *pointer = m_sizeAlloc.alloc(size, false);
  if (pointer == nullptr) {
    if (unknown2ec) {
      return getAllocator(ALLOCATOR_UNKNOWN_10)->allocate(size, alignment);
    }
    pointer = nullptr;
  }
  return pointer;
}

void GfSlotAllocator::deallocate(void *pointer) {
  if (!m_sizeAlloc.free(pointer) && unknown2ec) {
    getAllocator(ALLOCATOR_UNKNOWN_10)->deallocate(pointer);
  }
}

bool GfSlotAllocator::empty() const { return m_sizeAlloc.m_buffer == nullptr; }

u32 GfSlotAllocator::getAllocs() const { return m_sizeAlloc.m_allocs; }

void *GfSlotAllocator::getBuffer() { return m_sizeAlloc.m_buffer; }

size_t GfSlotAllocator::getBufferSize() const { return m_sizeAlloc.m_bufferSize; }

const char *GfSlotAllocator::getName() const { return m_name.c_str(); }

} // namespace gf
