#include "gf/asset/gf_asset_manager.h"

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
#include "mtl/alloc_handle.h"
#include "mtl/mem_manager.h"

namespace gf {

GfAssetManager::GfAssetManager(const GfSetupParam &param) : unknowndb918(0), m_slotMapping(nullptr), unknowne04c0(false), unknowne04c1(false) { initialize(param); }

void GfAssetManager::initialize(const GfSetupParam &param) {
#line 100
  m_slotMapping = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfSlotMapping();
  param.unknown08->attachWorkEvent(this, false);
  size_t size = mtl::MemManager::maxAllocSize(getAllocator(ALLOCATOR_ASSET)->getMemHandle()) & ~static_cast<size_t>(0x1fff);
  m_slotMapping->setup(param, getAllocator(ALLOCATOR_ASSET), size);
  GfFileSizePool::build(param);
  unknowne04c0 = true;
}

GfAssetManager::~GfAssetManager() {}

void GfAssetManager::build(const GfSetupParam &param) {
#line 68
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfAssetManager(param);
}

void GfAssetManager::destroy() {
  GfAssetManager *manager = get();
  manager->finalize();
  delete manager;
}

bool GfAssetManager::isInitialized() {
  if (get() != nullptr) {
    return get()->unknowne04c0;
  }
  return false;
}

AssetPackInfo *GfAssetManager::getAssetPackInfo(GF_ASSET_HANDLE *handle) {
  GfAssetManager *manager = get();
  u32 index = reinterpret_cast<u64>(handle) & 0x3ff;
  AssetPackInfo *info = &manager->unknown10.unknown007[index];
  return manager->unknown10.unknown010(index) ? info : nullptr;
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
    return ASSET_TYPE_BASE;
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
  if (handle != INVALID_ASSET_HANDLE && index != FILE_IDX_NONE) {
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

bool GfAssetManager::isLoading() { return get()->unknownce0b8.size() > 0; }

u32 GfAssetManager::getTimeout(GF_ASSET_HANDLE *handle) {
  if (handle == INVALID_ASSET_HANDLE) {
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
  if (handle != INVALID_ASSET_HANDLE) {
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
  if (handle != INVALID_ASSET_HANDLE) {
    AssetPackInfo *info = getAssetPackInfo(handle);
    if (info != nullptr) {
      info->setupStreamObject();
    }
  }
}

bool GfAssetManager::isStopLoad(GF_ASSET_HANDLE *handle) {
  if (handle != INVALID_ASSET_HANDLE) {
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
    return INVALID_HANDLE;
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

void GfAssetManager::clear() { destroySlotCache(ASSET_TYPE_BASE); }

u64 GfAssetManager::getTimeStamp(const char *name, GfAssetType type) {
  for (GfAssetPack *&pack : get()->unknowndb920) {
    if (type == ASSET_TYPE_BASE || pack->getAssetType() == type) {
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
