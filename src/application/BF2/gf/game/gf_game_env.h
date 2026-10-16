#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace mm {
struct Vec3;
}

namespace gf {

struct GfSetupParam;

enum CFILTER_HANDLE {};
enum CLOUD_SEA_PRIO {};
enum CLOUD_SEA_HANDLE {};
enum WEATHER_PRIO {};
enum WEATHER_HANDLE {};

struct ColorFilter {
  int filter;
  int farFilter;
  f32 time;
  CFILTER_HANDLE handle;
  int prio;
};

static_assert(sizeof(ColorFilter) == 0x14, "");

struct CloudSea {
  CLOUD_SEA cloudSea;
  CLOUD_SEA_PRIO prio;
  CLOUD_SEA_HANDLE handle;
};

static_assert(sizeof(CloudSea) == 0xc, "");

struct WeatherSet {
  WEATHERID weather;
  WEATHER_PRIO prio;
  WEATHER_HANDLE handle;
};

static_assert(sizeof(WeatherSet) == 0xc, "");

class GfGameEnv : public mm::mtl::PtrSingleton<GfGameEnv> {
public:
  static const u32 FILTER_MAX = 16;

  static void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  GfGameEnv(const GfSetupParam &param);
  ~GfGameEnv();
  static bool isStopEnemySearch();
  static bool isMapjumpBlackout();
  static bool isMapjump();
  static bool isMapjumpWithSaveData();
  static u32 getMapJumpID();
  static u32 getMapID();
  static void setMapID(u32 mapJump, u32 map);
  static CFILTER_HANDLE createColorFilter(const ColorFilter &filter);
  static void destroyColorFilter(CFILTER_HANDLE handle);
  static void setColorFilter(CFILTER_HANDLE handle, const ColorFilter &filter);
  static CLOUD_SEA_HANDLE createCloudSea(CLOUD_SEA cloudSea, CLOUD_SEA_PRIO prio);
  static void destroyCloudSea(CLOUD_SEA_HANDLE handle);
  static void setCloudSea(CLOUD_SEA_HANDLE handle, CLOUD_SEA cloudSea);
  static CLOUD_SEA getCloudType(CLOUD_SEA_HANDLE handle);
  static CLOUD_SEA getCurrentCloudSea();
  static void gevMapjump(GEV event, const MapjumpCallbackInfo &info);
  static void gevPlayEvent(GEV event, u32 eventId);
  static void gevGameState(GF_STATE previousState, GF_STATE state);
  static void update(const fw::UpdateInfo &info);
  void updateIsInRoom(const fw::UpdateInfo &info);
  static void updateGlobalIBLReferencePos(const fw::UpdateInfo &info);
  static bool isRoom();
  static void sendPlayerPositionToRender(const mm::Vec3 &position);
  static void setWeather(WEATHERID weather);
  static WEATHER_HANDLE createTempWeather(WEATHERID weather, WEATHER_PRIO prio);
  static void destroyTempWeather(WEATHER_HANDLE handle);
  static WEATHERID getTempWeather();

private:
  bool mapjump;
  bool mapjumpBlackout;
  bool mapjumpWithSaveData;
  u32 mapID;
  u32 mapJumpID;
  f32 stopEnemySearchTime;
  mm::mtl::FixedQueue<ColorFilter, FILTER_MAX> colorFilters;
  u64 colorFilterSerial;
  mm::mtl::FixedQueue<CloudSea, FILTER_MAX> cloudSeas;
  u64 cloudSeaSerial;
  mm::mtl::FixedQueue<WeatherSet, FILTER_MAX> tempWeathers;
  u64 tempWeatherSerial;
  int roomCount;
  u8 screenShotDisableTimer;
};

static_assert(sizeof(GfGameEnv) == 0x328, "");

} // namespace gf
