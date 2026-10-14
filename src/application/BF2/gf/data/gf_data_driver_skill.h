#pragma once
#include "gf/data/gf_data_driver.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

class GfDataDriverSkill {
public:
  static bool getName(u8 *&bdat, u32 &textId, u32 skill);
  static const char *getName(u32 skill);
  static bool getEnhanceCaption(u8 *&bdat, u32 &textId, u32 skill);
  static u32 getSkillFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getSkillCategoryFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getSkillPointFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getRoundFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getColumnFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getRowFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getEnhanceFromBdat(u32 driver, u32 row, u32 column, bool isHidden);
  static u32 getValidSkillNum(u32 driver, bool isHidden);
  static u16 getSkill(u32 driver, u32 row, u32 column, bool isHidden);
  static bool isSkillLevelUnlock(u32 driver, u32 column, bool isHidden);
  static u32 getSkillLevelUnlockNum(u32 driver, u32 column, bool isHidden);
  static bool isSkillUnlock(u32 driver, u32 row, u32 column, bool isHidden);
  static u16 getSkill(const SDataDriver &dataDriver, u32 row, u32 column, bool isHidden);
  static u32 getNextSkillPoint(u32 driver, u32 row, bool isHidden);
  static u32 getSkillLevel(u32 driver, u32 row, bool isHidden);
  static u16 getSkillLevel(const SDataDriver &dataDriver, u32 row, bool isHidden);
  static void setSkillLevel(u32 driver, u32 row, u32 level, bool isHidden);
  static bool getSkillEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver);
};

} // namespace gf
