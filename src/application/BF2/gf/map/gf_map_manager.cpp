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
#include "idcoli/idcoli.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {

static bool isSeamlessMap(GF_OBJ_HANDLE *handle) { return mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->setup)->isSeamless; }

GfMapManager::GfMapManager(const GfSetupParam &param) : initialized(false), mapHandle(INVALID_HANDLE), mapJumpId(0), mapId(0), assetHandle(INVALID_ASSET_HANDLE) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfMapManager::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  initialized = true;
}

GfMapManager::~GfMapManager() { GfObjManager::removeListener(this); }

void GfMapManager::build(const GfSetupParam &param) {
  // __LINE__ must be 71 as in the original file: its value changes the instruction order.
#line 71
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfMapManager(param);
}

void GfMapManager::destroy() {
  GfMapManager *mapManager = get();
  mapManager->finalize();
  delete mapManager;
}

void GfMapManager::finalize() {
  GfObjUtil::destroy(mapHandle);
  while (mapHandle != INVALID_HANDLE) {
    GfSleep(1);
  }
  GfEvent::removeEventCallback(this);
  initialized = false;
}

bool GfMapManager::isInitialized() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->initialized : false;
}

void GfMapManager::listenerGfObj(OBJEVT event, GF_OBJ_HANDLE *handle, u32 objectType) {
  if (objectType != OBJECT_TYPE_MAP) {
    return;
  }

  switch (event) {
  case OBJEVT_ENTRY:
    setupMapHandle(handle);
    break;
  case OBJEVT_LOADED:
    buildMapData(handle);
    break;
  case OBJEVT_DESTROY:
    destroyMapData(handle);
    break;
  case OBJEVT_REMOVE:
    resetMapHandle(handle);
    break;
  default:
    break;
  }
}

void GfMapManager::setupMapHandle(GF_OBJ_HANDLE *handle) {
  if (isSeamlessMap(handle)) {
    mapHandle = handle;
  }
}

void GfMapManager::buildMapData(GF_OBJ_HANDLE *handle) {
  GfMapManager *mapManager = get();
  if (!isSeamlessMap(handle)) {
    return;
  }

  mapManager->assetHandle = GfObjUtil::getAssetHandle(mapManager->mapHandle);
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
  mapJumpId = 0;
  mapId = 0;
  assetHandle = INVALID_ASSET_HANDLE;
  destoryWind();
  destroyLocalIBL();
  destroyGlobalIBL();
  destroyEffect();
  destroyNavi();
  destroyIdColi();
}

void GfMapManager::resetMapHandle(GF_OBJ_HANDLE *handle) {
  if (isSeamlessMap(handle)) {
    mapHandle = INVALID_HANDLE;
  }
}

void GfMapManager::createIdColi() { coli.create(assetHandle); }

void GfMapManager::destroyIdColi() { coli.destroy(); }

void GfMapManager::createNavi() { navi.create(assetHandle); }

void GfMapManager::destroyNavi() { navi.destroy(); }

void GfMapManager::createEffect() { effect.create(assetHandle, getModelObject()); }

fw::ModelObject *GfMapManager::getModelObject() {
  GfObj *obj = GfObjUtil::getObj(get()->mapHandle);
  if (obj != nullptr) {
    GfComModel *model = obj->getComponent<GfComModel>();
    if (model != nullptr) {
      return model->modelObject;
    }
  }
  return nullptr;
}

void GfMapManager::destroyEffect() { effect.destroy(); }

void GfMapManager::createGlobalIBL() { globalIbl.create(assetHandle); }

void GfMapManager::destroyGlobalIBL() { globalIbl.destroy(); }

void GfMapManager::createLocalIBL() { localIbl.create(assetHandle); }

void GfMapManager::destroyLocalIBL() { localIbl.destroy(); }

GF_OBJ_HANDLE *GfMapManager::getGfObjHandle() { return get()->mapHandle; }

void GfMapManager::destroyObj() {
  if (get()->mapHandle != INVALID_HANDLE) {
    GfObjUtil::destroy(get()->mapHandle);
  }
}

bool GfMapManager::isMapReady() {
  GfMapManager *mapManager = get();
  if (mapManager == nullptr || GfReqSmallCom::isExistCommand(SCOM_TYPE_CREATE_MAP_OBJ)) {
    return false;
  }

  if (mapManager->mapHandle == INVALID_HANDLE) {
    return mapManager->mapJumpId == 0 || mapManager->mapJumpId == static_cast<u32>(-1);
  }

  if (mapManager->coli.coliObject == nullptr) {
    return false;
  }
  return mapManager->effect.isInitialized;
}

bool GfMapManager::isExistObj() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->mapHandle != INVALID_HANDLE : false;
}

u32 GfMapManager::getMapJumpID() { return get()->mapJumpId; }

u32 GfMapManager::getMapID() { return get()->mapId; }

fw::EffectPack *GfMapManager::getEffectPack() { return get()->effect.effectPack; }

void GfMapManager::setEnvTime(u32 hour, u32 minute) { fw::RenderParam::setTime(hour, minute, fw::CAMERA_TYPE_MAIN); }

void GfMapManager::setEnvWeather(u32 weatherType) { fw::RenderParam::setWeather(weatherType, fw::CAMERA_TYPE_MAIN); }

void GfMapManager::setGlobalIBLReferencePos(const mm::Vec3 &position) {
  if (get() != nullptr) {
    get()->globalIbl.setReferencePos(position);
  }
}

void GfMapManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  switch (event) {
  case GEV_MAPJUMP_CHANGE_MAP:
    mapJumpId = info.mapJumpId;
    mapId = info.map;
    break;
  case GEV_MAPJUMP_DESTROY_FIELD:
    if (mapId != info.map) {
      effect.destroyEffefct();
    }
    break;
  default:
    break;
  }
}

const char *GfMapManager::getMapName() {
  if (get()->mapId != 0) {
    u32 name = GfBdatMaplist::get()->getMaplistnameID(get()->mapId);
    if (name != 0) {
      return GfBdatMsg::getNameMapInfo(name);
    }
  }
  return "";
}

const char *GfMapManager::getAssetName() {
  const char *name = "";
  if (get()->assetHandle != INVALID_ASSET_HANDLE) {
    GfAssetPack *pack = GfAssetManager::getAssetPack(get()->assetHandle, FILE_IDX_MODEL);
    if (pack != nullptr) {
      name = pack->files.getFileName(FILE_IDX_MODEL).c_str();
    }
  }
  return name;
}

void GfMapManager::createWind() {
  mm::Vec3 max;
  mm::Vec3 min;
  idcoli::IDColiAccMan accMan;
  if (accMan.getGrandAABB(max, min)) {
    windResource = fw::WindFactory::createWindResource(min, max);
  } else {
    windResource = fw::WindFactory::createWindResource(mm::Vec3(-10000.0f, -10000.0f, -10000.0f), mm::Vec3(10000.0f, 10000.0f, 10000.0f));
  }

  fw::WindManager *windManager = fw::WindManager::get();
  if (windManager != nullptr) {
    windManager->buildWorld(&windResource->resWind);
    windManager->setGlobalWind(0);
  }
}

void GfMapManager::destoryWind() {
  if (fw::WindManager::get() != nullptr) {
    fw::WindManager::get()->destroyWorld();
  }
  windResource = nullptr;
}

void GfMapManager::updateMapSpeed(const fw::UpdateInfo &info) {
  f32 speed = GfGameManager::getFieldSpeed(info);
  GfObjAcc(mapHandle).setFrameSpeed(speed);
}

GfAssetResource *GfMapManager::getModelResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->mapHandle), FILE_IDX_MODEL, ASSET_TYPE_BASE); }

fw::ColiObject *GfMapManager::getColiObject() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->coli.coliObject : nullptr;
}

GfAssetResource *GfMapManager::getColiResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->mapHandle), MAP_FILE_IDX_COLLISION, ASSET_TYPE_BASE); }

bool GfMapManager::isColisionExist() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->coli.coliObject != nullptr : false;
}

void GfMapManager::postUpdate(const fw::UpdateInfo &info) {
  fw::UpdateInfo mapInfo = info;
  mapInfo.deltaTime = mapInfo.frameTime * GfGameManager::getFieldSpeed(info);
  mapInfo.speed = GfGameManager::getFieldSpeed(info);
  effect.update(mapInfo);
}

void GfMapManager::update(const fw::UpdateInfo &info) {
  f32 speed = GfGameManager::getFieldSpeed(info);
  GfObjAcc(mapHandle).setFrameSpeed(speed);
}

} // namespace gf
