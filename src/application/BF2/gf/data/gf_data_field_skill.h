#pragma once
#include "types.h"

namespace gf {

class GfDataFieldSkill {
public:
  static const char *getName(u32 fieldSkill);
  static bool getName(u8 *&bdat, u32 &textId, u32 fieldSkill);
  static bool isFieldSkillSettingAccessed(u32 setting);
  static bool isFieldSkillSettingComplete(u32 setting);
  static void setFieldSkillSettingAccessed(u32 setting);
  static void setFieldSkillSettingComplete(u32 setting);
  static bool getCaption(u8 *&bdat, u32 &textId, u32 fieldSkill);
};

} // namespace gf
