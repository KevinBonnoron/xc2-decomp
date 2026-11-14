#include "gf/object/gf_obj_manager.h"

#include "framework/framework.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_multi_bind.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_util.h"
#include "ml/fixed_size_alloc.h"
#include "mm_mtl/algorithm.h"

namespace gf {

GfObjManager *GfObjManager::s_pThis;
mm::mtl::FixedList<GfObjManager::ObjListener, 256> GfObjManager::m_aListenerObj;

// Inferred helper: object info of a handle without the checks of getObjInfo; original name unknown.
static GFOBJ_INFO *unknown001(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *infos = GfObjManager::s_pThis->unknown18.unknown007;
  GFOBJ_INFO *info = &infos[reinterpret_cast<u64>(handle) & 0xfff];
  return info->unknown08 == handle ? info : nullptr;
}

// Inferred role: capacity of each object type, -1 when unlimited; original table name unknown.
static const int unknown042[] = {
    // Inferred role: gfobj capacities; original name unknown.
    -1,
    -1,
    -1,
    -1,
    -1,
    40,
    32,
    64,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
    -1,
};

GfObjManager::~GfObjManager() { s_pThis = nullptr; }

void GfObjManager::build(const GfSetupParam &param) {
  // __LINE__ must be 81 as in the original file: it is the line argument of the allocation.
#line 81
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfObjManager(param);
}

void GfObjManager::destroy() {
  s_pThis->finalize();
  if (s_pThis != nullptr) {
    delete s_pThis;
    s_pThis = nullptr;
  }
  GfSleep(10);
}

void GfObjManager::finalize() {
  requestDestroyAll();
  while (unknown420240.size() != 0 || unknown432260.size() != 0 || unknown44d2a0.size() != 0 || unknown483320.size() != 0) {
    GfSleep(1);
  }
  GfObjLayerSpeed::finalize();
  GfEvent::removeEventCallback(this);
  unknown10 = false;
}

void GfObjManager::update(const fw::UpdateInfo &info) {
  checkLoadingAndCreate(unknown020);
  checkTerminate();
  applyModelLayerPauseSpeed();
}

void GfObjManager::postUpdate(const fw::UpdateInfo &info) {
  updateLayerPauseObjects(info);
  updateFirstObjects(info);
  updateChangeParamObjects(info);
  GfObjLayerSpeed::cleanup();
}

bool GfObjManager::reloadForDebug(GF_OBJ_HANDLE *, bool) { return false; }

void GfObjManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  if (event == GEV_UNKNOWN_2) {
    unknown484a28 = true;
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
      GfObjUtil::applyExecUpdate(*it);
    }
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
      GfObjUtil::applyExecUpdate(*it);
    }
  } else if (event == GEV_UNKNOWN_6) {
    unknown484a28 = false;
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
      GfObjUtil::applyExecUpdate(*it);
    }
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
      GfObjUtil::applyExecUpdate(*it);
    }
  }
}

void GfObjManager::addListener(IGfObjListener *listener, IGfObjListener::OBJEVT event) {
  ObjListener objListener = {listener, event};
  m_aListenerObj.push_back(objListener);
}

void GfObjManager::removeListener(IGfObjListener *listener) {
  for (mm::mtl::FixedList<ObjListener, 256>::iterator it = m_aListenerObj.begin(); it != m_aListenerObj.end(); ++it) {
    if (it->unknown00 == listener) {
      m_aListenerObj.erase(it);
      return;
    }
  }
}

void GfObjManager::callGfObjListener(IGfObjListener::OBJEVT event, GF_OBJ_HANDLE *handle) {
  u32 objectType = GfObjUtil::getObjType(handle);
  for (mm::mtl::FixedList<ObjListener, 256>::iterator it = m_aListenerObj.begin(); it != m_aListenerObj.end(); ++it) {
    if (it->unknown08 == IGfObjListener::OBJEVT_UNKNOWN_0 || it->unknown08 == event) {
      it->unknown00->listenerGfObj(event, handle, objectType);
    }
  }
}

void GfObjManager::addApplyParam(GF_OBJ_HANDLE *handle) { addApplyParamObj(GfObjUtil::getObj(handle)); }

bool GfObjManager::isInitialized() {
  if (s_pThis != nullptr) {
    return s_pThis->unknown10;
  }
  return false;
}

int GfObjManager::getObjectNum(u32 objectType) { return s_pThis->unknown484540[objectType]; }

int GfObjManager::getGfObjCapacity(u32 objectType) {
  if (objectType >= sizeof(unknown042) / sizeof(unknown042[0])) {
    return -1;
  }
  if (objectType == OBJECT_TYPE_MOB && get() != nullptr && !GfGameManager::isPlayEvent()) {
    return get()->unknown484a2c;
  }
  return unknown042[objectType];
}

GFOBJ_INFO *GfObjManager::getObjInfo(GF_OBJ_HANDLE *handle) {
  if (s_pThis == nullptr) {
    return nullptr;
  }
  u32 index = reinterpret_cast<u64>(handle) & 0xfff;
  GFOBJ_INFO *info = &s_pThis->unknown18.unknown007[index];
  if (s_pThis->unknown18.unknown010(index)) {
    if (info->unknown08 == handle) {
      return info;
    }
    return nullptr;
  }
  return nullptr;
}

void GfObjManager::updateFirstObjects(const fw::UpdateInfo &info) {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown43b280.begin(); it != unknown43b280.end(); ++it) {
    GFOBJ_INFO *objInfo = getObjInfo(*it);
    if (objInfo != nullptr) {
      objInfo->unknown38.set(OBJ_FLAG_UNKNOWN_19, true);
    }
  }
  unknown43b280.clear();
}

bool GfObjManager::isSuspendUpdate() const { return unknown484a28; }

GF_OBJ_HANDLE *GfObjManager::getExistFixedObj(int index) const {
  u32 slot = index;
  if (slot >= 0x100) {
    return unknown020;
  }
  if (unknown18.unknown010(slot)) {
    return unknown18.unknown007[slot].unknown08;
  }
  return unknown020;
}

const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *GfObjManager::getLoadingObj() const { return &unknown420240; }

const mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096> *GfObjManager::getDestroyObj() const { return &unknown44d2a0; }

u32 GfObjManager::createGfObjHandle(const GFOBJ_INFO *info, u32 index, int multiBind) {
  u32 generation;
  if (multiBind < 0) {
    u32 current = s_pThis->unknown14;
    u32 next = unknown14 + 1;
    u32 stored = unknown14 + 1;
    generation = current << 12;
    if (next > 0xffffd) {
      stored = 0;
      generation = 0;
    }
    unknown14 = stored;
  } else {
    generation = 0xfffff000;
  }
  return generation | (index & 0xfff);
}

void GfObjManager::enterStayObject(GF_OBJ_HANDLE *handle) {
  if (handle != unknown020) {
    GfObjAcc acc(handle);
    if (acc.testFlag(OBJ_FLAG_UNKNOWN_8)) {
      acc.setFlag(OBJ_FLAG_UNKNOWN_9, true);
      s_pThis->checkLoadingAndCreate(handle);
    }
  }
}

void GfObjManager::requestDestroyAll() {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    GfObjUtil::destroy(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    GfObjUtil::destroy(*it);
  }
}

bool GfObjManager::isExistGfObj(bool isIgnoreMap) const {
  if (isIgnoreMap) {
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::const_iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
      GfObjAcc acc(*it);
      if (acc.getType() != OBJECT_TYPE_MAP) {
        return true;
      }
    }
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::const_iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
      GfObjAcc acc(*it);
      if (acc.getType() != OBJECT_TYPE_MAP) {
        return true;
      }
    }
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::const_iterator it = unknown44d2a0.begin(); it != unknown44d2a0.end(); ++it) {
      GfObjAcc acc(*it);
      if (acc.getType() != OBJECT_TYPE_MAP) {
        return true;
      }
    }
    return false;
  }
  if (unknown44d2a0.size() != 0) {
    return true;
  }
  if (unknown420240.size() != 0) {
    return true;
  }
  return unknown432260.size() != 0;
}

bool GfObjManager::isExistLayerObj(u32 layer) const {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::const_iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    if (GfObjUtil::getObjLayer(*it) == layer) {
      return true;
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::const_iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    if (GfObjUtil::getObjLayer(*it) == layer) {
      return true;
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::const_iterator it = unknown44d2a0.begin(); it != unknown44d2a0.end(); ++it) {
    if (GfObjUtil::getObjLayer(*it) == layer) {
      return true;
    }
  }
  return false;
}

void GfObjManager::destroyLayerObj(u32 layer) {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    if (GfObjUtil::getObjLayer(*it) == layer) {
      GfObjUtil::destroy(*it);
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    if (GfObjUtil::getObjLayer(*it) == layer) {
      GfObjUtil::destroy(*it);
    }
  }
}

void GfObjManager::destroyAllObj(bool isIgnoreMap) {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    GfObjAcc acc(*it);
    if (!isIgnoreMap || acc.getType() != OBJECT_TYPE_MAP) {
      GfObjUtil::destroy(*it);
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    GfObjAcc acc(*it);
    if (!isIgnoreMap || acc.getType() != OBJECT_TYPE_MAP) {
      GfObjUtil::destroy(*it);
    }
  }
}

void GfObjManager::getObjList(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs) {
  objs.clear();
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    objs.push_back(*it);
  }
}

bool GfObjManager::isValidMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) const {
  if (uniqId == 0) {
    return true;
  }
  for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::const_iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
    if ((*it)->unknown488 == uniqId) {
      return (*it)->isValid();
    }
  }
  return false;
}

GfAssetMultiBind *GfObjManager::getAssetMultiBind(u32 uniqId) const {
  for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::const_iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
    if ((*it)->unknown488 == uniqId) {
      return *it;
    }
  }
  return nullptr;
}

GfAssetMultiBind *GfObjManager::getMultiBinder(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
      GfAssetMultiBind *multiBind = *it;
      if (multiBind->unknown488 == acc.getMultiBindUniqId()) {
        return multiBind;
      }
    }
  }
  return nullptr;
}

void GfObjManager::loadedMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) {
  if (uniqId != 0) {
    for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
      if ((*it)->unknown488 == uniqId) {
        (*it)->loadedAsset(handle);
        return;
      }
    }
  }
}

void GfObjManager::unloadedMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) {
  if (uniqId != 0) {
    for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
      if ((*it)->unknown488 == uniqId) {
        (*it)->unloadedAsset(handle);
        return;
      }
    }
  }
}

void GfObjManager::destroyMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId) {
  if (uniqId != 0) {
    for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
      if ((*it)->unknown488 == uniqId) {
        if (!(*it)->unbind(handle)) {
          return;
        }
        if ((*it)->unknown08.size() != 0) {
          return;
        }
        if (*it != nullptr) {
          delete *it;
          *it = nullptr;
        }
        unknown484560.erase(it);
        return;
      }
    }
  }
}

void GfObjManager::createGfObjProperty(GF_OBJ_HANDLE *handle) {
  GFOBJ_INFO *info = getObjInfo(handle);
  if (info != nullptr && info->unknown98 == nullptr) {
    info->unknown98 = GfObjProperty::create(handle);
  }
}

bool GfObjManager::isEmptyObj() const {
  if (unknown420240.size() != 0) {
    return false;
  }
  if (unknown432260.size() != 0) {
    return false;
  }
  if (unknown44d2a0.size() != 0) {
    return false;
  }
  return unknown483320.size() == 0;
}

bool GfObjManager::hasReloadObjForDebug() { return false; }

void GfObjManager::addHandle(GF_OBJ_HANDLE *handle) { setStateLoading(handle); }

void GfObjManager::setStateLoading(GF_OBJ_HANDLE *handle) {
  unknown001(handle)->unknown06 = GFOBJ_STATE_UNKNOWN_1;
  if (mm::mtl::find(unknown420240.begin(), unknown420240.end(), handle) != unknown420240.end()) {
    return;
  }
  unknown420240.push_back(handle);
  GfAssetManager::setupLoadStart(GfObjUtil::getAssetHandle(handle));
}

void GfObjManager::setStateUpdate(GF_OBJ_HANDLE *handle) {
  unknown001(handle)->unknown06 = GFOBJ_STATE_UNKNOWN_2;
  unknown432260.push_back(handle);
  unknown43b280.push_back(handle);
}

void GfObjManager::setStateDestroy(GF_OBJ_HANDLE *handle) {
  unknown001(handle)->unknown06 = GFOBJ_STATE_UNKNOWN_3;
  unknown44d2a0.push_back(handle);
}

bool GfObjManager::isFinishLoadState(GfObjAcc &acc, bool unknown) {
  loadedMultiBind(acc.getHandle(), acc.getMultiBindUniqId());
  if (!isValidMultiBind(acc.getHandle(), acc.getMultiBindUniqId()) && !unknown) {
    return false;
  }
  if (!acc.isLoadedWaitOK()) {
    return false;
  }
  if (acc.isLayerPause()) {
    acc.setDisp(OBJDISP_UNKNOWN_2, false);
    acc.applyDisp();
  }
  return true;
}

bool GfObjManager::getWaitingMultiBindObj(mm::mtl::FixedList<GF_OBJ_HANDLE *, 768> &objs, u32 uniqId) const {
  for (mm::mtl::FixedList<GfAssetMultiBind *, 64>::const_iterator it = unknown484560.begin(); it != unknown484560.end(); ++it) {
    GfAssetMultiBind *multiBind = *it;
    if (multiBind->unknown488 == uniqId) {
      for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator bound = multiBind->unknown08.begin(); bound != multiBind->unknown08.end(); ++bound) {
        objs.push_back(*bound);
      }
      return objs.size() != 0;
    }
  }
  return false;
}

void GfObjManager::setMultiBind(GF_OBJ_HANDLE *handle, u32 uniqId, u32 count, bool flag) {
  GFOBJ_INFO *info = getObjInfo(handle);
  GfAssetMultiBind *multiBind = getAssetMultiBind(uniqId);
  if (multiBind == nullptr) {
    // __LINE__ must be 1233 as in the original file: it is the line argument of the allocation.
#line 1233
    multiBind = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) GfAssetMultiBind(uniqId, flag);
    unknown484560.push_back(multiBind);
  }
  multiBind->unknown48c = count;
  multiBind->bind(handle);
  info->unknown00 = uniqId;
}

void GfObjManager::addFollowObj(GF_OBJ_HANDLE *handle) {
  if (mm::mtl::find(unknown483320.begin(), unknown483320.end(), handle) == unknown483320.end()) {
    unknown483320.push_back(handle);
  }
}

void GfObjManager::destroyObjAsset(GF_ASSET_HANDLE *asset) {
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    if (GfAssetManager::isSameAsset(unknown001(*it)->unknown10, asset)) {
      GfObjUtil::destroy(*it);
    }
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    if (GfAssetManager::isSameAsset(unknown001(*it)->unknown10, asset)) {
      GfObjUtil::destroy(*it);
    }
  }
}

void GfObjManager::applyModelLayerPauseSpeed() {
  bool isRequest = false;
  for (u32 layer = 0; layer < fw::Framework::LAYER_UNKNOWN_32; layer++) {
    if (GfObjLayerSpeed::isRequest(layer)) {
      isRequest = true;
      break;
    }
  }
  if (isRequest) {
    for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
      GfObjAcc acc(*it);
      if (GfObjLayerSpeed::isRequest(acc.getLayer())) {
        acc.setFrameSpeed(GfObjLayerSpeed::getSpeed(acc.getLayer()));
      }
    }
  }
}

void GfObjManager::getObjListForDebug(mm::mtl::FixedList<GF_OBJ_HANDLE *, 1024> &objs) {
  objs.clear();
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 2048>::iterator it = unknown432260.begin(); it != unknown432260.end(); ++it) {
    objs.push_back(*it);
  }
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 4096>::iterator it = unknown420240.begin(); it != unknown420240.end(); ++it) {
    objs.push_back(*it);
  }
}

void GfObjManager::addDestroyObj(GF_OBJ_HANDLE *handle, bool flag) {
  GfObjAcc acc(handle);
  if (acc.isValid()) {
    if (mm::mtl::find(unknown4712e0.begin(), unknown4712e0.end(), handle) == unknown4712e0.end()) {
      if (mm::mtl::find(unknown44d2a0.begin(), unknown44d2a0.end(), handle) == unknown44d2a0.end()) {
        unknown4712e0.push_back(handle);
        GfAssetManager::isReload(acc.getAssetHandle());
        if (!acc.isRebuild()) {
          checkDeleteFollowObj(handle);
        }
        if (flag) {
          GfAssetMultiBind *multiBind = getMultiBinder(handle);
          if (multiBind != nullptr && !multiBind->unknown494) {
            for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 32>::iterator bound = multiBind->unknown08.begin(); bound != multiBind->unknown08.end(); ++bound) {
              GfObjUtil::destroy(*bound);
            }
          }
        }
      }
    }
  }
}

void GfObjManager::checkDeleteFollowObj(GF_OBJ_HANDLE *handle) {
  GfObjAcc acc(handle);
  GFOBJ_INFO *info = getObjInfo(handle);
  bool isReload = GfAssetManager::isReload(acc.getAssetHandle());
  for (mm::mtl::FixedList<GF_OBJ_HANDLE *, 256>::iterator it = unknown483320.begin(); it != unknown483320.end(); ++it) {
    GFOBJ_INFO *follow = getObjInfo(*it);
    if (follow->unknown88 == handle && info->unknown18 != GfObjUtil::getParentObj(follow->unknown18) && !isReload) {
      GfObjUtil::destroy(*it);
    }
  }
}

} // namespace gf

template class ml::fixed_size_alloc_inside<gf::GFOBJ_INFO, 4096>;
template mm::mtl::PtrSingleton<gf::GfObjManager>::~PtrSingleton();
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator);
template mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::iterator mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::erase(mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::iterator);
