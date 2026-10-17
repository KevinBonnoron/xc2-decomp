#include "gf/asset/gf_slot_mapping.h"

#include <algorithm>

#include "framework/sound/sound_manager.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/asset/gf_asset_util.h"
#include "gf/asset/gf_slot.h"
#include "gf/asset/gf_slot_allocator.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "ml/ml_mem.h"
#include "mtl/mem_manager.h"

namespace gf {

constexpr size_t ALL_SLOT_SIZE = 0x24eb0000;
constexpr size_t EXTEND_MEMORY_MARGIN = 0x8000;
constexpr u16 RETRY_COUNT_MAX = 999;
constexpr f32 RETRY_INTERVAL = 0.5f;

size_t GfSlotMapping::getAllSize() { return ALL_SLOT_SIZE; }

void GfSlotMapping::createMapping(const GfSetupParam &param) {
  destroyMapping();
  if (param.slotMappingType == 0) {
    slotAll->createSlot(ASSET_TYPE_MAP, 1, "SLOT_MA", 0x22a0000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_PC, 8, "SLOT_PC", 0x28000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_PC_MOTION, 64, "SLOT_PM", 0x78000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_BLADE, 22, "SLOT_BL", 0x28000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_BLADE_MOTION, 272, "SLOT_BM", 0x4a000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_WEAPON, 168, "SLOT_WP", 0x20000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_WEAPON_MOTION, 192, "SLOT_WM", 0x50000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_WEAPON_EFFECT, 512, "SLOT_WE", 0x20000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_ENEMY, 160, "SLOT_EN", 0x4000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_ENEMY_MOTION, 480, "SLOT_EM", 0x20000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_ENEMY_ARC, 160, "SLOT_EA", 0x2000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_EFFECT, 240, "SLOT_EF", 0x20000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_FIELD_OBJECT, 32, "SLOT_FO", 0x20000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_MAP_OBJECT, 300, "SLOT_MO", 0x30000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_OPTION, 304, "SLOT_OP", 0x14000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_TEMPORARY, 1304, "SLOT_TP", 0x10000, allocator, false);
    slotAll->createSlot(ASSET_TYPE_SE, 150, "SLOT_SE", 0x40000, allocator, false);
  }
  registSoundMemeory(ASSET_TYPE_TEMPORARY);
  registSoundMemeory(ASSET_TYPE_SE);
}

void GfSlotMapping::destroyMapping() {
  unregistSoundMemeory(ASSET_TYPE_SE);
  unregistSoundMemeory(ASSET_TYPE_TEMPORARY);
  slotAll->destroyMapping();
}

void GfSlotMapping::registSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (slotAll->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->attachPoolMemory(buffer, size);
  }
}

void GfSlotMapping::unregistSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (slotAll->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->detachPoolMemory(buffer, size);
  }
}

GfSlotMapping::GfSlotMapping() : slotAll(nullptr), topAddress(0), endAddress(0) {
  // __LINE__ must be 382 and 383 as in the original source: they are the line arguments of operator new.
#line 382
  slotAll = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotAll();
  allocator = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotAllocator();
}

GfSlotMapping::~GfSlotMapping() {
  if (allocator != nullptr) {
    delete allocator;
    allocator = nullptr;
  }

  if (slotAll != nullptr) {
    delete slotAll;
    slotAll = nullptr;
  }
}

void GfSlotMapping::setup(const GfSetupParam &param, GfAllocator *allocator, size_t size) {
  this->allocator->setupSizeAlloc("SLOT_ALL", allocator, size, SLOT_ALIGNMENT, false);
  createMapping(param);
  topAddress = mtl::MemManager::getTopAdr(getAllocator(ALLOCATOR_ASSET)->getMemHandle());
  endAddress = topAddress + mtl::MemManager::getTotalSize(getAllocator(ALLOCATOR_ASSET)->getMemHandle());
}

void GfSlotMapping::destroy() {
  while (requests.size() != 0) {
    GfSleep(1);
  }
  destroyMapping();
  allocator->destroy();
}

void GfSlotMapping::update(const fw::UpdateInfo &info) { updateSlotRequest(info); }

bool GfSlotMapping::setupFreeSlot(REQ *request) {
  GfSlotBase *slot;
  if (request->pack->slotHandle == INVALID_SLOT_HANDLE) {
    u32 priority = request->pack->priority;
    GfAssetType type = request->pack->files.assetType;
    if (GfAssetManager::isExistSameAsset(request->pack)) {
      return false;
    }

    size_t slotSize = slotAll->getByteSizeBySlotNum(type, request->pack->slotNum);
    size_t needSize = request->pack->getNeedLoadFileSize(slotAll->getBlockSize(type), false);
    if (needSize > slotSize) {
      slotAll->isMemoryDebug(type);
    }
    request->pack->setLoadSlotNum(slotAll->getSlotNumByByteSize(type, needSize));

    GF_SLOT_HANDLE *handle = slotAll->setupSlotByte(type, needSize, priority);
    if (handle == INVALID_SLOT_HANDLE) {
      GfAssetManager::destroySlotCache(type);
      if (request->retryCount < RETRY_COUNT_MAX) {
        request->retryCount++;
      }
      if (request->pack->userCount < 2) {
        return GfAssetUtil::isObjectDestroy(request->handle);
      }
      return false;
    }

    slot = slotAll->getSlot(handle);
    request->pack->slotHandle = handle;
  } else {
    slot = slotAll->getSlot(request->pack->slotHandle);
  }

  GfAssetManager::loadStart(request->pack, slot);
  return true;
}

void GfSlotMapping::requestSlotLoad(GF_ASSET_HANDLE *handle, GfAssetPack *pack) {
  for (REQ *request = requests.begin(); request != requests.end(); ++request) {
    if (request->pack == pack) {
      return;
    }
  }
  pack->addRef();
  REQ request = {};
  request.handle = handle;
  request.pack = pack;
  request.retryCount = 0;
  request.timer = RETRY_INTERVAL;
  requests.push_back(request);
  std::sort(requests.begin(), requests.end(), BiggerPrio());
}

bool GfSlotMapping::isRequest(const GfAssetPack *pack) const {
  for (const REQ *request = requests.begin(); request != requests.end(); ++request) {
    if (request->pack == pack) {
      return true;
    }
  }
  return false;
}

void GfSlotMapping::releaseSlot(GF_SLOT_HANDLE *handle) { slotAll->releaseSlot(handle); }

u32 GfSlotMapping::getSlots(GF_SLOT_HANDLE *handle) const { return slotAll->getSlot(handle)->getMultiSlot(); }

const char *GfSlotMapping::getSlotName(GF_SLOT_HANDLE *handle) const { return slotAll->getSlot(handle)->getName(); }

const char *GfSlotMapping::getSlotName(GfAssetType type) const { return slotAll->getSlotName(type); }

f32 GfSlotMapping::getSlotUsingRatio(GfAssetType type) const { return slotAll->getSlotUsingRatio(type); }

size_t GfSlotMapping::getSlotSize(GfAssetType type) const { return slotAll->getSlotSize(type); }

size_t GfSlotMapping::getSlotBlockSize(GfAssetType type) const { return slotAll->getBlockSize(type); }

u32 GfSlotMapping::getSlotCount(GfAssetType type) const { return slotAll->getSlotCount(type); }

GF_SLOT_HANDLE *GfSlotMapping::getSlotHandle(GfAssetType type, u32 index) const { return slotAll->getSlotHandle(type, index); }

u32 GfSlotMapping::getSystemSlotCount(GfAssetType type) const { return slotAll->getSystemSlotCount(type); }

bool GfSlotMapping::isSystemSlotParent(GfAssetType type, u32 index) { return slotAll->isSystemSlotParent(type, index); }

bool GfSlotMapping::isSystemSlotChild(GfAssetType type, u32 index) { return slotAll->isSystemSlotChild(type, index); }

GF_SLOT_HANDLE *GfSlotMapping::getSystemSlotHandle(GfAssetType type, u32 index) { return slotAll->getSystemSlotHandle(type, index); }

u32 GfSlotMapping::getSlotNumByByteSize(GfAssetType type, size_t size) const { return slotAll->getSlotNumByByteSize(type, size); }

GF_SLOT_HANDLE *GfSlotMapping::allocateSlot(GfAssetType type, size_t size) { return slotAll->setupSlotByte(type, size, 1); }

bool GfSlotMapping::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) {
  return slotAll->getSlotInfo(allocator, buffer, size, handle);
}

bool GfSlotMapping::isExistAsset(GF_SLOT_HANDLE *handle) const { return slotAll->isExistAsset(handle); }

void *GfSlotMapping::allocateSize(size_t size, size_t alignment) { return slotAll->allocateSize(ASSET_TYPE_TEMPORARY, size, alignment); }

bool GfSlotMapping::deallocateSize(void *pointer) {
  u64 address = reinterpret_cast<u64>(pointer);
  if (topAddress > address) {
    return false;
  }
  if (endAddress > address) {
    slotAll->deallocateSize(pointer);
    return true;
  }
  return false;
}

void GfSlotMapping::ExtendSlotAllocator::createAllocator(size_t size, const char *name) {
  memory = mtl::MemManager::allocate(ml::MlMem::getDebugMem(), size + EXTEND_MEMORY_MARGIN, 0x10, false, "no name", 0);
  handle = mtl::MemManager::create(memory, size + EXTEND_MEMORY_MARGIN, name, true);
  // __LINE__ must be 891 as in the original source: it is the line argument of operator new.
#line 891
  allocator = new (getAllocator(ALLOCATOR_DEBUG), __FILE__, __LINE__, 8) GfSlotAllocator();
  allocator->setupSizeAlloc(name, mtl::MemManager::getAllocator(handle), size, SLOT_ALIGNMENT, false);
}

void GfSlotMapping::ExtendSlotAllocator::destroyAllocator() {
  if (allocator != nullptr) {
    delete allocator;
    allocator = nullptr;
  }

  if (handle.isValid()) {
    mtl::MemManager::erase(handle);
    handle = mtl::ALLOC_HANDLE();
  }

  if (memory != nullptr) {
    mtl::MemManager::deallocate(memory, 0, false);
    memory = nullptr;
  }
}

bool GfSlotMapping::BiggerPrio::operator()(REQ &request, REQ &other) const { return request.pack->priority > other.pack->priority; }

} // namespace gf
