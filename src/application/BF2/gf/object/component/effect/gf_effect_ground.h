#pragma once
#include "types.h"
namespace effect {
struct SendParam;
} // namespace effect

namespace gf {
class GfComEffectCaster;
class GfEnvProperty;

struct GfCharaWaterInfo {
  f32 unknown00; // Inferred role: water height; original member name unknown.
};

class GfEffectGround {
public:
  // Inferred from GfComEffectCaster::convertSwimEffectState, which keeps the states below 3; original enumerator names
  // unknown.
  enum SwimEffectState {
    SWIM_EFFECT_STATE_UNKNOWN_0 = 0,
    SWIM_EFFECT_STATE_UNKNOWN_1 = 1,
    SWIM_EFFECT_STATE_UNKNOWN_2 = 2,
    SWIM_EFFECT_STATE_UNKNOWN_3 = 3,
  };

  static u32 getWaterHeightState(const GfComEffectCaster *caster);
  static bool getGroundEffectFileName(const GfComEffectCaster *caster, u32 type, const char *&fileName);
  static u32 getGroundMaterial(GfEnvProperty *env, const GfComEffectCaster *caster);
  static bool getGroundEffectFileNameImpl(u32 type, u32 effectType, u32 material, const char *&fileName);
  static bool tryGetWaterDepth(const GfComEffectCaster *caster, const GfCharaWaterInfo *waterInfo, f32 &depth);
  static SwimEffectState calcSwimEffectParam(const GfComEffectCaster *caster, bool unknown1, bool unknown2, effect::SendParam &param);
  static bool isOnWaterSurface(const GfComEffectCaster *caster);
  static u32 getWaterHeightStateImpl(f32 height, f32 first, f32 second);
};

} // namespace gf
