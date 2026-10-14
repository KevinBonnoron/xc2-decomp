#pragma once
#include "types.h"

namespace gf {

class GfDataField {
public:
  static const char *getFieldSkillVoice(u32 chara, u32 voice);
  static bool getLandmarkName(u8 *&bdat, u32 &textId, u32 landmark);
  static bool getTimeRangeName(u8 *&bdat, u32 &textId, u32 time);
  static bool getWeatherName(u8 *&bdat, u32 &textId, u32 weather);
};

} // namespace gf
