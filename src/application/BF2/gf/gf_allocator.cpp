#include "gf/gf_allocator.h"

#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_slot_mapping.h"
#include "mtl/mem_manager.h"

namespace gf {

constexpr size_t SLOT_ALLOCATE_MIN = 0x20000;

GfAllocator::GfAllocator() {}

GfAllocator::GfAllocator(mtl::ALLOC_HANDLE handle) : unknown08(handle) {}

void GfAllocator::setMemHandle(mtl::ALLOC_HANDLE handle) { unknown08 = handle; }

mtl::ALLOC_HANDLE GfAllocator::getMemHandle() const { return unknown08; }

void *GfAllocator::allocate(size_t size, size_t alignment) {
  if (getAllocator(ALLOCATOR_UNKNOWN0B) == this) {
    GfSlotMapping *mapping = GfAssetManager::getSlotMapping();
    if (size > SLOT_ALLOCATE_MIN && mapping != nullptr) {
      void *pointer = mapping->allocateSize(size, alignment);
      if (pointer != nullptr) {
        return pointer;
      }
    }
    void *pointer = getAllocator(ALLOCATOR_DEFAULT)->allocate(size, alignment);
    if (pointer != nullptr) {
      return pointer;
    }
  }
  return mtl::MemManager::allocate(unknown08, size, alignment, false, "no name", 0);
}

void *GfAllocator::allocateProgLarge(size_t size, size_t alignment) {
  if (getAllocator(ALLOCATOR_UNKNOWN0B) != this) {
    return nullptr;
  }
  GfSlotMapping *mapping = GfAssetManager::getSlotMapping();
  if (size > SLOT_ALLOCATE_MIN && mapping != nullptr) {
    void *pointer = mapping->allocateSize(size, alignment);
    if (pointer != nullptr) {
      return pointer;
    }
  }
  return getAllocator(ALLOCATOR_DEFAULT)->allocate(size, alignment);
}

void GfAllocator::deallocate(void *pointer) {
  GfSlotMapping *mapping = nullptr;
  if (getAllocator(ALLOCATOR_UNKNOWN0B) == this) {
    mapping = GfAssetManager::getSlotMapping();
  }
  if (mapping != nullptr) {
    bool isSlot = mapping->deallocateSize(pointer);
    if (pointer != nullptr && !isSlot) {
      mtl::MemManager::deallocate(pointer, 0, false);
    }
  } else if (pointer != nullptr) {
    mtl::MemManager::deallocate(pointer, 0, false);
  }
}

bool GfAllocator::deallocateProgLarge(void *pointer) {
  if (getAllocator(ALLOCATOR_UNKNOWN0B) == this) {
    GfSlotMapping *mapping = GfAssetManager::getSlotMapping();
    if (mapping != nullptr && mapping->deallocateSize(pointer)) {
      return true;
    }
  }
  return false;
}

const char *GfAllocator::getName() const { return unknown0c.c_str(); }

GfAllocatorManager::GfAllocatorManager() : unknown08(false) {}

GfAllocatorManager::~GfAllocatorManager() {}

void GfAllocatorManager::initialize(const GfSetupParam &) { unknown08 = true; }

void GfAllocatorManager::finalize() { unknown08 = false; }

GfAllocator *GfAllocatorManager::getAllocator(ALLOCATOR allocator) { return &get()->unknown10[allocator]; }

void GfAllocatorManager::buildAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE handle) { unknown10[allocator].setMemHandle(handle); }

void GfAllocatorManager::destroyAllocator(ALLOCATOR allocator, mtl::ALLOC_HANDLE) { unknown10[allocator].setMemHandle(mtl::ALLOC_HANDLE()); }

} // namespace gf
