#include "gf/game/gf_game_env.h"

#include "framework/framework.h"
#include "framework/render/render_param.h"
#include "fw/fw_camera.h"
#include "fw/fw_update_info.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_speed.h"
#include "gf/game/gf_layer_pause.h"
#include "gf/gf_allocator.h"
#include "gf/gf_manager.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/algorithm.h"
#include "nn/oe.h"

namespace gf {
struct GF_LP_HANDLE;

constexpr f32 MIN_LAYER_SPEED = 1e-06f;
constexpr f32 STOP_ENEMY_SEARCH_SEC = 3.0f;
constexpr u8 SCREEN_SHOT_DISABLE_FRAMES = 180;
constexpr int ROOM_COUNT_MAX = 99;

static void applyLayerPause(u32 layer, bool isPause) {
  if (fw::Framework::isLayerPause(layer) != isPause) {
    fw::Framework::setLayerPause(layer, isPause);
    GfObjLayerSpeed::reqApplyModelLayerSpeed(layer, isPause ? 0.0f : 1.0f);
    GfEvent::callLayerPause(layer, isPause);
  }
}

GfLayerPause::GfLayerPause(const GfSetupParam &param)
    : section4PauseBits(0), section1PauseBits(0), section7PauseBits(0), section10PauseBits(0), section0PauseBits(0), section4Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)),
      section0Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)), section1Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)), section7Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)),
      section10Handle(reinterpret_cast<GF_LP_HANDLE *>(-1)) {
  initialize(param);
}

void GfLayerPause::initialize(const GfSetupParam &) { initialized = true; }

GfLayerPause::~GfLayerPause() {}

void GfLayerPause::build(const GfSetupParam &param) {
  // __LINE__ must be 108 as in the original file: its value changes the instruction order.
#line 108
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfLayerPause(param);
}

void GfLayerPause::destroy() {
  GfLayerPause *layerPause = get();
  layerPause->finalize();
  delete layerPause;
}

void GfLayerPause::finalize() { initialized = false; }

bool GfLayerPause::isInitialized() { return get() != nullptr && get()->initialized; }

void GfLayerPause::update(const fw::UpdateInfo &) {}

void GfLayerPause::gevPause(u32 resumeBits, u32 pauseBits) {
  GfLayerPause *layerPause = get();
  if ((resumeBits & PAUSE_BIT_SYSTEM) != 0) {
    destroyLayerPause(layerPause->section4Handle);
    destroyLayerPause(layerPause->section0Handle);
    destroyLayerPause(layerPause->section1Handle);
    destroyLayerPause(layerPause->section7Handle);
  } else if ((pauseBits & PAUSE_BIT_SYSTEM) != 0) {
    layerPause->section4Handle = setLayerPause(4);
    layerPause->section0Handle = setLayerPause(0);
    layerPause->section1Handle = setLayerPause(1);
    layerPause->section7Handle = setLayerPause(7);
  }
  if ((resumeBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    destroyLayerPause(layerPause->section10Handle);
  } else if ((pauseBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    layerPause->section10Handle = setLayerPause(10);
  }
}

void GfLayerPause::destroyLayerPause(GF_LP_HANDLE *&handle) {
  if (handle == reinterpret_cast<GF_LP_HANDLE *>(-1)) {
    return;
  }
  u32 value = reinterpret_cast<u64>(handle);
  u32 index = value >> 8;
  u32 layer = value & 0xff;
  u32 *pauseBits = get()->getPauseBits(layer);
  *pauseBits &= ~(1 << index);
  if (*pauseBits == 0) {
    applyLayerPause(layer, false);
    if (layer != 0) {
      applyLayerPause(layer + 1, false);
      applyLayerPause(layer + 2, false);
    }
  }
  handle = reinterpret_cast<GF_LP_HANDLE *>(-1);
}

GF_LP_HANDLE *GfLayerPause::setLayerPause(u32 layer) {
  u32 *pauseBits = get()->getPauseBits(layer);
  u32 index;
  u32 bit = 1;
  for (index = 0; index < 32; index++) {
    if ((*pauseBits & bit) == 0) {
      break;
    }
    bit <<= 1;
  }
  if (index >= 32) {
    return reinterpret_cast<GF_LP_HANDLE *>(-1);
  }
  *pauseBits |= bit;
  if (layer != 0) {
    applyLayerPause(layer + 1, true);
    applyLayerPause(layer + 2, true);
  }
  applyLayerPause(layer, true);
  return reinterpret_cast<GF_LP_HANDLE *>(static_cast<u64>(layer | index << 8));
}

void GfLayerPause::destroyLayerPause() {
  GfLayerPause *layerPause = get();
  destroyLayerPause(layerPause->section4Handle);
  destroyLayerPause(layerPause->section0Handle);
  destroyLayerPause(layerPause->section1Handle);
  destroyLayerPause(layerPause->section7Handle);
  destroyLayerPause(layerPause->section10Handle);
}

bool GfLayerPause::isLayerPause(u32 layer) { return fw::Framework::isLayerPause(layer); }

GfGameSpeed::GfGameSpeed(const GfSetupParam &param) : intervalSpeed(1.0f), intervalTime(0.0f) { initialize(param); }

void GfGameSpeed::initialize(const GfSetupParam &) { initialized = true; }

GfGameSpeed::~GfGameSpeed() {}

void GfGameSpeed::build(const GfSetupParam &param) {
  // __LINE__ must be 347 as in the original file: its value changes the instruction order.
#line 347
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameSpeed(param);
  setGlobalSpeed(param.globalSpeed);
}

void GfGameSpeed::setGlobalSpeed(f32 speed) { get()->setSpeed(GF_SPEED_GLOBAL, speed); }

void GfGameSpeed::destroy() {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->finalize();
  delete gameSpeed;
}

void GfGameSpeed::finalize() { initialized = false; }

bool GfGameSpeed::isInitialized() { return get() != nullptr && get()->initialized; }

void GfGameSpeed::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->updateFrameSpeed(info);
  }
}

void GfGameSpeed::updateFrameSpeed(const fw::UpdateInfo &info) {
  bool isInterval = false;
  if (intervalTime > 0.0f) {
    intervalTime -= info.deltaTime;
    if (intervalTime <= 0.0f) {
      intervalSpeed = speeds[GF_SPEED_LAYER_4].original;
      intervalTime = 0.0f;
    }
    isInterval = true;
  }
  if (speeds[GF_SPEED_LAYER_1].apply || speeds[GF_SPEED_LAYER_4].apply || speeds[GF_SPEED_PLAY].apply || isInterval) {
    speeds[GF_SPEED_LAYER_1].apply = false;
    speeds[GF_SPEED_LAYER_4].apply = false;
    speeds[GF_SPEED_PLAY].apply = false;
    speeds[GF_SPEED_PLAY].current = speeds[GF_SPEED_PLAY].original;
    const f32 &speed4 = isInterval ? intervalSpeed : speeds[GF_SPEED_LAYER_4].original;
    f32 speed = speed4 * salvageSpeeds[GF_SPEED_LAYER_4].original * speeds[GF_SPEED_PLAY].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    const f32 &speed1 = isInterval ? intervalSpeed : speeds[GF_SPEED_LAYER_1].original;
    f32 speedLayer1 = speed1 * salvageSpeeds[GF_SPEED_LAYER_1].original * salvageSpeeds[GF_SPEED_PLAY].original;
    if (speedLayer1 <= 0.0f) {
      speedLayer1 = MIN_LAYER_SPEED;
    }
    fw::Framework::setLayerUpdateSpeed(0, speed);
    speeds[GF_SPEED_LAYER_0].current = speed;
    fw::Framework::setLayerUpdateSpeed(4, speed);
    speeds[GF_SPEED_LAYER_4].current = speed;
    fw::Framework::setLayerUpdateSpeed(5, speed);
    fw::Framework::setLayerUpdateSpeed(6, speed);
    fw::Framework::setLayerUpdateSpeed(1, speedLayer1);
    speeds[GF_SPEED_LAYER_1].current = speed;
    fw::Framework::setLayerUpdateSpeed(2, speedLayer1);
    fw::Framework::setLayerUpdateSpeed(3, speedLayer1);
  }
  if (speeds[GF_SPEED_LAYER_7].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_7].original * salvageSpeeds[GF_SPEED_LAYER_7].original;
    speeds[GF_SPEED_LAYER_7].apply = false;
    fw::Framework::setLayerUpdateSpeed(7, speed);
    speeds[GF_SPEED_LAYER_7].current = speed;
    fw::Framework::setLayerUpdateSpeed(8, speed);
    fw::Framework::setLayerUpdateSpeed(9, speed);
  }
  if (speeds[GF_SPEED_LAYER_10].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_10].original * salvageSpeeds[GF_SPEED_LAYER_10].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    speeds[GF_SPEED_LAYER_10].apply = false;
    fw::Framework::setLayerUpdateSpeed(10, speed);
    speeds[GF_SPEED_LAYER_10].current = speed;
    fw::Framework::setLayerUpdateSpeed(11, speed);
    fw::Framework::setLayerUpdateSpeed(12, speed);
  }
  if (speeds[GF_SPEED_LAYER_0].apply) {
    f32 speed = speeds[GF_SPEED_LAYER_0].original * salvageSpeeds[GF_SPEED_LAYER_0].original * speeds[GF_SPEED_PLAY].original;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    speeds[GF_SPEED_LAYER_0].apply = false;
    fw::Framework::setLayerUpdateSpeed(0, speed);
    speeds[GF_SPEED_LAYER_0].current = speed;
  }
  if (speeds[GF_SPEED_GLOBAL].apply) {
    speeds[GF_SPEED_GLOBAL].current = speeds[GF_SPEED_GLOBAL].original;
    speeds[GF_SPEED_GLOBAL].apply = false;
    f32 speed = speeds[GF_SPEED_GLOBAL].current;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    fw::Framework::setUpdateSpeed(speed);
  }
}

void GfGameSpeed::clear() {
  if (get() != nullptr) {
    get()->intervalSpeed = 1.0f;
    get()->intervalTime = 0.0f;
  }
}

void GfGameSpeed::setIntervalSpeed(f32 speed, f32 time) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->intervalSpeed = speed;
  gameSpeed->intervalTime = time;
}

void GfGameSpeed::setSpeed(GF_SPEED type, f32 speed) {
  f32 value = speed < 0.0f ? 1.0f : speed;
  if (speeds[type].original != value) {
    speeds[type].original = value;
    speeds[type].apply = true;
  }
}

f32 GfGameSpeed::getLayerSpeed(u32 layer) {
  GfGameSpeed *gameSpeed = get();
  switch (layer) {
  case 0:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_0);
  case 1:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_1);
  case 4:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_4);
  case 7:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_7);
  case 10:
    return gameSpeed->getSpeed(GF_SPEED_LAYER_10);
  }
  return 1.0f;
}

f32 GfGameSpeed::getSpeed(GF_SPEED type) { return speeds[type].current; }

f32 GfGameSpeed::getOriginalLayerSpeed(u32 layer) {
  GfGameSpeed *gameSpeed = get();
  switch (layer) {
  case 0:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_0);
  case 1:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_1);
  case 4:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_4);
  case 7:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_7);
  case 10:
    return gameSpeed->getOriginalSpeed(GF_SPEED_LAYER_10);
  }
  return 1.0f;
}

f32 GfGameSpeed::getOriginalSpeed(GF_SPEED type) { return speeds[type].original; }

f32 GfGameSpeed::getGlobalSpeed() {
  if (get() != nullptr) {
    return get()->getSpeed(GF_SPEED_GLOBAL);
  }
  return 0.0f;
}

void GfGameSpeed::setPlaySpeed(f32 speed) { get()->setSpeed(GF_SPEED_PLAY, speed); }

f32 GfGameSpeed::getPlaySpeed() {
  if (get() != nullptr) {
    return get()->getSpeed(GF_SPEED_PLAY);
  }
  return 0.0f;
}

bool GfGameSpeed::isApplySpeed(GF_SPEED type) { return speeds[type].apply; }

f32 GfGameSpeed::getSpeedSalvage(GF_SPEED type) { return salvageSpeeds[type].original; }

void GfGameSpeed::setSalvageSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_4].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_4].apply = true;
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_7].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_7].apply = true;
}

void GfGameSpeed::setSalvageCharacterSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->salvageSpeeds[GF_SPEED_LAYER_7].original = speed;
  gameSpeed->speeds[GF_SPEED_LAYER_7].apply = true;
}

void GfGameEnv::clear() {
  GfGameEnv *gameEnv = get();
  gameEnv->mapjump = false;
  gameEnv->mapjumpBlackout = false;
  gameEnv->mapjumpWithSaveData = false;
  gameEnv->mapID = 0;
  gameEnv->mapJumpID = 0;
  gameEnv->stopEnemySearchTime = 0.0f;
  gameEnv->colorFilterSerial = 1;
  gameEnv->cloudSeaSerial = 1;
  gameEnv->tempWeatherSerial = 1;
  gameEnv->roomCount = 0;
  gameEnv->screenShotDisableTimer = 0;
}

void GfGameEnv::build(const GfSetupParam &param) {
  // __LINE__ must be 720 as in the original file: its value changes the instruction order.
#line 720
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameEnv(param);
}

void GfGameEnv::destroy() { delete get(); }

GfGameEnv::GfGameEnv(const GfSetupParam &) { clear(); }

GfGameEnv::~GfGameEnv() {}

bool GfGameEnv::isStopEnemySearch() { return get()->stopEnemySearchTime > 0.0f; }

bool GfGameEnv::isMapjumpBlackout() { return get()->mapjumpBlackout; }

bool GfGameEnv::isMapjump() { return get()->mapjump; }

bool GfGameEnv::isMapjumpWithSaveData() { return get() != nullptr && get()->mapjumpWithSaveData; }

u32 GfGameEnv::getMapJumpID() { return get()->mapJumpID; }

u32 GfGameEnv::getMapID() { return get()->mapID; }

void GfGameEnv::setMapID(u32 mapJump, u32 map) {
  GfGameEnv *gameEnv = get();
  gameEnv->mapID = map;
  gameEnv->mapJumpID = mapJump;
}

void GfGameEnv::destroyColorFilter(CFILTER_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<ColorFilter, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->colorFilters.begin(), gameEnv->colorFilters.end(), [handle](const ColorFilter &colorFilter) { return colorFilter.handle == handle; });
  if (it == gameEnv->colorFilters.end()) {
    return;
  }
  if ((*it).handle != gameEnv->colorFilters.front().handle) {
    gameEnv->colorFilters.erase(it);
    return;
  }
  gameEnv->colorFilters.pop_front();
  if (!gameEnv->colorFilters.empty()) {
    const ColorFilter &current = gameEnv->colorFilters.front();
    fw::RenderParam::setColorFilter(current.filter, current.farFilter, current.time, fw::CAMERA_TYPE_MAIN);
  } else {
    fw::RenderParam::resetColorFilter(1.0f, fw::CAMERA_TYPE_MAIN);
  }
}

void GfGameEnv::setColorFilter(CFILTER_HANDLE handle, const ColorFilter &filter) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<ColorFilter, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->colorFilters.begin(), gameEnv->colorFilters.end(), [handle](const ColorFilter &colorFilter) { return colorFilter.handle == handle; });
  if (it == gameEnv->colorFilters.end()) {
    return;
  }
  (*it).time = filter.time;
  (*it).farFilter = filter.farFilter;
  (*it).filter = filter.filter;
  fw::RenderParam::setColorFilter(gameEnv->colorFilters.back().filter, gameEnv->colorFilters.back().farFilter, gameEnv->colorFilters.back().time, fw::CAMERA_TYPE_MAIN);
}

void GfGameEnv::destroyCloudSea(CLOUD_SEA_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->cloudSeas.begin(), gameEnv->cloudSeas.end(), [handle](const CloudSea &cloudSea) { return cloudSea.handle == handle; });
  if (it == gameEnv->cloudSeas.end()) {
    return;
  }
  if ((*it).handle != gameEnv->cloudSeas.front().handle) {
    gameEnv->cloudSeas.erase(it);
    return;
  }
  gameEnv->cloudSeas.pop_front();
  fw::RenderParam::setCloudSea(gameEnv->cloudSeas.empty() ? 0 : gameEnv->cloudSeas.front().cloudSea);
}

void GfGameEnv::setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA cloudSea) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it = mm::mtl::find_if(gameEnv->cloudSeas.begin(), gameEnv->cloudSeas.end(), [handle](const CloudSea &other) { return other.handle == handle; });
  if (it == gameEnv->cloudSeas.end()) {
    return;
  }
  (*it).cloudSea = cloudSea;
  fw::RenderParam::setCloudSea(gameEnv->cloudSeas.front().cloudSea);
}

CLOUD_SEA GfGameEnv::getCloudType(CLOUD_SEA_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->cloudSeas.begin(), gameEnv->cloudSeas.end(), [handle](const CloudSea &cloudSea) { return cloudSea.handle == handle; });
  if (it != gameEnv->cloudSeas.end()) {
    return (*it).cloudSea;
  }
  return CLOUD_SEA(0);
}

CLOUD_SEA GfGameEnv::getCurrentCloudSea() {
  GfGameEnv *gameEnv = get();
  if (!gameEnv->cloudSeas.empty()) {
    return gameEnv->cloudSeas.front().cloudSea;
  }
  return CLOUD_SEA(0);
}

void GfGameEnv::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  GfGameEnv *gameEnv = get();
  switch (event) {
  case GEV_MAPJUMP_START:
    gameEnv->mapjump = true;
    gameEnv->mapjumpWithSaveData = info.isWithSaveData;
    break;
  case GEV_MAPJUMP_DESTROY_FIELD:
    gameEnv->mapjumpBlackout = true;
    break;
  case GEV_MAPJUMP_CREATE_FIELD:
    gameEnv->stopEnemySearchTime = info.jumpType == MAPJUMP_TYPE_SAVE_DATA ? 0.0f : STOP_ENEMY_SEARCH_SEC;
    break;
  case GEV_MAPJUMP_FADEIN:
    gameEnv->mapjump = false;
    gameEnv->mapjumpBlackout = false;
    gameEnv->mapjumpWithSaveData = false;
    if (!GfGameManager::isEvent(false)) {
      nn::oe::DisableScreenShot();
      gameEnv->screenShotDisableTimer = SCREEN_SHOT_DISABLE_FRAMES;
    }
    break;
  }
}

void GfGameEnv::gevPlayEvent(GEV, u32) {}

void GfGameEnv::gevGameState(GF_STATE, GF_STATE state) {
  if (state == GF_STATE_DESTROY) {
    fw::RenderParam::setMotionBlur(false, fw::CAMERA_TYPE_MAIN);
  } else if (state == GF_STATE_CONTROL && !GfManager::isExecModeAdvertize()) {
    fw::RenderParam::setMotionBlur(true, fw::CAMERA_TYPE_MAIN);
  }
}

void GfGameEnv::update(const fw::UpdateInfo &info) {
  GfGameEnv *gameEnv = get();
  if (!gameEnv->mapjump && gameEnv->stopEnemySearchTime > 0.0f) {
    gameEnv->stopEnemySearchTime -= info.deltaTime;
    if (gameEnv->stopEnemySearchTime < 0.0f) {
      gameEnv->stopEnemySearchTime = 0.0f;
    }
  }
  gameEnv->updateIsInRoom(info);
  updateGlobalIBLReferencePos(info);
  if (!gameEnv->colorFilters.empty()) {
    const ColorFilter &filter = gameEnv->colorFilters.back();
    fw::RenderParam::setColorFilter(filter.filter, filter.farFilter, filter.time, fw::CAMERA_TYPE_MAIN);
  }
  if (gameEnv->screenShotDisableTimer != 0 && --gameEnv->screenShotDisableTimer == 0) {
    nn::oe::EnableScreenShot();
  }
}

void GfGameEnv::updateIsInRoom(const fw::UpdateInfo &) {
  mm::Vec3 position = fw::CameraManager::get()->layers[0].getCameraPosition();
  if (isMapjumpBlackout()) {
    return;
  }
  if (fw::RenderParam::isRoom(position, fw::CAMERA_TYPE_MAIN)) {
    if (roomCount <= 0) {
      roomCount = 1;
    } else if (roomCount < ROOM_COUNT_MAX) {
      roomCount++;
    }
  } else {
    if (roomCount >= 0) {
      roomCount = -1;
    } else if (roomCount > -ROOM_COUNT_MAX) {
      roomCount--;
    }
  }
}

void GfGameEnv::updateGlobalIBLReferencePos(const fw::UpdateInfo &) {
  if (fw::CameraManager::get() != nullptr) {
    GfMapManager::setGlobalIBLReferencePos(fw::CameraManager::get()->layers[0].getCameraPosition());
  }
}

bool GfGameEnv::isRoom() { return get()->roomCount > -3; }

void GfGameEnv::sendPlayerPositionToRender(const mm::Vec3 &position) { fw::RenderParam::setPlayerPosition(position, fw::CAMERA_TYPE_MAIN); }

void GfGameEnv::setWeather(WEATHERID weather) { GfFieldWeather::setMapWeatherID(weather); }

void GfGameEnv::destroyTempWeather(WEATHER_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<WeatherSet, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->tempWeathers.begin(), gameEnv->tempWeathers.end(), [handle](const WeatherSet &weatherSet) { return weatherSet.handle == handle; });
  if (it != gameEnv->tempWeathers.end()) {
    gameEnv->tempWeathers.erase(it);
  }
}

WEATHERID GfGameEnv::getTempWeather() {
  GfGameEnv *gameEnv = get();
  if (!gameEnv->tempWeathers.empty()) {
    return gameEnv->tempWeathers.front().weather;
  }
  return WEATHER_NULL;
}

} // namespace gf
