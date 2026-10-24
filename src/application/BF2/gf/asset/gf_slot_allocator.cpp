#include "gf/asset/gf_slot_allocator.h"

#include "gf/gf_allocator.h"

namespace gf {

constexpr u32 SIZE_ALLOC_BLOCK_SIZE = 0x2000;

GfSlotAllocator::GfSlotAllocator() : unknown08(nullptr), unknown10(nullptr), unknown2ec(true) {}

GfSlotAllocator::~GfSlotAllocator() { destroy(); }

void GfSlotAllocator::destroy() {
  if (unknown10 != nullptr) {
    unknown08->deallocate(unknown10);
    unknown10 = nullptr;
  }
  unknown18.destroy();
  unknown08 = nullptr;
}

size_t GfSlotAllocator::getBlockSize() const { return unknown18.unknown28; }

void GfSlotAllocator::setupSizeAlloc(const char *name, mm::mtl::IAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) {
  this->m_name = name;
  unknown08 = allocator;
  this->unknown2ec = useDebugMemory;
  unknown10 = unknown08->allocate(size, alignment);
  if (unknown10 != nullptr) {
    unknown18.setup(getAllocator(ALLOCATOR_DEFAULT), SIZE_ALLOC_BLOCK_SIZE, unknown10, size);
  }
}

void GfSlotAllocator::setup(const char *name, GfSlotAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) { setupSizeAlloc(name, allocator, size, alignment, useDebugMemory); }

void GfSlotAllocator::resize(size_t size) { unknown18.resize(size); }

void *GfSlotAllocator::allocate(size_t size, size_t alignment) {
  void *pointer = unknown18.alloc(size, false);
  if (pointer == nullptr) {
    if (unknown2ec) {
      return getAllocator(ALLOCATOR_DEBUG)->allocate(size, alignment);
    }
    pointer = nullptr;
  }
  return pointer;
}

void GfSlotAllocator::deallocate(void *pointer) {
  if (!unknown18.free(pointer) && unknown2ec) {
    getAllocator(ALLOCATOR_DEBUG)->deallocate(pointer);
  }
}

bool GfSlotAllocator::empty() const { return unknown18.unknown08 == nullptr; }

u32 GfSlotAllocator::getAllocs() const { return unknown18.unknown20; }

void *GfSlotAllocator::getBuffer() { return unknown18.unknown08; }

size_t GfSlotAllocator::getBufferSize() const { return unknown18.unknown10; }

const char *GfSlotAllocator::getName() const { return m_name.c_str(); }

} // namespace gf
