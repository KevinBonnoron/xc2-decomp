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

static bool isSeamlessMap(GF_OBJ_HANDLE *handle) { return mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->unknown30)->unknown75; }

GfMapManager::GfMapManager(const GfSetupParam &param) : unknown18(false), unknown20(INVALID_HANDLE), unknown28(0), unknown2c(0), unknown30(INVALID_ASSET_HANDLE) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfMapManager::initialize(const GfSetupParam &) {
  GfEvent::addEventCallback(this);
  unknown18 = true;
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
  GfObjUtil::destroy(unknown20);
  while (unknown20 != INVALID_HANDLE) {
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
    unknown20 = handle;
  }
}

void GfMapManager::buildMapData(GF_OBJ_HANDLE *handle) {
  GfMapManager *mapManager = get();
  if (!isSeamlessMap(handle)) {
    return;
  }

  mapManager->unknown30 = GfObjUtil::getAssetHandle(mapManager->unknown20);
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
  unknown28 = 0;
  unknown2c = 0;
  unknown30 = INVALID_ASSET_HANDLE;
  destoryWind();
  destroyLocalIBL();
  destroyGlobalIBL();
  destroyEffect();
  destroyNavi();
  destroyIdColi();
}

void GfMapManager::resetMapHandle(GF_OBJ_HANDLE *handle) {
  if (isSeamlessMap(handle)) {
    unknown20 = INVALID_HANDLE;
  }
}

void GfMapManager::createIdColi() { unknown58.create(unknown30); }

void GfMapManager::destroyIdColi() { unknown58.destroy(); }

void GfMapManager::createNavi() { unknown50.create(unknown30); }

void GfMapManager::destroyNavi() { unknown50.destroy(); }

void GfMapManager::createEffect() { unknown40.create(unknown30, getModelObject()); }

fw::ModelObject *GfMapManager::getModelObject() {
  GfObj *obj = GfObjUtil::getObj(get()->unknown20);
  if (obj != nullptr) {
    GfComModel *model = obj->getComponent<GfComModel>();
    if (model != nullptr) {
      return model->unknown18;
    }
  }
  return nullptr;
}

void GfMapManager::destroyEffect() { unknown40.destroy(); }

void GfMapManager::createGlobalIBL() { unknown60.create(unknown30); }

void GfMapManager::destroyGlobalIBL() { unknown60.destroy(); }

void GfMapManager::createLocalIBL() { unknown68.create(unknown30); }

void GfMapManager::destroyLocalIBL() { unknown68.destroy(); }

GF_OBJ_HANDLE *GfMapManager::getGfObjHandle() { return get()->unknown20; }

void GfMapManager::destroyObj() {
  if (get()->unknown20 != INVALID_HANDLE) {
    GfObjUtil::destroy(get()->unknown20);
  }
}

bool GfMapManager::isMapReady() {
  GfMapManager *mapManager = get();
  if (mapManager == nullptr || GfReqSmallCom::isExistCommand(SCOM_TYPE_CREATE_MAP_OBJ)) {
    return false;
  }

  if (mapManager->unknown20 == INVALID_HANDLE) {
    return mapManager->unknown28 == 0 || mapManager->unknown28 == static_cast<u32>(-1);
  }

  if (mapManager->unknown58.unknown00 == nullptr) {
    return false;
  }
  return mapManager->unknown40.unknown00;
}

bool GfMapManager::isExistObj() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->unknown20 != INVALID_HANDLE : false;
}

u32 GfMapManager::getMapJumpID() { return get()->unknown28; }

u32 GfMapManager::getMapID() { return get()->unknown2c; }

fw::EffectPack *GfMapManager::getEffectPack() { return get()->unknown40.unknown08; }

void GfMapManager::setEnvTime(u32 hour, u32 minute) { fw::RenderParam::setTime(hour, minute, fw::CAMERA_TYPE_MAIN); }

void GfMapManager::setEnvWeather(u32 weatherType) { fw::RenderParam::setWeather(weatherType, fw::CAMERA_TYPE_MAIN); }

void GfMapManager::setGlobalIBLReferencePos(const mm::Vec3 &position) {
  if (get() != nullptr) {
    get()->unknown60.setReferencePos(position);
  }
}

void GfMapManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  switch (event) {
  case GEV_MAPJUMP_CHANGE_MAP:
    unknown28 = info.unknown00;
    unknown2c = info.unknown04;
    break;
  case GEV_MAPJUMP_DESTROY_FIELD:
    if (unknown2c != info.unknown04) {
      unknown40.destroyEffefct();
    }
    break;
  default:
    break;
  }
}

const char *GfMapManager::getMapName() {
  if (get()->unknown2c != 0) {
    u32 name = GfBdatMaplist::get()->getMaplistnameID(get()->unknown2c);
    if (name != 0) {
      return GfBdatMsg::getNameMapInfo(name);
    }
  }
  return "";
}

const char *GfMapManager::getAssetName() {
  const char *name = "";
  if (get()->unknown30 != INVALID_ASSET_HANDLE) {
    GfAssetPack *pack = GfAssetManager::getAssetPack(get()->unknown30, FILE_IDX_MODEL);
    if (pack != nullptr) {
      name = pack->m_assetType.getFileName(FILE_IDX_MODEL).c_str();
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
    windManager->buildWorld(&unknown38->resWind);
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
  GfObjAcc(unknown20).setFrameSpeed(speed);
}

GfAssetResource *GfMapManager::getModelResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->unknown20), FILE_IDX_MODEL, ASSET_TYPE_BASE); }

fw::ColiObject *GfMapManager::getColiObject() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->unknown58.unknown00 : nullptr;
}

GfAssetResource *GfMapManager::getColiResource() { return GfAssetManager::getResource(GfObjUtil::getAssetHandle(get()->unknown20), MAP_FILE_IDX_COLLISION, ASSET_TYPE_BASE); }

bool GfMapManager::isColisionExist() {
  GfMapManager *mapManager = get();
  return mapManager != nullptr ? mapManager->unknown58.unknown00 != nullptr : false;
}

void GfMapManager::postUpdate(const fw::UpdateInfo &info) {
  fw::UpdateInfo mapInfo = info;
  mapInfo.deltaTime = mapInfo.frameTime * GfGameManager::getFieldSpeed(info);
  mapInfo.speed = GfGameManager::getFieldSpeed(info);
  unknown40.update(mapInfo);
}

void GfMapManager::update(const fw::UpdateInfo &info) {
  f32 speed = GfGameManager::getFieldSpeed(info);
  GfObjAcc(unknown20).setFrameSpeed(speed);
}

} // namespace gf
