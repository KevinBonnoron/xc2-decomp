#include "gf/data/gf_data_enemy.h"

#include "bdat.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "ml/rand.h"
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

void GfDataEnemy::setupSDataEnemy(SDataEnemy &dataEnemy, u32 arrange, u32 level) {
  GfBdatChrEnArrange *bdatArrange = GfBdatChrEnArrange::get();
  dataEnemy.unknown00 = arrange;
  dataEnemy.unknown08 = bdatArrange->getChrEnArrangeParamID(arrange);
  dataEnemy.unknown0a = bdatArrange->getChrEnArrangeBladeID(arrange);
  dataEnemy.unknown0c = bdatArrange->getChrEnArrangeName(arrange);
  dataEnemy.unknown0e = bdatArrange->getChrEnArrangeLv(arrange);
  dataEnemy.unknown10 = bdatArrange->getChrEnArrangeExpRev(arrange);
  dataEnemy.unknown12 = bdatArrange->getChrEnArrangeGoldRev(arrange);
  dataEnemy.unknown14 = bdatArrange->getChrEnArrangeDropTableID(arrange);
  dataEnemy.unknown16 = bdatArrange->getChrEnArrangeDropTableID2(arrange);
  dataEnemy.unknown18 = bdatArrange->getChrEnArrangeDropTableID3(arrange);
  dataEnemy.unknown1a = bdatArrange->getChrEnArrangePreciousID(arrange);
  dataEnemy.unknown1c = bdatArrange->getChrEnArrangeScale(arrange);
  dataEnemy.unknown1e = bdatArrange->getChrEnArrangeChrSize(arrange);
  if (bdatArrange->isChrEnArrangeFlagNamed(arrange)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_0;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_0;
  }
  if (bdatArrange->isChrEnArrangeFlagmBoss(arrange)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_1;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_1;
  }
  if (bdatArrange->isChrEnArrangeFlagFAOff(arrange)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_2;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_2;
  }
  if (bdatArrange->isChrEnArrangeFlagNoEcSkip(arrange)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_3;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_3;
  }
  if (bdatArrange->isChrEnArrangeFlagLinkType(arrange)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_4;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_4;
  }
  dataEnemy.m_linkRadius = bdatArrange->getChrEnArrangeLinkRadius(arrange);
  dataEnemy.unknown20 = bdatArrange->getChrEnArrangeDetects(arrange);
  dataEnemy.unknown22 = bdatArrange->getChrEnArrangeSearchRange(arrange);
  dataEnemy.unknown24 = bdatArrange->getChrEnArrangeSearchAngle(arrange);
  dataEnemy.unknown26 = bdatArrange->getChrEnArrangeSearchRadius(arrange);
  dataEnemy.unknown27 = bdatArrange->getChrEnArrangeBatArea(arrange);
  dataEnemy.unknown29 = bdatArrange->getChrEnArrangeAiGroup(arrange);
  dataEnemy.unknown2a = bdatArrange->getChrEnArrangeAiGroupNum(arrange);
  dataEnemy.unknown2c = bdatArrange->getChrEnArrangeBookID(arrange);
  dataEnemy.unknown2e = bdatArrange->getChrEnArrangeEnhanceID1(arrange);
  dataEnemy.unknown30 = bdatArrange->getChrEnArrangeEnhanceID2(arrange);
  dataEnemy.unknown32 = bdatArrange->getChrEnArrangeEnhanceID3(arrange);
  dataEnemy.unknown34 = bdatArrange->getChrEnArrangeParamRev(arrange);
  dataEnemy.unknown36 = bdatArrange->getChrEnArrangeRstDebuffRev(arrange);
  dataEnemy.unknown38 = bdatArrange->getChrEnArrangeHealPotTypeRev(arrange);
  dataEnemy.unknown3a = bdatArrange->getChrEnArrangeSummonID(arrange);
  dataEnemy.unknown3c = bdatArrange->getChrEnArrangeBGMID(arrange);
  dataEnemy.unknown3d = bdatArrange->getChrEnArrangeSeEnvID(arrange);
  dataEnemy.unknown3e = bdatArrange->getChrEnArrangeZoneID(arrange);
  dataEnemy.unknown41 = bdatArrange->getChrEnArrangeBladeAtr(arrange);
  dataEnemy.unknown42 = bdatArrange->getChrEnArrangeExtraParts(arrange);
  GfBdatChrEnParam *bdatParam = GfBdatChrEnParam::get();
  u32 param = dataEnemy.unknown08;
  dataEnemy.unknown44 = bdatParam->getChrEnParamResourceID(param);
  dataEnemy.unknown46 = bdatParam->getChrEnParamAiID(param);
  dataEnemy.unknown48 = bdatParam->getChrEnParamEnemyRole(param);
  dataEnemy.unknown49 = bdatParam->getChrEnParamWalkSpeed(param);
  dataEnemy.unknown4a = bdatParam->getChrEnParamRunSpeed(param);
  dataEnemy.unknown4b = bdatParam->getChrEnParamBtlSpeed(param);
  dataEnemy.unknown4c = bdatParam->getChrEnParamHpDefault(param);
  dataEnemy.unknown4d = bdatParam->getChrEnParamHpLimit(param);
  dataEnemy.unknown4e = bdatParam->getChrEnParamScoutStartHp(param);
  dataEnemy.unknown4f = bdatParam->getChrEnParamScoutEndHp(param);
  dataEnemy.unknown50 = bdatParam->getChrEnParamHpMaxRev(param);
  dataEnemy.unknown52 = bdatParam->getChrEnParamStrengthRev(param);
  dataEnemy.unknown54 = bdatParam->getChrEnParamPowEtherRev(param);
  dataEnemy.unknown56 = bdatParam->getChrEnParamDexRev(param);
  dataEnemy.unknown58 = bdatParam->getChrEnParamAgilityRev(param);
  dataEnemy.unknown5a = bdatParam->getChrEnParamLuckRev(param);
  dataEnemy.unknown5c = bdatParam->getChrEnParamParmor(param);
  dataEnemy.unknown5e = bdatParam->getChrEnParamEarmor(param);
  dataEnemy.m_resistancePower = bdatParam->getChrEnParamRstPower(param);
  dataEnemy.m_resistanceEther = bdatParam->getChrEnParamRstEther(param);
  dataEnemy.unknown62 = bdatParam->getChrEnParamAtr(param);
  dataEnemy.unknown63 = bdatParam->getChrEnParamCriticalRate(param);
  dataEnemy.unknown64 = bdatParam->getChrEnParamGuardRate(param);
  if (bdatParam->isChrEnParamFlagGrdDirFront(param)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_5;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_5;
  }
  if (bdatParam->isChrEnParamFlagGrdDirLeft(param)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_6;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_6;
  }
  if (bdatParam->isChrEnParamFlagGrdDirRight(param)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_7;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_7;
  }
  if (bdatParam->isChrEnParamFlagGrdDirBack(param)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_8;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_8;
  }
  if (bdatParam->isChrEnParamFlagFldDmgType(param)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_9;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_9;
  }
  dataEnemy.unknown65 = bdatParam->getChrEnParamHealPotDrop(param);
  dataEnemy.m_resistanceCombo = bdatParam->getChrEnParamRstFiCombo(param);
  dataEnemy.m_invincibleCombo = bdatParam->getChrEnParamIvdFiCombo(param);
  dataEnemy.unknown6a = bdatParam->getChrEnParamAura(param);
  dataEnemy.unknown6c = bdatParam->getChrEnParamDyingHP(param);
  dataEnemy.unknown6d = bdatParam->getChrEnParamWTNormal(param);
  dataEnemy.unknown6e = bdatParam->getChrEnParamWTDying(param);
  dataEnemy.unknown6f = bdatParam->getChrEnParamHate0Target(param);
  dataEnemy.unknown70 = bdatParam->getChrEnParamDeathArts(param);
  dataEnemy.unknown74 = bdatParam->getChrEnParamDeathArtsStop(param);
  for (u32 index = 0; index < 16; index++) {
    dataEnemy.unknown78[index] = bdatParam->getChrEnParamArtsNum(param, index);
  }
  GfBdatRsc *bdatRsc = GfBdatRsc::get();
  u32 resource = dataEnemy.unknown44;
  dataEnemy.unknown98 = bdatRsc->getRscEnTypeFamily(resource);
  dataEnemy.m_genus = bdatRsc->getRscEnTypeGenus(resource);
  dataEnemy.unknown9a = bdatRsc->getRscEnActType(resource);
  dataEnemy.unknown9b = bdatRsc->getRscEnFldMoveType(resource);
  dataEnemy.unknown9c = bdatRsc->getRscEnMemorySlot(resource);
  if (bdatRsc->isRscEnFlagNoCamera(resource)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_11;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_11;
  }
  if (bdatRsc->isRscEnFlagWeaponDrawDisp(resource)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_12;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_12;
  }
  for (u32 index = 0; index < 5; index++) {
    dataEnemy.m_equipWeapon[index] = bdatRsc->getRscEnWeaponNum(resource, index);
  }
  if (bdatRsc->isRscEnGenusFlaggimmicktype(dataEnemy.m_genus)) {
    dataEnemy.unknown04 |= ENEMY_FLAG_UNKNOWN_10;
  } else {
    dataEnemy.unknown04 &= ~ENEMY_FLAG_UNKNOWN_10;
  }
  u32 driverLevel = bdatArrange->getChrEnArrangeDriverLev(arrange);
  if (driverLevel != 0) {
    level = GfDataDriver::getLevel(driverLevel);
  }
  u32 levelRand = bdatArrange->getChrEnArrangeLvRand(arrange);
  if (levelRand != 0) {
    u32 random = ml::mtRand(levelRand + 1);
    level = random + level < 1000 ? random + level : 999;
  }
  setupGameParamForLevel(dataEnemy, level);
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

  return GfDataBlade::getSDataBlade(blade).m_weaponType;
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
