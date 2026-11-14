#pragma once
#include "mm_mtl/singleton.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
}

namespace gf {

struct GfSetupParam;

enum GF_SPEED {
  GF_SPEED_UNKNOWN_0, // Inferred role: gf speed global; original name unknown.
  GF_SPEED_UNKNOWN_1, // Inferred role: gf speed play; original name unknown.
  GF_SPEED_UNKNOWN_2, // Inferred role: gf speed layer 0; original name unknown.
  GF_SPEED_UNKNOWN_3, // Inferred role: gf speed layer 4; original name unknown.
  GF_SPEED_UNKNOWN_4, // Inferred role: gf speed layer 1; original name unknown.
  GF_SPEED_UNKNOWN_5, // Inferred role: gf speed layer 7; original name unknown.
  GF_SPEED_UNKNOWN_6, // Inferred role: gf speed layer 10; original name unknown.
  // GF_SPEED_MAX is the number of enumerators above.
  GF_SPEED_MAX,
};

class GfGameSpeed : public mm::mtl::PtrSingleton<GfGameSpeed> {
public:
  // Inferred role: speed; original type name unknown.
  struct unknown004 {
    unknown004() : unknown00(1.0f), unknown04(1.0f), unknown08(true) {}

    f32 unknown00;  // Inferred role: original; original member name unknown.
    f32 unknown04;  // Inferred role: current; original member name unknown.
    bool unknown08; // Inferred role: apply; original member name unknown.
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
  bool unknown08;                     // Inferred role: initialized; original member name unknown.
  f32 unknown0c;                      // Inferred role: interval speed; original member name unknown.
  f32 unknown10;                      // Inferred role: interval time; original member name unknown.
  unknown004 unknown14[GF_SPEED_MAX]; // Inferred role: speeds; original member name unknown.
  unknown004 unknown68[GF_SPEED_MAX]; // Inferred role: salvage speeds; original member name unknown.
};

static_assert(sizeof(GfGameSpeed) == 0xc0, "");

} // namespace gf
