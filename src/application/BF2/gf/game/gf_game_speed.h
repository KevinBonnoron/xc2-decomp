#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum GF_SPEED {
  GF_SPEED_GLOBAL,
  GF_SPEED_PLAY,
  GF_SPEED_LAYER_0,
  GF_SPEED_LAYER_4,
  GF_SPEED_LAYER_1,
  GF_SPEED_LAYER_7,
  GF_SPEED_LAYER_10,
  GF_SPEED_MAX,
};

class GfGameSpeed : public mm::mtl::PtrSingleton<GfGameSpeed> {
public:
  struct Speed {
    Speed() : original(1.0f), current(1.0f), apply(true) {}

    f32 original;
    f32 current;
    bool apply;
  };

  GfGameSpeed(const GfSetupParam &param);
  void initialize(const GfSetupParam &param);
  ~GfGameSpeed();
  static void build(const GfSetupParam &param);
  static void setGlobalSpeed(f32 speed);
  static void destroy();
  void finalize();
  static bool isInitialized();
  static void update(const fw::UpdateInfo &info);
  void updateFrameSpeed(const fw::UpdateInfo &info);
  static void clear();
  static void setIntervalSpeed(f32 speed, f32 time);
  static void setLayerSpeed(u32 layer, f32 speed);
  void setSpeed(GF_SPEED type, f32 speed);
  static f32 getLayerSpeed(u32 layer);
  f32 getSpeed(GF_SPEED type);
  static f32 getOriginalLayerSpeed(u32 layer);
  f32 getOriginalSpeed(GF_SPEED type);
  static f32 getGlobalSpeed();
  static void setPlaySpeed(f32 speed);
  static f32 getPlaySpeed();
  bool isApplySpeed(GF_SPEED type);
  f32 getSpeedSalvage(GF_SPEED type);
  static void setSalvageSpeed(f32 speed);
  static void setSalvageCharacterSpeed(f32 speed);

private:
  bool initialized;
  f32 intervalSpeed;
  f32 intervalTime;
  Speed speeds[GF_SPEED_MAX];
  Speed salvageSpeeds[GF_SPEED_MAX];
};

static_assert(sizeof(GfGameSpeed) == 0xc0, "");

} // namespace gf
