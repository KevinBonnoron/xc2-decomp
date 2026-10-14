#pragma once
#include "types.h"

namespace gf {

class GfDataMob {
public:
  static const char *getName(u32 mob);
  static bool getName(u8 *&name, u32 &size, u32 mob);
  static u8 getRace(u32 mob);
  static const char *getModelName(u32 mob);
  static const char *getMotionName(u32 mob);
  static const char *getAddMotionName(u32 mob);
  static const char *getEffectName(u32 mob);
  static u16 getFootStep(u32 mob);
  static u8 getFootStepEffect(u32 mob);
};

} // namespace gf
