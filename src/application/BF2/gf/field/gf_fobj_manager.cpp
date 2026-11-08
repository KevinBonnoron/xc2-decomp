#include "gf/field/gf_fobj_manager.h"

#include "bdat.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_event.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_dropitem_params.h"
#include "gf/field/gf_fobj_dropitem.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_bdat.h"

namespace gf {

constexpr u32 DROPITEM_ITEM_MAX = 1024;
constexpr u32 GOTTEN_EFFECT_COUNT = 32;
constexpr int WILDCARD_FOBJ_SE_INTERVAL_ROW = 68;
constexpr int WILDCARD_FOBJ_SE_MAX_ROW = 69;

GfFobjManager::GfFobjManager(const GfSetupParam &param)
    : unknown9058(false), unknown9060(nullptr), unknown9068(nullptr), unknown9070(nullptr), unknown9078(true), unknown907c(0.0f), unknown9080(false), unknown9088(nullptr), unknown90d0(nullptr) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfFobjManager::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  if (unknown9060 != nullptr) {
    delete unknown9060;
    unknown9060 = nullptr;
  }
  unknown9060 = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfDropitemParams();
  GfFobjGottenEffectManager::CreateInfo effectInfo;
  effectInfo.unknown00 = GOTTEN_EFFECT_COUNT;
  unknown9088.create(effectInfo);
  u8 *bdat = GfDataBdat::getFP(BDAT_FLD_WILDCARD_DATA);
  GfFobjSeManager::CreateInfo seInfo;
  seInfo.unknown00 = Bdat::getValCheck(bdat, 0, WILDCARD_FOBJ_SE_INTERVAL_ROW, gmk::BDAT_TYPE_F32).valueF32;
  seInfo.unknown04 = Bdat::getValCheck(bdat, 1, WILDCARD_FOBJ_SE_MAX_ROW, gmk::BDAT_TYPE_U16).valueU16;
  unknown90d0.create(seInfo);
  unknown9058 = true;
}

GfFobjManager::~GfFobjManager() { GfObjManager::removeListener(this); }

void GfFobjManager::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFobjManager(param); }

void GfFobjManager::destroy() {
  GfFobjManager *manager = get();
  manager->finalize();
  delete manager;
}

void GfFobjManager::finalize() {
  unknown90d0.dispose();
  unknown9088.dispose();
  for (auto it = unknown18.begin(); it != unknown18.end(); ++it) {
    GfObjUtil::destroy((*it)->unknown10);
  }
  for (auto it = unknown4838.begin(); it != unknown4838.end(); ++it) {
    GfObjUtil::destroy((*it)->unknown10);
  }
  while (unknown18.size() != 0 || unknown4838.size() != 0) {
    GfSleep(1);
  }
  if (unknown9060 != nullptr) {
    delete unknown9060;
    unknown9060 = nullptr;
  }
  GfEvent::removeEventCallback(this);
  unknown9058 = false;
}

bool GfFobjManager::isInitialized() {
  GfFobjManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown9058;
  }
  return false;
}

void GfFobjManager::update(const fw::UpdateInfo &info) {
  GfFobjManager *manager = get();
  if (manager != nullptr && manager->unknown9058) {
    if (manager->unknown9068 == nullptr) {
      manager->unknown9068 = Bdat::isExistFP("RSC_dropitemList");
    }
    if (manager->unknown9070 == nullptr) {
      manager->unknown9070 = Bdat::isExistFP("RSC_dropitemParam");
    }
    if (manager->unknown9078) {
      for (auto it = manager->unknown4838.begin(); it != manager->unknown4838.end(); ++it) {
        (*it)->update(info);
      }
    }
    if (manager->unknown9060 != nullptr) {
      manager->unknown9060->update();
    }
    manager->unknown9088.update(info.unknown04);
    manager->unknown90d0.update(info.unknown04);
  }
}

GfDropitemParams *GfFobjManager::getDropitemParams() {
  GfFobjManager *manager = get();
  if (manager != nullptr) {
    return manager->unknown9060;
  }
  return nullptr;
}

void GfFobjManager::debugRecreateBdat_dropitem() {
  GfFobjManager *manager = get();
  if (manager != nullptr) {
    manager->unknown9070 = nullptr;
    manager->unknown9068 = nullptr;
    if (manager->unknown9060 != nullptr) {
      manager->unknown9060->dispose();
    }
  }
}

void GfFobjManager::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (objectType == OBJECT_TYPE_FOBJ) {
    if (event == OBJEVT_LOADED) {
      for (auto it = unknown18.begin(); it != unknown18.end(); ++it) {
        GfFobjDropitem *dropitem = *it;
        if (dropitem->unknown10 == handle) {
          if (unknown4838.size() == DROPITEM_ITEM_MAX) {
            GF_OBJ_HANDLE *oldest = unknown4838.front()->unknown10;
            GfObjUtil::destroy(oldest);
            leaveGameField(oldest);
          }
          unknown4838.push_back(*it);
          unknown18.erase(it);
          dropitem->initialize();
          return;
        }
      }
    } else if (event == OBJEVT_DESTROY) {
      leaveGameField(handle);
    }
  }
}

void GfFobjManager::leaveGameField(GF_OBJ_HANDLE *handle) {
  for (auto it = unknown18.begin(); it != unknown18.end(); ++it) {
    if ((*it)->unknown10 == handle) {
      (*it)->destroy();
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      unknown18.erase(it);
      break;
    }
  }
  for (auto it = unknown4838.begin(); it != unknown4838.end(); ++it) {
    if ((*it)->unknown10 == handle) {
      (*it)->destroy();
      if (*it != nullptr) {
        delete *it;
        *it = nullptr;
      }
      unknown4838.erase(it);
      return;
    }
  }
}

void GfFobjManager::registFiledObj(GfFobjDropitem *dropitem) {
  GfFobjManager *manager = get();
  if (manager->unknown18.size() == DROPITEM_ITEM_MAX) {
    GF_OBJ_HANDLE *oldest = manager->unknown18.front()->unknown10;
    GfObjUtil::destroy(oldest);
    manager->leaveGameField(oldest);
  }
  manager->unknown18.push_back(dropitem);
}

bool GfFobjManager::isExistObj() {
  GfFobjManager *manager = get();
  if (manager->unknown18.size() != 0) {
    return true;
  }

  return manager->unknown4838.size() != 0;
}

void GfFobjManager::destroyObj() {
  GfFobjManager *manager = get();
  for (auto it = manager->unknown18.begin(); it != manager->unknown18.end(); ++it) {
    GfObjUtil::destroy((*it)->unknown10);
  }
  for (auto it = manager->unknown4838.begin(); it != manager->unknown4838.end(); ++it) {
    GfObjUtil::destroy((*it)->unknown10);
  }
}

void GfFobjManager::gevPlayEvent(GEV event, u32 value) {
  if (GfDataEvent::getEventType(value) != 1) {
    if (event == GEV_EVENT_END) {
      unknown9078 = false;
    } else if (event == GEV_EVENT_PLAY_END) {
      unknown9078 = true;
    }
    for (auto it = unknown18.begin(); it != unknown18.end(); ++it) {
      (*it)->setEventDisp(unknown9078);
    }
    for (auto it = unknown4838.begin(); it != unknown4838.end(); ++it) {
      (*it)->setEventDisp(unknown9078);
    }
  }
}

void GfFobjManager::gevGameObjLeave(GF_OBJ_HANDLE *handle) { leaveGameField(handle); }

} // namespace gf

template mm::mtl::PtrSingleton<gf::GfFobjManager>::~PtrSingleton();
