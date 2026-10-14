#include "gf/game/gf_game_util.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_skill.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/util/gf_util.h"
#include <stdarg.h>

namespace gf {

enum {
  FLAG_GAME_CLEAR = 0xbdcd,
};

enum {
  SCENARIO_FLAG_WITHOUT_CRYSTAL_FIRST = 1001,
  SCENARIO_FLAG_WITHOUT_CRYSTAL_LAST = 1030,
};

constexpr u32 COIN_MAX = 9'999;
constexpr u32 ETHER_MAX = 999'999'999;
constexpr u32 DRIVER_ARTS_LEVEL_MAX = 5;
constexpr u32 DRIVER_SKILL_LEVEL_MAX = 3;
constexpr u32 GAME_CLEAR_COUNT_MAX = 9'999;
constexpr u32 ACHIEVEMENT_POPUP_MAX = 300;

u32 GfGameUtil::getFsLevelSum(u32 fieldSkill) {
  mm::mtl::FixedVector<u16, 422> blades;
  GfDataBlade::getListForFieldSkill(blades);
  u32 levelSum = 0;
  if (blades.size() != 0) {
    u16 *blade = blades.begin();
    u16 *end = blades.end();
    do {
      DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, *blade, static_cast<GimmickType>(0));
      for (u32 index = 0; index < 3; index++) {
        if (dataParamAcc.getFieldSkill(index, false) == fieldSkill) {
          levelSum += dataParamAcc.getFieldSkillLevel(index, false);
          break;
        }
      }
    } while (++blade != end);
  }

  return levelSum;
}

void GfGameUtil::addCoin(int coin) {
  int total = GfDataUtil::getCoin() + coin;
  GfDataUtil::setCoin(total < 0 ? 0 : (total > static_cast<int>(COIN_MAX) ? COIN_MAX : total));
}

void GfGameUtil::addEther(int ether) {
  int total = GfDataHana::getEther() + ether;
  GfDataHana::setEther(total < 0 ? 0 : (total > static_cast<int>(ETHER_MAX) ? ETHER_MAX : total));
}

void GfGameUtil::execLevelUpForDebug(u32 driver, u32 level) {}

void GfGameUtil::execDriverArtsLevelUp(u32 driver, u32 arts, u32 level) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
  if (dataParamAcc.isScenarioMask()) {
    return;
  }

  u32 weaponType = bdatBattle->getArtsDrWpnType(arts);
  u32 artsLevel = dataParamAcc.getDriverArtsLevel(arts);
  while (artsLevel < level && artsLevel < DRIVER_ARTS_LEVEL_MAX) {
    u32 weaponPoint = dataParamAcc.getWeaponPoint(weaponType);
    u32 needWeaponPoint = bdatBattle->getArtsDrNeedWP(arts, artsLevel + 1);
    if (weaponPoint < needWeaponPoint) {
      break;
    }

    dataParamAcc.setDriverArtsLevel(arts, artsLevel + 1);
    dataParamAcc.addWeaponPoint(weaponType, -needWeaponPoint);
    artsLevel = dataParamAcc.getDriverArtsLevel(arts);
  }
}

DriverSkillLevelUpResult GfGameUtil::execDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden) {
  u32 skillLevel = GfDataDriverSkill::getSkillLevel(driver, row, isHidden);
  if (skillLevel >= DRIVER_SKILL_LEVEL_MAX) {
    return DRIVER_SKILL_LEVEL_UP_MAX_LEVEL;
  }

  if (skillLevel + 1 != level) {
    return DRIVER_SKILL_LEVEL_UP_INVALID_LEVEL;
  }

  if (!GfDataDriverSkill::isSkillUnlock(driver, row, level, isHidden)) {
    return DRIVER_SKILL_LEVEL_UP_LOCKED;
  }

  if (GfDataDriverSkill::getNextSkillPoint(driver, row, isHidden) > GfDataDriver::getSkillPoint(driver)) {
    return DRIVER_SKILL_LEVEL_UP_NOT_ENOUGH_POINT;
  }

  GfDataDriver::addSkillPoint(driver, -GfDataDriverSkill::getNextSkillPoint(driver, row, isHidden));
  GfDataDriverSkill::setSkillLevel(driver, row, level, isHidden);
  return DRIVER_SKILL_LEVEL_UP_OK;
}

DriverSkillLevelUpResult GfGameUtil::checkDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden) {
  u32 skillLevel = GfDataDriverSkill::getSkillLevel(driver, row, isHidden);
  if (skillLevel >= DRIVER_SKILL_LEVEL_MAX) {
    return DRIVER_SKILL_LEVEL_UP_MAX_LEVEL;
  }

  if (skillLevel + 1 != level) {
    return DRIVER_SKILL_LEVEL_UP_INVALID_LEVEL;
  }

  if (!GfDataDriverSkill::isSkillUnlock(driver, row, level, isHidden)) {
    return DRIVER_SKILL_LEVEL_UP_LOCKED;
  }

  if (GfDataDriverSkill::getNextSkillPoint(driver, row, isHidden) > GfDataDriver::getSkillPoint(driver)) {
    return DRIVER_SKILL_LEVEL_UP_NOT_ENOUGH_POINT;
  }

  return DRIVER_SKILL_LEVEL_UP_OK;
}

u16 GfGameUtil::getAntiBladeAreaBdatId() { return GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea(); }

bool GfGameUtil::incEnemySuppress(u32 enemy) { return GfDataEnemy::incEnemySuppress(enemy); }

const char *GfGameUtil::getBladeModel(u32 blade, bool isDefault) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  if (!dataBlade->resourceNameModel2.empty() && !isDefault && isCondBladeModel(blade)) {
    return dataBlade->resourceNameModel2.c_str();
  }

  return dataBlade->resourceNameModel.c_str();
}

const char *GfGameUtil::getBladeMotion(u32 blade, bool isDefault) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  if (!dataBlade->resourceNameMotion2.empty() && !isDefault && isCondBladeModel(blade)) {
    return dataBlade->resourceNameMotion2.c_str();
  }

  return dataBlade->resourceNameMotion.c_str();
}

void GfGameUtil::incGameClearCount() {
  GfGameFlag::setLocal(1, FLAG_GAME_CLEAR, 1);
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->gameClearCount < GAME_CLEAR_COUNT_MAX) {
    dataGame->gameClearCount++;
  }
}

void GfGameUtil::makeWeaponStateIdle(mm::mtl::FixStr<32> &state, u32 driver, bool isBattle) {
  const char *motionName = util::getFilePtrFromPath(GfDataDriver::getMotionResourceName(driver));
  state = "S_";
  state += motionName;
  state += "_";
  state += isBattle ? "btidle" : "idle";
}

void GfGameUtil::makeWeaponCommandBattle(mm::mtl::FixStr<32> &command, u32 driver, bool isStart, bool isMotion) {
  const char *resourceName = isMotion ? GfDataDriver::getMotionResourceName(driver) : GfDataDriver::getModelResourceName(driver);
  const char *fileName = util::getFilePtrFromPath(resourceName);
  command = "C_";
  command += fileName;
  command += "_";
  command += isStart ? "btstart" : "btend";
}

void GfGameUtil::makeWeaponRecieveStateForUiModel(mm::mtl::FixStr<32> &state, u32 weaponType) {
  if (weaponType >= 10) {
    state.format("S_%d_bladearts_01", weaponType);
  } else {
    state.format("S_0%d_bladearts_01", weaponType);
  }
}

void GfGameUtil::makeCommandBattle(mm::mtl::FixStr<32> &command, bool isStart) {
  command = "C_";
  command += isStart ? "btstart" : "btend";
}

void GfGameUtil::makeStateBattleByBlade(mm::mtl::FixStr<32> &state, u32 blade, bool isStart) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  state.format("S_%02d_", dataParamAcc.getWeaponType(-1, false));
  state += isStart ? "btstart" : "btend";
}

u32 GfGameUtil::getObjAttribute(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  return dataParamAcc.getAttribute(-1, false);
}

void GfGameUtil::addInGameLog(GAMELOG_PRIO priority, const char *format, ...) {
  va_list arguments;
  va_start(arguments, format);
  va_end(arguments);
}

GF_OBJ_HANDLE *GfGameUtil::getDebugPickObj() { return reinterpret_cast<GF_OBJ_HANDLE *>(-1); }

bool GfGameUtil::execActivateMercenaryTeamForBlade(u32 blade) {
  if (GfDataBlade::isActivateMercenaryTeam(blade)) {
    return false;
  }

  ActivateType activateType = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
  GfDataBlade::setActivateMercenaryTeam(blade);
  GfEvent::callBladeActivate(blade, activateType, ACTIVATE_TYPE_MERCENARY_TEAM);
  return true;
}

bool GfGameUtil::execActivateReserverForBlade(u32 blade) {
  ActivateType activateType = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
  if (GfDataBlade::isActivateReserver(blade)) {
    if (GfDataBlade::getSetDriver(blade) != 0) {
      GfDataDriver::unsetBlade(blade);
    }

    return true;
  }

  if (!GfDataBlade::setActivateReserver(blade)) {
    return false;
  }

  GfEvent::callBladeActivate(blade, activateType, ACTIVATE_TYPE_RESERVER);
  return true;
}

u32 GfGameUtil::execAddRareBlade(const SDataBlade &dataBlade) {
  u32 blade = GfDataBlade::addRareBlade(dataBlade);
  if (blade != 0) {
    SDataBlade *addedBlade = GfDataBlade::getSDataBlade(blade);
    ActivateType activateType = GfDataBlade::getBladeActivateType(*addedBlade);
    if (blade == BLADE_REAL_ALIAS_TARGET) {
      GfDataBlade::setCreator(BLADE_REAL_ALIAS, GfDataBlade::getCreator(BLADE_REAL_ALIAS_TARGET));
    }

    if (addedBlade->createEvent != 0) {
      setWatchedEvent(addedBlade->createEvent);
    }

    GfEvent::callBladeActivate(blade, activateType, ACTIVATE_TYPE_RESERVER);
  }

  return blade;
}

u32 GfGameUtil::execAddCommonBlade(const SDataBlade &dataBlade) {
  u32 blade = GfDataBlade::addCommonBlade(dataBlade);
  if (blade != 0) {
    SDataBlade *addedBlade = GfDataBlade::getSDataBlade(blade);
    if (addedBlade->createEvent != 0) {
      setWatchedEvent(addedBlade->createEvent);
    }

    GfEvent::callBladeActivate(blade, ACTIVATE_TYPE_UNUSE, ACTIVATE_TYPE_RESERVER);
  }

  return blade;
}

bool GfGameUtil::isDummyBlade(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  if (dataParamAcc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  return GfDataBlade::isDummyBlade(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0);
}

void GfGameUtil::changeHikariCurrent(bool hikariCurrent) {
  GfDataBlade::setHikariCurrent(hikariCurrent);
  GfEvent::callHikariCurrent(hikariCurrent);
}

bool GfGameUtil::getDriverAcceList(mm::mtl::FixedVector<u16, 16> &drivers) {
  for (u32 driver = DRIVER_REX; driver <= DRIVER_METSU; driver++) {
    if (driver == DRIVER_VANDAMME && GfDataUtil::isVandammeDead()) {
      continue;
    }

    drivers.push_back(driver);
  }

  return !drivers.empty();
}

bool GfGameUtil::isDispRexCrystal() {
  u16 scenarioFlag = GfDataUtil::getScenarioFlag();
  if (scenarioFlag == 0) {
    return false;
  }

  return scenarioFlag < SCENARIO_FLAG_WITHOUT_CRYSTAL_FIRST || scenarioFlag > SCENARIO_FLAG_WITHOUT_CRYSTAL_LAST;
}

bool GfGameUtil::isDispHomuraCrystal() {
  u16 scenarioFlag = GfDataUtil::getScenarioFlag();
  return scenarioFlag < SCENARIO_FLAG_WITHOUT_CRYSTAL_FIRST || scenarioFlag > SCENARIO_FLAG_WITHOUT_CRYSTAL_LAST;
}

bool GfGameUtil::isBladeInVillage(u32 blade) {
  if (GfDataBlade::isActivateUnuse(blade) || GfDataBlade::isUnselect(blade)) {
    return false;
  }

  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver != 0 && (GfDataDriver::isActivateReserver(driver) || GfDataDriver::isActivateParty(driver))) {
    return false;
  }

  return true;
}

bool GfGameUtil::setupSaveAchievementPopup(u32 blade, u32 achievement, u32 level) {
  if (!GfDataBlade::isActivateUnuse(blade) && !GfDataBlade::isUnselect(blade)) {
    u32 driver = GfDataBlade::getSetDriver(blade);
    if (driver == 0 || !GfDataDriver::isActivateUnuse(driver)) {
      return false;
    }
  }

  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->achievementPopupNum < ACHIEVEMENT_POPUP_MAX) {
    SDataAchievementPopup &popup = dataGame->achievementPopups[dataGame->achievementPopupNum++];
    popup.blade = blade;
    popup.achievement = achievement;
    popup.level = level;
  }

  return true;
}

} // namespace gf
