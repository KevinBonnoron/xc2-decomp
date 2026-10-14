#pragma once
#include "types.h"

namespace gf {

class GfDataBladeArts {
public:
  static const char *getName(u32 arts);
  static bool getName(u8 *&bdat, u32 &textId, u32 arts);
  static u32 getIcon(u32 arts);
  static bool getCaption(u8 *&bdat, u32 &textId, u32 arts);
  static u32 getEnhance(u32 arts, u32 level);
  static bool getEnhanceCaption(u8 *&bdat, u32 &textId, u32 arts, u32 level);
  static bool getExName(u8 *&bdat, u32 &textId, u32 arts);
  static const char *getExName(u32 arts);
  static bool getExCaption(u8 *&bdat, u32 &textId, u32 arts);
};

} // namespace gf
