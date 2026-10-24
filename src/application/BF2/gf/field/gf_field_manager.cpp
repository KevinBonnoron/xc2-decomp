#include "gf/field/gf_field_manager.h"

#include "framework/render/render_param.h"
#include "framework/wind/wind_manager.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/field/gf_field_collect.h"
#include "gf/field/gf_field_dmg.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/field/gf_field_lod.h"
#include "gf/field/gf_field_map_gimmick.h"
#include "gf/field/gf_field_sound.h"
#include "gf/field/gf_field_tbox.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/field/gf_field_zone.h"
#include "gf/field/gf_field_zone_script.h"
#include "gf/field/gf_fobj_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "gf/scom/gf_scom_script.h"
#include "gf/script/gf_script_manager.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_landmark.h"
#include "mm_math/mm_vec3.h"

namespace gf {

GfFieldManager::GfFieldManager(const GfSetupParam &param) : initialized(false), enemyBaloonRadius(0.0f) {
  initialize(param);
  GfObjManager::addListener(this, OBJEVT_ALL);
}

void GfFieldManager::initialize(const GfSetupParam &param) {
  GfEvent::addEventCallback(this);
  GfFieldTime::build(param);
  GfFieldWeather::build(param);
  GfFieldSound::build(param);
  GfFieldZone::build(param);
  GfFieldGimmick::build(param);
  GfFieldCollect::build(param);
  GfFieldTbox::build(param);
  GfFieldMapGimmick::build(param);
  GfFieldGrave::build(param);
  GfFieldJump::build(param);
  GfFieldWarp::build(param);
  GfFieldGmkTutorial::build(param);
  GfFieldLod::build(param);
  GfFobjManager::build(param);
  GfFieldDmgManager::build(param);
  initialized = true;
  SCOM_SCRIPT::create(SCRIPT_SLOT_FIELD_SYSTEM, "field", false);
}

GfFieldManager::~GfFieldManager() { GfObjManager::removeListener(this); }

void GfFieldManager::build(const GfSetupParam &param) {
  // __LINE__ must be 70 as in the original file: its value changes the instruction order.
#line 70
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfFieldManager(param);
}

void GfFieldManager::destroy() {
  GfFieldManager *fieldManager = get();
  fieldManager->finalize();
  delete fieldManager;
}

void GfFieldManager::finalize() {
  if (!GfGameManager::isGameObjEmpty()) {
    GfSleep(1);
  }
  GfFieldDmgManager::destroy();
  GfFobjManager::destroy();
  GfFieldLod::destroy();
  GfFieldGmkTutorial::destroy();
  GfFieldWarp::destroy();
  GfFieldJump::destroy();
  GfFieldGrave::destroy();
  GfFieldMapGimmick::destroy();
  GfFieldTbox::destroy();
  GfFieldCollect::destroy();
  GfFieldGimmick::destroy();
  GfFieldZone::destroy();
  GfFieldSound::destroy();
  GfFieldWeather::destroy();
  GfFieldTime::destroy();
  GfEvent::removeEventCallback(this);
  initialized = false;
}

bool GfFieldManager::isInitialized() {
  GfFieldManager *fieldManager = get();
  return fieldManager != nullptr ? fieldManager->initialized : false;
}

void GfFieldManager::clear() {
  if (GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->clear();
  }
  GfFieldWeather::clear();
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->clear();
  }
  GfFieldLod::validateByInitData();
}

void GfFieldManager::setupGame() {
  if (GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->setupGame();
  }
  GfFieldWeather::setupGame();
}

void GfFieldManager::setSuspendGame(bool isSuspend) {
  if (GfFieldTime::get() != nullptr && !isSuspend) {
    GfFieldTime::get()->saveSuspendRealTime();
  }
}

void GfFieldManager::listenerGfObj(OBJEVT, GF_OBJ_HANDLE *, u32) {}

bool GfFieldManager::isExistObj() { return GfFobjManager::isExistObj(); }

void GfFieldManager::destroyObj() { GfFobjManager::destroyObj(); }

fw::EffectPack *GfFieldManager::getEffectPack() { return GfMapManager::getEffectPack(); }

void GfFieldManager::gevReloadBdat(RELOAD_BDAT reload, u32 value) {
  getFieldParam(GfGameManager::getMapJumpID());
  if (GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->gevReloadBdat(reload, value);
  }
}

void GfFieldManager::getFieldParam(u32 mapJump) {
  u32 map = GfDataMap::getMapID(mapJump);
  if (map != 0) {
    enemyBaloonRadius = GfBdatMaplist::get()->getMapliste_balloondisp_r(map);
  }
}

bool GfFieldManager::execMapScript(const char *script) { return GfFieldZoneScript::execScript(script); }

void GfFieldManager::destroyMapScript() { GfFieldZoneScript::destroyScript(); }

bool GfFieldManager::isExecMapScriptBusy() { return GfFieldZoneScript::isExecScriptBusy(); }

bool GfFieldManager::isDestroyMapScriptBusy() { return GfFieldZoneScript::isDestroyScriptBusy(); }

void GfFieldManager::updateGlobalWind() { fw::RenderParam::setGlobalWindPower(fw::WindManager::getGlobalWindPower(), fw::CAMERA_TYPE_MAIN); }

f32 GfFieldManager::getEnemyBaloonRadius() { return get()->enemyBaloonRadius; }

const char *GfFieldManager::getMapName() { return GfMapManager::getMapName(); }

bool GfFieldManager::getLandmarkNameId(u8 *&bdat, int &textId) {
  gmk::GmkLandmark *landmark = gmk::GmkLandmarkManager::get()->frontLandmark;
  if (landmark != nullptr) {
    bdat = GfDataBdat::getFP(BDAT_FLD_LANDMARK);
    textId = landmark->createInfo.info->id;
    return true;
  }
  return false;
}

void GfFieldManager::setLandmarkPoint(u32 landmark, const mm::Vec3 &position, f32 rotationY) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown04 = landmark;
  dataGame->unknown10 = position;
  dataGame->unknown20 = rotationY;
}

u32 GfFieldManager::getLandmarkPoint() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->unknown04 != 0) {
    return dataGame->unknown04;
  }
  return GfGameManager::getMapJumpID();
}

const mm::Vec3 &GfFieldManager::getLandmarkPos() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown04 == 0 ? mm::Vec3::zero : dataGame->unknown10;
}

f32 GfFieldManager::getLandmarkRotY() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown04 != 0 ? dataGame->unknown20 : 0.0f;
}

void GfFieldManager::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  if (event == GEV_MAPJUMP_CREATE_FIELD) {
    getFieldParam(info.mapJumpId);
  }
  GfFieldZone::get()->gevMapjump(event, info);
  GfFieldLod::get()->gevMapjump(event, info);
  GfFieldMapGimmick::get()->gevMapjump(event, info);
  GfFieldGrave::get()->gevMapjump(event, info);
  GfFieldJump::get()->gevMapjump(event, info);
  GfFieldWarp::get()->gevMapjump(event, info);
  GfFieldGmkTutorial::get()->gevMapjump(event, info);
  GfFieldTbox::get()->gevMapjump(event, info);
  GfFieldCollect::get()->gevMapjump(event, info);
  GfFieldWeather::gevMapjump(event, info);
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->gevMapjump(event, info);
  }
}

void GfFieldManager::gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter) {
  GfFieldWeather::gevGameMapModel(handle, isEnter);
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->gevGameMapModel(handle, isEnter);
  }
}

void GfFieldManager::gevBattleStart() {}

void GfFieldManager::gevBattleEnd() {
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->gevBattleEnd();
  }
}

void GfFieldManager::gevPause(u32 resumeBits, u32 pauseBits) {
  GfFieldWeather::gevPause(resumeBits, pauseBits);
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->gevPause(resumeBits, pauseBits);
  }
}

void GfFieldManager::gevPlayEvent(GEV event, u32 value) {
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->gevPlayEvent(event, value);
  }
  if (GfFieldLod::get() != nullptr) {
    GfFieldLod::get()->gevPlayEvent(event, value);
  }
}

void GfFieldManager::postUpdate(const fw::UpdateInfo &info) {
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->postUpdate(info);
  }
}

void GfFieldManager::update(const fw::UpdateInfo &info) {
  if (GfObjManager::get() != nullptr && GfObjManager::get()->hasReloadObjForDebug()) {
    return;
  }

  if (GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->update(info);
  }
  GfFieldZone::update(info);
  if (GfFieldSound::get() != nullptr) {
    GfFieldSound::get()->update(info);
  }
  GfFieldWeather::update(info);
  if (!GfPause::isPause(PAUSE_BIT_SYSTEM)) {
    GfFobjManager::update(info);
    GfFieldGimmick::update(info);
    GfFieldCollect::update(info);
    GfFieldTbox::update(info);
    if (GfFieldMapGimmick::get() != nullptr) {
      GfFieldMapGimmick::get()->update(info.deltaTime);
    }
    if (GfFieldGrave::get() != nullptr) {
      GfFieldGrave::get()->update(info.deltaTime);
    }
    if (GfFieldJump::get() != nullptr) {
      GfFieldJump::get()->update(info.deltaTime);
    }
    if (GfFieldWarp::get() != nullptr) {
      GfFieldWarp::get()->update(info.deltaTime);
    }
    GfFieldLod::update(info);
  }

  GfFieldTime *fieldTime = GfFieldTime::get();
  if (fieldTime != nullptr) {
    GfMapManager::setEnvTime(fieldTime->getHour(), fieldTime->getMin());
  }
  updateGlobalWind();
}

} // namespace gf
