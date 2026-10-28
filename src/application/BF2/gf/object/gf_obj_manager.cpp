#include "gf/object/gf_obj_manager.h"

#include "gf/asset/gf_asset_multi_bind.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"

namespace gf {

GfObjManager *GfObjManager::s_pThis;
mm::mtl::FixedList<GfObjManager::ObjListener, 256> GfObjManager::m_aListenerObj;

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
    if (it->unknown08 == IGfObjListener::OBJEVT_ALL || it->unknown08 == event) {
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

bool GfObjManager::isSuspendUpdate() const { return unknown484a28; }

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
  if (handle != INVALID_HANDLE) {
    GfObjAcc acc(handle);
    if (acc.testFlag(OBJ_FLAG_LOADED_WAIT)) {
      acc.setFlag(OBJ_FLAG_LOADED_WAIT_OK, true);
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
  return unknown484538 == 0;
}

bool GfObjManager::hasReloadObjForDebug() { return false; }

void GfObjManager::addHandle(GF_OBJ_HANDLE *handle) { setStateLoading(handle); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfObjManager>::~PtrSingleton();
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 4096>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 2048>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 1024>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 256>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 64>::iterator);
template mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::erase(mm::mtl::FixedList<gf::GF_OBJ_HANDLE *, 32>::iterator);
template mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::iterator mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::erase(mm::mtl::FixedList<gf::GfAssetMultiBind *, 64>::iterator);
