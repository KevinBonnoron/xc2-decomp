#pragma once
#include "types.h"

namespace gf {

class GfDataBladeSkill {
public:
  static const char *getName(u32 skill);
  static bool getName(u8 *&bdat, u32 &textId, u32 skill);
  static u32 getEnhance(u32 skill, u32 level);
  static bool getEnhanceCaption(u8 *&bdat, u32 &textId, u32 skill, u32 level);
};

} // namespace gf
