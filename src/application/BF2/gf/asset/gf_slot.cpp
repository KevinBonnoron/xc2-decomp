#include "gf/asset/gf_slot.h"

#include "mm_mtl/fixstr.h"

namespace gf {

constexpr size_t SLOT_ALIGNMENT = 0x2000;

GfSlotBase::GfSlotBase(const char *name, GfSlotAllocator *parent, u32 slotSize, bool useDebugMemory)
    : handle(INVALID_SLOT_HANDLE), slotSize(slotSize), parent(nullptr), multiSlot(1), index(0), useDebugMemory(useDebugMemory) {
  allocator.setup(name, parent, slotSize, SLOT_ALIGNMENT, useDebugMemory);
}

GfSlotBase::~GfSlotBase() { allocator.destroy(); }

void GfSlotBase::destroy() { allocator.destroy(); }

void *GfSlotBase::allocate(size_t size, size_t alignment) { return allocator.allocate(size, alignment); }

void GfSlotBase::deallocate(void *pointer) { allocator.deallocate(pointer); }

const char *GfSlotBase::getName() const { return allocator.name.c_str(); }

size_t GfSlotBase::getBlockSize() const { return allocator.getBlockSize(); }

bool GfSlotBase::empty() const { return parent == nullptr && handle == INVALID_SLOT_HANDLE; }

bool GfSlotBase::isChildSlot() const { return parent != nullptr; }

void GfSlotBase::setSlotHandle(GF_SLOT_HANDLE *handle, u32 index) {
  this->handle = handle;
  this->index = index;
}

GF_SLOT_HANDLE *GfSlotBase::getSlotHandle() const { return handle; }

size_t GfSlotBase::getSlotSize() const { return slotSize; }

void GfSlotBase::releaseSlot() {
  handle = INVALID_SLOT_HANDLE;
  parent = nullptr;
  multiSlot = 1;
  allocator.resize(slotSize);
}

void *GfSlotBase::getBuffer() { return allocator.getBuffer(); }

size_t GfSlotBase::getBufferSize() const { return allocator.getBufferSize(); }

void GfSlotBase::setParentSlot(GfSlotBase *parent) { this->parent = parent; }

void GfSlotBase::setMultiSlot(u32 multiSlot) {
  if (allocator.getAllocs() != 0) {
    return;
  }

  this->multiSlot = multiSlot;
  allocator.resize(slotSize * multiSlot);
}

u32 GfSlotBase::getMultiSlot() const { return multiSlot; }

bool GfSlotBase::isExistAsset() const { return allocator.getAllocs() != 0; }

} // namespace gf
