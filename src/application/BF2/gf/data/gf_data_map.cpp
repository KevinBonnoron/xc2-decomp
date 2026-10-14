#include "gf/data/gf_data_map.h"
#include "bdat.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  FLAG_MAP_COMPLETE = 0x33d2,
  FLAG_ZONE_COMPLETE = 0x33e1,
};

enum {
  BDAT_MAP_JUMP = 0xa1,
  BDAT_MAP_JUMP_EXTRA = 0xa2,
};

enum {
  SCENARIO_FLAG_ARCADIA_DESTROY = 0x1f65,
};

constexpr u32 ZONE_COUNT = 8;
constexpr u32 ZONE_ELPIS = 8;
constexpr u32 TIME_RANGE_COUNT = 9;
constexpr u32 WEATHER_COUNT = 4;

bool GfDataMap::getName(u8 *&bdat, u32 &textId, u32 map) {
  textId = GfBdatMaplist::get()->getMaplistnameID(map);
  bdat = GfBdatMsg::getFpMapInfo();
  return textId != 0;
}

const char *GfDataMap::getName(u32 map) {
  u8 *bdat;
  u32 textId;
  if (getName(bdat, textId, map)) {
    const char *name = Bdat::getMSText(bdat, textId);
    if (name != nullptr) {
      return name;
    }
  }

  return "";
}

bool GfDataMap::getZoneName(u8 *&bdat, u32 &textId, u32 zone) {
  switch (zone) {
  case 1:
    return getName(bdat, textId, MAP_AVARITIA);
  case 2:
    return getName(bdat, textId, MAP_GULA);
  case 3:
    return getName(bdat, textId, MAP_INVIDIA);
  case 4:
    return getName(bdat, textId, MAP_SUPERBIA);
  case 5:
    return getName(bdat, textId, MAP_LIBERALITAS);
  case 6:
    return getName(bdat, textId, MAP_ARCADIA);
  case 7:
    return getName(bdat, textId, MAP_LUXURIA);
  case 8:
    return getName(bdat, textId, MAP_ELPIS);
  default:
    return false;
  }
}

u32 GfDataMap::getZoneIdForDevelopPoint(u32 map) {
  if (map == 0 || GfBdatMaplist::get() == nullptr) {
    return 0;
  }

  return GfBdatMaplist::get()->getMaplistzone(map);
}

u32 GfDataMap::getZoneIdForGameMap(u32 map) {
  u32 zone = getZoneIdForDevelopPoint(map);
  if (zone == 0) {
    return 0;
  }

  if (map == MAP_ELPIS) {
    return ZONE_ELPIS;
  }

  return zone;
}

const char *GfDataMap::getZoneName(u32 zone) {
  u8 *bdat;
  u32 textId;
  const char *name = getZoneName(bdat, textId, zone) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (name == nullptr) {
    name = "";
  }

  return name;
}

u32 GfDataMap::getFieldZoneId(u32 fieldZone) {
  switch (fieldZone) {
  case 0:
    return 1;
  case 1:
    return 2;
  case 2:
    return 3;
  case 3:
    return 4;
  case 4:
    return 7;
  case 5:
    return 5;
  case 6:
    return 6;
  default:
    return 0;
  }
}

bool GfDataMap::isMapCompleteFlag(u32 map) { return GfGameFlag::getLocal(1, FLAG_MAP_COMPLETE + map) != 0; }

void GfDataMap::setMapCompleteFlag(u32 map) { GfGameFlag::setLocal(1, FLAG_MAP_COMPLETE + map, 1); }

bool GfDataMap::isZoneCompleteFlag(u32 zone) {
  if (zone >= 1 && zone <= ZONE_COUNT) {
    return GfGameFlag::getLocal(1, FLAG_ZONE_COMPLETE) != 0;
  }

  return false;
}

SDataMap *GfDataMap::getSDataMap() { return &GfDataManager::getDataGame()->map; }

const char *GfDataMap::getMapResourceName(u32 mapJump) {
  u32 map = getMapID(mapJump);
  if (map == 0) {
    return "";
  }

  return GfBdatMaplist::get()->getMaplistresource(map);
}

u32 GfDataMap::getMapID(u32 mapJump) {
  if (mapJump == 0) {
    return 0;
  }

  u8 *bdat = GfDataBdat::getFP(BDAT_MAP_JUMP);
  u8 *bdatExtra = GfDataBdat::getFP(BDAT_MAP_JUMP_EXTRA);
  int id = mapJump;
  u8 map = 0;
  if (id >= Bdat::getIdTop(bdat) && id < Bdat::getIdTop(bdat) + Bdat::getIdCount(bdat)) {
    map = Bdat::getValCheck(bdat, "MapList", id, 1);
  } else if (id >= Bdat::getIdTop(bdatExtra) && id < Bdat::getIdTop(bdatExtra) + Bdat::getIdCount(bdatExtra)) {
    map = Bdat::getValCheck(bdatExtra, "MapList", id, 1);
  }

  return map;
}

const char *GfDataMap::getMapResourceNameByMapID(u32 map) {
  if (map == 0) {
    return nullptr;
  }

  return GfBdatMaplist::get()->getMaplistresource(map);
}

u32 GfDataMap::getMapJumpID(u32 map) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MAP_JUMP);
  u32 mapJump = Bdat::getIdTop(bdat);
  u32 end = mapJump + Bdat::getIdCount(bdat);
  for (; mapJump < end; mapJump++) {
    if (static_cast<u8>(Bdat::getValCheck(bdat, "MapList", mapJump, 1)) == map) {
      return mapJump;
    }
  }

  return 0;
}

bool GfDataMap::getTimeRangeName(u8 *&bdat, u32 &textId, u32 time) {
  if (time < TIME_RANGE_COUNT) {
    GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
    bdat = GfBdatMsg::getFpMapInfo();
    textId = bdatMaplist->getTimeInfomsg(time);
    return textId != 0;
  }

  return false;
}

const char *GfDataMap::getTimeRangeName(u32 time) {
  u8 *bdat;
  u32 textId;
  const char *name = getTimeRangeName(bdat, textId, time) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataMap::getWeatherName(u8 *&bdat, u32 &textId, WEATYPE weatherType) {
  if (static_cast<int>(weatherType) < 1) {
    return false;
  }

  GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
  bdat = GfBdatMsg::getFpMapInfo();
  textId = bdatMaplist->getWeatherInfomsg(weatherType);
  return textId != 0;
}

const char *GfDataMap::getWeatherName(WEATYPE weatherType) {
  if (weatherType == WEATYPE_DEFAULT) {
    return "Default";
  }

  u8 *bdat;
  u32 textId;
  const char *name = getWeatherName(bdat, textId, weatherType) ? Bdat::getMSText(bdat, textId) : nullptr;
  if (name == nullptr) {
    name = "";
  }

  return name;
}

const char *GfDataMap::getWeatherIDName(WEATHERID weather) {
  static const char *const weatherIdNames[] = {
      "NULL",
      "WEATHER_A",
      "WEATHER_B",
      "WEATHER_C",
      "WEATHER_D",
      "WEATHER_F",
  };

  return weatherIdNames[weather];
}

const char *GfDataMap::getWeatherEffName(WEATYPE weatherType) {
  if (weatherType == WEATYPE_DEFAULT) {
    return "";
  }

  return GfBdatMaplist::get()->getWeatherInfoeff(weatherType);
}

const char *GfDataMap::getWeatherSndName(WEATYPE weatherType) {
  if (weatherType == WEATYPE_DEFAULT) {
    return "";
  }

  return GfBdatMaplist::get()->getWeatherInfosnd(weatherType);
}

const char *GfDataMap::getWeatherSndBeginName(WEATYPE weatherType) {
  if (weatherType == WEATYPE_DEFAULT) {
    return "";
  }

  return GfBdatMaplist::get()->getWeatherInfosndBegin(weatherType);
}

u32 GfDataMap::getWeatherForceConditionOn(u32 map, WEATHERID weather) { return GfBdatMaplist::get()->getMaplistw_ON_cndID(map, weather - 1); }

u32 GfDataMap::getWeatherForceConditionOff(u32 map, WEATHERID weather) { return GfBdatMaplist::get()->getMaplistw_OFF_cndID(map, weather - 1); }

u32 GfDataMap::getWeatherTimeBonus(u32 map, WEATHERID weather) { return GfBdatMaplist::get()->getMaplistw_time_BNS(map, weather - 1); }

u32 GfDataMap::getWeatherTimeEnd(u32 map, WEATHERID weather) { return GfBdatMaplist::get()->getMaplistw_end_time(map, weather - 1); }

u32 GfDataMap::getWeatherPopRate(u32 map, WEATHERID weather) { return GfBdatMaplist::get()->getMaplistw_pop_rate(map, weather - 1); }

WEATYPE GfDataMap::getWeatherType(u32 map, WEATHERID weather) {
  u32 index = weather - 1;
  if (index >= WEATHER_COUNT) {
    return WEATYPE_INVALID;
  }

  return static_cast<WEATYPE>(GfBdatMaplist::get()->getMaplistw_type(map, index));
}

WEATHERID GfDataMap::getWeatherIdByWeaType(u32 map, WEATYPE weatherType) {
  GfBdatMaplist *bdatMaplist = GfBdatMaplist::get();
  if (bdatMaplist->getMaplistw_type(map, 0) == static_cast<u32>(weatherType)) {
    return WEATHER_A;
  }

  if (bdatMaplist->getMaplistw_type(map, 1) == static_cast<u32>(weatherType)) {
    return WEATHER_B;
  }

  if (bdatMaplist->getMaplistw_type(map, 2) == static_cast<u32>(weatherType)) {
    return WEATHER_C;
  }

  if (bdatMaplist->getMaplistw_type(map, 3) == static_cast<u32>(weatherType)) {
    return WEATHER_D;
  }

  return WEATHER_F;
}

CLOUD_SEA GfDataMap::getCloudType(u32 map) { return static_cast<CLOUD_SEA>(GfDataManager::getDataGame()->mapInfos[map].cloudType != 0); }

void GfDataMap::setCloudType(u32 map, CLOUD_SEA cloudType) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->mapInfos[map].cloudType = cloudType != 0;
}

bool GfDataMap::isArcadiaDestroy() { return GfDataUtil::getScenarioFlag() >= SCENARIO_FLAG_ARCADIA_DESTROY; }

} // namespace gf
