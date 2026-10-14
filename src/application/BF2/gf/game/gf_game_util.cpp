#include "gf/game/gf_game_util.h"

#include <stdarg.h>

#include "battle/data_manager_battle.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_develop.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_skill.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_mercenaries.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_util.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

enum {
  FLAG_GAME_CLEAR = 0xbdcd,
};

enum {
  NATION_FIRST = 1,
  NATION_IYASAKI = 5,
  NATION_ARCADIA = 6,
};

enum {
  DEBUG_CHANGE_IDEA_TRUST = 4,
};

enum {
  GAME_COND_METSU_WITHOUT_CRYSTAL = 2695,
};

enum {
  STATS_MONEY = 0x36,
  STATS_PARTY_MONEY = 0x37,
  STATS_PARTY_MONEY_COUNT = 0x38,
};

enum {
  VOICE_RESULT_PLAY = 2,
};

enum {
  SCENARIO_FLAG_WITHOUT_CRYSTAL_FIRST = 1001,
  SCENARIO_FLAG_WITHOUT_CRYSTAL_LAST = 1030,
};

constexpr u32 WEAPON_TYPE_EVENT_BATTLE_IDLE_FIRST = 18;
constexpr u32 WEAPON_TYPE_EVENT_BATTLE_IDLE_SECOND = 19;

GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

constexpr u32 MONEY_MAX = 999'999'999;
constexpr u32 COIN_MAX = 9'999;
constexpr u32 ETHER_MAX = 999'999'999;
constexpr u32 NATION_COUNT = 8;
constexpr u32 DEVELOP_LEVEL_MAX = 5;
constexpr int TRUST_RANK_MAX = 6;
constexpr int TRUST_RANK_LIMIT = 16;
constexpr u32 TRUST_POINT_MAX = 0xffff;
constexpr u32 ACHIEVEMENT_LEVEL_MAX = 5;
constexpr u32 DRIVER_LEVEL_MAX = 99;
constexpr u32 DRIVER_ARTS_LEVEL_MAX = 5;
constexpr u32 DRIVER_SKILL_LEVEL_MAX = 3;
constexpr u32 GAME_CLEAR_COUNT_MAX = 9'999;
constexpr u32 ACHIEVEMENT_POPUP_MAX = 300;
constexpr int PARTY_GAUGE_MAX = 300;

static const u32 nationLocations[NATION_COUNT] = {3, 6, 9, 10, 14, 12, 13, 15};

bool GfGameUtil::isUiGfObjHandleValid(GF_OBJ_HANDLE *handle) {
  if (handle == INVALID_HANDLE) {
    return false;
  }

  GfObjAcc objAcc(handle);
  return objAcc.isValid() && !objAcc.isDestroy() && !objAcc.testFlag(OBJ_FLAG_UI_HIDDEN);
}

static void makeWeaponBattleIdleState(mm::mtl::FixStr<32> &state, u32 weaponType) {
  mm::mtl::FixStr<16> weaponName;
  if (weaponType >= 10) {
    weaponName.format("%d_", weaponType);
  } else {
    weaponName.format("0%d_", weaponType);
  }

  state = "S_";
  state += weaponName.c_str();
  state += "btidle";
}

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

void GfGameUtil::addMoney(int money) {
  int total = GfDataUtil::getMoney() + money;
  GfDataUtil::setMoney(total < 0 ? 0 : (total > static_cast<int>(MONEY_MAX) ? MONEY_MAX : total));
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->addMoneyLog();
  }

  if (money > 0) {
    SCOM_ACHIEV_INC::addTotalCount(STATS_MONEY, money);
    SCOM_ACHIEV_INC::create(STATS_MONEY, money, 0);
    SCOM_ACHIEV_INC::createParty(STATS_PARTY_MONEY, money);
    SCOM_ACHIEV_INC::createParty(STATS_PARTY_MONEY_COUNT, 1);
  }
}

void GfGameUtil::addCoin(int coin) {
  int total = GfDataUtil::getCoin() + coin;
  GfDataUtil::setCoin(total < 0 ? 0 : (total > static_cast<int>(COIN_MAX) ? COIN_MAX : total));
}

void GfGameUtil::addEther(int ether) {
  int total = GfDataHana::getEther() + ether;
  GfDataHana::setEther(total < 0 ? 0 : (total > static_cast<int>(ETHER_MAX) ? ETHER_MAX : total));
}

void GfGameUtil::execLevelUp(u32 driver, u32 level) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  if (dataParamAcc.isScenarioMask()) {
    return;
  }

  u32 oldLevel = dataParamAcc.getLevel(false);
  u32 exp = dataParamAcc.getExp() + dataParamAcc.getBattleExp();
  if (oldLevel >= DRIVER_LEVEL_MAX) {
    return;
  }

  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 currentLevel = dataParamAcc.getLevel(false); currentLevel < level; currentLevel = dataParamAcc.getLevel(false)) {
    if (currentLevel < bdatBattle->getGrowStart() || currentLevel >= bdatBattle->getGrowEnd() - 1) {
      break;
    }

    u32 needExp = bdatBattle->getGrowLevelExp(currentLevel + 1);
    if (exp < needExp) {
      break;
    }

    GfDataDriver::setLevel(driver, currentLevel + 1);
    exp -= needExp;
  }

  if (dataParamAcc.getLevel(false) == oldLevel) {
    return;
  }

  GfDataDriver::setExp(driver, exp);
  GfDataDriver::setBattleExp(driver, 0);
  ParamObj paramObj = {INVALID_HANDLE, OBJECT_TYPE_DRIVER, driver};
  SCOM_FIELD_VOICE::createLevelup(paramObj);
  GF_OBJ_HANDLE *handle = GfGameParty::getHandleDriverByBdatID(driver);
  if (handle != INVALID_HANDLE) {
    SCOM_MAXIMUM_HEAL::create(handle);
  }

  GfEvent::callDriverLevel(driver, dataParamAcc.getLevel(false), oldLevel);
  GfDataDriver::openDriverArtsForLevelup(driver);
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

void GfGameUtil::addWp(u32 driver, u32 weaponType, int weaponPoint) {
  if (driver == 0) {
    GfObjAcc objAcc(GfGameManager::getPartyLeaderDriver());
    driver = objAcc.getDriverId();
    if (driver == 0) {
      return;
    }
  }

  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
  if (dataParamAcc.isScenarioMask()) {
    return;
  }

  if (weaponType == 0) {
    weaponType = dataParamAcc.getWeaponType(-1, false);
  }

  dataParamAcc.addWeaponPoint(weaponType, weaponPoint);
}

void GfGameUtil::addWpForReserve(int weaponPoint) {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_RESERVER, 0);
  if (drivers.size() != 0) {
    u16 *driver = drivers.begin();
    do {
      addWp(*driver, 0, weaponPoint);
    } while (++driver != drivers.end());
  }
}

void GfGameUtil::addWpForObject(u32 driver, u32 weaponType, int weaponPoint) { addWp(driver, weaponType, weaponPoint); }

void GfGameUtil::addSP(u32 driver, int skillPoint) {
  if (driver == 0) {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY_AND_RESERVER, 0);
    if (drivers.size() != 0) {
      u16 *member = drivers.begin();
      do {
        addSP(*member, skillPoint);
      } while (++member != drivers.end());
    }
  } else {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
    if (!dataParamAcc.isScenarioMask()) {
      GfDataDriver::addSkillPoint(driver, skillPoint);
    }
  }
}

void GfGameUtil::addIdeaPoint(u32 driver, u32 idea, int point) {
  int total = GfGameManager::getOwnerBonus()->values[OWNER_BONUS_IDEA_POINT] + point;
  if (driver == 0) {
    mm::mtl::FixedVector<u16, 16> drivers;
    GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_PARTY_AND_RESERVER, 0);
    if (drivers.size() != 0) {
      u16 *member = drivers.begin();
      do {
        addIdeaPoint(*member, idea, total);
      } while (++member != drivers.end());
    }
  } else {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
    DataIdeaAcc dataIdeaAcc(dataParamAcc);
    int oldLevel = dataIdeaAcc.getLevel(idea);
    dataIdeaAcc.addPoint(idea, total);
    if (oldLevel != dataIdeaAcc.getLevel(idea)) {
      SCOM_POPUP::createIdea(driver, idea, dataIdeaAcc.getLevel(idea));
    }
  }
}

void GfGameUtil::setIdeaPointForDebug(u32 driver, u32 idea, int point) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  DataIdeaAcc dataIdeaAcc(dataParamAcc);
  dataIdeaAcc.setPointForDebug(idea, point);
}

void GfGameUtil::addDevelopPoint(u32 nation, u32 point) {
  bool isArcadiaDestroy = GfDataMap::isArcadiaDestroy();
  if (nation == NATION_ARCADIA && isArcadiaDestroy) {
    nation = NATION_IYASAKI;
  }

  u32 addPoint = GfGameManager::getOwnerBonus()->values[OWNER_BONUS_DEVELOP_POINT] + point;
  if (nation == 0) {
    nation = NATION_FIRST;
  }

  u32 pointMax = QuestListAcc::get()->getFLD_DevelopmentLevelValue(DEVELOP_LEVEL_MAX + 2);
  u32 total = addPoint + GfDataDevelop::getPoint(nation);
  GfDataDevelop::setPoint(nation, total > pointMax ? pointMax : total);
  SCOM_LEVELUP_DEVELOP::create();
}

void GfGameUtil::execDevelopLevelUp() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 pointLevel1 = questListAcc->getFLD_DevelopmentLevelValue(3);
  u32 pointLevel2 = questListAcc->getFLD_DevelopmentLevelValue(4);
  u32 pointLevel3 = questListAcc->getFLD_DevelopmentLevelValue(5);
  u32 pointLevel4 = questListAcc->getFLD_DevelopmentLevelValue(6);
  u32 pointLevel5 = questListAcc->getFLD_DevelopmentLevelValue(7);
  for (u32 nation = NATION_FIRST; nation <= NATION_COUNT; nation++) {
    u32 oldLevel = GfDataDevelop::getLevel(nation);
    u32 point = GfDataDevelop::getPoint(nation);
    if (oldLevel < pointLevel5 && point >= pointLevel5) {
      GfDataDevelop::setLevel(nation, 5);
    } else if (oldLevel < pointLevel4 && point >= pointLevel4) {
      GfDataDevelop::setLevel(nation, 4);
    } else if (oldLevel < pointLevel3 && point >= pointLevel3) {
      GfDataDevelop::setLevel(nation, 3);
    } else if (oldLevel < pointLevel2 && point >= pointLevel2) {
      GfDataDevelop::setLevel(nation, 2);
    } else if (oldLevel < pointLevel1 && point >= pointLevel1) {
      GfDataDevelop::setLevel(nation, 1);
    }

    u32 level = GfDataDevelop::getLevel(nation);
    if (oldLevel != level) {
      SCOM_POPUP::createDevelop(nationLocations[nation - NATION_FIRST], level);
    }
  }

  GfQuestManager::eventCheckTaskAll();
}

void GfGameUtil::setDevelopLevelForDebug(u32 nation, u32 level) {
  if (nation == 0 || GfDataDevelop::getLevel(nation) >= level) {
    return;
  }

  GfDataDevelop::setPoint(nation, QuestListAcc::get()->getFLD_DevelopmentLevelValue(level + 2));
  SCOM_LEVELUP_DEVELOP::create();
}

static int getEffectiveTrustRank(u32 blade) {
  int trustRank = GfDataBlade::getTrustRank(blade);
  u32 creator = GfDataBlade::getCreator(blade);
  u32 setDriver = GfDataBlade::getSetDriver(blade);
  u32 driver = setDriver == 0 ? creator : setDriver;
  if (trustRank > TRUST_RANK_MAX && trustRank < TRUST_RANK_LIMIT) {
    trustRank = TRUST_RANK_MAX;
  }

  if (creator != 0 && creator == driver) {
    return trustRank;
  }

  return trustRank > 1 ? trustRank - 1 : trustRank;
}

void GfGameUtil::addTrustRankForKizunaRing(u32 blade) {
  int oldTrustRank = getEffectiveTrustRank(blade);
  int trustRank = GfDataBlade::getTrustRank(blade);
  if (trustRank >= TRUST_RANK_MAX) {
    return;
  }

  GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(trustRank + 1));
  int newTrustRank = getEffectiveTrustRank(blade);
  if (newTrustRank <= oldTrustRank) {
    return;
  }

  GfEvent::callDebugChangeIdea(DEBUG_CHANGE_IDEA_TRUST, blade, 0, 0);
  u32 driver = GfDataBlade::getSetDriver(blade);
  if (driver != 0 || (driver = GfDataBlade::getCreator(blade)) != 0) {
    SCOM_POPUP::createAffinity(blade, driver, newTrustRank);
  }
}

void GfGameUtil::addTrustPoint(u32 blade, u32 trustPoint) {
  if (trustPoint == 0) {
    return;
  }

  u32 total = GfDataBlade::getTrustPoint(blade) + trustPoint;
  if (total > TRUST_POINT_MAX) {
    total = TRUST_POINT_MAX;
  }

  GfDataBlade::setTrustPoint(blade, total);
  GfEvent::callDebugChangeIdea(DEBUG_CHANGE_IDEA_TRUST, blade, 0, 0);
  int oldTrustRank = GfDataBlade::getTrustRank(blade);
  if (GfDataBlade::isCompleteAchievement(blade)) {
    for (u32 trustRank = GfDataBlade::getTrustRank(blade);
         trustRank >= TRUST_RANK_MAX && trustRank < TRUST_RANK_LIMIT && GfBdatBlade::get()->getFLD_IdeaTableTrustPoint(trustRank) <= total;
         trustRank = GfDataBlade::getTrustRank(blade)) {
      GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(trustRank + 1));
    }

    if (oldTrustRank < GfDataBlade::getTrustRank(blade)) {
      u32 driver = GfDataBlade::getSetDriver(blade);
      if (driver != 0 || (driver = GfDataBlade::getCreator(blade)) != 0) {
        SCOM_POPUP::createAffinity(blade, driver, GfDataBlade::getTrustRank(blade));
      }
    }
  }

  GfQuestManager::eventCheckTaskAll();
}

void GfGameUtil::setTrustPointForDebug(u32 blade, u32 trustPoint) {
  GfDataBlade::setTrustPoint(blade, trustPoint);
  GfEvent::callDebugChangeIdea(DEBUG_CHANGE_IDEA_TRUST, blade, 0, 0);
  GfQuestManager::eventCheckTaskAll();
}

void GfGameUtil::setAchievementReleaseLevel(u32 blade, u32 line, u32 level) {
  level = level > ACHIEVEMENT_LEVEL_MAX ? ACHIEVEMENT_LEVEL_MAX : level;
  ACHIEVEMENT_TYPE achievementType;
  u32 index;
  if (!GfDataAchievement::getAchievementType(achievementType, index, line) || !GfDataBlade::setAchievReleaseLevel(blade, line, level)) {
    return;
  }

  u32 achievement = GfDataBlade::getAchievementID(blade, line, level);
  if (achievement != 0) {
    QuestListAcc *questListAcc = QuestListAcc::get();
    u32 ideaCategory = questListAcc->getFLD_AchievementListIdeaCategory(achievement);
    int ideaValue = questListAcc->getFLD_AchievementListIdeaCategory(achievement);
    if (ideaValue != 0) {
      SCOM_ADD_IDEA::create(INVALID_HANDLE, ideaCategory, ideaValue);
    }
  }

  GfAchievementRelease release;
  release.blade = blade;
  release.achievementType = achievementType;
  release.level = level;
  GfEvent::callAchievmentRelease(release);
}

u16 GfGameUtil::getAntiBladeAreaBdatId() { return GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea(); }

bool GfGameUtil::incEnemySuppress(u32 enemy) { return GfDataEnemy::incEnemySuppress(enemy); }

bool GfGameUtil::isEnableDeleteObject(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  return !objAcc.isBattle();
}

const char *GfGameUtil::getBladeModel(u32 blade, bool isDefault) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  if (!dataBlade->resourceNameModel2.empty() && !isDefault && isCondBladeModel(blade)) {
    return dataBlade->resourceNameModel2.c_str();
  }

  return dataBlade->resourceNameModel.c_str();
}

bool GfGameUtil::isCondBladeModel(u32 blade) {
  if (GfGameManager::isChangeNormalHomuraForce(blade)) {
    return false;
  }

  GfObjAcc objAcc(GfGameParty::getHandleDriver(GfGameParty::getPartyId(OBJECT_TYPE_BLADE, blade)));
  if (objAcc.isValid() && objAcc.isBattle()) {
    return false;
  }

  if (GfGameManager::isBattle()) {
    return false;
  }

  return GfGameCond::isGameCond(GfDataBlade::getSDataBlade(blade)->condition);
}

const char *GfGameUtil::getBladeMotion(u32 blade, bool isDefault) {
  SDataBlade *dataBlade = GfDataBlade::getSDataBlade(blade);
  if (!dataBlade->resourceNameMotion2.empty() && !isDefault && isCondBladeModel(blade)) {
    return dataBlade->resourceNameMotion2.c_str();
  }

  return dataBlade->resourceNameMotion.c_str();
}

const char *GfGameUtil::getDriverModel(u32 driver) {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  const char *model2 = bdatDriver->getChrDrModel2(driver);
  if (model2 != nullptr && *model2 != '\0' && isCondDriverModel(driver)) {
    return bdatDriver->getChrDrModel2(driver);
  }

  return bdatDriver->getChrDrModel(driver);
}

bool GfGameUtil::isCondDriverModel(u32 driver) { return GfGameCond::isGameCond(GfBdatChrDr::get()->getChrDrCondition(driver)); }

const char *GfGameUtil::getSalvageDriverModel(u32 driver) {
  if (driver == DRIVER_REX) {
    return isTrueRex() ? "pc/pc000104" : "pc/pc000102";
  }

  return "";
}

void GfGameUtil::incGameClearCount() {
  GfGameFlag::setLocal(1, FLAG_GAME_CLEAR, 1);
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->gameClearCount < GAME_CLEAR_COUNT_MAX) {
    dataGame->gameClearCount++;
  }
}

void GfGameUtil::makeWeaponStateIdle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isBattle) {
  const char *motionName = util::getFilePtrFromPath(GfObjUtil::getMotionResourceName(handle));
  state = "S_";
  state += motionName;
  state += "_";
  state += isBattle ? "btidle" : "idle";
}

void GfGameUtil::makeWeaponStateIdle(mm::mtl::FixStr<32> &state, u32 driver, bool isBattle) {
  const char *motionName = util::getFilePtrFromPath(GfDataDriver::getMotionResourceName(driver));
  state = "S_";
  state += motionName;
  state += "_";
  state += isBattle ? "btidle" : "idle";
}

void GfGameUtil::makeWeaponStateStartBattle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle) {
  state = "S_";
  state += util::getFilePtrFromPath(GfObjUtil::getMotionResourceName(handle));
  state += "_";
  state += "btstart";
}

void GfGameUtil::makeStateIdle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isBattle) {
  if (!isBattle) {
    state = "S_idle";
    return;
  }

  DataParamAcc dataParamAcc(handle);
  if (dataParamAcc.getObjType() == OBJECT_TYPE_BLADE || dataParamAcc.getObjType() == OBJECT_TYPE_ENEMY) {
    state = "S_btidle";
    return;
  }

  u32 blade = dataParamAcc.getBlade(-1, false);
  if (blade == 0) {
    return;
  }

  if (GfGameManager::isEvent(false)) {
    u32 weaponType = GfDataBlade::getBladeWpnType(blade);
    if (dataParamAcc.getObjType() == OBJECT_TYPE_DRIVER &&
        (weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_FIRST || weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_SECOND)) {
      state = "S_btidle";
      return;
    }
  }

  makeWeaponBattleIdleState(state, GfDataBlade::getBladeWpnType(blade));
}

void GfGameUtil::makeStateIdleByBlade(mm::mtl::FixStr<32> &state, u32 blade, bool isBattle) {
  if (!isBattle) {
    state = "S_idle";
    return;
  }

  if (blade == 0) {
    return;
  }

  u32 weaponType = GfDataBlade::getBladeWpnType(blade);
  if (GfGameManager::isEvent(false) && (weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_FIRST || weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_SECOND)) {
    state = "S_btidle";
    return;
  }

  makeWeaponBattleIdleState(state, weaponType);
}

void GfGameUtil::makeWeaponCommandBattle(mm::mtl::FixStr<32> &command, GF_OBJ_HANDLE *handle, bool isStart, bool isMotion) {
  const char *resourceName = isMotion ? GfObjUtil::getMotionResourceName(handle) : GfObjUtil::getResourceName(handle);
  const char *fileName = util::getFilePtrFromPath(resourceName);
  command = "C_";
  command += fileName;
  command += "_";
  command += isStart ? "btstart" : "btend";
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

void GfGameUtil::makeStateBattle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isStart) {
  GfObjAcc objAcc(handle);
  u32 type = objAcc.getType();
  u32 bdatId = objAcc.getBdatId();
  if (type == OBJECT_TYPE_DRIVER && !(bdatId >= DRIVER_SHIN && bdatId <= DRIVER_SHIN_2)) {
    DataParamAcc dataParamAcc(handle);
    state.format("S_%02d_", dataParamAcc.getWeaponType(-1, false));
  } else {
    state = "S_";
  }

  state += isStart ? "btstart" : "btend";
}

void GfGameUtil::makeStateBattleByBlade(mm::mtl::FixStr<32> &state, u32 blade, bool isStart) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  state.format("S_%02d_", dataParamAcc.getWeaponType(-1, false));
  state += isStart ? "btstart" : "btend";
}

void GfGameUtil::requestFieldDamage(GF_OBJ_HANDLE *handle) {
  if (GfGameScene::get() != nullptr) {
    GfGameScene::get()->setDamageCharacter(handle);
  }
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

GF_OBJ_HANDLE *GfGameUtil::getDebugPickObj() { return INVALID_HANDLE; }

bool GfGameUtil::isGameObjWait(GF_OBJ_HANDLE *handle) { return GfObjUtil::testFlag(handle, OBJ_FLAG_WAIT); }

bool GfGameUtil::isPlayVoice(GF_OBJ_HANDLE *handle) { return GfGameVoice::getResult(handle) == VOICE_RESULT_PLAY; }

bool GfGameUtil::isDispWorldMap(u32 map) {
  u32 condition = GfBdatMaplist::get()->getMaplistmapON_cndID(map);
  return condition != 0 && GfGameCond::isGameCond(condition);
}

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

void GfGameUtil::execEquipMercenariesBlade(u32 driver, u32 blade) {
  if (!GfDataBlade::isActivateMercenaryTeam(blade)) {
    return;
  }

  if (GfDataDriver::getBladeSet(driver) >= 0 && !GfDataBlade::isDummyBlade(GfDataDriver::getBlade(driver, -1))) {
    return;
  }

  u32 team = GfDataMercenaries::getTeamID(blade);
  GfGameMercenaries::cancelMission(GfDataMercenaries::getMissionIdByBlade(blade));
  GfGameMercenaries::clearTeamMember(team);
  if (GfDataBlade::isActivateReserver(blade)) {
    GfDataBlade::setActivateDriver(blade, -1, driver, 0);
  }
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

void GfGameUtil::execAddDevelopPointArcadia2Iyasaki() {
  u32 point = GfDataDevelop::getPoint(NATION_ARCADIA);
  GfDataDevelop::resetPoint(NATION_ARCADIA);
  SCOM_ADD_DEVELOP::create(NATION_IYASAKI, point);
}

void GfGameUtil::dispRexCrystal(GF_OBJ_HANDLE *handle, bool isDisp) {
  GfObjAcc objAcc(handle);
  int mesh = objAcc.getExtMeshIdx("cc_rex");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, isDisp ? 1.0f : 0.0f);
  }
}

void GfGameUtil::dispHomuraCrystal(GF_OBJ_HANDLE *handle, bool isDisp) {
  if (handle == INVALID_HANDLE) {
    return;
  }

  GfObjAcc objAcc(handle);
  int mesh = objAcc.getExtMeshIdx("cc_homu");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, isDisp ? 1.0f : 0.0f);
  }

  mesh = objAcc.getExtMeshIdx("cc_zohar");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, isDisp ? 0.0f : 1.0f);
  }
}

void GfGameUtil::dispMetsuCrystal(GF_OBJ_HANDLE *handle, bool isDisp) {
  if (handle == INVALID_HANDLE) {
    return;
  }

  GfObjAcc objAcc(handle);
  int mesh = objAcc.getExtMeshIdx("Front_Armor");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, isDisp ? 1.0f : 0.0f);
  }
}

bool GfGameUtil::isDummyBlade(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  if (dataParamAcc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  return GfDataBlade::isDummyBlade(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0);
}

bool GfGameUtil::isHomuraHoodStyle() { return GfGameCond::isGameCond(GfDataBlade::getSDataBlade(BLADE_HOMURA)->condition); }

bool GfGameUtil::isTrueRex() { return GfGameCond::isGameCond(GfBdatChrDr::get()->getChrDrCondition(DRIVER_REX)); }

void GfGameUtil::changeHikariCurrent(bool hikariCurrent) {
  GfDataBlade::setHikariCurrent(hikariCurrent);
  GfEvent::callHikariCurrent(hikariCurrent);
}

void GfGameUtil::setMaxPartyGauge() {
  if (btl::DataManager::get() != nullptr) {
    btl::DataManager::get()->SetPartyGauge(PARTY_GAUGE_MAX, false);
  }
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

bool GfGameUtil::isDispMetsuCrystal() { return !GfGameCond::isGameCond(GAME_COND_METSU_WITHOUT_CRYSTAL); }

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

void GfGameUtil::execSaveAchievementPopup(u32 blade) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  u32 &popupNum = dataGame->achievementPopupNum;
  for (u32 index = 0; index < popupNum;) {
    SDataAchievementPopup &popup = dataGame->achievementPopups[index];
    if (popup.blade != blade) {
      index++;
      continue;
    }

    SCOM_POPUP::createAchievement(blade, popup.achievement, popup.level);
    if (index >= popupNum) {
      popupNum--;
      break;
    }

    popup = dataGame->achievementPopups[popupNum - 1];
    popupNum--;
  }
}

} // namespace gf
