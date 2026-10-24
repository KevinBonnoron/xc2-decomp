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
    : unknown0c(0), unknown10(0), unknown14(0), unknown18(0), unknown1c(0), unknown20(reinterpret_cast<GF_LP_HANDLE *>(-1)), unknown28(reinterpret_cast<GF_LP_HANDLE *>(-1)),
      unknown30(reinterpret_cast<GF_LP_HANDLE *>(-1)), unknown38(reinterpret_cast<GF_LP_HANDLE *>(-1)), unknown40(reinterpret_cast<GF_LP_HANDLE *>(-1)) {
  initialize(param);
}

void GfLayerPause::initialize(const GfSetupParam &) { unknown08 = true; }

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

void GfLayerPause::finalize() { unknown08 = false; }

bool GfLayerPause::isInitialized() { return get() != nullptr && get()->unknown08; }

void GfLayerPause::update(const fw::UpdateInfo &) {}

void GfLayerPause::gevPause(u32 resumeBits, u32 pauseBits) {
  GfLayerPause *layerPause = get();
  if ((resumeBits & PAUSE_BIT_SYSTEM) != 0) {
    destroyLayerPause(layerPause->unknown20);
    destroyLayerPause(layerPause->unknown28);
    destroyLayerPause(layerPause->unknown30);
    destroyLayerPause(layerPause->unknown38);
  } else if ((pauseBits & PAUSE_BIT_SYSTEM) != 0) {
    layerPause->unknown20 = setLayerPause(4);
    layerPause->unknown28 = setLayerPause(0);
    layerPause->unknown30 = setLayerPause(1);
    layerPause->unknown38 = setLayerPause(7);
  }
  if ((resumeBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    destroyLayerPause(layerPause->unknown40);
  } else if ((pauseBits & PAUSE_BIT_EVENT_SKIP) != 0) {
    layerPause->unknown40 = setLayerPause(10);
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
  destroyLayerPause(layerPause->unknown20);
  destroyLayerPause(layerPause->unknown28);
  destroyLayerPause(layerPause->unknown30);
  destroyLayerPause(layerPause->unknown38);
  destroyLayerPause(layerPause->unknown40);
}

bool GfLayerPause::isLayerPause(u32 layer) { return fw::Framework::isLayerPause(layer); }

GfGameSpeed::GfGameSpeed(const GfSetupParam &param) : unknown0c(1.0f), unknown10(0.0f) { initialize(param); }

void GfGameSpeed::initialize(const GfSetupParam &) { unknown08 = true; }

GfGameSpeed::~GfGameSpeed() {}

void GfGameSpeed::build(const GfSetupParam &param) {
  // __LINE__ must be 347 as in the original file: its value changes the instruction order.
#line 347
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameSpeed(param);
  setGlobalSpeed(param.unknown20);
}

void GfGameSpeed::setGlobalSpeed(f32 speed) { get()->setSpeed(GF_SPEED_GLOBAL, speed); }

void GfGameSpeed::destroy() {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->finalize();
  delete gameSpeed;
}

void GfGameSpeed::finalize() { unknown08 = false; }

bool GfGameSpeed::isInitialized() { return get() != nullptr && get()->unknown08; }

void GfGameSpeed::update(const fw::UpdateInfo &info) {
  if (get() != nullptr) {
    get()->updateFrameSpeed(info);
  }
}

void GfGameSpeed::updateFrameSpeed(const fw::UpdateInfo &info) {
  bool isInterval = false;
  if (unknown10 > 0.0f) {
    unknown10 -= info.unknown04;
    if (unknown10 <= 0.0f) {
      unknown0c = unknown14[GF_SPEED_LAYER_4].unknown00;
      unknown10 = 0.0f;
    }
    isInterval = true;
  }
  if (unknown14[GF_SPEED_LAYER_1].unknown08 || unknown14[GF_SPEED_LAYER_4].unknown08 || unknown14[GF_SPEED_PLAY].unknown08 || isInterval) {
    unknown14[GF_SPEED_LAYER_1].unknown08 = false;
    unknown14[GF_SPEED_LAYER_4].unknown08 = false;
    unknown14[GF_SPEED_PLAY].unknown08 = false;
    unknown14[GF_SPEED_PLAY].unknown04 = unknown14[GF_SPEED_PLAY].unknown00;
    const f32 &speed4 = isInterval ? unknown0c : unknown14[GF_SPEED_LAYER_4].unknown00;
    f32 speed = speed4 * unknown68[GF_SPEED_LAYER_4].unknown00 * unknown14[GF_SPEED_PLAY].unknown00;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    const f32 &speed1 = isInterval ? unknown0c : unknown14[GF_SPEED_LAYER_1].unknown00;
    f32 speedLayer1 = speed1 * unknown68[GF_SPEED_LAYER_1].unknown00 * unknown68[GF_SPEED_PLAY].unknown00;
    if (speedLayer1 <= 0.0f) {
      speedLayer1 = MIN_LAYER_SPEED;
    }
    fw::Framework::setLayerUpdateSpeed(0, speed);
    unknown14[GF_SPEED_LAYER_0].unknown04 = speed;
    fw::Framework::setLayerUpdateSpeed(4, speed);
    unknown14[GF_SPEED_LAYER_4].unknown04 = speed;
    fw::Framework::setLayerUpdateSpeed(5, speed);
    fw::Framework::setLayerUpdateSpeed(6, speed);
    fw::Framework::setLayerUpdateSpeed(1, speedLayer1);
    unknown14[GF_SPEED_LAYER_1].unknown04 = speed;
    fw::Framework::setLayerUpdateSpeed(2, speedLayer1);
    fw::Framework::setLayerUpdateSpeed(3, speedLayer1);
  }
  if (unknown14[GF_SPEED_LAYER_7].unknown08) {
    f32 speed = unknown14[GF_SPEED_LAYER_7].unknown00 * unknown68[GF_SPEED_LAYER_7].unknown00;
    unknown14[GF_SPEED_LAYER_7].unknown08 = false;
    fw::Framework::setLayerUpdateSpeed(7, speed);
    unknown14[GF_SPEED_LAYER_7].unknown04 = speed;
    fw::Framework::setLayerUpdateSpeed(8, speed);
    fw::Framework::setLayerUpdateSpeed(9, speed);
  }
  if (unknown14[GF_SPEED_LAYER_10].unknown08) {
    f32 speed = unknown14[GF_SPEED_LAYER_10].unknown00 * unknown68[GF_SPEED_LAYER_10].unknown00;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    unknown14[GF_SPEED_LAYER_10].unknown08 = false;
    fw::Framework::setLayerUpdateSpeed(10, speed);
    unknown14[GF_SPEED_LAYER_10].unknown04 = speed;
    fw::Framework::setLayerUpdateSpeed(11, speed);
    fw::Framework::setLayerUpdateSpeed(12, speed);
  }
  if (unknown14[GF_SPEED_LAYER_0].unknown08) {
    f32 speed = unknown14[GF_SPEED_LAYER_0].unknown00 * unknown68[GF_SPEED_LAYER_0].unknown00 * unknown14[GF_SPEED_PLAY].unknown00;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    unknown14[GF_SPEED_LAYER_0].unknown08 = false;
    fw::Framework::setLayerUpdateSpeed(0, speed);
    unknown14[GF_SPEED_LAYER_0].unknown04 = speed;
  }
  if (unknown14[GF_SPEED_GLOBAL].unknown08) {
    unknown14[GF_SPEED_GLOBAL].unknown04 = unknown14[GF_SPEED_GLOBAL].unknown00;
    unknown14[GF_SPEED_GLOBAL].unknown08 = false;
    f32 speed = unknown14[GF_SPEED_GLOBAL].unknown04;
    if (speed <= 0.0f) {
      speed = MIN_LAYER_SPEED;
    }
    fw::Framework::setUpdateSpeed(speed);
  }
}

void GfGameSpeed::clear() {
  if (get() != nullptr) {
    get()->unknown0c = 1.0f;
    get()->unknown10 = 0.0f;
  }
}

void GfGameSpeed::setIntervalSpeed(f32 speed, f32 time) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->unknown0c = speed;
  gameSpeed->unknown10 = time;
}

void GfGameSpeed::setSpeed(GF_SPEED type, f32 speed) {
  f32 value = speed < 0.0f ? 1.0f : speed;
  if (unknown14[type].unknown00 != value) {
    unknown14[type].unknown00 = value;
    unknown14[type].unknown08 = true;
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

f32 GfGameSpeed::getSpeed(GF_SPEED type) { return unknown14[type].unknown04; }

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

f32 GfGameSpeed::getOriginalSpeed(GF_SPEED type) { return unknown14[type].unknown00; }

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

bool GfGameSpeed::isApplySpeed(GF_SPEED type) { return unknown14[type].unknown08; }

f32 GfGameSpeed::getSpeedSalvage(GF_SPEED type) { return unknown68[type].unknown00; }

void GfGameSpeed::setSalvageSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->unknown68[GF_SPEED_LAYER_4].unknown00 = speed;
  gameSpeed->unknown14[GF_SPEED_LAYER_4].unknown08 = true;
  gameSpeed->unknown68[GF_SPEED_LAYER_7].unknown00 = speed;
  gameSpeed->unknown14[GF_SPEED_LAYER_7].unknown08 = true;
}

void GfGameSpeed::setSalvageCharacterSpeed(f32 speed) {
  GfGameSpeed *gameSpeed = get();
  gameSpeed->unknown68[GF_SPEED_LAYER_7].unknown00 = speed;
  gameSpeed->unknown14[GF_SPEED_LAYER_7].unknown08 = true;
}

void GfGameEnv::clear() {
  GfGameEnv *gameEnv = get();
  gameEnv->unknown08 = false;
  gameEnv->unknown09 = false;
  gameEnv->unknown0a = false;
  gameEnv->unknown0c = 0;
  gameEnv->unknown10 = 0;
  gameEnv->unknown14 = 0.0f;
  gameEnv->unknown168 = 1;
  gameEnv->unknown240 = 1;
  gameEnv->unknown318 = 1;
  gameEnv->unknown320 = 0;
  gameEnv->unknown324 = 0;
}

void GfGameEnv::build(const GfSetupParam &param) {
  // __LINE__ must be 720 as in the original file: its value changes the instruction order.
#line 720
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameEnv(param);
}

void GfGameEnv::destroy() { delete get(); }

GfGameEnv::GfGameEnv(const GfSetupParam &) { clear(); }

GfGameEnv::~GfGameEnv() {}

bool GfGameEnv::isStopEnemySearch() { return get()->unknown14 > 0.0f; }

bool GfGameEnv::isMapjumpBlackout() { return get()->unknown09; }

bool GfGameEnv::isMapjump() { return get()->unknown08; }

bool GfGameEnv::isMapjumpWithSaveData() { return get() != nullptr && get()->unknown0a; }

u32 GfGameEnv::getMapJumpID() { return get()->unknown10; }

u32 GfGameEnv::getMapID() { return get()->unknown0c; }

void GfGameEnv::setMapID(u32 mapJump, u32 map) {
  GfGameEnv *gameEnv = get();
  gameEnv->unknown0c = map;
  gameEnv->unknown10 = mapJump;
}

void GfGameEnv::destroyColorFilter(CFILTER_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<ColorFilter, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown18.begin(), gameEnv->unknown18.end(), [handle](const ColorFilter &colorFilter) { return colorFilter.unknown0c == handle; });
  if (it == gameEnv->unknown18.end()) {
    return;
  }
  if ((*it).unknown0c != gameEnv->unknown18.front().unknown0c) {
    gameEnv->unknown18.erase(it);
    return;
  }
  gameEnv->unknown18.pop_front();
  if (!gameEnv->unknown18.empty()) {
    const ColorFilter &current = gameEnv->unknown18.front();
    fw::RenderParam::setColorFilter(current.unknown00, current.unknown04, current.unknown08, fw::CAMERA_TYPE_MAIN);
  } else {
    fw::RenderParam::resetColorFilter(1.0f, fw::CAMERA_TYPE_MAIN);
  }
}

void GfGameEnv::setColorFilter(CFILTER_HANDLE handle, const ColorFilter &filter) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<ColorFilter, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown18.begin(), gameEnv->unknown18.end(), [handle](const ColorFilter &colorFilter) { return colorFilter.unknown0c == handle; });
  if (it == gameEnv->unknown18.end()) {
    return;
  }
  (*it).unknown08 = filter.unknown08;
  (*it).unknown04 = filter.unknown04;
  (*it).unknown00 = filter.unknown00;
  fw::RenderParam::setColorFilter(gameEnv->unknown18.back().unknown00, gameEnv->unknown18.back().unknown04, gameEnv->unknown18.back().unknown08, fw::CAMERA_TYPE_MAIN);
}

void GfGameEnv::destroyCloudSea(CLOUD_SEA_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown170.begin(), gameEnv->unknown170.end(), [handle](const CloudSea &cloudSea) { return cloudSea.unknown08 == handle; });
  if (it == gameEnv->unknown170.end()) {
    return;
  }
  if ((*it).unknown08 != gameEnv->unknown170.front().unknown08) {
    gameEnv->unknown170.erase(it);
    return;
  }
  gameEnv->unknown170.pop_front();
  fw::RenderParam::setCloudSea(gameEnv->unknown170.empty() ? 0 : gameEnv->unknown170.front().unknown00);
}

void GfGameEnv::setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA cloudSea) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown170.begin(), gameEnv->unknown170.end(), [handle](const CloudSea &other) { return other.unknown08 == handle; });
  if (it == gameEnv->unknown170.end()) {
    return;
  }
  (*it).unknown00 = cloudSea;
  fw::RenderParam::setCloudSea(gameEnv->unknown170.front().unknown00);
}

CLOUD_SEA GfGameEnv::getCloudType(CLOUD_SEA_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown170.begin(), gameEnv->unknown170.end(), [handle](const CloudSea &cloudSea) { return cloudSea.unknown08 == handle; });
  if (it != gameEnv->unknown170.end()) {
    return (*it).unknown00;
  }
  return CLOUD_SEA(0);
}

CLOUD_SEA GfGameEnv::getCurrentCloudSea() {
  GfGameEnv *gameEnv = get();
  if (!gameEnv->unknown170.empty()) {
    return gameEnv->unknown170.front().unknown00;
  }
  return CLOUD_SEA(0);
}

void GfGameEnv::gevMapjump(GEV event, const MapjumpCallbackInfo &info) {
  GfGameEnv *gameEnv = get();
  switch (event) {
  case GEV_MAPJUMP_START:
    gameEnv->unknown08 = true;
    gameEnv->unknown0a = info.unknown0c;
    break;
  case GEV_MAPJUMP_DESTROY_FIELD:
    gameEnv->unknown09 = true;
    break;
  case GEV_MAPJUMP_CREATE_FIELD:
    gameEnv->unknown14 = info.unknown10 == MAPJUMP_TYPE_SAVE_DATA ? 0.0f : STOP_ENEMY_SEARCH_SEC;
    break;
  case GEV_MAPJUMP_FADEIN:
    gameEnv->unknown08 = false;
    gameEnv->unknown09 = false;
    gameEnv->unknown0a = false;
    if (!GfGameManager::isEvent(false)) {
      nn::oe::DisableScreenShot();
      gameEnv->unknown324 = SCREEN_SHOT_DISABLE_FRAMES;
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
  if (!gameEnv->unknown08 && gameEnv->unknown14 > 0.0f) {
    gameEnv->unknown14 -= info.unknown04;
    if (gameEnv->unknown14 < 0.0f) {
      gameEnv->unknown14 = 0.0f;
    }
  }
  gameEnv->updateIsInRoom(info);
  updateGlobalIBLReferencePos(info);
  if (!gameEnv->unknown18.empty()) {
    const ColorFilter &filter = gameEnv->unknown18.back();
    fw::RenderParam::setColorFilter(filter.unknown00, filter.unknown04, filter.unknown08, fw::CAMERA_TYPE_MAIN);
  }
  if (gameEnv->unknown324 != 0 && --gameEnv->unknown324 == 0) {
    nn::oe::EnableScreenShot();
  }
}

void GfGameEnv::updateIsInRoom(const fw::UpdateInfo &) {
  mm::Vec3 position = fw::CameraManager::get()->unknown20[0].getCameraPosition();
  if (isMapjumpBlackout()) {
    return;
  }
  if (fw::RenderParam::isRoom(position, fw::CAMERA_TYPE_MAIN)) {
    if (unknown320 <= 0) {
      unknown320 = 1;
    } else if (unknown320 < ROOM_COUNT_MAX) {
      unknown320++;
    }
  } else {
    if (unknown320 >= 0) {
      unknown320 = -1;
    } else if (unknown320 > -ROOM_COUNT_MAX) {
      unknown320--;
    }
  }
}

void GfGameEnv::updateGlobalIBLReferencePos(const fw::UpdateInfo &) {
  if (fw::CameraManager::get() != nullptr) {
    GfMapManager::setGlobalIBLReferencePos(fw::CameraManager::get()->unknown20[0].getCameraPosition());
  }
}

bool GfGameEnv::isRoom() { return get()->unknown320 > -3; }

void GfGameEnv::sendPlayerPositionToRender(const mm::Vec3 &position) { fw::RenderParam::setPlayerPosition(position, fw::CAMERA_TYPE_MAIN); }

void GfGameEnv::setWeather(WEATHERID weather) { GfFieldWeather::setMapWeatherID(weather); }

void GfGameEnv::destroyTempWeather(WEATHER_HANDLE handle) {
  GfGameEnv *gameEnv = get();
  mm::mtl::FixedQueue<WeatherSet, FILTER_MAX>::iterator it =
      mm::mtl::find_if(gameEnv->unknown248.begin(), gameEnv->unknown248.end(), [handle](const WeatherSet &weatherSet) { return weatherSet.unknown08 == handle; });
  if (it != gameEnv->unknown248.end()) {
    gameEnv->unknown248.erase(it);
  }
}

WEATHERID GfGameEnv::getTempWeather() {
  GfGameEnv *gameEnv = get();
  if (!gameEnv->unknown248.empty()) {
    return gameEnv->unknown248.front().unknown00;
  }
  return WEATHER_NULL;
}

} // namespace gf
