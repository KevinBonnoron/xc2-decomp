#pragma once
#include <stddef.h>

#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_slot_allocator.h"
#include "mm_mtl/allocator.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
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

  GF_SLOT_HANDLE *m_slotHandle;
  size_t m_slotSize;
  GfSlotAllocator unknown18; // Inferred role: allocator; original member name unknown.
  GfSlotBase *m_parentSlot;
  u32 m_multiSlot;
  u32 unknown314;  // Inferred role: index; original member name unknown.
  bool unknown318; // Inferred role: use debug memory; original member name unknown.
};

static_assert(offsetof(GfSlotBase, m_slotHandle) == 0x08, "");
static_assert(offsetof(GfSlotBase, m_slotSize) == 0x10, "");
static_assert(offsetof(GfSlotBase, unknown18) == 0x18, "");
static_assert(offsetof(GfSlotBase, m_parentSlot) == 0x308, "");
static_assert(offsetof(GfSlotBase, m_multiSlot) == 0x310, "");
static_assert(offsetof(GfSlotBase, unknown314) == 0x314, "");
static_assert(offsetof(GfSlotBase, unknown318) == 0x318, "");
static_assert(sizeof(GfSlotBase) == 0x320, "");

class GfSlotAll {
public:
  static const u32 SLOT_MAX = 1304;
  static const u32 SLOT_TYPE_COUNT = ASSET_TYPE_SE - ASSET_TYPE_MAP + 1;

  typedef mm::mtl::FixedVector<GfSlotBase *, SLOT_MAX> SlotList;

  GfSlotAll() : unknown00(0) {}
  GfSlotBase *getSlot(GF_SLOT_HANDLE *handle) const;
  const char *getSlotName(GfAssetType type) const;
  f32 getSlotUsingRatio(GfAssetType type) const;
  size_t getSlotSize(GfAssetType type) const;
  u32 getSlotCount(GfAssetType type);
  GF_SLOT_HANDLE *getSlotHandle(GfAssetType type, u32 index) const;
  u32 getSystemSlotCount(GfAssetType type);
  bool isSystemSlotParent(GfAssetType type, u32 index);
  bool isSystemSlotChild(GfAssetType type, u32 index);
  GF_SLOT_HANDLE *getSystemSlotHandle(GfAssetType type, u32 index) const;
  void destroyMapping();
  void destroy(SlotList &list);
  size_t getBlockSize(GfAssetType type) const;
  GF_SLOT_HANDLE *setupSlotByte(GfAssetType type, size_t size, u32 index);
  u32 getSlotNumByByteSize(GfAssetType type, size_t size) const;
  GF_SLOT_HANDLE *setupSlotNum(GfAssetType type, u32 num, u32 index);
  GF_SLOT_HANDLE *createSlotHandle(GfAssetType type, u32 index);
  GF_SLOT_HANDLE *setupSlotNumTail(GfAssetType type, u32 num, u32 index);
  void releaseSlot(GF_SLOT_HANDLE *handle);
  void createSlot(GfAssetType type, u32 count, const char *name, u32 slotSize, GfSlotAllocator *parent, bool useDebugMemory);
  size_t getByteSizeBySlotNum(GfAssetType type, u32 num) const;
  static bool isEnableDelete(const SlotList &list, u32 start, u32 num, u32 index);
  bool isMemoryDebug(GfAssetType type) const;
  bool getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle);
  bool getSlotInfo(void *&buffer, size_t &size, GfAssetType type);
  bool isExistAsset(GF_SLOT_HANDLE *handle) const;
  void *allocateSize(GfAssetType type, size_t size, size_t alignment);
  void deallocateSize(void *pointer);

  u64 unknown00;                                            // Inferred role: handle serial; original member name unknown.
  mm::mtl::FixedArray<SlotList, SLOT_TYPE_COUNT> unknown08; // Inferred role: slots; original member name unknown.
};

static_assert(offsetof(GfSlotAll, unknown08) == 0x08, "");
static_assert(sizeof(GfSlotAll) == 0x2b550, "");

} // namespace gf
