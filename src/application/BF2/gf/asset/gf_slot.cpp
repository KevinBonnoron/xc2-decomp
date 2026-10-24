#include "gf/asset/gf_slot.h"

#include "gf/asset/gf_asset_util.h"
#include "gf/gf_allocator.h"
#include "mm_mtl/fixstr.h"

namespace gf {

constexpr size_t BASE_BLOCK_SIZE = 0x8000;

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

static u64 getHandleType(GF_SLOT_HANDLE *handle) { return (reinterpret_cast<u64>(handle) >> 16) & 0xffff; }

static u32 getHandleIndex(GF_SLOT_HANDLE *handle) { return reinterpret_cast<u64>(handle) & 0xffff; }

GfSlotBase *GfSlotAll::getSlot(GF_SLOT_HANDLE *handle) const {
  u32 index = getHandleIndex(handle);
  return slots[getHandleType(handle) - ASSET_TYPE_MAP][index];
}

const char *GfSlotAll::getSlotName(GfAssetType type) const { return slots[type - ASSET_TYPE_MAP][0]->getName(); }

f32 GfSlotAll::getSlotUsingRatio(GfAssetType type) const {
  const SlotList &list = slots[type - ASSET_TYPE_MAP];
  u32 used = 0;
  for (u32 i = 0; i < list.size(); i++) {
    if (!(*list.at(i))->empty()) {
      used++;
    }
  }
  return static_cast<f32>(used) / static_cast<f32>(list.size());
}

size_t GfSlotAll::getSlotSize(GfAssetType type) const { return slots[type - ASSET_TYPE_MAP][0]->getSlotSize(); }

u32 GfSlotAll::getSlotCount(GfAssetType type) {
  u32 slotCount = getSystemSlotCount(type);
  u32 count = 0;
  for (u32 i = 0; i < slotCount; i++) {
    if (!slots[type - ASSET_TYPE_MAP][i]->isChildSlot()) {
      count++;
    }
  }
  return count;
}

GF_SLOT_HANDLE *GfSlotAll::getSlotHandle(GfAssetType type, u32 index) const {
  const SlotList &list = slots[type - ASSET_TYPE_MAP];
  GF_SLOT_HANDLE *handle = INVALID_SLOT_HANDLE;
  u32 slotCount = list.size();
  u32 parentIndex = 0;
  for (u32 i = 0; i < slotCount; i++) {
    if (!list[i]->isChildSlot()) {
      if (parentIndex == index) {
        handle = list[i]->getSlotHandle();
        break;
      }
      parentIndex++;
    }
  }
  return handle;
}

u32 GfSlotAll::getSystemSlotCount(GfAssetType type) { return slots[type - ASSET_TYPE_MAP].size(); }

bool GfSlotAll::isSystemSlotParent(GfAssetType type, u32 index) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  return list[index]->getSlotHandle() != INVALID_SLOT_HANDLE && !list[index]->isChildSlot();
}

bool GfSlotAll::isSystemSlotChild(GfAssetType type, u32 index) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  return list[index]->getSlotHandle() != INVALID_SLOT_HANDLE && list[index]->isChildSlot();
}

GF_SLOT_HANDLE *GfSlotAll::getSystemSlotHandle(GfAssetType type, u32 index) const { return slots[type - ASSET_TYPE_MAP][index]->getSlotHandle(); }

void GfSlotAll::destroyMapping() {
  for (SlotList *list = slots.begin(); list != slots.end(); ++list) {
    destroy(*list);
  }
}

void GfSlotAll::destroy(SlotList &list) {
  for (GfSlotBase **slot = list.begin(); slot != list.end(); ++slot) {
    if (*slot != nullptr) {
      delete *slot;
      *slot = nullptr;
    }
  }
  list.clear();
}

size_t GfSlotAll::getBlockSize(GfAssetType type) const {
  if (type == ASSET_TYPE_BASE) {
    return BASE_BLOCK_SIZE;
  }
  return slots[type - ASSET_TYPE_MAP][0]->getBlockSize();
}

GF_SLOT_HANDLE *GfSlotAll::setupSlotByte(GfAssetType type, size_t size, u32 index) { return setupSlotNum(type, getSlotNumByByteSize(type, size), index); }

u32 GfSlotAll::getSlotNumByByteSize(GfAssetType type, size_t size) const {
  const SlotList &list = slots[type - ASSET_TYPE_MAP];
  if (list.empty()) {
    return 0;
  }

  size_t slotSize = list.front()->getSlotSize();
  u32 num = size / slotSize;
  if (num == 0 || size % slotSize != 0) {
    num++;
  }
  return num;
}

GF_SLOT_HANDLE *GfSlotAll::setupSlotNum(GfAssetType type, u32 num, u32 index) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  if (list.empty()) {
    return INVALID_SLOT_HANDLE;
  }

  for (u32 start = 0; start < list.size(); start++) {
    u32 end = start + num;
    if (end > list.size()) {
      break;
    }

    for (u32 i = start; i < end; i++) {
      if (list[i]->getSlotHandle() != INVALID_SLOT_HANDLE) {
        break;
      }

      if (i == end - 1) {
        GF_SLOT_HANDLE *handle = createSlotHandle(type, start);
        for (u32 j = start; j < end; j++) {
          list[j]->setSlotHandle(handle, index);
          if (j > start) {
            list[j]->setParentSlot(list[start]);
          }
        }
        list[start]->setMultiSlot(num);
        return handle;
      }
    }
  }

  return INVALID_SLOT_HANDLE;
}

GF_SLOT_HANDLE *GfSlotAll::createSlotHandle(GfAssetType type, u32 index) {
  u64 serial = handleSerial++;
  if ((serial >> 32) != 0) {
    serial = handleSerial++;
  }
  return reinterpret_cast<GF_SLOT_HANDLE *>((serial << 32) | (type << 16) | index);
}

GF_SLOT_HANDLE *GfSlotAll::setupSlotNumTail(GfAssetType type, u32 num, u32 index) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  if (list.empty()) {
    return INVALID_SLOT_HANDLE;
  }

  for (s32 start = list.size() - 1; start >= 0; start--) {
    if (start + num > list.size()) {
      continue;
    }

    s32 end = start + num;

    for (u32 i = start; i < end; i++) {
      if (list[i]->getSlotHandle() != INVALID_SLOT_HANDLE) {
        break;
      }

      if (i == end - 1) {
        GF_SLOT_HANDLE *handle = createSlotHandle(type, start);
        for (s32 j = start; j < end; j++) {
          list[j]->setSlotHandle(handle, index);
          if (j > start) {
            list[j]->setParentSlot(list[start]);
          }
        }
        list[start]->setMultiSlot(num);
        return handle;
      }
    }
  }

  return INVALID_SLOT_HANDLE;
}

void GfSlotAll::releaseSlot(GF_SLOT_HANDLE *handle) {
  u32 index = getHandleIndex(handle);
  SlotList &list = slots[getHandleType(handle) - ASSET_TYPE_MAP];
  u32 multiSlot = list[index]->getMultiSlot();
  for (u32 i = index + 1; i < index + multiSlot; i++) {
    list[i]->releaseSlot();
  }
  list[index]->releaseSlot();
}

void GfSlotAll::createSlot(GfAssetType type, u32 count, const char *name, u32 slotSize, GfSlotAllocator *parent, bool useDebugMemory) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  for (u32 i = 0; i < count; i++) {
    mm::mtl::FixStr<16> slotName;
    slotName.format("%s%d", name, i + 1);
    // __LINE__ must be 502 as in the original source: it is the line argument of operator new.
#line 502
    GfSlotBase *slot = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotBase(slotName.c_str(), parent, slotSize, useDebugMemory);
    list.push_back(slot);
  }
}

size_t GfSlotAll::getByteSizeBySlotNum(GfAssetType type, u32 num) const { return slots[type - ASSET_TYPE_MAP][0]->getSlotSize() * num; }

bool GfSlotAll::isEnableDelete(const SlotList &list, u32 start, u32 num, u32 index) {
  for (u32 i = start; i < start + num; i++) {
    if (list[i]->getSlotHandle() != INVALID_SLOT_HANDLE && (list[i]->index >= index || !GfAssetUtil::isEnableDeleteObject(list[i]->getSlotHandle()))) {
      return false;
    }
  }
  return true;
}

bool GfSlotAll::isMemoryDebug(GfAssetType type) const { return slots[type - ASSET_TYPE_MAP][0]->useDebugMemory; }

bool GfSlotAll::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) {
  if (handle == INVALID_SLOT_HANDLE) {
    return false;
  }

  u32 index = getHandleIndex(handle);
  SlotList &list = slots[getHandleType(handle) - ASSET_TYPE_MAP];
  buffer = list[index]->getBuffer();
  size = list[index]->getBufferSize() * list[index]->getMultiSlot();
  allocator = list[index];
  return true;
}

bool GfSlotAll::getSlotInfo(void *&buffer, size_t &size, GfAssetType type) {
  SlotList &list = slots[type - ASSET_TYPE_MAP];
  if (list.empty()) {
    return false;
  }

  buffer = list[0]->getBuffer();
  size = list[0]->getBufferSize() * list.size();
  return true;
}

bool GfSlotAll::isExistAsset(GF_SLOT_HANDLE *handle) const {
  if (handle == INVALID_SLOT_HANDLE) {
    return false;
  }
  u32 index = getHandleIndex(handle);
  return slots[getHandleType(handle) - ASSET_TYPE_MAP][index]->isExistAsset();
}

void *GfSlotAll::allocateSize(GfAssetType type, size_t size, size_t alignment) {
  u32 num = getSlotNumByByteSize(type, size);
  if (num == 0) {
    return nullptr;
  }

  GF_SLOT_HANDLE *handle = setupSlotNumTail(type, num, 0);
  if (handle == INVALID_SLOT_HANDLE) {
    return nullptr;
  }

  mm::mtl::IAllocator *allocator;
  void *buffer = nullptr;
  size_t bufferSize;
  getSlotInfo(allocator, buffer, bufferSize, handle);
  return buffer;
}

void GfSlotAll::deallocateSize(void *pointer) {
  for (s32 type = ASSET_TYPE_MAP; type <= ASSET_TYPE_SE; type++) {
    SlotList &list = slots[type - ASSET_TYPE_MAP];
    void *first = list[0]->getBuffer();
    void *last = list[list.size() - 1]->getBuffer();
    if (first <= pointer && pointer <= last) {
      for (s32 i = static_cast<s32>(list.size()) - 1; i >= 0; i--) {
        if (list[i]->getBuffer() == pointer) {
          releaseSlot(list[i]->getSlotHandle());
          return;
        }
      }
    }
  }
}

} // namespace gf
