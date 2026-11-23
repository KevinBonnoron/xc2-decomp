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

constexpr size_t ALL_SLOT_UNKNOWN_619380736 = 0x24eb0000; // Inferred role: all slot size; original name unknown.
constexpr size_t EXTEND_UNKNOWN_32768 = 0x8000;           // Inferred role: extend memory margin; original name unknown.
constexpr u16 RETRY_UNKNOWN_999 = 999;                    // Inferred role: retry count max; original name unknown.
constexpr f32 unknown015 = 0.5f;                          // Inferred role: retry interval; original name unknown.

size_t GfSlotMapping::getAllSize() { return ALL_SLOT_UNKNOWN_619380736; }

void GfSlotMapping::createMapping(const GfSetupParam &param) {
  destroyMapping();
  if (param.unknown1c == 0) {
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_3, 1, "SLOT_MA", 0x22a0000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_4, 8, "SLOT_PC", 0x28000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_5, 64, "SLOT_PM", 0x78000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_6, 22, "SLOT_BL", 0x28000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_7, 272, "SLOT_BM", 0x4a000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_8, 168, "SLOT_WP", 0x20000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_16, 192, "SLOT_WM", 0x50000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_9, 512, "SLOT_WE", 0x20000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_10, 160, "SLOT_EN", 0x4000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_11, 480, "SLOT_EM", 0x20000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_12, 160, "SLOT_EA", 0x2000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_13, 240, "SLOT_EF", 0x20000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_14, 32, "SLOT_FO", 0x20000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_15, 300, "SLOT_MO", 0x30000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_17, 304, "SLOT_OP", 0x14000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_18, 1304, "SLOT_TP", 0x10000, m_slotAllocator, false);
    m_slotAll->createSlot(ASSET_TYPE_UNKNOWN_19, 150, "SLOT_SE", 0x40000, m_slotAllocator, false);
  }
  registSoundMemeory(ASSET_TYPE_UNKNOWN_18);
  registSoundMemeory(ASSET_TYPE_UNKNOWN_19);
}

void GfSlotMapping::destroyMapping() {
  unregistSoundMemeory(ASSET_TYPE_UNKNOWN_19);
  unregistSoundMemeory(ASSET_TYPE_UNKNOWN_18);
  m_slotAll->destroyMapping();
}

void GfSlotMapping::registSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (m_slotAll->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->attachPoolMemory(buffer, size);
  }
}

void GfSlotMapping::unregistSoundMemeory(GfAssetType type) {
  size_t size;
  void *buffer;
  if (m_slotAll->getSlotInfo(buffer, size, type) && fw::SoundManager::get() != nullptr) {
    fw::SoundManager::get()->detachPoolMemory(buffer, size);
  }
}

GfSlotMapping::GfSlotMapping() : m_slotAll(nullptr), unknown1818(0), unknown1820(0) {
  // __LINE__ must be 382 and 383 as in the original source: they are the line arguments of operator new.
#line 382
  m_slotAll = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfSlotAll();
  m_slotAllocator = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfSlotAllocator();
}

GfSlotMapping::~GfSlotMapping() {
  if (m_slotAllocator != nullptr) {
    delete m_slotAllocator;
    m_slotAllocator = nullptr;
  }

  if (m_slotAll != nullptr) {
    delete m_slotAll;
    m_slotAll = nullptr;
  }
}

void GfSlotMapping::setup(const GfSetupParam &param, GfAllocator *allocator, size_t size) {
  this->m_slotAllocator->setupSizeAlloc("SLOT_ALL", allocator, size, SLOT_UNKNOWN_8192, false);
  createMapping(param);
  unknown1818 = mtl::MemManager::getTopAdr(getAllocator(ALLOCATOR_UNKNOWN_3)->getMemHandle());
  unknown1820 = unknown1818 + mtl::MemManager::getTotalSize(getAllocator(ALLOCATOR_UNKNOWN_3)->getMemHandle());
}

void GfSlotMapping::destroy() {
  while (unknown10.size() != 0) {
    GfSleep(1);
  }
  destroyMapping();
  m_slotAllocator->destroy();
}

void GfSlotMapping::update(const fw::UpdateInfo &info) { updateSlotRequest(info); }

bool GfSlotMapping::setupFreeSlot(REQ *request) {
  GfSlotBase *slot;
  if (request->m_assetPack->m_GF_SLOT_HANDLE == unknown006) {
    u32 priority = request->m_assetPack->unknown250;
    GfAssetType type = request->m_assetPack->m_assetType.m_assetType;
    if (GfAssetManager::isExistSameAsset(request->m_assetPack)) {
      return false;
    }

    size_t slotSize = m_slotAll->getByteSizeBySlotNum(type, request->m_assetPack->unknown248);
    size_t needSize = request->m_assetPack->getNeedLoadFileSize(m_slotAll->getBlockSize(type), false);
    if (needSize > slotSize) {
      m_slotAll->isMemoryDebug(type);
    }
    request->m_assetPack->setLoadSlotNum(m_slotAll->getSlotNumByByteSize(type, needSize));

    GF_SLOT_HANDLE *handle = m_slotAll->setupSlotByte(type, needSize, priority);
    if (handle == unknown006) {
      GfAssetManager::destroySlotCache(type);
      if (request->unknown10 < RETRY_UNKNOWN_999) {
        request->unknown10++;
      }
      if (request->m_assetPack->unknown254 < 2) {
        return GfAssetUtil::isObjectDestroy(request->m_GF_ASSET_HANDLE);
      }
      return false;
    }

    slot = m_slotAll->getSlot(handle);
    request->m_assetPack->m_GF_SLOT_HANDLE = handle;
  } else {
    slot = m_slotAll->getSlot(request->m_assetPack->m_GF_SLOT_HANDLE);
  }

  GfAssetManager::loadStart(request->m_assetPack, slot);
  return true;
}

void GfSlotMapping::requestSlotLoad(GF_ASSET_HANDLE *handle, GfAssetPack *pack) {
  for (REQ *request = unknown10.begin(); request != unknown10.end(); ++request) {
    if (request->m_assetPack == pack) {
      return;
    }
  }
  pack->addRef();
  REQ request = {};
  request.m_GF_ASSET_HANDLE = handle;
  request.m_assetPack = pack;
  request.unknown10 = 0;
  request.unknown14 = unknown015;
  unknown10.push_back(request);
  std::sort(unknown10.begin(), unknown10.end(), BiggerPrio());
}

bool GfSlotMapping::isRequest(const GfAssetPack *pack) const {
  for (const REQ *request = unknown10.begin(); request != unknown10.end(); ++request) {
    if (request->m_assetPack == pack) {
      return true;
    }
  }
  return false;
}

void GfSlotMapping::releaseSlot(GF_SLOT_HANDLE *handle) { m_slotAll->releaseSlot(handle); }

u32 GfSlotMapping::getSlots(GF_SLOT_HANDLE *handle) const { return m_slotAll->getSlot(handle)->getMultiSlot(); }

const char *GfSlotMapping::getSlotName(GF_SLOT_HANDLE *handle) const { return m_slotAll->getSlot(handle)->getName(); }

const char *GfSlotMapping::getSlotName(GfAssetType type) const { return m_slotAll->getSlotName(type); }

f32 GfSlotMapping::getSlotUsingRatio(GfAssetType type) const { return m_slotAll->getSlotUsingRatio(type); }

size_t GfSlotMapping::getSlotSize(GfAssetType type) const { return m_slotAll->getSlotSize(type); }

size_t GfSlotMapping::getSlotBlockSize(GfAssetType type) const { return m_slotAll->getBlockSize(type); }

u32 GfSlotMapping::getSlotCount(GfAssetType type) const { return m_slotAll->getSlotCount(type); }

GF_SLOT_HANDLE *GfSlotMapping::getSlotHandle(GfAssetType type, u32 index) const { return m_slotAll->getSlotHandle(type, index); }

u32 GfSlotMapping::getSystemSlotCount(GfAssetType type) const { return m_slotAll->getSystemSlotCount(type); }

bool GfSlotMapping::isSystemSlotParent(GfAssetType type, u32 index) { return m_slotAll->isSystemSlotParent(type, index); }

bool GfSlotMapping::isSystemSlotChild(GfAssetType type, u32 index) { return m_slotAll->isSystemSlotChild(type, index); }

GF_SLOT_HANDLE *GfSlotMapping::getSystemSlotHandle(GfAssetType type, u32 index) { return m_slotAll->getSystemSlotHandle(type, index); }

u32 GfSlotMapping::getSlotNumByByteSize(GfAssetType type, size_t size) const { return m_slotAll->getSlotNumByByteSize(type, size); }

GF_SLOT_HANDLE *GfSlotMapping::allocateSlot(GfAssetType type, size_t size) { return m_slotAll->setupSlotByte(type, size, 1); }

bool GfSlotMapping::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) { return m_slotAll->getSlotInfo(allocator, buffer, size, handle); }

bool GfSlotMapping::isExistAsset(GF_SLOT_HANDLE *handle) const { return m_slotAll->isExistAsset(handle); }

void *GfSlotMapping::allocateSize(size_t size, size_t alignment) { return m_slotAll->allocateSize(ASSET_TYPE_UNKNOWN_18, size, alignment); }

bool GfSlotMapping::deallocateSize(void *pointer) {
  u64 address = reinterpret_cast<u64>(pointer);
  if (unknown1818 > address) {
    return false;
  }
  if (unknown1820 > address) {
    m_slotAll->deallocateSize(pointer);
    return true;
  }
  return false;
}

void GfSlotMapping::ExtendSlotAllocator::createAllocator(size_t size, const char *name) {
  unknown08 = mtl::MemManager::allocate(ml::MlMem::getDebugMem(), size + EXTEND_UNKNOWN_32768, 0x10, false, "no name", 0);
  m_ALLOC_HANDLE = mtl::MemManager::create(unknown08, size + EXTEND_UNKNOWN_32768, name, true);
  // __LINE__ must be 891 as in the original source: it is the line argument of operator new.
#line 891
  m_slotAllocator = new (getAllocator(ALLOCATOR_UNKNOWN_10), __FILE__, __LINE__, 8) GfSlotAllocator();
  m_slotAllocator->setupSizeAlloc(name, mtl::MemManager::getAllocator(m_ALLOC_HANDLE), size, SLOT_UNKNOWN_8192, false);
}

void GfSlotMapping::ExtendSlotAllocator::destroyAllocator() {
  if (m_slotAllocator != nullptr) {
    delete m_slotAllocator;
    m_slotAllocator = nullptr;
  }

  if (m_ALLOC_HANDLE.isValid()) {
    mtl::MemManager::erase(m_ALLOC_HANDLE);
    m_ALLOC_HANDLE = mtl::ALLOC_HANDLE();
  }

  if (unknown08 != nullptr) {
    mtl::MemManager::deallocate(unknown08, 0, false);
    unknown08 = nullptr;
  }
}

bool GfSlotMapping::BiggerPrio::operator()(REQ &request, REQ &other) const { return request.m_assetPack->unknown250 > other.m_assetPack->unknown250; }

} // namespace gf
