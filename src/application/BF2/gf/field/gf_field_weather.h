#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_env.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;
struct GF_OBJ_HANDLE;

class GfFieldWeather : public mm::mtl::PtrSingleton<GfFieldWeather> {
public:
  enum CLOUD_SEA_REQUEST {
    CLOUD_SEA_REQUEST_NONE,
    CLOUD_SEA_REQUEST_LOW,
    CLOUD_SEA_REQUEST_HIGH,
  };

  GfFieldWeather(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfFieldWeather();
  void applyNowMapWeatherForMapModel(u32 map);
  static void gevMapjump(GEV gev, const MapjumpCallbackInfo &info);
  static void gevGameMapModel(GF_OBJ_HANDLE *handle, bool isEnter);
  static void gevPause(u32 resumeBits, u32 pauseBits);
  void execChangeWeather(const WeatherParam &param);
  void createWeather(u32 map, WEATHERID weather, f32 fadeSec);
  bool isColud2Condition(u32 map) const;
  void createWeather(const WeatherParam &param, f32 fadeSec);
  void execChangeCloud(u32 map);
  static void setCloudSeaForDebug(u32 map, CLOUD_SEA cloudSea);
  static WEATYPE getCurrentWtrType(bool isPrevious);
  static u32 getCurrentWtrTypeBit(bool isPrevious);
  static WEATHERID getCurrentMapWeatherID(bool isPrevious);
  static u32 getCurrentMapWeatherBit(bool isPrevious);
  static f32 getCurrentPastSec(bool isPrevious);
  static f32 getCurrentExistSec(bool isPrevious);
  static const char *getCurrentEffName(bool isPrevious);
  static const char *getCurrentSndName(bool isPrevious);
  static const char *getCurrentWeatherName(bool isPrevious);
  void createWeatherForce(WEATYPE type, f32 fadeSec, const char *effect);
  void updateEvent(const fw::UpdateInfo &info);
  static void setCurrentRemainSecZero();
  void updateWeather(const fw::UpdateInfo &info);
  void applyNowMapWeather(u32 prevMap, u32 map);
  static void setCloudSea(u32 map, CLOUD_SEA cloudSea);
  static void setMapWeatherID(WEATHERID weather);
  static bool isInfiniteTime();
  static bool isWeatherSE();
  static void setWeatherForEvent(WEATYPE type, const char *effect);
  static void setWeather(WEATYPE type, bool isTimeLimited);
  static bool getWeatherName(u8 *&bdat, u32 &textId);
  static const char *getWeatherName();
  static void setupGame();
  void updateCloudSea(const fw::UpdateInfo &info);
  void createCloudSeaCondition();
  void destroyCloudSeaCondition();
  void applyCloudSelect();
  void createCloudSeaDefault();
  void destroyCloudSeaDefault();
  static CLOUD_SEA getCloudSeaCondition();
  static CLOUD_SEA getCloudSea(u32 map);
  static CLOUD_SEA getCurrentCloudSea();
  static void setDispWeather(bool isDisp);
  static bool isDispWeather();
  static void clear();
  static void build(const GfSetupParam &param);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);

private:
  bool mInitialized;
  bool mIsInfiniteTime;
  u8 _0a[0x10 - 0x0a];
  mm::mtl::FixedQueue<GEV, 16> mEvents;
  MapjumpCallbackInfo mMapjumpInfo;
  u8 _74[0x78 - 0x74];
  CLOUD_SEA_HANDLE mCloudSeaDefault;
  CLOUD_SEA_REQUEST mCloudSeaRequest;
  CLOUD_SEA_HANDLE mCloudSeaCondition;
  bool mIsDispWeather;
};

static_assert(sizeof(GfFieldWeather) == 0x88, "");

} // namespace gf
