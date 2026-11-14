#include "gf/data/gf_data_enemy.h"

#include "bdat.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "mm_mtl/fixstr.h"

namespace gf {

enum {
  FLAG_UNKNOWN_46 = 0x2e, // Inferred role: flag enemy suppress; original name unknown.
};

constexpr u32 ENEMY_SUPPRESS_UNKNOWN_1499 = 0x5db;   // Inferred role: enemy suppress count; original name unknown.
constexpr u32 ENEMY_SUPPRESS_UNKNOWN_65535 = 0xffff; // Inferred role: enemy suppress max; original name unknown.
constexpr f32 unknown015 = 0.001f;                   // Inferred role: permille; original name unknown.

void GfDataEnemy::setupGameParamForLevel(SDataEnemy &dataEnemy, u32 level) {
  GfBdatChrEnParam *bdat = GfBdatChrEnParam::get();
  f32 hpMax = bdat->getChrEnParamTableHpMaxBase(level);
  f32 strength = bdat->getChrEnParamTableStrengthBase(level);
  f32 powerEther = bdat->getChrEnParamTablePowEtherBase(level);
  f32 dex = bdat->getChrEnParamTableDexBase(level);
  f32 agility = bdat->getChrEnParamTableAgilityBase(level);
  f32 luck = bdat->getChrEnParamTableLuckBase(level);
  dataEnemy.unknownac = static_cast<u32>(hpMax * (dataEnemy.unknown50 * unknown015));
  dataEnemy.unknownb0 = static_cast<u32>(strength * (dataEnemy.unknown52 * unknown015));
  dataEnemy.unknownb2 = static_cast<u32>(powerEther * (dataEnemy.unknown54 * unknown015));
  dataEnemy.unknownb4 = static_cast<u32>(dex * (dataEnemy.unknown56 * unknown015));
  dataEnemy.unknownb6 = static_cast<u32>(agility * (dataEnemy.unknown58 * unknown015));
  dataEnemy.unknownb8 = static_cast<u32>(luck * (dataEnemy.unknown5a * unknown015));
  dataEnemy.unknowna8 = level;
}

const char *GfDataEnemy::getName(u32 arrange) {
  u32 textId = GfBdatChrEnArrange::get()->getChrEnArrangeName(arrange);
  u8 *bdat = GfBdatMsg::getFpEnemy();
  const char *name = textId == 0 ? nullptr : Bdat::getMSText(bdat, textId);
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataEnemy::getName(u8 *&bdat, u32 &textId, u32 arrange) {
  textId = GfBdatChrEnArrange::get()->getChrEnArrangeName(arrange);
  bdat = GfBdatMsg::getFpEnemy();
  return textId != 0;
}

u32 GfDataEnemy::getRscIdByArrangeId(u32 arrange) {
  u32 param = GfBdatChrEnArrange::get()->getChrEnArrangeParamID(arrange);
  if (param == 0) {
    return 0;
  }

  return GfBdatChrEnParam::get()->getChrEnParamResourceID(param);
}

const char *GfDataEnemy::getVoiceStr(u32 arrange) {
  u32 resource = getRscIdByArrangeId(arrange);
  if (resource == 0) {
    return nullptr;
  }

  return GfBdatRsc::get()->getRscEnVoice(resource);
}

const char *GfDataEnemy::getAddMotionName(u32 resource) {
  const char *addMotionName = GfBdatRsc::get()->getRscEnRefMotion(resource);
  if (addMotionName == nullptr || addMotionName[0] == '\0') {
    addMotionName = nullptr;
  }

  return addMotionName;
}

const char *GfDataEnemy::getResourceNameModel(u32 arrange) {
  u32 resource = getRscIdByArrangeId(arrange);
  if (resource == 0) {
    return nullptr;
  }

  return GfBdatRsc::get()->getRscEnModel(resource);
}

const char *GfDataEnemy::getResourceNameMotion(u32 arrange) {
  u32 resource = getRscIdByArrangeId(arrange);
  if (resource == 0) {
    return nullptr;
  }

  return GfBdatRsc::get()->getRscEnMotion(resource);
}

const char *GfDataEnemy::getSePack(u32 resource) {
  if (resource == 0) {
    return nullptr;
  }

  return GfBdatRsc::get()->getRscEnSePack(resource);
}

u32 GfDataEnemy::getEnemySuppress(u32 enemy) {
  if (enemy < 1 || enemy > ENEMY_SUPPRESS_UNKNOWN_1499) {
    return 0;
  }

  return GfGameFlag::getLocal(16, FLAG_UNKNOWN_46 + enemy);
}

bool GfDataEnemy::incEnemySuppress(u32 enemy) {
  if (enemy >= 1 && enemy <= ENEMY_SUPPRESS_UNKNOWN_1499) {
    u32 suppress = GfGameFlag::getLocal(16, FLAG_UNKNOWN_46 + enemy);
    if (suppress < ENEMY_SUPPRESS_UNKNOWN_65535) {
      GfGameFlag::setLocal(16, FLAG_UNKNOWN_46 + enemy, suppress + 1);
      return true;
    }
  }

  return false;
}

u32 GfDataEnemy::getBladeID(u32 arrange) {
  if (arrange == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(arrange);
}

u32 GfDataEnemy::getEquipBlade(u32 arrange) {
  if (arrange != 0) {
    GfBdatChrEnArrange *bdatEnemyArrange = GfBdatChrEnArrange::get();
    u32 enemyBlade = bdatEnemyArrange->getChrEnArrangeEnemyBladeID(arrange);
    if (bdatEnemyArrange->getChrEnArrangeStart() <= enemyBlade && bdatEnemyArrange->getChrEnArrangeEnd() > enemyBlade) {
      return GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(enemyBlade);
    }
  }

  return 0;
}

u32 GfDataEnemy::getEquipBladeEnArrangeID(u32 arrange) {
  if (arrange == 0) {
    return 0;
  }

  return GfBdatChrEnArrange::get()->getChrEnArrangeEnemyBladeID(arrange);
}

u32 GfDataEnemy::getWeaponType(u32 arrange) {
  u32 blade = getEquipBlade(arrange);
  if (blade == 0) {
    return 0;
  }

  return GfDataBlade::getSDataBlade(blade).unknown821;
}

bool GfDataEnemy::getDriverAddAnim(mm::mtl::FixStr<128> &animName, u32 driver, u32 number) {
  DataParamAcc dataParam(OBJECT_TYPE_ENEMY, driver, static_cast<GimmickType>(0));
  bool valid = false;
  if (dataParam.isValid()) {
    if (number >= 10) {
      animName.format("%s_%d", dataParam.getModelResourceName(), number);
    } else {
      animName.format("%s_0%d", dataParam.getModelResourceName(), number);
    }
    valid = true;
  }

  return valid;
}

bool GfDataEnemy::getDriverEffect(mm::mtl::FixStr<128> &modelName, mm::mtl::FixStr<128> &effectName, u32 driver, u32 number) {
  DataParamAcc dataParam(OBJECT_TYPE_ENEMY, driver, static_cast<GimmickType>(0));
  bool valid = false;
  if (dataParam.isValid()) {
    if (number >= 10) {
      effectName.format("%s_%d", dataParam.getModelResourceName(), number);
    } else {
      effectName.format("%s_0%d", dataParam.getModelResourceName(), number);
    }
    modelName.format("%s", dataParam.getModelResourceName());
    valid = true;
  }

  return valid;
}

const char *GfDataEnemy::getLoopEffect(u32 resource) {
  if (resource == 0) {
    return nullptr;
  }

  const char *loopEffect = GfBdatRsc::get()->getRscEnLoopEffect(resource);
  if (loopEffect == nullptr) {
    return loopEffect;
  }

  return loopEffect[0] == '\0' ? nullptr : loopEffect;
}

bool GfDataEnemy::isNamed(u32 arrange) {
  if (GfBdatChrEnArrange::get() == nullptr) {
    return false;
  }

  return GfBdatChrEnArrange::get()->isChrEnArrangeFlagNamed(arrange);
}

bool GfDataEnemy::isBoss(u32 arrange) {
  if (GfBdatChrEnArrange::get() == nullptr) {
    return false;
  }

  return GfBdatChrEnArrange::get()->isChrEnArrangeFlagmBoss(arrange);
}

bool GfDataEnemy::getExtraParts(u32 resource, u32 part) {
  if (part >= PARTS_UNKNOWN_4) {
    return true;
  }

  return GfBdatRsc::get()->getRscEnExtraParts(resource, part) != 0;
}

u32 GfDataEnemy::getSavedHp(u32 savedHpType) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  return dataGame->unknown10ad58[savedHpType - 4];
}

void GfDataEnemy::setSavedHp(u32 savedHpType, u32 savedHp) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  dataGame->unknown10ad58[savedHpType - 1] = savedHp;
}

u32 GfDataEnemy::getSavedHpType(u32 arrange) { return GfBdatChrEnArrange::get()->getChrEnArrangeHpOver(arrange); }

bool GfDataEnemy::isDrTypeHasWeapon(u32 arrange) {
  u32 resource = getRscIdByArrangeId(arrange);
  if (resource == 0) {
    return false;
  }

  u32 drType = GfBdatRsc::get()->getRscEnDrType(resource);
  return drType == 1 || drType == 3;
}

} // namespace gf
