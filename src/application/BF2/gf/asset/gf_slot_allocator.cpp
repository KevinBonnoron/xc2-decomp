#include "gf/asset/gf_slot_allocator.h"

#include "gf/gf_allocator.h"

namespace gf {

constexpr u32 SIZE_ALLOC_BLOCK_SIZE = 0x2000;

GfSlotAllocator::GfSlotAllocator() : parent(nullptr), buffer(nullptr), useDebugMemory(true) {}

GfSlotAllocator::~GfSlotAllocator() { destroy(); }

void GfSlotAllocator::destroy() {
  if (buffer != nullptr) {
    parent->deallocate(buffer);
    buffer = nullptr;
  }
  sizeAlloc.destroy();
  parent = nullptr;
}

size_t GfSlotAllocator::getBlockSize() const { return sizeAlloc.blockSize; }

void GfSlotAllocator::setupSizeAlloc(const char *name, mm::mtl::IAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) {
  this->name = name;
  parent = allocator;
  this->useDebugMemory = useDebugMemory;
  buffer = parent->allocate(size, alignment);
  if (buffer != nullptr) {
    sizeAlloc.setup(getAllocator(ALLOCATOR_DEFAULT), SIZE_ALLOC_BLOCK_SIZE, buffer, size);
  }
}

void GfSlotAllocator::setup(const char *name, GfSlotAllocator *allocator, size_t size, size_t alignment, bool useDebugMemory) {
  setupSizeAlloc(name, allocator, size, alignment, useDebugMemory);
}

void GfSlotAllocator::resize(size_t size) { sizeAlloc.resize(size); }

void *GfSlotAllocator::allocate(size_t size, size_t alignment) {
  void *pointer = sizeAlloc.alloc(size, false);
  if (pointer == nullptr) {
    if (useDebugMemory) {
      return getAllocator(ALLOCATOR_DEBUG)->allocate(size, alignment);
    }
    pointer = nullptr;
  }
  return pointer;
}

void GfSlotAllocator::deallocate(void *pointer) {
  if (!sizeAlloc.free(pointer) && useDebugMemory) {
    getAllocator(ALLOCATOR_DEBUG)->deallocate(pointer);
  }
}

bool GfSlotAllocator::empty() const { return sizeAlloc.buffer == nullptr; }

u32 GfSlotAllocator::getAllocs() const { return sizeAlloc.allocs; }

void *GfSlotAllocator::getBuffer() { return sizeAlloc.buffer; }

size_t GfSlotAllocator::getBufferSize() const { return sizeAlloc.bufferSize; }

const char *GfSlotAllocator::getName() const { return name.c_str(); }

} // namespace gf
