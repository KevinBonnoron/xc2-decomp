#pragma once
#include "types.h"

namespace gf {

class GfComEffectCaster;

struct GfCharaWaterInfo {
  f32 unknown00; // Inferred role: water height; original member name unknown.
};

class GfEffectGround {
public:
  static u32 getWaterHeightState(const GfComEffectCaster *caster);
  static bool getGroundEffectFileNameImpl(u32 type, u32 effectType, u32 material, const char *&fileName);
  static bool tryGetWaterDepth(const GfComEffectCaster *caster, const GfCharaWaterInfo *waterInfo, f32 &depth);
  static bool isOnWaterSurface(const GfComEffectCaster *caster);
  static u32 getWaterHeightStateImpl(f32 height, f32 first, f32 second);
};

} // namespace gf
