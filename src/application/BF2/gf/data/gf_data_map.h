#pragma once
#include "mm_math/mm_vec3.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum WEATYPE {
  WEATYPE_UNKNOWN_0 = 0,     // Inferred role: weatype default; original name unknown.
  WEATYPE_UNKNOWN_12 = 12,   // Inferred role: weather type of the second cloud sea; original enumerator name unknown.
  WEATYPE_UNKNOWN_21 = 0x15, // Inferred role: weatype invalid; original name unknown.
};

// WEATHER_A to WEATHER_F are the strings of the game's weather id table (GfDataMap::getWeatherIDName: "NULL", "WEATHER_A", "WEATHER_B", "WEATHER_C", "WEATHER_D", "WEATHER_F").
enum WEATHERID {
  WEATHER_UNKNOWN_0, // Inferred role: weather null; original name unknown.
  WEATHER_A,
  WEATHER_B,
  WEATHER_C,
  WEATHER_D,
  WEATHER_F,
};

enum CLOUD_SEA {};

enum {
  MAP_UNKNOWN_3 = 3,   // Inferred role: map avaritia; original name unknown.
  MAP_UNKNOWN_6 = 6,   // Inferred role: map gula; original name unknown.
  MAP_UNKNOWN_7 = 7,   // Inferred role: first map shown with the sepia filter; original name unknown.
  MAP_UNKNOWN_9 = 9,   // Inferred role: map invidia; original name unknown.
  MAP_UNKNOWN_10 = 10, // Inferred role: map superbia; original name unknown.
  MAP_UNKNOWN_12 = 12, // Inferred role: map arcadia; original name unknown.
  MAP_UNKNOWN_13 = 13, // Inferred role: map luxuria; original name unknown.
  MAP_UNKNOWN_14 = 14, // Inferred role: map liberalitas; original name unknown.
  MAP_UNKNOWN_15 = 15, // Inferred role: map elpis; original name unknown.
  MAP_UNKNOWN_17 = 17, // Inferred role: second map shown with the sepia filter; original name unknown.
  MAP_UNKNOWN_19 = 19, // Inferred role: third map shown with the sepia filter; original name unknown.
};

// Inferred role: save data map; original type name unknown.
struct unknown118 {
  mm::Vec3 unknown00[3]; // Inferred role: driver save pos; original member name unknown.
  mm::Vec3 unknown30[3]; // Inferred role: blade save pos; original member name unknown.
  mm::Vec3 unknown60[3]; // Inferred role: driver save rot; original member name unknown.
  mm::Vec3 unknown90[3]; // Inferred role: blade save rot; original member name unknown.
  u32 unknownc0;         // Inferred role: skip travel id; original member name unknown.
};

static_assert(offsetof(unknown118, unknown30) == 0x030, "");
static_assert(offsetof(unknown118, unknown60) == 0x060, "");
static_assert(offsetof(unknown118, unknown90) == 0x090, "");
static_assert(offsetof(unknown118, unknownc0) == 0x0c0, "");
static_assert(sizeof(unknown118) == 0x0d0, "");

struct WeatherParam {
  // The game's SDataGame constructor and the weather dummy of gf_field_weather.cpp zero these members in this order, leaving the tail of the resource unset.
  WeatherParam() : unknown08(WEATYPE_UNKNOWN_0), unknown0c(WEATHER_UNKNOWN_0), unknown10(0.0f), unknown14(0.0f), unknown18(0) { unknown00[0] = '\0'; }

  char unknown00[8];   // Inferred role: resource; original member name unknown.
  WEATYPE unknown08;   // Inferred role: type; original member name unknown.
  WEATHERID unknown0c; // Inferred role: weather; original member name unknown.
  f32 unknown10;       // Inferred role: past sec; original member name unknown.
  f32 unknown14;       // Inferred role: exist sec; original member name unknown.
  u32 unknown18;       // Inferred role: map; original member name unknown.
};

static_assert(sizeof(WeatherParam) == 0x1c, "");

// Inferred role: save data map info; original type name unknown.
struct unknown119 {
  unknown119() : unknown1c(0) {}

  WeatherParam unknown00; // Inferred role: weather param; original member name unknown.
  u32 unknown1c;          // Inferred role: cloud type; original member name unknown.
};

static_assert(offsetof(unknown119, unknown1c) == 0x1c, "");
static_assert(sizeof(unknown119) == 0x20, "");

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
  static unknown118 *getSDataMap();
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
  static CLOUD_SEA getCloudType(u32 map);
  static void setCloudType(u32 map, CLOUD_SEA cloudType);
  static void resetCloudType();
  static bool isArcadiaDestroy();
  static u32 getDevelopMapId(u32 map);
};

} // namespace gf
