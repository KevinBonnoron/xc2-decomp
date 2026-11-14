#include "gf/asset/gf_asset_manager.h"

#include <new>
#include <string.h>

#include "gf/asset/gf_asset_pack.h"
#include "gf/asset/gf_asset_resource.h"
#include "gf/asset/gf_file_size_pool.h"
#include "gf/asset/gf_slot_mapping.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/object/gf_obj_handle.h"
#include "ml/win_view.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_list.h" // IWYU pragma: keep
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/reference_object.h"
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace gf {

constexpr u32 ASSET_HANDLE_UNKNOWN_1023 = 1023;       // Inferred role: mask of the pool index kept in the low bits of an asset handle; original name unknown.
constexpr u32 ASSET_HANDLE_UNKNOWN_1048575 = 1048575; // Inferred role: serial of an asset handle that is skipped; original name unknown.

GfAssetManager::GfAssetManager(const GfSetupParam &param) : unknowndb918(0), m_slotMapping(nullptr), unknowne04c0(false), unknowne04c1(false) { initialize(param); }

void GfAssetManager::initialize(const GfSetupParam &param) {
#line 100
  m_slotMapping = new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfSlotMapping();
  param.unknown08->attachWorkEvent(this, false);
  size_t size = mtl::MemManager::maxAllocSize(getAllocator(ALLOCATOR_UNKNOWN_3)->getMemHandle()) & ~static_cast<size_t>(0x1fff);
  m_slotMapping->setup(param, getAllocator(ALLOCATOR_UNKNOWN_3), size);
  GfFileSizePool::build(param);
  unknowne04c0 = true;
}

GfAssetManager::~GfAssetManager() {}

void GfAssetManager::build(const GfSetupParam &param) {
#line 68
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfAssetManager(param);
}

void GfAssetManager::destroy() {
  GfAssetManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfAssetManager::finalize() {
  unknowne04c1 = true;
  GfFileSizePool::destroy();
  while (unknownce0b8.size() != 0) {
    GfSleep(1);
  }
  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = unknownd70f8.begin(); it != unknownd70f8.end(); ++it) {
    AssetPackInfo *info = getAssetPackInfo(*it);
    if (info != nullptr) {
      info->~AssetPackInfo();
      unknown10.unknown004(info);
    }
  }
  unknownd70f8.clear();
  unknownd28d8.clear();
  bool isAllCached;
  do {
    isAllCached = true;
    for (mm::mtl::FixedList<GfAssetPack *, 1024>::iterator it = unknowndb920.begin(); it != unknowndb920.end(); ++it) {
      if (!(*it)->isCached()) {
        isAllCached = false;
        GfSleep(1);
        break;
      }
    }
  } while (!isAllCached);
  for (mm::mtl::FixedList<GfAssetPack *, 1024>::iterator it = unknowndb920.begin(); it != unknowndb920.end(); ++it) {
    (*it)->releaseResource();
  }
  GfSleep(5);
  for (mm::mtl::FixedList<GfAssetPack *, 1024>::iterator it = unknowndb920.begin(); it != unknowndb920.end(); ++it) {
    mm::mtl::safeRelease(*it);
  }
  unknowndb920.clear();
  m_slotMapping->destroy();
  GfManager::getSetupParam().unknown08->detachWorkEvent(this);
  if (m_slotMapping != nullptr) {
    delete m_slotMapping;
    m_slotMapping = nullptr;
  }
  unknowne04c0 = false;
}

bool GfAssetManager::isInitialized() {
  if (get() != nullptr) {
    return get()->unknowne04c0;
  }
  return false;
}

AssetPackInfo *GfAssetManager::getAssetPackInfo(GF_ASSET_HANDLE *handle) {
  GfAssetManager *manager = get();
  u32 index = reinterpret_cast<u64>(handle) & ASSET_HANDLE_UNKNOWN_1023;
  AssetPackInfo *info = &manager->unknown10.unknown007[index];
  return manager->unknown10.unknown010(index) ? info : nullptr;
}

void GfAssetManager::destroy(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr && !info->unknown304) {
    info->setDestroy();
    GfAssetManager *manager = get();
    mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = mm::mtl::find(manager->unknownd70f8.begin(), manager->unknownd70f8.end(), handle);
    if (it == manager->unknownd70f8.end()) {
      it = mm::mtl::find(manager->unknownce0b8.begin(), manager->unknownce0b8.end(), handle);
      if (it == manager->unknownce0b8.end()) {
        return;
      }
    }
    manager->unknownd28d8.push_back(*it);
  }
}

void GfAssetManager::setNoCacheAsset(GF_ASSET_HANDLE *handle, bool noCache) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->setNoCache(noCache);
  }
}

void GfAssetManager::enableGameResource(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr && !info->unknown305) {
    info->setUsingGame(true);
  }
}

void GfAssetManager::disableGameResource(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr && info->unknown305) {
    info->setUsingGame(false);
  }
}

GF_ASSET_HANDLE *GfAssetManager::createAssetHandle(const GfInitParam &) {
  GfAssetManager *manager = get();
  u32 index = 0;
  AssetPackInfo *info = new (manager->unknown10.unknown003(&index)) AssetPackInfo;
  u32 serial = manager->unknowndb918++;
  if (serial >= ASSET_HANDLE_UNKNOWN_1048575) {
    serial = manager->unknowndb918++;
  }
  GF_ASSET_HANDLE *handle = reinterpret_cast<GF_ASSET_HANDLE *>(static_cast<u64>((index & ASSET_HANDLE_UNKNOWN_1023) | serial << 10));
  info->unknown08 = handle;
  manager->unknownce0b8.push_back(handle);
  return handle;
}

GfAssetPack *GfAssetManager::createAssetFiles(const GfAssetFilesInfo &info) {
  GfAssetManager *manager = get();
  u64 value = GfAssetPack::calcAssetPackValue(info.unknown30, info.unknown08);
  GfAssetPack *pack = nullptr;
  for (GfAssetPack *other : manager->unknowndb920) {
    if (other->unknown10 == value && !other->unknown238) {
      if (info.unknown00 == unknown018) {
        return nullptr;
      }
      pack = other;
      break;
    }
  }
  if (pack == nullptr) {
    pack = GfAssetPack::create(info);
    manager->unknowndb920.push_back(pack);
    pack->addRef();
  }
  AssetPackInfo *packInfo = getAssetPackInfo(info.unknown00);
  if (packInfo != nullptr) {
    packInfo->setAssetPack(info.unknown08, pack);
    packInfo->unknown300 = info.unknown38;
  }
  if (info.unknown08 != ASSET_TYPE_UNKNOWN_0 && pack->isNeedLoad()) {
    manager->m_slotMapping->requestSlotLoad(info.unknown00, pack);
  }
  callEventAssetPack(pack);
  return pack;
}

void GfAssetManager::loadStart(GfAssetPack *pack, mm::mtl::IAllocator *allocator) { pack->loadStart(allocator); }

void GfAssetManager::callEventAssetPack(GfAssetPack *pack) {
  for (IGfAssetEvent *event : get()->unknowne0280) {
    event->unknown001(pack);
  }
}

void GfAssetManager::releaseSlotHandle(GF_SLOT_HANDLE *handle) { get()->m_slotMapping->releaseSlot(handle); }

GfAssetPack *GfAssetManager::getAssetPack(GF_SLOT_HANDLE *handle) {
  for (GfAssetPack *pack : get()->unknowndb920) {
    if (pack->unknown230 == handle) {
      return pack;
    }
  }
  return nullptr;
}

GfAssetPack *GfAssetManager::getAssetPack(GF_ASSET_HANDLE *handle, GfFileIdx index) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return nullptr;
  }
  return info->getAssetPack(index);
}

GfAssetPack *GfAssetManager::getAssetPack(GfAssetType type, const char *name) {
  for (GfAssetPack *&pack : get()->unknowndb920) {
    if (strcmp(pack->getAssetName(), name) == 0) {
      return pack;
    }
  }
  return nullptr;
}

bool GfAssetManager::getAssetPack(mm::mtl::FixedVector<GfAssetPack *, 256> &packs, GfAssetType type) {
  for (GfAssetPack *&pack : get()->unknowndb920) {
    if (pack->getAssetType() == type) {
      packs.push_back(pack);
    }
  }
  return packs.size() != 0;
}

GfAssetPack *GfAssetManager::getAssetPack(GF_ASSET_HANDLE *handle, GfAssetType type) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return nullptr;
  }
  return info->getAssetPackByAssetType(type);
}

GfAssetType GfAssetManager::getBaseAssetType(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return ASSET_TYPE_UNKNOWN_0;
  }
  return info->unknown308;
}

GfSlotMapping *GfAssetManager::getSlotMapping() {
  GfAssetManager *manager = get();
  if (manager != nullptr) {
    return manager->m_slotMapping;
  }
  return nullptr;
}

GfAssetResource *GfAssetManager::getResource(GF_ASSET_HANDLE *handle, GfFileIdx index, GfAssetType type) {
  GfAssetResource *resource = nullptr;
  if (handle != unknown018 && index != FILE_IDX_UNKNOWN_FFFFFFFF) {
    AssetPackInfo *info = getAssetPackInfo(handle);
    if (info != nullptr) {
      resource = info->getResource(index);
    }
    if (resource != nullptr) {
      resource = resource->isValidData() ? resource : nullptr;
    }
  }
  return resource;
}

GfAssetResource *GfAssetManager::getResource(GF_ASSET_HANDLE *handle, const char *name, GfFileIdx index) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    GfAssetPack *pack = info->getAssetPack(name);
    if (pack != nullptr) {
      return pack->getResource(index);
    }
  }
  return nullptr;
}

GF_ASSET_HANDLE *GfAssetManager::getAssetHandle(const char *name) {
  GfAssetManager *manager = get();
  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = manager->unknownd70f8.begin(); it != manager->unknownd70f8.end(); ++it) {
    AssetPackInfo *info = getAssetPackInfo(*it);
    if (info == nullptr) {
      continue;
    }

    if (info->getAssetPack(name) != nullptr) {
      return *it;
    }
  }

  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = manager->unknownce0b8.begin(); it != manager->unknownce0b8.end(); ++it) {
    AssetPackInfo *info = getAssetPackInfo(*it);
    if (info == nullptr) {
      continue;
    }

    if (info->getAssetPack(name) != nullptr) {
      return *it;
    }
  }

  return unknown018;
}

bool GfAssetManager::isLoading() { return get()->unknownce0b8.size() > 0; }

bool GfAssetManager::isLoading(const GfAssetPack *pack) {
  mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> *list = getLoadingAsset();
  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = list->begin(); it != list->end(); ++it) {
    AssetPackInfo *info = getAssetPackInfo(*it);
    if (info == nullptr) {
      continue;
    }

    if (info->isExistAssetPack(pack)) {
      return true;
    }
  }

  return false;
}

u32 GfAssetManager::getTimeout(GF_ASSET_HANDLE *handle) {
  if (handle == unknown018) {
    return 0;
  }
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return 0;
  }
  return info->unknown334;
}

bool GfAssetManager::isLoaded(GF_ASSET_HANDLE *handle, mm::mtl::FixStr<128> *name) {
  bool loaded = true;
  if (handle != unknown018) {
    AssetPackInfo *info = getAssetPackInfo(handle);
    if (info != nullptr) {
      if (!info->isLoaded(name)) {
        loaded = false;
      } else {
        loaded = !info->unknown307;
      }
    }
  }
  return loaded;
}

void GfAssetManager::setupStreamObject(GF_ASSET_HANDLE *handle) {
  if (handle != unknown018) {
    AssetPackInfo *info = getAssetPackInfo(handle);
    if (info != nullptr) {
      info->setupStreamObject();
    }
  }
}

bool GfAssetManager::isStopLoad(GF_ASSET_HANDLE *handle) {
  if (handle != unknown018) {
    AssetPackInfo *info = getAssetPackInfo(handle);
    if (info != nullptr) {
      return info->isStopLoad();
    }
  }
  return true;
}

bool GfAssetManager::isDestroy(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->unknown304;
}

bool GfAssetManager::isReload(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->unknown307;
}

GF_OBJ_HANDLE *GfAssetManager::getObj(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return unknown020;
  }
  return info->unknown2d8;
}

bool GfAssetManager::isExist(GF_ASSET_HANDLE *handle, GfFileIdx index) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->isExist(index);
}

void GfAssetManager::setExtendResource(GF_ASSET_HANDLE *handle, u32 index, GfExtendResource *resource) { getAssetPackInfo(handle)->setExtendResource(index, resource); }

void GfAssetManager::destroySlotCache(GfAssetType type) {
  mm::mtl::FixedList<u32, 32> &types = get()->unknowne0140;
  mm::mtl::FixedList<u32, 32>::iterator it = mm::mtl::find(types.begin(), types.end(), type);
  if (it == types.end()) {
    types.push_back(type);
  }
}

GfExtendResource *GfAssetManager::getExtentResource(GF_ASSET_HANDLE *handle, u32 index) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return nullptr;
  }
  return info->unknown2e0[index];
}

void GfAssetManager::destroyExtResource(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->releaseExtResource();
  }
}

bool GfAssetManager::isSameAsset(GF_ASSET_HANDLE *handle, GF_ASSET_HANDLE *other) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    AssetPackInfo *otherInfo = getAssetPackInfo(other);
    if (otherInfo != nullptr) {
      return info->isUseSameAsset(otherInfo);
    }
  }
  return false;
}

void GfAssetManager::addEvent(IGfAssetEvent *event) { get()->unknowne0280.push_back(event); }

void GfAssetManager::removeEvent(IGfAssetEvent *event) {
  mm::mtl::FixedList<IGfAssetEvent *, 32> &events = get()->unknowne0280;
  mm::mtl::FixedList<IGfAssetEvent *, 32>::iterator it = mm::mtl::find(events.begin(), events.end(), event);
  if (events.end() != it) {
    events.erase(it);
  }
}

bool GfAssetManager::isExistSameAsset(GfAssetPack *pack) {
  for (GfAssetPack *other : get()->unknowndb920) {
    if (other != pack && other->unknown10 == pack->unknown10 && other->isExistSameAsset(*pack)) {
      return true;
    }
  }
  return false;
}

bool GfAssetManager::isExistSameAsset(GF_ASSET_HANDLE *handle, const char *name) {
  if (name == nullptr) {
    return false;
  }
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->getAssetPack(name) != nullptr;
}

void GfAssetManager::clear() { destroySlotCache(ASSET_TYPE_UNKNOWN_0); }

u64 GfAssetManager::getTimeStamp(const char *name, GfAssetType type) {
  for (GfAssetPack *&pack : get()->unknowndb920) {
    if (type == ASSET_TYPE_UNKNOWN_0 || pack->getAssetType() == type) {
      u64 timeStamp = pack->getTimeStamp(name);
      if (timeStamp != 0) {
        return timeStamp;
      }
    }
  }
  return 0;
}

size_t GfAssetManager::getSlotBlockSize(GfAssetType type) { return get()->m_slotMapping->getSlotBlockSize(type); }

u32 GfAssetManager::getSlotNumByByteSize(GfAssetType type, size_t size) { return get()->m_slotMapping->getSlotNumByByteSize(type, size); }

bool GfAssetManager::isExistOuterResource() {
  for (GfAssetPack *pack : get()->unknowndb920) {
    if (pack->isExistReferenceMemory()) {
      return true;
    }
  }
  return false;
}

mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> *GfAssetManager::getLoadingAsset() { return &get()->unknownce0b8; }

bool GfAssetManager::getObjectByUsingAssetPackLocal(mm::mtl::FixedList<GF_OBJ_HANDLE *, 1024> &objects, const mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024> &handles, GF_ASSET_HANDLE *handle) const {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  for (GF_ASSET_HANDLE *other : handles) {
    if (other != handle) {
      AssetPackInfo *otherInfo = getAssetPackInfo(other);
      if (otherInfo != nullptr) {
        otherInfo->getReloadObjectByUsingAssetPack(objects, info);
      }
    }
  }
  return objects.size() != 0;
}

bool GfAssetManager::getSlotHandle(mm::mtl::FixedVector<GF_SLOT_HANDLE *, 88> &slots, GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->getSlotHandle(slots);
}

GF_SLOT_HANDLE *GfAssetManager::allocateFromAssetTypeSlot(GfAssetType type, size_t size) {
  GfAssetManager *manager = get();
  if (manager != nullptr && manager->m_slotMapping != nullptr) {
    return manager->m_slotMapping->allocateSlot(type, size);
  }
  return reinterpret_cast<GF_SLOT_HANDLE *>(-1);
}

bool GfAssetManager::getSlotInfo(mm::mtl::IAllocator *&allocator, void *&buffer, size_t &size, GF_SLOT_HANDLE *handle) {
  GfAssetManager *manager = get();
  if (manager != nullptr && manager->m_slotMapping != nullptr) {
    return manager->m_slotMapping->getSlotInfo(allocator, buffer, size, handle);
  }
  return true;
}

void GfAssetManager::setModelInfo(GF_ASSET_HANDLE *handle, const char *name) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->setModelName(name);
  }
}

bool GfAssetManager::isFullResource(GF_ASSET_HANDLE *handle) const {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return false;
  }
  return info->isFullResource();
}

fw::SoundPack *GfAssetManager::getSePackByFileIdx(GF_ASSET_HANDLE *handle, GfFileIdx index) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info == nullptr) {
    return nullptr;
  }
  return info->getSePackByFileIdx(index);
}

u32 GfAssetManager::getUsedAssetPackInfo() {
  if (get() != nullptr) {
    return get()->unknown10.unknown009;
  }
  return 0;
}

u32 GfAssetManager::getDestroyAssetPackInfo() {
  if (get() != nullptr) {
    return get()->unknownd28d8.size();
  }
  return 0;
}

const char *GfAssetManager::getModelInfo(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    return info->unknown30c.c_str();
  }
  return "";
}

void GfAssetManager::setMotionInfo(GF_ASSET_HANDLE *handle, const char *name) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->setMotionName(name);
  }
}

const char *GfAssetManager::getMotionInfo(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    return info->unknown320.c_str();
  }
  return "";
}

void GfAssetManager::releaseRefResource(void *data) {
  for (GfAssetPack *pack : unknowndb920) {
    if (pack->releaseRefResource(data)) {
      return;
    }
  }
}

void GfAssetManager::setupLoadStart(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->setupLoadStart();
  }
}

void GfAssetManager::lockEnterRersource(GF_ASSET_HANDLE *handle) {
  AssetPackInfo *info = getAssetPackInfo(handle);
  if (info != nullptr) {
    info->lockEnterRersource();
  }
}

void GfAssetManager::updateCheckLoading() {
  for (mm::mtl::FixedList<GfAssetPack *, 1024>::iterator it = unknowndb920.begin(); it != unknowndb920.end(); ++it) {
    if (!(*it)->isPreSizeSizeValid()) {
      (*it)->applyPreFileSize();
    }
  }

  for (mm::mtl::FixedList<GF_ASSET_HANDLE *, 1024>::iterator it = unknownce0b8.begin(); it != unknownce0b8.end();) {
    AssetPackInfo *info = getAssetPackInfo(*it);
    if (info == nullptr) {
      it = unknownce0b8.erase(it);
    } else if (info->unknown304) {
      unknownd70f8.push_back(*it);
      it = unknownce0b8.erase(it);
    } else if (info->isLoaded(nullptr) && info->isPreSizeSizeValid()) {
      info->releaseEmptySlot();
      info->setLoadComplete();
      unknownd70f8.push_back(*it);
      it = unknownce0b8.erase(it);
    } else {
      ++it;
    }
  }
}

void GfAssetManager::update(const fw::UpdateInfo &info) {
  if (GfFileSizePool::get() != nullptr) {
    GfFileSizePool::get()->update();
  }
  getSlotMapping()->update(info);
  updateCheckLoading();
  updateCheckDestroy();
  updateCheckCacheReload();
}

} // namespace gf

template mm::mtl::FixedList<gf::GF_ASSET_HANDLE *, 1024>::iterator mm::mtl::FixedList<gf::GF_ASSET_HANDLE *, 1024>::erase(mm::mtl::FixedList<gf::GF_ASSET_HANDLE *, 1024>::iterator);

template mm::mtl::PtrSingleton<gf::GfAssetManager>::~PtrSingleton();

template mm::mtl::FixedList<gf::IGfAssetEvent *, 32>::iterator mm::mtl::FixedList<gf::IGfAssetEvent *, 32>::erase(mm::mtl::FixedList<gf::IGfAssetEvent *, 32>::iterator it);
