#include "gf/data/gf_data_driver_skill.h"

#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_driver.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  SYSTEM_BALANCE_SKILL_UNLOCK_COLUMN_2 = 0x87,
  SYSTEM_BALANCE_SKILL_UNLOCK_COLUMN_3 = 0x88,
};

constexpr u32 SKILL_DRIVER_END = 7;
constexpr u32 HIDDEN_SKILL_FIRST = 15;

static const char *const skillTables[] = {
    "BTL_Skill_Dr_Table01",
    "BTL_Skill_Dr_Table02",
    "BTL_Skill_Dr_Table03",
    "BTL_Skill_Dr_Table04",
    "BTL_Skill_Dr_Table05",
    "BTL_Skill_Dr_Table06",
};

static int getSkillIndex(u32 row, u32 column, bool isHidden) { return row * SKILL_COLUMN_COUNT + column + (isHidden ? HIDDEN_SKILL_FIRST : 0); }

static u32 getSkillUnlockNum(u32 column) {
  u8 *bdat = Bdat::getFP("BTL_SystemBalance");
  u32 unlockNum = 0;
  switch (column) {
  case 2:
    unlockNum = static_cast<s16>(Bdat::getValCheck(bdat, "Param", SYSTEM_BALANCE_SKILL_UNLOCK_COLUMN_2, 5));
    break;
  case 3:
    unlockNum = static_cast<s16>(Bdat::getValCheck(bdat, "Param", SYSTEM_BALANCE_SKILL_UNLOCK_COLUMN_3, 5));
    break;
  }

  return unlockNum;
}

bool GfDataDriverSkill::getName(u8 *&bdat, u32 &textId, u32 skill) {
  textId = GfBdatBtl::get()->getBTL_Skill_DrName(skill);
  bdat = GfBdatMsg::getFpBtlSkillDr();
  return textId != 0;
}

const char *GfDataDriverSkill::getName(u32 skill) {
  u8 *bdat;
  u32 textId;
  if (getName(bdat, textId, skill)) {
    const char *name = Bdat::getMSText(bdat, textId);
    if (name != nullptr) {
      return name;
    }
  }

  return "";
}

bool GfDataDriverSkill::getEnhanceCaption(u8 *&bdat, u32 &textId, u32 skill) {
  u32 enhance = GfBdatBtl::get()->getBTL_Skill_DrEnhance(skill);
  if (enhance == 0) {
    return false;
  }

  textId = GfBdatBtl::get()->getBTL_EnhanceCaption(enhance);
  bdat = GfBdatMsg::getFpBtlEnhanceCap();
  return textId != 0;
}

u32 GfDataDriverSkill::getSkillFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  u16 skill = 0;
  if (driver < SKILL_DRIVER_END && column != 0) {
    skill = Bdat::getValCheck(Bdat::getFP(skillTables[driver - 1]), "SkillID", getSkillIndex(row, column, isHidden), 2);
  }

  return skill;
}

u32 GfDataDriverSkill::getSkillCategoryFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  u16 skill = getSkillFromBdat(driver, row, column, isHidden);
  if (skill != 0) {
    GfBdatBtl *bdatBattle = GfBdatBtl::get();
    u32 enhance = bdatBattle->getBTL_Skill_DrEnhance(skill);
    if (enhance != 0) {
      u32 effect = bdatBattle->getBTL_EnhanceEnhanceEffect(enhance);
      if (effect != 0) {
        return bdatBattle->getBTL_EnhanceEffCategory(effect);
      }
    }
  }

  return 0;
}

u32 GfDataDriverSkill::getSkillPointFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  u16 skillPoint = 0;
  if (driver < SKILL_DRIVER_END && column != 0) {
    skillPoint = Bdat::getValCheck(Bdat::getFP(skillTables[driver - 1]), "NeedSp", getSkillIndex(row, column, isHidden), 2);
  }

  return skillPoint;
}

u32 GfDataDriverSkill::getRoundFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  if (driver >= SKILL_DRIVER_END) {
    return 0;
  }

  u8 value = Bdat::getValCheck(Bdat::getFP(skillTables[driver - 1]), "Round", getSkillIndex(row, column, isHidden), 1);
  return value;
}

u32 GfDataDriverSkill::getColumnFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  if (driver >= SKILL_DRIVER_END) {
    return 0;
  }

  u8 value = Bdat::getValCheck(Bdat::getFP(skillTables[driver - 1]), "ColumnNum", getSkillIndex(row, column, isHidden), 1);
  return value;
}

u32 GfDataDriverSkill::getRowFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  if (driver >= SKILL_DRIVER_END) {
    return 0;
  }

  u8 value = Bdat::getValCheck(Bdat::getFP(skillTables[driver - 1]), "RowNum", getSkillIndex(row, column, isHidden), 1);
  return value;
}

u32 GfDataDriverSkill::getEnhanceFromBdat(u32 driver, u32 row, u32 column, bool isHidden) {
  u16 skill = getSkillFromBdat(driver, row, column, isHidden);
  if (skill == 0) {
    return 0;
  }

  return GfBdatBtl::get()->getBTL_Skill_DrEnhance(skill);
}

u32 GfDataDriverSkill::getValidSkillNum(u32 driver, bool isHidden) {
  u32 count = 0;
  for (u32 row = 0; row < SKILL_ROW_COUNT; row++) {
    for (u32 column = 1; column <= SKILL_COLUMN_COUNT; column++) {
      if (getSkill(driver, row, column, isHidden) != 0) {
        count++;
      }
    }
  }

  return count;
}

u32 GfDataDriverSkill::getSkill(u32 driver, u32 row, u32 column, bool isHidden) {
  if (column == 0) {
    return 0;
  }

  return getSkill(*GfDataDriver::getSDataDriver(driver), row, column, isHidden);
}

bool GfDataDriverSkill::isSkillLevelUnlock(u32 driver, u32 column, bool isHidden) {
  if (column < 2) {
    return true;
  }

  return getSkillUnlockNum(column) <= getValidSkillNum(driver, isHidden);
}

u32 GfDataDriverSkill::getSkillLevelUnlockNum(u32 driver, u32 column, bool isHidden) {
  if (column < 2) {
    return 0;
  }

  u32 unlockNum = getSkillUnlockNum(column);
  u32 validNum = getValidSkillNum(driver, isHidden);
  return unlockNum > validNum ? unlockNum - validNum : 0;
}

bool GfDataDriverSkill::isSkillUnlock(u32 driver, u32 row, u32 column, bool isHidden) {
  if (column == 0) {
    return false;
  }

  if (column == 1) {
    return true;
  }

  return getSkillUnlockNum(column) <= getValidSkillNum(driver, isHidden);
}

u16 GfDataDriverSkill::getSkill(const SDataDriver &dataDriver, u32 row, u32 column, bool isHidden) {
  if (column - 1 >= SKILL_COLUMN_COUNT || dataDriver.unknown22 >= SKILL_DRIVER_END) {
    return 0;
  }

  const SDataDriverSkillRow *rows = isHidden ? dataDriver.unknown62 : dataDriver.unknown30;
  return rows[row].unknown00[column - 1];
}

u32 GfDataDriverSkill::getNextSkillPoint(u32 driver, u32 row, bool isHidden) {
  if (driver >= SKILL_DRIVER_END) {
    return 0;
  }

  u32 level = getSkillLevel(*GfDataDriver::getSDataDriver(driver), row, isHidden);
  if (level >= SKILL_COLUMN_COUNT) {
    return 0;
  }

  if (getSkillFromBdat(driver, row, level + 1, isHidden) == 0) {
    return 0;
  }

  return getSkillPointFromBdat(driver, row, level + 1, isHidden);
}

u32 GfDataDriverSkill::getSkillLevel(u32 driver, u32 row, bool isHidden) { return getSkillLevel(*GfDataDriver::getSDataDriver(driver), row, isHidden); }

u16 GfDataDriverSkill::getSkillLevel(const SDataDriver &dataDriver, u32 row, bool isHidden) {
  if (dataDriver.unknown22 >= SKILL_DRIVER_END) {
    return 0;
  }

  const SDataDriverSkillRow *rows = isHidden ? dataDriver.unknown62 : dataDriver.unknown30;
  return rows[row].unknown08;
}

void GfDataDriverSkill::setSkillLevel(u32 driver, u32 row, u32 level, bool isHidden) {
  if (driver >= SKILL_DRIVER_END) {
    return;
  }

  SDataDriver *dataDriver = GfDataDriver::getSDataDriver(driver);
  SDataDriverSkillRow *rows = isHidden ? dataDriver->unknown62 : dataDriver->unknown30;
  rows[row].unknown08 = static_cast<u8>(level);
  for (u32 column = 1; column <= level; column++) {
    rows[row].unknown00[column - 1] = getSkillFromBdat(driver, row, column, isHidden);
  }
}

bool GfDataDriverSkill::getSkillEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 row = 0; row < SKILL_ROW_COUNT; row++) {
    for (u32 column = 1; column <= SKILL_COLUMN_COUNT; column++) {
      u16 skill = getSkill(driver, row, column, false);
      if (skill != 0) {
        u32 enhance = bdatBattle->getBTL_Skill_DrEnhance(skill);
        if (enhance != 0) {
          enhances.push_back(enhance);
        }
      }

      u16 hiddenSkill = getSkill(driver, row, column, true);
      if (hiddenSkill != 0) {
        u32 enhance = bdatBattle->getBTL_Skill_DrEnhance(hiddenSkill);
        if (enhance != 0) {
          enhances.push_back(enhance);
        }
      }
    }
  }

  return !enhances.empty();
}

} // namespace gf
