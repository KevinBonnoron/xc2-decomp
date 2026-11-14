#include "gf/field/gf_field_weather.h"

#include <string.h>

#include "fw/fw_update_info.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_util.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather_obj.h"
#include "gf/game/event/gf_game_event.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/gf_pause.h"
#include "gf/map/gf_map_manager.h"
#include "ml/rand.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"

namespace gf {
struct GF_OBJ_HANDLE;

constexpr u32 WEATHER_UNKNOWN_16 = 16;                            // Inferred role: weather list max; original name unknown.
constexpr f32 unknown045 = 100.0f;                                // Inferred role: weather rand scale; original name unknown.
constexpr u32 WEATHER_UNKNOWN_6 = 1 << TIME_RANGE_UNKNOWN_6;      // Inferred role: weather time bonus daytime; original name unknown.
constexpr u32 WEATHER_TIME_UNKNOWN_7 = 1 << TIME_RANGE_UNKNOWN_7; // Inferred role: weather time bonus nighttime; original name unknown.
constexpr u32 WEATHER_UNKNOWN_8 = 1 << 8;                         // Inferred role: weather time bonus none; original name unknown.
constexpr u32 WEATHER_UNKNOWN_15 = 1 << 15;                       // Inferred role: weather time bonus range all; original name unknown.
constexpr f32 unknown046 = 10.0f;                                 // Inferred role: weather time bonus sec; original name unknown.
constexpr f32 unknown047 = 30.0f;                                 // Inferred role: weather time bonus all sec; original name unknown.
constexpr u32 WEATHER_UNKNOWN_14 = 1 << 14;                       // Inferred role: weather time bonus rare; original name unknown.
constexpr f32 unknown048 = 3.0f;                                  // Inferred role: weather rare rate; original name unknown.
constexpr f32 unknown049 = 4.0f;                                  // Inferred role: weather fade sec; original name unknown.
constexpr f32 unknown050 = 0.001f;                                // Inferred role: weather start past sec; original name unknown.
constexpr f32 unknown051 = 10800.0f;                              // Inferred role: weather default exist sec; original name unknown.
constexpr u32 WEATHER_UNKNOWN_1 = 1;                              // Inferred role: weather atr cloud2; original name unknown.
constexpr u32 WEATHER_UNKNOWN_2 = 2;                              // Inferred role: weather atr cloud2 late; original name unknown.
constexpr u16 CLOUD2_UNKNOWN_9010 = 9010;                         // Inferred role: cloud2 scenario start; original name unknown.
constexpr u16 CLOUD2_UNKNOWN_9015 = 9015;                         // Inferred role: cloud2 late scenario start; original name unknown.
constexpr u16 CLOUD2_UNKNOWN_10048 = 10048;                       // Inferred role: cloud2 scenario end; original name unknown.

// Inferred role: time bonus of the time ranges set in both the condition bits and the current time range bits; original function name unknown.
static f32 unknown003(const GfFieldTime *time, u32 timeBits) {
  f32 bonus = 0.0f;
  for (u32 range = TIME_RANGE_UNKNOWN_0; range < TIME_RANGE_UNKNOWN_6; range++) {
    u32 rangeBit = 1 << range;
    if ((timeBits & rangeBit) != 0 && (time->getTimeRangeBits() & rangeBit) != 0) {
      bonus = unknown046;
    }
  }

  return bonus;
}

namespace _gffwt {

mm::mtl::FixedList<WeatherInfo *, WEATHER_UNKNOWN_16> s_list;

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
    return info->unknown08;
  }

  return WEATYPE_UNKNOWN_21;
}

WEATHERID getCurrentMapWeatherID(bool isPrevious) {
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    return info->unknown0c;
  }

  return WEATHER_F;
}

u32 getCurrentMapID(bool isPrevious) {
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    return info->unknown18;
  }

  return 0;
}

f32 getCurrentPastSec(bool isPrevious) {
  f32 pastSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    pastSec = info->unknown10;
  }

  return pastSec;
}

f32 getCurrentExistSec(bool isPrevious) {
  f32 existSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    existSec = info->unknown14;
  }

  return existSec;
}

f32 getCurrentFadePastSec(bool isPrevious) {
  f32 fadePastSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    fadePastSec = info->unknown24;
  }

  return fadePastSec;
}

f32 getCurrentFadeExistSec(bool isPrevious) {
  f32 fadeExistSec = 0.0f;
  WeatherInfo *info = getCurrentInfo(isPrevious);
  if (info != nullptr) {
    fadeExistSec = info->unknown28;
  }

  return fadeExistSec;
}

void destroyList() {
  for (mm::mtl::FixedList<WeatherInfo *, WEATHER_UNKNOWN_16>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
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

f32 getTimeBonus(u32 timeBits) {
  GfFieldTime *time = GfFieldTime::get();
  f32 bonus = 0.0f;
  if (time == nullptr) {
    return bonus;
  }

  if (timeBits == WEATHER_TIME_UNKNOWN_7) {
    if ((time->getTimeRangeBits() & WEATHER_TIME_UNKNOWN_7) == 0) {
      return bonus;
    }
  } else if (timeBits == WEATHER_UNKNOWN_8) {
    return bonus;
  } else if (timeBits == WEATHER_UNKNOWN_6) {
    if ((time->getTimeRangeBits() & WEATHER_UNKNOWN_6) == 0) {
      return bonus;
    }
  } else {
    bonus = unknown003(time, timeBits);
    if ((timeBits & WEATHER_UNKNOWN_15) != 0 && (time->getTimeRangeBits() & WEATHER_UNKNOWN_15) != 0) {
      bonus += unknown047;
    }
    return bonus;
  }

  bonus = unknown046;
  return bonus;
}

f32 getWeatherRand() { return (1.0f - ml::mtRandf1()) * unknown045; }

WeatherInfo *getCurrentWeatherInfo() {
  if (s_list.size() != 1 || s_list.back()->unknown20 < 1.0f) {
    return nullptr;
  }

  return s_list.back();
}

WeatherInfo *getFadeinWeatherInfo() {
  if (s_list.empty()) {
    return nullptr;
  }

  if (s_list.size() == 1 && s_list.back()->unknown20 >= 1.0f) {
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
  for (mm::mtl::FixedList<WeatherInfo *, WEATHER_UNKNOWN_16>::iterator it = s_list.begin(); it != s_list.end(); ++it) {
    (*it)->setPause(isPause);
  }
}

} // namespace _gffwt

// Inferred role: weather param of the map saved in the game data, a dummy one when the map has none; original function name unknown.
static unknown119 &unknown001(u32 map) {
  static unknown119 dummy;
  if (map != 0) {
    const char *resource = GfBdatMaplist::get()->getMaplistresource(map);
    if (resource != nullptr) {
      for (unknown119 &info : GfDataManager::getDataGame()->unknown10a53c) {
        if (__builtin_strcmp(info.unknown00.unknown00, resource) == 0) {
          return info;
        }
      }
    }
  }

  return dummy;
}

// Inferred role: applies the weather param to the weather info; original function name unknown.
static void unknown002(WeatherInfo *info, const WeatherParam &param) {
  if (info->unknown0c == 0 || info->unknown0c != param.unknown0c || info->unknown18 == param.unknown18) {
    info->unknown10 = param.unknown10;
    if (param.unknown14 > 0.0f) {
      info->unknown14 = param.unknown14;
    }
  }
  if (info->unknown00[0] == '\0') {
    strcpy(info->unknown00, param.unknown00);
  }
  info->unknown20 = info->unknown24 / info->unknown28;
}

// Inferred role: saves the weather being faded in, or else the current one, in the game data of the map; original function name unknown.
static void unknown004(u32 map) {
  f32 existSec = 0.0f;
  WeatherInfo *info = _gffwt::getFadeinWeatherInfo();
  if (info != nullptr) {
    if (info->unknown0c == WEATHER_F) {
      existSec = unknown051;
    } else {
      u32 timeEnd = GfDataMap::getWeatherTimeEnd(map, info->unknown0c);
      f32 sec = timeEnd * 10.0f * 60.0f;
      f32 halfSec = sec * 0.5f;
      existSec = halfSec + ml::mtRandf1() * halfSec;
    }
  } else {
    info = _gffwt::getCurrentWeatherInfo();
    if (info == nullptr) {
      return;
    }
  }

  WeatherParam &param = unknown001(map).unknown00;
  param.unknown0c = info->unknown0c;
  param.unknown08 = info->unknown08;
  param.unknown10 = info->unknown10;
  param.unknown14 = info->unknown14;
  if (existSec > 0.0f) {
    param.unknown10 = 0.0f;
    param.unknown14 = existSec;
  }
}

// Inferred role: saves the weather being faded in, or else the current one, in the game data of the previous map and of the map having the same weather type; original function name unknown.
static void unknown005(u32 prevMap, u32 map) {
  WeatherInfo *current = _gffwt::getFadeinWeatherInfo();
  if (current == nullptr) {
    current = _gffwt::getCurrentWeatherInfo();
  }
  if (current == nullptr) {
    return;
  }

  if (!GfGameEvent::isMapWeatherEnable()) {
    WeatherParam &param = unknown001(prevMap).unknown00;
    param.unknown0c = current->unknown0c;
    param.unknown08 = current->unknown08;
    param.unknown10 = current->unknown10;
    param.unknown14 = current->unknown14;
  }
  WEATYPE type = current->unknown08;
  if (type == WEATYPE_UNKNOWN_0) {
    return;
  }
  for (int weather = WEATHER_A; weather <= WEATHER_F; weather++) {
    if (type == GfDataMap::getWeatherType(map, static_cast<WEATHERID>(weather))) {
      WeatherParam &param = unknown001(map).unknown00;
      param.unknown0c = static_cast<WEATHERID>(weather);
      param.unknown10 = current->unknown10;
      param.unknown14 = current->unknown14;
      param.unknown08 = current->unknown08;
      return;
    }
  }
}

GfFieldWeather::GfFieldWeather(const GfSetupParam &param)
    : unknown08(false), unknown09(false), unknown0a(false), unknown74(WEATHER_UNKNOWN_0), unknown78(CLOUD_SEA_HANDLE(0)), unknown7c(CLOUD_SEA_REQUEST_UNKNOWN_0), unknown80(CLOUD_SEA_HANDLE(0)),
      unknown84(true) {
  initialize(param);
}

void GfFieldWeather::initialize(const GfSetupParam &) {
  _gffwt::destroyList();
  createCloudSeaDefault();
  unknown08 = true;
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
  weather->unknown10.push(gev);
  weather->unknown60 = info;
}

void GfFieldWeather::gevGameMapModel(GF_OBJ_HANDLE *, bool) {}

void GfFieldWeather::gevPause(u32 resumeBits, u32 pauseBits) {
  if ((pauseBits & PAUSE_BIT_UNKNOWN_0) != 0) {
    _gffwt::setPause(true);
  }
  if ((resumeBits & PAUSE_BIT_UNKNOWN_0) != 0) {
    _gffwt::setPause(false);
  }
}

void GfFieldWeather::execChangeWeather(const WeatherParam &param) {
  get()->unknown09 = false;
  u32 map = param.unknown18;
  if (map == 0) {
    return;
  }

  for (int weather = 4; weather > 0; weather--) {
    if (GfGameCond::isGameCond(GfDataMap::getWeatherForceConditionOn(map, static_cast<WEATHERID>(weather))) && !GfGameEvent::isMapWeatherEnable()) {
      createWeather(map, static_cast<WEATHERID>(weather), unknown049);
      return;
    }
  }

  if (_gffwt::s_list.size() == 1) {
    WeatherInfo *current = _gffwt::s_list.back();
    if (current != nullptr && !(current->unknown20 < 1.0f) && param.unknown08 != 0 && param.unknown08 == current->unknown08 && !_gffwt::isCurrentWeatherEnd()) {
      unknown002(_gffwt::getCurrentWeatherInfo(), param);
      return;
    }
  }
  if (!_gffwt::isCurrentWeatherEnd() && param.unknown0c != 0) {
    createWeather(param, unknown049);
    return;
  }

  for (int weather = 4; weather > 0; weather--) {
    if (GfGameCond::isGameCond(GfDataMap::getWeatherForceConditionOff(map, static_cast<WEATHERID>(weather)))) {
      continue;
    }

    u32 timeBonus = GfDataMap::getWeatherTimeBonus(map, static_cast<WEATHERID>(weather));
    if ((timeBonus & WEATHER_UNKNOWN_14) != 0 && _gffwt::getWeatherRand() < unknown048) {
      createWeather(map, static_cast<WEATHERID>(weather), unknown049);
      break;
    }

    u32 popRate = GfDataMap::getWeatherPopRate(map, static_cast<WEATHERID>(weather));
    if (GfDataMap::getWeatherType(map, static_cast<WEATHERID>(weather)) != WEATYPE_UNKNOWN_0) {
      f32 rate = popRate + _gffwt::getTimeBonus(timeBonus);
      if (rate < 0.0f) {
        rate = 0.0f;
      } else if (rate > unknown045) {
        rate = unknown045;
      }
      if (_gffwt::getWeatherRand() < rate) {
        createWeather(map, static_cast<WEATHERID>(weather), unknown049);
        return;
      }
    }
  }

  WEATHERID weather = WEATHER_F;
  u32 attribute = GfBdatMaplist::get()->getMaplistweatherATR(map);
  if (attribute != 0) {
    u16 scenario = GfDataUtil::getScenarioFlag();
    bool isCloud2 = false;
    if (attribute == WEATHER_UNKNOWN_2) {
      isCloud2 = scenario >= CLOUD2_UNKNOWN_9015 && scenario < CLOUD2_UNKNOWN_10048;
    } else if (attribute == WEATHER_UNKNOWN_1) {
      isCloud2 = scenario >= CLOUD2_UNKNOWN_9010 && scenario < CLOUD2_UNKNOWN_10048;
    }
    if (isCloud2) {
      weather = GfDataMap::getWeatherIdByWeaType(map, WEATYPE_UNKNOWN_12);
    }
  }
  createWeather(map, weather, unknown049);
}

void GfFieldWeather::createWeather(u32 map, WEATHERID weather, f32 fadeSec) {
  if (map == 0) {
    return;
  }

  WEATYPE prevType = _gffwt::getCurrentWtrType(false);
  WEATYPE type = weather == WEATHER_F ? WEATYPE_UNKNOWN_0 : GfDataMap::getWeatherType(map, weather);
  if (prevType == type && _gffwt::getCurrentMapID(false) == map && !_gffwt::isCurrentWeatherEnd()) {
    return;
  }

  f32 existSec = unknown051;
  if (weather != WEATHER_F) {
    u32 timeEnd = GfDataMap::getWeatherTimeEnd(map, weather);
    f32 sec = timeEnd * 10.0f * 60.0f;
    f32 halfSec = sec * 0.5f;
    existSec = halfSec + ml::mtRandf1() * halfSec;
  }

  unknown001(map);
  _gffwt::destroyFadeWeather();
  if (_gffwt::s_list.size() == 1) {
    WeatherInfo *current = _gffwt::s_list.front();
    if (current->unknown08 == type && current->unknown18 == map) {
      current->resetParam(unknown050, existSec, fadeSec);
      return;
    }
  }

#line 724
  WeatherInfo *info = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WeatherInfo(type, map, weather, unknown050, existSec, fadeSec);
  _gffwt::s_list.push_back(info);
  if (_gffwt::s_list.front() != info) {
    _gffwt::s_list.front()->fadeoutEnv();
  }
  applyNowMapWeatherForMapModel(map);
  if (prevType != _gffwt::getCurrentWtrType(false)) {
    GfEvent::callChangeWeather(_gffwt::getCurrentWtrType(false), prevType);
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
  if (attribute == WEATHER_UNKNOWN_1) {
    return scenario >= CLOUD2_UNKNOWN_9010 && scenario < CLOUD2_UNKNOWN_10048;
  }
  if (attribute == WEATHER_UNKNOWN_2) {
    return scenario >= CLOUD2_UNKNOWN_9015 && scenario < CLOUD2_UNKNOWN_10048;
  }

  return false;
}

void GfFieldWeather::createWeather(const WeatherParam &param, f32 fadeSec) {
  if (param.unknown0c == 0) {
    return;
  }

  createWeather(param.unknown18, param.unknown0c, fadeSec);
  WeatherInfo *info = _gffwt::getFadeinWeatherInfo();
  if (info == nullptr) {
    info = _gffwt::getCurrentWeatherInfo();
  }
  if (info == nullptr) {
    return;
  }

  unknown002(info, param);
}

void GfFieldWeather::execChangeCloud(u32 map) { setCloudSeaForDebug(map, GfDataMap::getCloudType(map)); }

void GfFieldWeather::setCloudSeaForDebug(u32, CLOUD_SEA cloudSea) {
  if (get() != nullptr) {
    get()->unknown7c = cloudSea != 0 ? CLOUD_SEA_REQUEST_UNKNOWN_2 : CLOUD_SEA_REQUEST_UNKNOWN_1;
  }
}

WEATYPE GfFieldWeather::getCurrentWtrType(bool isPrevious) { return _gffwt::getCurrentWtrType(isPrevious); }

u32 GfFieldWeather::getCurrentWtrTypeBit(bool isPrevious) {
  WEATYPE type = getCurrentWtrType(isPrevious);
  return type == WEATYPE_UNKNOWN_0 ? 0 : 1 << type;
}

WEATHERID GfFieldWeather::getCurrentMapWeatherID(bool isPrevious) { return _gffwt::getCurrentMapWeatherID(isPrevious); }

u32 GfFieldWeather::getCurrentMapWeatherBit(bool isPrevious) { return 1 << (getCurrentMapWeatherID(isPrevious) - 1); }

f32 GfFieldWeather::getCurrentPastSec(bool isPrevious) {
  if (isPrevious) {
    f32 fadePastSec = _gffwt::getCurrentFadePastSec(true);
    f32 fadeExistSec = _gffwt::getCurrentFadeExistSec(true);
    if (fadePastSec > 0.0f) {
      return fadeExistSec - fadePastSec;
    }
  }

  f32 fadePastSec = _gffwt::getCurrentFadePastSec(isPrevious);
  f32 fadeExistSec = _gffwt::getCurrentFadeExistSec(isPrevious);
  if (fadeExistSec > 0.0f && fadeExistSec <= fadePastSec) {
    return _gffwt::getCurrentPastSec(isPrevious);
  }

  return fadePastSec;
}

f32 GfFieldWeather::getCurrentExistSec(bool isPrevious) {
  if (isPrevious) {
    f32 fadePastSec = _gffwt::getCurrentFadePastSec(true);
    f32 fadeExistSec = _gffwt::getCurrentFadeExistSec(true);
    if (fadePastSec > 0.0f) {
      return fadeExistSec;
    }
  }

  f32 fadePastSec = _gffwt::getCurrentFadePastSec(isPrevious);
  f32 fadeExistSec = _gffwt::getCurrentFadeExistSec(isPrevious);
  if (fadeExistSec > 0.0f && fadeExistSec <= fadePastSec) {
    return _gffwt::getCurrentExistSec(isPrevious);
  }

  return fadeExistSec;
}

const char *GfFieldWeather::getCurrentEffName(bool isPrevious) { return GfDataMap::getWeatherEffName(getCurrentWtrType(isPrevious)); }

const char *GfFieldWeather::getCurrentSndName(bool isPrevious) { return GfDataMap::getWeatherSndName(getCurrentWtrType(isPrevious)); }

const char *GfFieldWeather::getCurrentWeatherName(bool isPrevious) { return GfDataMap::getWeatherName(getCurrentWtrType(isPrevious)); }

void GfFieldWeather::createWeatherForce(WEATYPE type, f32 fadeSec, const char *effect) {
  WEATYPE prevType = _gffwt::getCurrentWtrType(false);
  if (effect == nullptr && prevType == type) {
    return;
  }

  _gffwt::destroyFadeWeather();
  if (_gffwt::s_list.size() == 1) {
    WeatherInfo *current = _gffwt::s_list.front();
    if (effect == nullptr && current->unknown08 == type) {
      current->resetParam(unknown050, unknown050, fadeSec);
      return;
    }
  }

#line 783
  WeatherInfo *info = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) WeatherInfo(type, GfGameManager::getMapID(), WEATHER_A, unknown050, unknown051, fadeSec);
  info->setForceEffect(effect);
  _gffwt::s_list.push_back(info);
  if (_gffwt::s_list.front() != info) {
    _gffwt::s_list.front()->fadeoutEnv();
  }
  applyNowMapWeatherForMapModel(GfGameManager::getMapID());
  if (__builtin_strcmp(GfDataMap::getWeatherName(type), "Unknown") != 0) {
    GfMapManager::setEnvWeather(_gffwt::getCurrentWtrType(false));
  }
  if (prevType != _gffwt::getCurrentWtrType(false)) {
    GfEvent::callChangeWeather(_gffwt::getCurrentWtrType(false), prevType);
  }
}

void GfFieldWeather::updateEvent(const fw::UpdateInfo &info) {
  while (!unknown10.empty()) {
    switch (unknown10.front()) {
    case GEV_UNKNOWN_1:
      unknown005(unknown60.unknown08, unknown60.unknown04);
      unknown0a = false;
      break;
    case GEV_UNKNOWN_2:
      if (unknown60.unknown08 != unknown60.unknown04) {
        setCurrentRemainSecZero();
        updateWeather(info);
      }
      applyNowMapWeather(unknown60.unknown08, unknown60.unknown04);
      unknown0a = true;
      break;
    case GEV_UNKNOWN_5:
      if (GfGameManager::isStartGame()) {
        createWeather(unknown001(GfGameManager::getMapID()).unknown00, unknown049);
      }
      applyNowMapWeatherForMapModel(unknown60.unknown04);
      setCloudSea(unknown60.unknown04, GfDataMap::getCloudType(unknown60.unknown04));
      break;
    default:
      break;
    }
    unknown10.pop_front();
  }

  WEATHERID tempWeather = GfGameEnv::getTempWeather();
  WEATHERID prevTempWeather = unknown74;
  if (tempWeather == WEATHER_UNKNOWN_0) {
    if (prevTempWeather == WEATHER_UNKNOWN_0) {
      return;
    }
    unknown74 = WEATHER_UNKNOWN_0;
    applyNowMapWeather(unknown60.unknown08, unknown60.unknown04);
    return;
  }

  unknown74 = tempWeather;
  if (prevTempWeather == WEATHER_UNKNOWN_0) {
    unknown004(GfGameManager::getMapID());
  }
  if (_gffwt::getCurrentMapWeatherID(false) != tempWeather) {
    setMapWeatherID(tempWeather);
  }
}

void GfFieldWeather::setCurrentRemainSecZero() {
  if (_gffwt::s_list.size() == 1) {
    WeatherInfo *info = _gffwt::s_list.front();
    info->unknown10 = info->unknown14;
  }
}

void GfFieldWeather::updateWeather(const fw::UpdateInfo &info) {
  if (!unknown0a) {
    return;
  }

  fw::UpdateInfo updateInfo = info;
  if (GfPause::isPause(PAUSE_BIT_UNKNOWN_0)) {
    updateInfo.unknown08 = GfGameManager::getFieldSpeed(updateInfo);
    updateInfo.unknown04 = updateInfo.unknown08 * updateInfo.unknown04;
  }

  WeatherInfo *fadein = _gffwt::getFadeinWeatherInfo();
  if (fadein != nullptr) {
    fadein->updateFadein(updateInfo);
  }
  WeatherInfo *fadeout = _gffwt::getFadeoutWeatherInfo();
  if (fadeout != nullptr && fadeout->updateFadeout(updateInfo)) {
    _gffwt::destroyFadeWeather();
    if (__builtin_strcmp(GfDataMap::getWeatherName(_gffwt::getCurrentWtrType(false)), "Unknown") != 0) {
      GfMapManager::setEnvWeather(_gffwt::getCurrentWtrType(false));
    }
  }

  WeatherInfo *current = _gffwt::getCurrentWeatherInfo();
  if (current == nullptr) {
    return;
  }

  current->update(updateInfo, false);
  bool isChanged = false;
  if (current->isTimeup() && !isInfiniteTime()) {
    execChangeWeather(unknown001(current->unknown18).unknown00);
    isChanged = true;
  }

  if (!current->isTimeRangeOK() && !isInfiniteTime()) {
    execChangeWeather(unknown001(current->unknown18).unknown00);
  } else if (current->unknown0c < WEATHER_F && GfGameCond::isGameCond(GfDataMap::getWeatherForceConditionOff(current->unknown18, current->unknown0c)) && !GfGameEvent::isMapWeatherEnable()) {
    execChangeWeather(unknown001(current->unknown18).unknown00);
  } else if (!isChanged) {
    for (int weather = WEATHER_A; weather <= WEATHER_D; weather++) {
      if (current->unknown0c != weather && GfGameCond::isGameCond(GfDataMap::getWeatherForceConditionOn(current->unknown18, static_cast<WEATHERID>(weather))) && !GfGameEvent::isMapWeatherEnable()) {
        execChangeWeather(unknown001(current->unknown18).unknown00);
        break;
      }
    }
  }

  if (!GfGameManager::isEvent(false) && GfGameManager::isControlFree()) {
    unknown004(GfGameManager::getMapID());
  }
}

void GfFieldWeather::applyNowMapWeather(u32 prevMap, u32 map) {
  if (GfGameManager::isStartGame()) {
    return;
  }

  setupGame();
  execChangeWeather(unknown001(map).unknown00);
  setCloudSeaForDebug(map, GfDataMap::getCloudType(map));
  if (map != prevMap) {
    setCurrentRemainSecZero();
  }
}

void GfFieldWeather::setCloudSea(u32, CLOUD_SEA cloudSea) {
  GfFieldWeather *weather = get();
  weather->unknown7c = cloudSea != 0 ? CLOUD_SEA_REQUEST_UNKNOWN_2 : CLOUD_SEA_REQUEST_UNKNOWN_1;
}

void GfFieldWeather::setMapWeatherID(WEATHERID weather) {
  if (get() != nullptr) {
    get()->createWeather(GfGameManager::getMapID(), weather, unknown049);
  }
}

bool GfFieldWeather::isInfiniteTime() { return get()->unknown09; }

bool GfFieldWeather::isWeatherSE() { return _gffwt::isCurrentSE(); }

void GfFieldWeather::setWeatherForEvent(WEATYPE type, const char *effect) {
  if (get() != nullptr) {
    get()->createWeatherForce(type, unknown049, effect);
  }
}

void GfFieldWeather::setWeather(WEATYPE type, bool isTimeLimited) {
  GfFieldWeather *weather = get();
  if (weather == nullptr) {
    return;
  }

  if (type == WEATYPE_UNKNOWN_0) {
    weather->unknown09 = !isTimeLimited;
    weather->createWeather(GfGameManager::getMapID(), WEATHER_F, unknown049);
  }
  for (int id = WEATHER_A; id <= WEATHER_D; id++) {
    if (GfDataMap::getWeatherType(GfGameManager::getMapID(), static_cast<WEATHERID>(id)) == type) {
      weather->unknown09 = !isTimeLimited;
      setMapWeatherID(static_cast<WEATHERID>(id));
      return;
    }
  }
}

bool GfFieldWeather::getWeatherName(u8 *&bdat, u32 &textId) { return GfDataMap::getWeatherName(bdat, textId, getCurrentWtrType(false)); }

const char *GfFieldWeather::getWeatherName() { return GfDataMap::getWeatherName(getCurrentWtrType(false)); }

void GfFieldWeather::setupGame() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->unknown10a53c[0].unknown00.unknown00[0] != '\0') {
    return;
  }

  GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
  for (u32 map = bdatMaplist->getMaplistStart(); map < bdatMaplist->getMaplistEnd(); map++) {
    const char *resource = bdatMaplist->getMaplistresource(map);
    for (unknown119 &info : dataGame->unknown10a53c) {
      WeatherParam &param = info.unknown00;
      if (__builtin_strcmp(param.unknown00, resource) == 0) {
        break;
      }
      if (param.unknown00[0] == '\0') {
        __builtin_strcpy(param.unknown00, resource);
        param.unknown18 = map;
        break;
      }
    }
  }

  u32 map = GfDataMap::getMapID(GfDataManager::getDataGame()->unknown1097f0.unknownc0);
  setCloudSeaForDebug(map, static_cast<CLOUD_SEA>(dataGame->unknown10a53c[map].unknown1c));
}

void GfFieldWeather::updateCloudSea(const fw::UpdateInfo &) {
  u32 map = GfGameManager::getMapID();
  if (GfGameCond::isGameCond(GfBdatMaplist::get()->getMaplistebb_ON_cndID(map))) {
    if (unknown80 == 0) {
      createCloudSeaCondition();
      GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(1));
    }
  } else {
    if (unknown80 != 0) {
      destroyCloudSeaCondition();
      GfGameUtilCloudSea::setInnCloudSea(static_cast<CLOUD_SEA>(0));
    }
    applyCloudSelect();
  }
}

void GfFieldWeather::createCloudSeaCondition() {
  destroyCloudSeaCondition();
  unknown80 = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(1), static_cast<CLOUD_SEA_PRIO>(1));
}

void GfFieldWeather::destroyCloudSeaCondition() {
  if (unknown80 != 0) {
    GfGameEnv::destroyCloudSea(unknown80);
    unknown80 = static_cast<CLOUD_SEA_HANDLE>(0);
  }
}

void GfFieldWeather::applyCloudSelect() {
  if (unknown7c != CLOUD_SEA_REQUEST_UNKNOWN_0) {
    GfGameEnv::setCloudSea(unknown78, static_cast<CLOUD_SEA>(unknown7c != CLOUD_SEA_REQUEST_UNKNOWN_1));
    unknown7c = CLOUD_SEA_REQUEST_UNKNOWN_0;
  }
}

void GfFieldWeather::createCloudSeaDefault() {
  destroyCloudSeaDefault();
  unknown78 = GfGameEnv::createCloudSea(static_cast<CLOUD_SEA>(0), static_cast<CLOUD_SEA_PRIO>(0));
}

void GfFieldWeather::destroyCloudSeaDefault() {
  if (unknown78 != 0) {
    GfGameEnv::destroyCloudSea(unknown78);
    unknown78 = static_cast<CLOUD_SEA_HANDLE>(0);
  }
}

CLOUD_SEA GfFieldWeather::getCloudSeaCondition() { return GfGameEnv::getCloudType(get()->unknown80); }

CLOUD_SEA GfFieldWeather::getCloudSea(u32 map) {
  if (map != 0) {
    return static_cast<CLOUD_SEA>(GfDataManager::getDataGame()->unknown10a53c[map].unknown1c != 0);
  }

  return GfGameEnv::getCurrentCloudSea();
}

CLOUD_SEA GfFieldWeather::getCurrentCloudSea() { return GfGameEnv::getCurrentCloudSea(); }

void GfFieldWeather::setDispWeather(bool isDisp) {
  if (get() != nullptr) {
    get()->unknown84 = isDisp;
  }
}

bool GfFieldWeather::isDispWeather() {
  if (get() != nullptr) {
    return get()->unknown84;
  }

  return false;
}

void GfFieldWeather::clear() {
  GfFieldWeather *weather = get();
  _gffwt::destroyList();
  weather->destroyCloudSeaCondition();
}

void GfFieldWeather::build(const GfSetupParam &param) {
  // __LINE__ must be 1330 as in the original file: it is the line argument of operator new.
#line 1330
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfFieldWeather(param);
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
  unknown08 = false;
}

bool GfFieldWeather::isInitialized() {
  if (get() != nullptr) {
    return get()->unknown08;
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
