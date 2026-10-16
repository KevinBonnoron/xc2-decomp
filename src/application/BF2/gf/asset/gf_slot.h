#pragma once
#include <stddef.h>

#include "gf/asset/gf_slot_allocator.h"
#include "mm_mtl/allocator.h"
#include "types.h"

namespace gf {

struct GF_SLOT_HANDLE;

static GF_SLOT_HANDLE *const INVALID_SLOT_HANDLE = reinterpret_cast<GF_SLOT_HANDLE *>(-1);

class GfSlotBase : public mm::mtl::IAllocator {
public:
  GfSlotBase(const char *name, GfSlotAllocator *parent, u32 slotSize, bool useDebugMemory);
  ~GfSlotBase() override;
  void destroy();
  void *allocate(size_t size, size_t alignment) override;
  void deallocate(void *pointer) override;
  const char *getName() const override;
  size_t getBlockSize() const;
  bool empty() const;
  bool isChildSlot() const;
  void setSlotHandle(GF_SLOT_HANDLE *handle, u32 index);
  GF_SLOT_HANDLE *getSlotHandle() const;
  size_t getSlotSize() const;
  void releaseSlot();
  void *getBuffer();
  size_t getBufferSize() const;
  void setParentSlot(GfSlotBase *parent);
  void setMultiSlot(u32 multiSlot);
  u32 getMultiSlot() const;
  bool isExistAsset() const;

  GF_SLOT_HANDLE *handle;
  size_t slotSize;
  GfSlotAllocator allocator;
  GfSlotBase *parent;
  u32 multiSlot;
  u32 index;
  bool useDebugMemory;
};

static_assert(offsetof(GfSlotBase, handle) == 0x08, "");
static_assert(offsetof(GfSlotBase, slotSize) == 0x10, "");
static_assert(offsetof(GfSlotBase, allocator) == 0x18, "");
static_assert(offsetof(GfSlotBase, parent) == 0x308, "");
static_assert(offsetof(GfSlotBase, multiSlot) == 0x310, "");
static_assert(offsetof(GfSlotBase, index) == 0x314, "");
static_assert(offsetof(GfSlotBase, useDebugMemory) == 0x318, "");
static_assert(sizeof(GfSlotBase) == 0x320, "");

} // namespace gf
