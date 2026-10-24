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
  if (param.unknown1c == 0) {
    unknown08->createSlot(ASSET_TYPE_MAP, 1, "SLOT_MA", 0x22a0000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_PC, 8, "SLOT_PC", 0x28000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_PC_MOTION, 64, "SLOT_PM", 0x78000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_BLADE, 22, "SLOT_BL", 0x28000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_BLADE_MOTION, 272, "SLOT_BM", 0x4a000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_WEAPON, 168, "SLOT_WP", 0x20000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_WEAPON_MOTION, 192, "SLOT_WM", 0x50000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_WEAPON_EFFECT, 512, "SLOT_WE", 0x20000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_ENEMY, 160, "SLOT_EN", 0x4000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_ENEMY_MOTION, 480, "SLOT_EM", 0x20000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_ENEMY_ARC, 160, "SLOT_EA", 0x2000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_EFFECT, 240, "SLOT_EF", 0x20000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_FIELD_OBJECT, 32, "SLOT_FO", 0x20000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_MAP_OBJECT, 300, "SLOT_MO", 0x30000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_OPTION, 304, "SLOT_OP", 0x14000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_TEMPORARY, 1304, "SLOT_TP", 0x10000, unknown00, false);
    unknown08->createSlot(ASSET_TYPE_SE, 150, "SLOT_SE", 0x40000, unknown00, false);
  }
  registSoundMemeory(ASSET_TYPE_TEMPORARY);
  registSoundMemeory(ASSET_TYPE_SE);
}

void GfSlotMapping::destroyMapping() {
  unregistSoundMemeory(ASSET_TYPE_SE);
  unregistSoundMemeory(ASSET_TYPE_TEMPORARY);
  unknown08->destroyMapping();
}

void GfSlotMapping::registSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (unknown08->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->attachPoolMemory(buffer, size);
  }
}

void GfSlotMapping::unregistSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (unknown08->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->detachPoolMemory(buffer, size);
  }
}

GfSlotMapping::GfSlotMapping() : unknown08(nullptr), unknown1818(0), unknown1820(0) {
  // __LINE__ must be 382 and 383 as in the original source: they are the line arguments of operator new.
#line 382
  unknown08 = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotAll();
  unknown00 = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotAllocator();
}

GfSlotMapping::~GfSlotMapping() {
  if (unknown00 != nullptr) {
    delete unknown00;
    unknown00 = nullptr;
  }

  if (unknown08 != nullptr) {
    delete unknown08;
    unknown08 = nullptr;
  }
}

void GfSlotMapping::setup(const GfSetupParam &param, GfAllocator *allocator, size_t size) {
  this->unknown00->setupSizeAlloc("SLOT_ALL", allocator, size, SLOT_ALIGNMENT, false);
  createMapping(param);
  unknown1818 = mtl::MemManager::getTopAdr(getAllocator(ALLOCATOR_ASSET)->getMemHandle());
  unknown1820 = unknown1818 + mtl::MemManager::getTotalSize(getAllocator(ALLOCATOR_ASSET)->getMemHandle());
}

void GfSlotMapping::destroy() {
  while (unknown10.size() != 0) {
    GfSleep(1);
  }
  destroyMapping();
  unknown00->destroy();
}

void GfSlotMapping::update(const fw::UpdateInfo &info) { updateSlotRequest(info); }

bool GfSlotMapping::setupFreeSlot(REQ *request) {
  GfSlotBase *slot;
  if (request->unknown08->unknown230 == INVALID_SLOT_HANDLE) {
    u32 priority = request->unknown08->unknown250;
    GfAssetType type = request->unknown08->m_assetType.unknown00;
    if (GfAssetManager::isExistSameAsset(request->unknown08)) {
      return false;
    }

    size_t slotSize = unknown08->getByteSizeBySlotNum(type, request->unknown08->unknown248);
    size_t needSize = request->unknown08->getNeedLoadFileSize(unknown08->getBlockSize(type), false);
    if (needSize > slotSize) {
      unknown08->isMemoryDebug(type);
    }
    request->unknown08->setLoadSlotNum(unknown08->getSlotNumByByteSize(type, needSize));

    GF_SLOT_HANDLE *handle = unknown08->setupSlotByte(type, needSize, priority);
    if (handle == INVALID_SLOT_HANDLE) {
      GfAssetManager::destroySlotCache(type);
      if (request->unknown10 < RETRY_COUNT_MAX) {
        request->unknown10++;
      }
      if (request->unknown08->unknown254 < 2) {
        return GfAssetUtil::isObjectDestroy(request->unknown00);
      }
      return false;
    }

    slot = unknown08->getSlot(handle);
    request->unknown08->unknown230 = handle;
  } else {
    slot = unknown08->getSlot(request->unknown08->unknown230);
  }

  GfAssetManager::loadStart(request->unknown08, slot);
  return true;
}

void GfSlotMapping::requestSlotLoad(GF_ASSET_HANDLE *handle, GfAssetPack *pack) {
  for (REQ *request = unknown10.begin(); request != unknown10.end(); ++request) {
    if (request->unknown08 == pack) {
      return;
    }
  }
  pack->addRef();
  REQ request = {};
  request.unknown00 = handle;
  request.unknown08 = pack;
  request.unknown10 = 0;
  request.unknown14 = RETRY_INTERVAL;
  unknown10.push_back(request);
  std::sort(unknown10.begin(), unknown10.end(), BiggerPrio());
}

bool GfSlotMapping::isRequest(const GfAssetPack *pack) const {
  for (const REQ *request = unknown10.begin(); request != unknown10.end(); ++request) {
    if (request->unknown08 == pack) {
      return true;
    }
  }
  return false;
}

void GfSlotMapping::releaseSlot(GF_SLOT_HANDLE *handle) { unknown08->releaseSlot(handle); }

u32 GfSlotMapping::getSlots(GF_SLOT_HANDLE *handle) const { return unknown08->getSlot(handle)->getMultiSlot(); }

const char *GfSlotMapping::getSlotName(GF_SLOT_HANDLE *handle) const { return unknown08->getSlot(handle)->getName(); }

const char *GfSlotMapping::getSlotName(GfAssetType type) const { return unknown08->getSlotName(type); }

f32 GfSlotMapping::getSlotUsingRatio(GfAssetType type) const { return unknown08->getSlotUsingRatio(type); }

size_t GfSlotMapping::getSlotSize(GfAssetType type) const { return unknown08->getSlotSize(type); }

size_t GfSlotMapping::getSlotBlockSize(GfAssetType type) const { return unknown08->getBlockSize(type); }

u32 GfSlotMapping::getSlotCount(GfAssetType type) const { return unknown08->getSlotCount(type); }

GF_SLOT_HANDLE *GfSlotMapping::getSlotHandle(GfAssetType type, u32 index) const { return unknown08->getSlotHandle(type, index); }

u32 GfSlotMapping::getSystemSlotCount(GfAssetType type) const { return unknown08->getSystemSlotCount(type); }

bool GfSlotMapping::isSystemSlotParent(GfAssetType type, u32 index) { return unknown08->isSystemSlotParent(type, index); }

bool GfSlotMapping::isSystemSlotChild(GfAssetType type, u32 index) { return unknown08->isSystemSlotChild(type, index); }

GF_SLOT_HANDLE *GfSlotMapping::getSystemSlotHandle(GfAssetType type, u32 index) { return unknown08->getSystemSlotHandle(type, index); }

u32 GfSlotMapping::getSlotNumByByteSize(GfAssetType type, size_t size) const { return unknown08->getSlotNumByByteSize(type, size); }

GF_SLOT_HANDLE *GfSlotMapping::allocateSlot(GfAssetType type, size_t size) { return unknown08->setupSlotByte(type, size, 1); }

bool GfSlotMapping::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) { return unknown08->getSlotInfo(allocator, buffer, size, handle); }

bool GfSlotMapping::isExistAsset(GF_SLOT_HANDLE *handle) const { return unknown08->isExistAsset(handle); }

void *GfSlotMapping::allocateSize(size_t size, size_t alignment) { return unknown08->allocateSize(ASSET_TYPE_TEMPORARY, size, alignment); }

bool GfSlotMapping::deallocateSize(void *pointer) {
  u64 address = reinterpret_cast<u64>(pointer);
  if (unknown1818 > address) {
    return false;
  }
  if (unknown1820 > address) {
    unknown08->deallocateSize(pointer);
    return true;
  }
  return false;
}

void GfSlotMapping::ExtendSlotAllocator::createAllocator(size_t size, const char *name) {
  unknown08 = mtl::MemManager::allocate(ml::MlMem::getDebugMem(), size + EXTEND_MEMORY_MARGIN, 0x10, false, "no name", 0);
  unknown10 = mtl::MemManager::create(unknown08, size + EXTEND_MEMORY_MARGIN, name, true);
  // __LINE__ must be 891 as in the original source: it is the line argument of operator new.
#line 891
  unknown00 = new (getAllocator(ALLOCATOR_DEBUG), __FILE__, __LINE__, 8) GfSlotAllocator();
  unknown00->setupSizeAlloc(name, mtl::MemManager::getAllocator(unknown10), size, SLOT_ALIGNMENT, false);
}

void GfSlotMapping::ExtendSlotAllocator::destroyAllocator() {
  if (unknown00 != nullptr) {
    delete unknown00;
    unknown00 = nullptr;
  }

  if (unknown10.isValid()) {
    mtl::MemManager::erase(unknown10);
    unknown10 = mtl::ALLOC_HANDLE();
  }

  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

bool GfSlotMapping::BiggerPrio::operator()(REQ &request, REQ &other) const { return request.unknown08->unknown250 > other.unknown08->unknown250; }

} // namespace gf
