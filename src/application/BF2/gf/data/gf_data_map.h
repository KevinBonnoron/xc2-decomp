#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum WEATYPE {
  WEATYPE_DEFAULT = 0,
  WEATYPE_INVALID = 0x15,
};

enum WEATHERID {
  WEATHER_NULL,
  WEATHER_A,
  WEATHER_B,
  WEATHER_C,
  WEATHER_D,
  WEATHER_F,
};

enum CLOUD_SEA {};

enum {
  MAP_AVARITIA = 3,
  MAP_GULA = 6,
  MAP_INVIDIA = 9,
  MAP_SUPERBIA = 10,
  MAP_ARCADIA = 12,
  MAP_LUXURIA = 13,
  MAP_LIBERALITAS = 14,
  MAP_ELPIS = 15,
};

struct SDataMap {
  mm::Vec3 driverSavePos[3];
  mm::Vec3 bladeSavePos[3];
  mm::Vec3 driverSaveRot[3];
  mm::Vec3 bladeSaveRot[3];
  u32 skipTravelID;
};

static_assert(offsetof(SDataMap, bladeSavePos) == 0x030, "");
static_assert(offsetof(SDataMap, driverSaveRot) == 0x060, "");
static_assert(offsetof(SDataMap, bladeSaveRot) == 0x090, "");
static_assert(offsetof(SDataMap, skipTravelID) == 0x0c0, "");
static_assert(sizeof(SDataMap) == 0x0d0, "");

struct SDataMapInfo {
  u8 _00[0x1c - 0x00];
  u32 cloudType;
};

static_assert(offsetof(SDataMapInfo, cloudType) == 0x1c, "");
static_assert(sizeof(SDataMapInfo) == 0x20, "");

class GfDataMap {
public:
  static bool getName(u8 *&bdat, u32 &textId, u32 map);
  static const char *getName(u32 map);
  static bool getZoneName(u8 *&bdat, u32 &textId, u32 zone);
  static u32 getZoneIdForDevelopPoint(u32 map);
  static u32 getZoneIdForGameMap(u32 map);
  static const char *getZoneName(u32 zone);
  static u32 getFieldZoneId(u32 fieldZone);
  static bool isMapCompleteFlag(u32 map);
  static void setMapCompleteFlag(u32 map);
  static bool isZoneCompleteFlag(u32 zone);
  static SDataMap *getSDataMap();
  static const char *getMapResourceName(u32 mapJump);
  static u32 getMapID(u32 mapJump);
  static const char *getMapResourceNameByMapID(u32 map);
  static u32 getMapJumpID(u32 map);
  static bool getTimeRangeName(u8 *&bdat, u32 &textId, u32 time);
  static const char *getTimeRangeName(u32 time);
  static bool getWeatherName(u8 *&bdat, u32 &textId, WEATYPE weatherType);
  static const char *getWeatherName(WEATYPE weatherType);
  static const char *getWeatherIDName(WEATHERID weather);
  static const char *getWeatherEffName(WEATYPE weatherType);
  static const char *getWeatherSndName(WEATYPE weatherType);
  static const char *getWeatherSndBeginName(WEATYPE weatherType);
  static u32 getWeatherForceConditionOn(u32 map, WEATHERID weather);
  static u32 getWeatherForceConditionOff(u32 map, WEATHERID weather);
  static u32 getWeatherTimeBonus(u32 map, WEATHERID weather);
  static u32 getWeatherTimeEnd(u32 map, WEATHERID weather);
  static u32 getWeatherPopRate(u32 map, WEATHERID weather);
  static WEATYPE getWeatherType(u32 map, WEATHERID weather);
  static WEATHERID getWeatherIdByWeaType(u32 map, WEATYPE weatherType);
  static bool getCloudType(u32 map);
  static void setCloudType(u32 map, CLOUD_SEA cloudType);
  static bool isArcadiaDestroy();
};

} // namespace gf
