#pragma once
#include "gf/data/gf_data_map.h"
#include "gf/sound/gf_sound.h"
#include "types.h"
#include <stddef.h>

namespace fw {
struct UpdateInfo;
}

namespace gf {

class WeatherObj {
public:
  virtual ~WeatherObj() {}
  virtual void create(WEATYPE type) = 0;
  virtual void destroy() = 0;
  virtual void fadeout() = 0;
  virtual void update(const fw::UpdateInfo &info, f32 rate, bool isFadeout) = 0;
  virtual bool isPlay() const = 0;
  virtual void setForceName(const char *) {}
  virtual void setPause(bool isPause) = 0;
};

class WeatherEff : public WeatherObj {
public:
  WeatherEff();
  bool isPlay() const override;
  void create(WEATYPE type) override;
  void destroy() override;
  void fadeout() override;
  bool isEraseEffect() const;
  bool isDispEffect() const;
  void update(const fw::UpdateInfo &info, f32 rate, bool isFadeout) override;
  void applyAlpha(const fw::UpdateInfo &info);
  void applySpeed(const fw::UpdateInfo &info);
  void setForceName(const char *name) override;
  void setPause(bool isPause) override;

private:
  WEATYPE mType;
  bool mIsErased;
  f32 mAlpha;
  u32 mEffectHandle;
};

static_assert(sizeof(WeatherEff) == 0x18, "");

class WeatherSnd : public WeatherObj {
public:
  WeatherSnd();
  bool isPlay() const override;
  void create(WEATYPE type) override;
  void destroy() override;
  void fadeout() override;
  void update(const fw::UpdateInfo &info, f32 rate, bool isFadeout) override;
  bool isRoomSe() const;
  bool isEraseSe() const;
  bool isCreateSe(f32 rate) const;
  void applyVolume(const fw::UpdateInfo &info, f32 rate);
  void setPause(bool isPause) override;

private:
  SoundHandle mSoundHandle;
  WEATYPE mType;
  bool mIsSkipped;
  f32 mVolume;
};

static_assert(sizeof(WeatherSnd) == 0x20, "");

struct WeatherInfo {
  WeatherInfo(WEATYPE type, u32 map, WEATHERID weather, f32 pastSec, f32 existSec, f32 fadeExistSec);
  ~WeatherInfo();
  void destroyEnv();
  bool isTimeRangeOK() const;
  bool isTimeup() const;
  void fadeoutEnv();
  void update(const fw::UpdateInfo &info, bool isFadeout);
  bool updateFadein(const fw::UpdateInfo &info);
  void createEnv();
  bool updateFadeout(const fw::UpdateInfo &info);
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
  WeatherObj *eff;
  WeatherObj *snd;
};

static_assert(offsetof(WeatherInfo, type) == 0x08, "");
static_assert(offsetof(WeatherInfo, map) == 0x18, "");
static_assert(offsetof(WeatherInfo, fadeRate) == 0x20, "");
static_assert(offsetof(WeatherInfo, eff) == 0x30, "");
static_assert(sizeof(WeatherInfo) == 0x40, "");

} // namespace gf
