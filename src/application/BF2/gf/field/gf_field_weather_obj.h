#pragma once
#include "gf/data/gf_data_map.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

class WeatherEff;
class WeatherSnd;

struct WeatherInfo {
  WeatherInfo(WEATYPE type, u32 map, WEATHERID weather, f32 pastSec, f32 existSec, f32 fadeExistSec);
  ~WeatherInfo();
  void destroyEnv();
  bool isTimeRangeOK() const;
  bool isTimeup() const;
  void fadeoutEnv();
  void update(const fw::UpdateInfo &info, bool isPause);
  void updateFadein(const fw::UpdateInfo &info);
  void createEnv();
  void updateFadeout(const fw::UpdateInfo &info);
  bool isTimeEnd() const;
  bool isPlaySE() const;
  void setForceEffect(const char *effect);
  void resetParam(f32 pastSec, f32 existSec, f32 fadeExistSec);
  void setPause(bool isPause);

  char resource[8];
  WEATYPE type;
  WEATHERID weather;
  f32 pastSec;
  f32 existSec;
  u32 map;
  u8 _1c[0x20 - 0x1c];
  f32 fadeRate;
  f32 fadePastSec;
  f32 fadeExistSec;
  u8 _2c[0x30 - 0x2c];
  WeatherEff *eff;
  WeatherSnd *snd;
};

static_assert(offsetof(WeatherInfo, type) == 0x08, "");
static_assert(offsetof(WeatherInfo, map) == 0x18, "");
static_assert(offsetof(WeatherInfo, fadeRate) == 0x20, "");
static_assert(offsetof(WeatherInfo, eff) == 0x30, "");
static_assert(sizeof(WeatherInfo) == 0x40, "");

} // namespace gf
