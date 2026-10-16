#include "gf/field/gf_field_weather.h"

#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_weather_obj.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"

namespace gf {
struct GF_OBJ_HANDLE;

constexpr u32 WEATHER_LIST_MAX = 16;
constexpr f32 WEATHER_RAND_SCALE = 100.0f;
constexpr u32 WEATHER_ATR_CLOUD2 = 1;
constexpr u32 WEATHER_ATR_CLOUD2_LATE = 2;
constexpr u16 CLOUD2_SCENARIO_START = 9010;
constexpr u16 CLOUD2_LATE_SCENARIO_START = 9015;
constexpr u16 CLOUD2_SCENARIO_END = 10048;

namespace _gffwt {

mm::mtl::FixedList<WeatherInfo *, WEATHER_LIST_MAX> s_list;

bool isCurrentWeatherEnd() {
  if (s_list.empty() || s_list.front()->isTimeEnd()) {
    return true;
  }

  return !s_list.front()->isTimeRangeOK();
}

WeatherInfo *getCurrentInfo(bool isPrevious) {
  if (s_list.empty()) {
    return nullptr;
  }

  if (s_list.size() == 1) {
    return isPrevious ? nullptr : s_list.front();
  }

  if (isPrevious) {
    return *s_list.begin();
  }

  return *++s_list.begin();
}

bool isCurrentSE() {
  WeatherInfo *info = getCurrentInfo(false);
  if (info != nullptr) {
    return info->isPlaySE();
  }

  return false;
}

WEATYPE getCurrentWtrType(bool isPrevious) {
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    return info->type;
  }

  return WEATYPE_INVALID;
}

WEATHERID getCurrentMapWeatherID(bool isPrevious) {
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    return info->weather;
  }

  return WEATHER_F;
}

u32 getCurrentMapID(bool isPrevious) {
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    return info->map;
  }

  return 0;
}

f32 getCurrentPastSec(bool isPrevious) {
  f32 pastSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    pastSec = info->pastSec;
  }

  return pastSec;
}

f32 getCurrentExistSec(bool isPrevious) {
  f32 existSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    existSec = info->existSec;
  }

  return existSec;
}

f32 getCurrentFadePastSec(bool isPrevious) {
  f32 fadePastSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    fadePastSec = info->fadePastSec;
  }

  return fadePastSec;
}

f32 getCurrentFadeExistSec(bool isPrevious) {
  f32 fadeExistSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    fadeExistSec = info->fadeExistSec;
  }

  return fadeExistSec;
}

void destroyList() {
  for (mm::mtl::FixedList<WeatherInfo *, WEATHER_LIST_MAX>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    if (*it != nullptr) {
      delete *it;
      *it = nullptr;
    }
  }

  s_list.clear();
}

void destroyFadeWeather() {
  while (s_list.size() > 1) {
    delete s_list.front();
    s_list.pop_front();
  }
}

f32 getWeatherRand() { return (1.0f - ml::mtRandf1()) * WEATHER_RAND_SCALE; }

WeatherInfo *getCurrentWeatherInfo() {
  if (s_list.size() != 1 || s_list.back()->fadeRate < 1.0f) {
    return nullptr;
  }

  return s_list.back();
}

WeatherInfo *getFadeinWeatherInfo() {
  if (s_list.empty()) {
    return nullptr;
  }

  if (s_list.size() == 1 && s_list.back()->fadeRate >= 1.0f) {
    return nullptr;
  }

  return s_list.back();
}

WeatherInfo *getFadeoutWeatherInfo() {
  if (s_list.size() < 2) {
    return nullptr;
  }

  return s_list.front();
}

void setPause(bool isPause) {
  for (mm::mtl::FixedList<WeatherInfo *, WEATHER_LIST_MAX>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    (*it)->setPause(isPause);
  }
}

} // namespace _gffwt

void GfFieldWeather::initialize(const GfSetupParam &) {
  _gffwt::destroyList();
  createCloudSeaDefault();
  mInitialized = true;
}

GfFieldWeather::~GfFieldWeather() {}

void GfFieldWeather::applyNowMapWeatherForMapModel(u32 map) {
  if (GfGameManager::getMapID() != map) {
    return;
  }

  if (__builtin_strcmp(GfDataMap::getWeatherName(_gffwt::getCurrentWtrType(false)), "Unknown") == 0) {
    return;
  }

  GfMapManager::setEnvWeather(_gffwt::getCurrentWtrType(false));
}

void GfFieldWeather::gevMapjump(GEV gev, const MapjumpCallbackInfo &info) {
  GfFieldWeather *weather = get();
  weather->mEvents.push(gev);
  weather->mMapjumpInfo = info;
}

void GfFieldWeather::gevGameMapModel(GF_OBJ_HANDLE *, bool) {}

void GfFieldWeather::gevPause(u32 resumeBits, u32 pauseBits) {
  if ((pauseBits & PAUSE_BIT_SYSTEM) != 0) {
    _gffwt::setPause(true);
  }
  if ((resumeBits & PAUSE_BIT_SYSTEM) != 0) {
    _gffwt::setPause(false);
  }
}

bool GfFieldWeather::isColud2Condition(u32 map) const {
  if (map == 0) {
    return false;
  }

  u32 attribute = GfBdatMaplist::get()->getMaplistweatherATR(map);
  if (attribute == 0) {
    return false;
  }

  u16 scenario = GfDataUtil::getScenarioFlag();
  if (attribute == WEATHER_ATR_CLOUD2) {
    return scenario >= CLOUD2_SCENARIO_START && scenario < CLOUD2_SCENARIO_END;
  }
  if (attribute == WEATHER_ATR_CLOUD2_LATE) {
    return scenario >= CLOUD2_LATE_SCENARIO_START && scenario < CLOUD2_SCENARIO_END;
  }

  return false;
}

void GfFieldWeather::execChangeCloud(u32 map) { setCloudSeaForDebug(map, GfDataMap::getCloudType(map)); }

void GfFieldWeather::setCloudSeaForDebug(u32, CLOUD_SEA cloudSea) {
  if (get() != nullptr) {
    get()->mCloudSeaRequest = cloudSea != 0 ? CLOUD_SEA_REQUEST_HIGH : CLOUD_SEA_REQUEST_LOW;
  }
}

WEATYPE GfFieldWeather::getCurrentWtrType(bool isPrevious) { return _gffwt::getCurrentWtrType(isPrevious); }

u32 GfFieldWeather::getCurrentWtrTypeBit(bool isPrevious) {
  WEATYPE type = getCurrentWtrType(isPrevious);
  return type == WEATYPE_DEFAULT ? 0 : 1 << type;
}

WEATHERID GfFieldWeather::getCurrentMapWeatherID(bool isPrevious) { return _gffwt::getCurrentMapWeatherID(isPrevious); }

u32 GfFieldWeather::getCurrentMapWeatherBit(bool isPrevious) { return 1 << (getCurrentMapWeatherID(isPrevious) - 1); }

const char *GfFieldWeather::getCurrentEffName(bool isPrevious) { return GfDataMap::getWeatherEffName(getCurrentWtrType(isPrevious)); }

const char *GfFieldWeather::getCurrentSndName(bool isPrevious) { return GfDataMap::getWeatherSndName(getCurrentWtrType(isPrevious)); }

const char *GfFieldWeather::getCurrentWeatherName(bool isPrevious) { return GfDataMap::getWeatherName(getCurrentWtrType(isPrevious)); }

void GfFieldWeather::setCurrentRemainSecZero() {
  if (_gffwt::s_list.size() == 1) {
    WeatherInfo *info = _gffwt::s_list.front();
    info->pastSec = info->existSec;
  }
}

void GfFieldWeather::setCloudSea(u32, CLOUD_SEA cloudSea) {
  GfFieldWeather *weather = get();
  weather->mCloudSeaRequest = cloudSea != 0 ? CLOUD_SEA_REQUEST_HIGH : CLOUD_SEA_REQUEST_LOW;
}

bool GfFieldWeather::isInfiniteTime() { return get()->mIsInfiniteTime; }

bool GfFieldWeather::isWeatherSE() { return _gffwt::isCurrentSE(); }

bool GfFieldWeather::getWeatherName(u8 *&bdat, u32 &textId) { return GfDataMap::getWeatherName(bdat, textId, getCurrentWtrType(false)); }

const char *GfFieldWeather::getWeatherName() { return GfDataMap::getWeatherName(getCurrentWtrType(false)); }

void GfFieldWeather::setupGame() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->mapInfos[0].weatherParam.resource[0] != '\0') {
    return;
  }

  GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
  for (u32 map = bdatMaplist->getMaplistStart(); map < bdatMaplist->getMaplistEnd(); map++) {
    const char *resource = bdatMaplist->getMaplistresource(map);
    for (SDataMapInfo &info : dataGame->mapInfos) {
      WeatherParam &param = info.weatherParam;
      if (__builtin_strcmp(param.resource, resource) == 0) {
        break;
      }
      if (param.resource[0] == '\0') {
        __builtin_strcpy(param.resource, resource);
        param.map = map;
        break;
      }
    }
  }

  u32 map = GfDataMap::getMapID(GfDataManager::getDataGame()->map.skipTravelID);
  setCloudSeaForDebug(map, static_cast<CLOUD_SEA>(dataGame->mapInfos[map].cloudType));
}

void GfFieldWeather::updateCloudSea(const fw::UpdateInfo &) {
  u32 map = GfGameManager::getMapID();
  if (GfGameCond::isGameCond(GfBdatMaplist::get()->getMaplistebb_ON_cndID(map))) {
    if (mCloudSeaCondition == 0) {
      createCloudSeaCondition();
      GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(1));
    }
  } else {
    if (mCloudSeaCondition != 0) {
      destroyCloudSeaCondition();
      GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(0));
    }
    applyCloudSelect();
  }
}

void GfFieldWeather::createCloudSeaCondition() {
  destroyCloudSeaCondition();
  mCloudSeaCondition = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(1), static_cast<CLOUD_SEA_PRIO>(1));
}

void GfFieldWeather::destroyCloudSeaCondition() {
  if (mCloudSeaCondition != 0) {
    GfGameEnv::destroyCloudSea(mCloudSeaCondition);
    mCloudSeaCondition = static_cast<CLOUD_SEA_HANDLE>(0);
  }
}

void GfFieldWeather::applyCloudSelect() {
  if (mCloudSeaRequest != CLOUD_SEA_REQUEST_NONE) {
    GfGameEnv::setCloudSea(mCloudSeaDefault, static_cast<CLOUD_SEA>(mCloudSeaRequest != CLOUD_SEA_REQUEST_LOW));
    mCloudSeaRequest = CLOUD_SEA_REQUEST_NONE;
  }
}

void GfFieldWeather::createCloudSeaDefault() {
  destroyCloudSeaDefault();
  mCloudSeaDefault = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(0), static_cast<CLOUD_SEA_PRIO>(0));
}

void GfFieldWeather::destroyCloudSeaDefault() {
  if (mCloudSeaDefault != 0) {
    GfGameEnv::destroyCloudSea(mCloudSeaDefault);
    mCloudSeaDefault = static_cast<CLOUD_SEA_HANDLE>(0);
  }
}

CLOUD_SEA GfFieldWeather::getCloudSeaCondition() { return GfGameEnv::getCloudType(get()->mCloudSeaCondition); }

CLOUD_SEA GfFieldWeather::getCloudSea(u32 map) {
  if (map != 0) {
    return static_cast<CLOUD_SEA>(GfDataManager::getDataGame()->mapInfos[map].cloudType != 0);
  }

  return GfGameEnv::getCurrentCloudSea();
}

CLOUD_SEA GfFieldWeather::getCurrentCloudSea() { return GfGameEnv::getCurrentCloudSea(); }

void GfFieldWeather::setDispWeather(bool isDisp) {
  if (get() != nullptr) {
    get()->mIsDispWeather = isDisp;
  }
}

bool GfFieldWeather::isDispWeather() {
  if (get() != nullptr) {
    return get()->mIsDispWeather;
  }

  return false;
}

void GfFieldWeather::clear() {
  GfFieldWeather *weather = get();
  _gffwt::destroyList();
  weather->destroyCloudSeaCondition();
}

void GfFieldWeather::destroy() {
  GfFieldWeather *weather = get();
  weather->finalize();
  delete weather;
}

void GfFieldWeather::finalize() {
  destroyCloudSeaDefault();
  destroyCloudSeaCondition();
  _gffwt::destroyList();
  mInitialized = false;
}

bool GfFieldWeather::isInitialized() {
  if (get() != nullptr) {
    return get()->mInitialized;
  }

  return false;
}

void GfFieldWeather::update(const fw::UpdateInfo &info) {
  GfFieldWeather *weather = get();
  weather->updateEvent(info);
  weather->updateWeather(info);
  weather->updateCloudSea(info);
}

} // namespace gf
