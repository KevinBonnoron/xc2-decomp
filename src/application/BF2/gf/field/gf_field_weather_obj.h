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
  WEATYPE unknown08; // Inferred role: m type; original member name unknown.
  bool unknown0c;    // Inferred role: m is erased; original member name unknown.
  f32 unknown10;     // Inferred role: m alpha; original member name unknown.
  u32 unknown14;     // Inferred role: m effect handle; original member name unknown.
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
  SoundHandle unknown08; // Inferred role: m sound handle; original member name unknown.
  WEATYPE unknown10;     // Inferred role: m type; original member name unknown.
  bool unknown14;        // Inferred role: m is skipped; original member name unknown.
  f32 unknown18;         // Inferred role: m volume; original member name unknown.
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

  char unknown00[8];   // Inferred role: resource; original member name unknown.
  WEATYPE unknown08;   // Inferred role: type; original member name unknown.
  WEATHERID unknown0c; // Inferred role: weather; original member name unknown.
  f32 unknown10;       // Inferred role: past sec; original member name unknown.
  f32 unknown14;       // Inferred role: exist sec; original member name unknown.
  u32 unknown18;       // Inferred role: map; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  f32 unknown20; // Inferred role: fade rate; original member name unknown.
  f32 unknown24; // Inferred role: fade past sec; original member name unknown.
  f32 unknown28; // Inferred role: fade exist sec; original member name unknown.
  u8 _2c[0x30 - 0x2c];
  WeatherObj *unknown30; // Inferred role: eff; original member name unknown.
  WeatherObj *unknown38; // Inferred role: snd; original member name unknown.
};

static_assert(offsetof(WeatherInfo, unknown08) == 0x08, "");
static_assert(offsetof(WeatherInfo, unknown18) == 0x18, "");
static_assert(offsetof(WeatherInfo, unknown20) == 0x20, "");
static_assert(offsetof(WeatherInfo, unknown30) == 0x30, "");
static_assert(sizeof(WeatherInfo) == 0x40, "");

} // namespace gf
