#include "gf/map/gf_map_manager.h"

#include "framework/render/render_param.h"
#include "framework/wind/wind_factory.h"
#include "framework/wind/wind_manager.h"
#include "fw/fw_update_info.h"
#include "gf/asset/gf_asset_def.h"
#include "gf/asset/gf_asset_manager.h"
#include "gf/asset/gf_asset_pack.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/object/component/model/gf_com_model.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/request/gf_scom.h"
#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {

static bool isSeamlessMap(GF_OBJ_HANDLE *handle) { return mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->unknown30)->unknown75; }

GfMapManager::GfMapManager(const GfSetupParam &param) : unknown18(false), m_gfObjHandle(unknown020), m_mapJumpID(0), m_mapID(0), m_GF_ASSET_HANDLE(unknown018) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_UNKNOWN_0);
}

void GfMapManager::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  unknown18 = true;
}

GfMapManager::~GfMapManager() { GfObjManager::removeListener(this); }

void GfMapManager::build(const GfSetupParam &param) {
  // __LINE__ must be 71 as in the original file: its value changes the instruction order.
#line 71
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfMapManager(param);
}

void GfMapManager::destroy() {
  GfMapManager *mapManager = get();
  mapManager->finalize();
  delete mapManager;
}

void GfMapManager::finalize() {
  GfObjUtil::destroy(m_gfObjHandle);
  while (m_gfObjHandle != unknown020) {
    GfSleep(1);
  }
  GfEvent::removeEventCallback(this);
  unknown18 = false;
}

bool GfMapManager::isInitialized() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->unknown18 : false;
}

void GfMapManager::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (objectType != OBJECT_TYPE_MAP) {
    return;
  }

  switch (event) {
  case OBJEVT_UNKNOWN_1:
    setupMapHandle(handle);
    break;
  case OBJEVT_UNKNOWN_2:
    buildMapData(handle);
    break;
  case OBJEVT_UNKNOWN_3:
    destroyMapData(handle);
    break;
  case OBJEVT_UNKNOWN_4:
    resetMapHandle(handle);
    break;
  default:
    break;
  }
}

void GfMapManager::setupMapHandle(GF_OBJ_HANDLE *handle) {
  if (isSeamlessMap(handle)) {
    m_gfObjHandle = handle;
  }
}

void GfMapManager::buildMapData(GF_OBJ_HANDLE *handle) {
  GfMapManager *mapManager = get();
  if (!isSeamlessMap(handle)) {
    return;
  }

  mapManager->m_GF_ASSET_HANDLE = GfObjUtil::getAssetHandle(mapManager->m_gfObjHandle);
  mapManager->createIdColi();
  mapManager->createNavi();
  mapManager->createEffect();
  mapManager->createGlobalIBL();
  mapManager->createLocalIBL();
  mapManager->createWind();
}

void GfMapManager::destroyMapData(GF_OBJ_HANDLE *handle) {
  if (!isSeamlessMap(handle)) {
    return;
  }

  GfEvent::callGameMapModel(handle, false);
  m_mapJumpID = 0;
  m_mapID = 0;
  m_GF_ASSET_HANDLE = unknown018;
  destoryWind();
  destroyLocalIBL();
  destroyGlobalIBL();
  destroyEffect();
  destroyNavi();
  destroyIdColi();
}

void GfMapManager::resetMapHandle(GF_OBJ_HANDLE *handle) {
  if (isSeamlessMap(handle)) {
    m_gfObjHandle = unknown020;
  }
}

void GfMapManager::createIdColi() { m_mapColi.create(m_GF_ASSET_HANDLE); }

void GfMapManager::destroyIdColi() { m_mapColi.destroy(); }

void GfMapManager::createNavi() { m_mapNavi.create(m_GF_ASSET_HANDLE); }

void GfMapManager::destroyNavi() { m_mapNavi.destroy(); }

void GfMapManager::createEffect() { m_mapEff.create(m_GF_ASSET_HANDLE, getModelObject()); }

fw::ModelObject *GfMapManager::getModelObject() {
  GfObj *obj = GfObjUtil::getObj(get()->m_gfObjHandle);
  if (obj != nullptr) {
    GfComModel *model = obj->getComponent<GfComModel>();
    if (model != nullptr) {
      return model->unknown18;
    }
  }
  return nullptr;
}

void GfMapManager::destroyEffect() { m_mapEff.destroy(); }

void GfMapManager::createGlobalIBL() { m_mapGIBL.create(m_GF_ASSET_HANDLE); }

void GfMapManager::destroyGlobalIBL() { m_mapGIBL.destroy(); }

void GfMapManager::createLocalIBL() { m_mapLIBL.create(m_GF_ASSET_HANDLE); }

void GfMapManager::destroyLocalIBL() { m_mapLIBL.destroy(); }

GF_OBJ_HANDLE *GfMapManager::getGfObjHandle() { return get()->m_gfObjHandle; }

void GfMapManager::destroyObj() {
  if (get()->m_gfObjHandle != unknown020) {
    GfObjUtil::destroy(get()->m_gfObjHandle);
  }
}

bool GfMapManager::isMapReady() {
  GfMapManager *mapManager = get();
  if (mapManager == nullptr || GfReqSmallCom::isExistCommand(SCOM_TYPE_CREATE_MAP_OBJ)) {
    return false;
  }

  if (mapManager->m_gfObjHandle == unknown020) {
    return mapManager->m_mapJumpID == 0 || mapManager->m_mapJumpID == static_cast<u32>(-1);
  }

  if (mapManager->m_mapColi.unknown00 == nullptr) {
    return false;
  }
  return mapManager->m_mapEff.unknown00;
}

bool GfMapManager::isExistObj() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->m_gfObjHandle != unknown020 : false;
}

u32 GfMapManager::getMapJumpID() { return get()->m_mapJumpID; }

u32 GfMapManager::getMapID() { return get()->m_mapID; }

fw::EffectPack *GfMapManager::getEffectPack() { return get()->m_mapEff.m_effectPack; }

void GfMapManager::setEnvTime(u32 hour, u32 minute) { fw::RenderParam::setTime(hour, minute, fw::CAMERA_TYPE_UNKNOWN_0); }

void GfMapManager::setEnvWeather(u32 weatherType) { fw::RenderParam::setWeather(weatherType, fw::CAMERA_TYPE_UNKNOWN_0); }

void GfMapManager::setGlobalIBLReferencePos(const mm::Vec3 &position) {
  if (get() != nullptr) {
    get()->m_mapGIBL.setReferencePos(position);
  }
}

void GfMapManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  switch (event) {
  case GEV_UNKNOWN_4:
    m_mapJumpID = info.unknown00;
    m_mapID = info.unknown04;
    break;
  case GEV_UNKNOWN_2:
    if (m_mapID != info.unknown04) {
      m_mapEff.destroyEffefct();
    }
    break;
  default:
    break;
  }
}

const char *GfMapManager::getMapName() {
  if (get()->m_mapID != 0) {
    u32 name = GfBdatMaplist::get()->getMaplistnameID(get()->m_mapID);
    if (name != 0) {
      return GfBdatMsg::getNameMapInfo(name);
    }
  }
  return "";
}

const char *GfMapManager::getAssetName() {
  const char *name = "";
  if (get()->m_GF_ASSET_HANDLE != unknown018) {
    GfAssetPack *pack = GfAssetManager::getAssetPack(get()->m_GF_ASSET_HANDLE, FILE_IDX_UNKNOWN_0);
    if (pack != nullptr) {
      name = pack->m_assetType.getFileName(FILE_IDX_UNKNOWN_0).c_str();
    }
  }
  return name;
}

void GfMapManager::createWind() {
  mm::Vec3 max;
  mm::Vec3 min;
  idcoli::IDColiAccMan accMan;
  if (accMan.getGrandAABB(max, min)) {
    unknown38 = fw::WindFactory::createWindResource(min, max);
  } else {
    unknown38 = fw::WindFactory::createWindResource(mm::Vec3(-10000.0f, -10000.0f, -10000.0f), mm::Vec3(10000.0f, 10000.0f, 10000.0f));
  }

  fw::WindManager *windManager = fw::WindManager::get();
  if (windManager != nullptr) {
    windManager->buildWorld(&unknown38->m_resWind);
    windManager->setGlobalWind(0);
  }
}

void GfMapManager::destoryWind() {
  if (fw::WindManager::get() != nullptr) {
    fw::WindManager::get()->destroyWorld();
  }
  unknown38 = nullptr;
}

void GfMapManager::updateMapSpeed(const fw::UpdateInfo &info) {
  f32 speed = GfGameManager::getFieldSpeed(info);
  GfObjAcc(m_gfObjHandle).setFrameSpeed(speed);
}

GfAssetResource *GfMapManager::getModelResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->m_gfObjHandle), FILE_IDX_UNKNOWN_0, ASSET_TYPE_UNKNOWN_0); }

fw::ColiObject *GfMapManager::getColiObject() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->m_mapColi.unknown00 : nullptr;
}

GfAssetResource *GfMapManager::getColiResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->m_gfObjHandle), MAP_FILE_IDX_UNKNOWN_1, ASSET_TYPE_UNKNOWN_0); }

bool GfMapManager::isColisionExist() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->m_mapColi.unknown00 != nullptr : false;
}

void GfMapManager::postUpdate(const fw::UpdateInfo &info) {
  fw::UpdateInfo mapInfo = info;
  mapInfo.unknown04 = mapInfo.unknown00 * GfGameManager::getFieldSpeed(info);
  mapInfo.unknown08 = GfGameManager::getFieldSpeed(info);
  m_mapEff.update(mapInfo);
}

void GfMapManager::update(const fw::UpdateInfo &info) {
  f32 speed = GfGameManager::getFieldSpeed(info);
  GfObjAcc(m_gfObjHandle).setFrameSpeed(speed);
}

} // namespace gf
