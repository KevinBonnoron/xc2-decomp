#include "gf/game/gf_game_util.h"

#include "gf/object/gf_obj_handle.h"
#include <stdarg.h>

#include "battle/data_manager_battle.h"
#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
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
#include "gf/data/gf_item_handle.h"
#include "gf/data/gf_object_type.h"
#include "gf/event/gf_event.h"
#include "gf/field/gf_field_gimmick.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_mount.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_scene.h"
#include "gf/game/gf_game_voice.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/mercenaries/gf_game_mercenaries.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_append.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "gf/scom/gf_scom_achiev.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_util.h"
#include "gmk/gmk_base.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {

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
  BELONGING_FIRST = 1,
  BELONGING_SECOND = 2,
};

enum {
  SCENARIO_FLAG_WITHOUT_CRYSTAL_FIRST = 1001,
  SCENARIO_FLAG_WITHOUT_CRYSTAL_LAST = 1030,
};

constexpr u32 WEAPON_TYPE_EVENT_BATTLE_IDLE_FIRST = 18;
constexpr u32 WEAPON_TYPE_EVENT_BATTLE_IDLE_SECOND = 19;

constexpr u32 ETHER_MAX = 999'999'999;
constexpr int TRUST_RANK_LIMIT = 16;
constexpr u32 TRUST_POINT_MAX = 0xffff;
constexpr u32 ACHIEVEMENT_LEVEL_MAX = 5;
constexpr u32 DRIVER_SKILL_LEVEL_MAX = 3;
constexpr u32 GAME_CLEAR_COUNT_MAX = 9'999;
constexpr u32 ACHIEVEMENT_POPUP_MAX = 300;
constexpr int PARTY_GAUGE_MAX = 300;
constexpr u32 FOLLOW_OBJ_MAX = 768;
constexpr u32 SAIKA_HANDLE_MAX = 8;
constexpr u32 APPEND_HANDLE_MAX = 10;
constexpr u32 DRIVER_ACCESSORY_SLOT_COUNT = 2;
constexpr u32 PARTY_DRIVER_COUNT = 3;

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
    for (u32 trustRank = GfDataBlade::getTrustRank(blade); trustRank >= TRUST_RANK_MAX && trustRank < TRUST_RANK_LIMIT && GfBdatBlade::get()->getFLD_IdeaTableTrustPoint(trustRank) <= total;
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

void GfGameUtil::setDispByGmkType(gmk::GmkType type, bool isDisp) { gmk::setDispByGmkType(type, isDisp); }

void GfGameUtil::setDispByGmkTypeAndBdatId(gmk::GmkType type, int bdatId, bool isDisp) { gmk::setDispByGmkTypeAndBdatId(type, bdatId, isDisp); }

void GfGameUtil::setDispByGmkTypeAndGmkIdx(gmk::GmkType type, u32 index, bool isDisp) {
  int gmkSet = GfFieldGimmick::getBdatIdFrom_FLD_maplist_To_RSC_GmkSetList(gmk::getCurrentMapBdatId());
  gmk::setDispByGmkTypeAndGmkIdx(gmkSet, type, index, isDisp);
}

u16 GfGameUtil::getAntiBladeAreaBdatId() { return GfFieldGimmick::getBdatIdOfActiveGmkAntiBladeArea(); }

bool GfGameUtil::getGmkTargetPointPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle) {
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(handle);
  if (gmkInst != nullptr) {
    u32 type = gmkInst->getGmkType();
    if (type <= gmk::GMK_TYPE_ROUTED_ENEMY) {
      return getGmkTargetPointPos(position, gmkInst->createInfo.info->id);
    }
  }

  return false;
}

bool GfGameUtil::incEnemySuppress(u32 enemy) { return GfDataEnemy::incEnemySuppress(enemy); }

bool GfGameUtil::isEnableDeleteObject(GF_OBJ_HANDLE *handle) {
  GfObjAcc objAcc(handle);
  return !objAcc.isBattle();
}

u32 GfGameUtil::getFormationPlayerID(GF_OBJ_HANDLE *handle) {
  if (GfObjUtil::isTrinityBlade(handle)) {
    return -1;
  }

  GfGameParty::getPartyId(handle);
  u32 hierarchy = GfGameParty::getHierarchyByHandle(handle);
  if (hierarchy == 0) {
    return -1;
  }

  GfObjAcc objAcc(handle);
  if (objAcc.isRebuild()) {
    int *formationPlayerId;
    if (objAcc.getType() == OBJECT_TYPE_DRIVER) {
      formationPlayerId = &mm::mtl::dynamicCast<GfObjSetupDriver>(GfObjManager::getObjInfo(handle)->setup)->formationPlayerId;
    } else if (objAcc.getType() == OBJECT_TYPE_BLADE) {
      formationPlayerId = &mm::mtl::dynamicCast<GfObjSetupBlade>(GfObjManager::getObjInfo(handle)->setup)->formationPlayerId;
    } else {
      return hierarchy - 1;
    }

    if (*formationPlayerId >= 0) {
      return *formationPlayerId;
    }
  }

  return hierarchy - 1;
}

void GfGameUtil::setHp(GF_OBJ_HANDLE *handle, u32 hp) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  MsgObjectHealHp message(hp, HEAL_TYPE_SET);
  message.isRevive = true;
  obj->sendMessage(obj, message);
}

void GfGameUtil::debugFallDead(GF_OBJ_HANDLE *handle) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj == nullptr) {
    return;
  }

  MsgObjectDead message(DEAD_TYPE_EMERGENCY_ESCAPE);
  obj->sendMessage(obj, message);
}

bool GfGameUtil::isDriverRide(GF_OBJ_HANDLE *handle) {
  GfObjSetupDriver *setup = GfObjUtil::getObjSetup<GfObjSetupDriver>(handle);
  return setup != nullptr && setup->isRide;
}

bool GfGameUtil::isSceneRide() {
  if (GfGameManager::isBattle()) {
    return false;
  }

  for (u32 partyId = 0; partyId < PARTY_DRIVER_COUNT; partyId++) {
    GfObjAcc objAcc(GfGameParty::getHandleDriver(partyId));
    if (!objAcc.isValid()) {
      continue;
    }

    if (objAcc.isBattle()) {
      return false;
    }
  }

  return true;
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

u32 GfGameUtil::getNowHp(GF_OBJ_HANDLE *handle, u32 objectType, u32 id) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->status != nullptr) {
      return property->status->hp;
    }
  }

  DataParamAcc dataParamAcc(objectType, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getHpMax(true);
}

u32 GfGameUtil::getMaxHp(GF_OBJ_HANDLE *handle, u32 objectType, u32 id) {
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    GfComProperty *property = obj->getComponent<GfComProperty>();
    if (property != nullptr && property->status != nullptr) {
      return property->status->maxHp;
    }
  }

  DataParamAcc dataParamAcc(objectType, id, GIMMICK_TYPE_NONE);
  return dataParamAcc.getHpMax(true);
}

bool GfGameUtil::getNowHpForUi(GF_OBJ_HANDLE *handle, u32 *hp) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr || property->character == nullptr) {
    return false;
  }

  *hp = property->character->hp;
  return true;
}

bool GfGameUtil::getMaxHpForUi(GF_OBJ_HANDLE *handle, u32 *maxHp) {
  GfObjProperty *property = GfObjUtil::getProperty(handle);
  if (property == nullptr || property->character == nullptr) {
    return false;
  }

  *maxHp = property->character->maxHp;
  return true;
}

void GfGameUtil::incGameClearCount() {
  GfGameFlag::setLocal(1, FLAG_GAME_CLEAR, 1);
  SDataGame *dataGame = GfDataManager::getDataGame();
  if (dataGame->gameClearCount < GAME_CLEAR_COUNT_MAX) {
    dataGame->gameClearCount++;
  }
}

void GfGameUtil::refreshEnhanceState(u32 driver) {
  GfObj *obj = GfObjUtil::getObj(GfGameParty::getHandleDriverByBdatID(driver));
  if (obj == nullptr) {
    return;
  }

  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, GIMMICK_TYPE_NONE);
  MsgObjectChangeHpMax message(dataParamAcc.getHpMax(false));
  obj->sendMessage(obj, message);
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
    if (dataParamAcc.getObjType() == OBJECT_TYPE_DRIVER && (weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_FIRST || weaponType == WEAPON_TYPE_EVENT_BATTLE_IDLE_SECOND)) {
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

void GfGameUtil::changeObjAttribute(GF_OBJ_HANDLE *handle, u32 attribute) {
  DataParamAcc dataParamAcc(handle);
  u32 objectType = dataParamAcc.getObjType();
  if (objectType == OBJECT_TYPE_DRIVER || objectType == OBJECT_TYPE_BLADE) {
    GfReqCommand::reqChangeAttribute(dataParamAcc.getObjType(), dataParamAcc.getBlade(-1, false), attribute);
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

void GfGameUtil::setBladeSelect(GF_OBJ_HANDLE *handle, int slot) {
  DataParamAcc dataParamAcc(handle);
  u32 oldAttribute = dataParamAcc.getAttribute(-1, false);
  dataParamAcc.setBladeSet(slot);
  GfObj *obj = GfObjUtil::getObj(handle);
  if (obj != nullptr) {
    MsgObjectChangeAttribute message;
    message.attribute = dataParamAcc.getAttribute(-1, false);
    message.oldAttribute = oldAttribute;
    obj->sendMessage(obj, message);
  }
}

GF_OBJ_HANDLE *GfGameUtil::getDebugPickObj() { return INVALID_HANDLE; }

void GfGameUtil::startWire(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time) {
  if (GfGameScene::get() == nullptr) {
    return;
  }

  GfAppendWire *wire = GfGameScene::get()->getAppendControl(handle);
  if (wire != nullptr) {
    wire->startWire(target, time);
  }
}

void GfGameUtil::startWireWithClose(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance) {
  if (GfGameScene::get() == nullptr) {
    return;
  }

  GfAppendWire *wire = GfGameScene::get()->getAppendControl(handle);
  if (wire != nullptr) {
    wire->startWireWithClose(target, time, closeTime, closeDistance);
  }
}

void GfGameUtil::startWireWithBone(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, const char *bone, f32 time) {
  if (GfGameScene::get() == nullptr) {
    return;
  }

  GfAppendWire *wire = GfGameScene::get()->getAppendControl(handle);
  if (wire != nullptr) {
    wire->startWireWithBone(target, bone, time);
  }
}

void GfGameUtil::endWire(GF_OBJ_HANDLE *handle, f32 time) {
  if (GfGameScene::get() == nullptr) {
    return;
  }

  GfAppendWire *wire = GfGameScene::get()->getAppendControl(handle);
  if (wire != nullptr) {
    wire->endWire(time);
  }
}

void GfGameUtil::setGameObjWait(GF_OBJ_HANDLE *handle, bool isWait) {
  GfObjUtil::setFlag(handle, OBJ_FLAG_WAIT, isWait);
  mm::mtl::FixedList<GF_OBJ_HANDLE *, FOLLOW_OBJ_MAX> followObjs;
  if (GfObjManager::get() != nullptr && GfObjManager::get()->getFollowObj(followObjs, handle)) {
    for (GF_OBJ_HANDLE *followObj : followObjs) {
      setGameObjWait(followObj, isWait);
    }
  }
}

bool GfGameUtil::isGameObjWait(GF_OBJ_HANDLE *handle) { return GfObjUtil::testFlag(handle, OBJ_FLAG_WAIT); }

bool GfGameUtil::isPlayVoice(GF_OBJ_HANDLE *handle) { return GfGameVoice::getResult(handle) == VOICE_RESULT_PLAY; }

void GfGameUtil::levelupForEnemy(GF_OBJ_HANDLE *handle, u32 addLevel) {
  DataParamAcc dataParamAcc(handle);
  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
  if (setup == nullptr) {
    return;
  }

  u32 levelMax = GfBdatChrEnParam::get()->getChrEnParamTableEnd() - 1;
  u32 level = dataParamAcc.getLevel(false) + addLevel;
  GfDataEnemy::setupGameParamForLevel(*setup->dataEnemy, level > levelMax ? levelMax : level);
  GfObj *obj = GfObjUtil::getObj(handle);
  MsgObjectChangeHpMax changeHpMax(dataParamAcc.getHpMax(false));
  obj->sendMessage(obj, changeHpMax);
  u32 maxHp = dataParamAcc.getHpMax(false);
  u32 hp = dataParamAcc.getHp();
  if (hp < maxHp) {
    MsgObjectHealHp healHp(maxHp - hp, HEAL_TYPE_NORMAL);
    obj = GfObjUtil::getObj(handle);
    obj->sendMessage(obj, healHp);
  }
}

bool GfGameUtil::isDispWorldMap(u32 map) {
  u32 condition = GfBdatMaplist::get()->getMaplistmapON_cndID(map);
  return condition != 0 && GfGameCond::isGameCond(condition);
}

u32 GfGameUtil::getBladeOnBookedItem(u32 blade) {
  u32 item = GfDataBlade::getBookedItemInfo(blade);
  if (item == 0) {
    return 0;
  }

  return GfItemUtil::getItemBoxCount(item) == 0 ? 0 : item;
}

bool GfGameUtil::execActivateUnuseForBlade(u32 blade, bool isRelease) {
  if (GfDataBlade::isCommonBlade(blade)) {
    GfKizunaringBlade::removeAchievement(blade);
  }

  if (isRelease) {
    for (u32 slot = 0; slot < GfDataBlade::getEquipOrbMax(blade); slot++) {
      GfEquipUtil::equipBladeOrb(blade, 0, slot, GfItemHandle(0));
    }
  }

  ActivateType activateType = GfDataBlade::getBladeActivateType(*GfDataBlade::getSDataBlade(blade));
  if (GfDataBlade::setActivateUnuse(blade)) {
    if (isRelease && GfDataBlade::isRareBlade(blade)) {
      GfDataBlade::resetAttachedParty(blade);
    }

    GfEvent::callBladeActivate(blade, activateType, ACTIVATE_TYPE_UNUSE);
  }

  return false;
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

void GfGameUtil::changeAlphaBelonging(GF_OBJ_HANDLE *handle, u32 belonging, f32 alpha, f32 time) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_BELONGING);
  if (weapon == nullptr) {
    return;
  }

  switch (belonging) {
  case BELONGING_SECOND:
    SCOM_OBJ_ALPHA::create(weapon->getCurrentHandles()[1], time, alpha);
    break;
  case BELONGING_FIRST:
    SCOM_OBJ_ALPHA::create(weapon->getCurrentHandles()[0], time, alpha);
    break;
  }
}

bool GfGameUtil::hasBelonging(GF_OBJ_HANDLE *handle, u32 belonging) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_BELONGING);
  if (weapon == nullptr) {
    return false;
  }

  switch (belonging) {
  case BELONGING_SECOND:
    return weapon->getCurrentHandles()[1] != INVALID_HANDLE;
  case BELONGING_FIRST:
    return weapon->getCurrentHandles()[0] != INVALID_HANDLE;
  default:
    return false;
  }
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

void GfGameUtil::setSaikaLensOff(GF_OBJ_HANDLE *handle) {
  u16 scenarioFlag = GfDataUtil::getScenarioFlag();
  GfObjAcc objAcc(handle);
  switch (objAcc.getType()) {
  case OBJECT_TYPE_BLADE:
    if (objAcc.getBladeId() != BLADE_SAIKA) {
      return;
    }
    break;
  case OBJECT_TYPE_ENEMY:
    if (GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(objAcc.getEnArrangeId()) != BLADE_SAIKA) {
      return;
    }
    break;
  }

  int mesh = objAcc.getExtMeshIdx("mt_lens_L");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, scenarioFlag > SCENARIO_FLAG_SAIKA_LENS_OFF ? 0.0f : 1.0f);
  }

  mesh = objAcc.getExtMeshIdx("mt_lens_R");
  if (mesh >= 0) {
    objAcc.setExtMeshAlpha(mesh, scenarioFlag > SCENARIO_FLAG_SAIKA_LENS_OFF ? 0.0f : 1.0f);
  }
}

void GfGameUtil::setSaikaLensOff() {
  mm::mtl::FixedVector<GF_OBJ_HANDLE *, SAIKA_HANDLE_MAX> handles;
  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getList(OBJECT_TYPE_BLADE)) {
    DataParamAcc dataParamAcc(handle);
    if (dataParamAcc.isValid() && dataParamAcc.getBdatId() == BLADE_SAIKA) {
      handles.push_back(handle);
    }
  }

  GfBdatChrEnArrange *bdatEnemyArrange = GfBdatChrEnArrange::get();
  for (GF_OBJ_HANDLE *const &handle : *GfGameObj::getListEnemyBlade()) {
    DataParamAcc dataParamAcc(handle);
    if (bdatEnemyArrange->getChrEnArrangeBladeID(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0) == BLADE_SAIKA) {
      handles.push_back(handle);
    }
  }

  for (GF_OBJ_HANDLE *handle : handles) {
    setSaikaLensOff(handle);
  }
}

bool GfGameUtil::isDummyBlade(GF_OBJ_HANDLE *handle) {
  DataParamAcc dataParamAcc(handle);
  if (dataParamAcc.getObjType() != OBJECT_TYPE_BLADE) {
    return false;
  }

  return GfDataBlade::isDummyBlade(dataParamAcc.isValid() ? dataParamAcc.getBdatId() : 0);
}

GF_OBJ_HANDLE *GfGameUtil::getDriverWeaponRight(GF_OBJ_HANDLE *handle) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    GF_OBJ_HANDLE *weaponHandle = weapon->getCurrentHandles()[0];
    if (weaponHandle != INVALID_HANDLE) {
      return weaponHandle;
    }
  }

  weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON_EXTRA);
  if (weapon != nullptr) {
    GF_OBJ_HANDLE *weaponHandle = weapon->getCurrentHandles()[0];
    if (weaponHandle != INVALID_HANDLE) {
      return weaponHandle;
    }
  }

  return INVALID_HANDLE;
}

GF_OBJ_HANDLE *GfGameUtil::getDriverWeaponLeft(GF_OBJ_HANDLE *handle) {
  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON);
  if (weapon != nullptr) {
    GF_OBJ_HANDLE *weaponHandle = weapon->getCurrentHandles()[1];
    if (weaponHandle != INVALID_HANDLE) {
      return weaponHandle;
    }
  }

  weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON_EXTRA);
  if (weapon != nullptr) {
    GF_OBJ_HANDLE *weaponHandle = weapon->getCurrentHandles()[0];
    if (weaponHandle != INVALID_HANDLE) {
      return weaponHandle;
    }
  }

  return INVALID_HANDLE;
}

void GfGameUtil::setKosmosArts3EnableBothWeapon(GF_OBJ_HANDLE *handle, bool isEnable) {
  GfObjAcc objAcc(handle);
  if (objAcc.getType() != OBJECT_TYPE_BLADE || objAcc.getBladeId() != BLADE_KOSMOS) {
    return;
  }

  GfWeapon *weapon = GfMountManager::getGfWeapon(handle, GFATTACH_WEAPON);
  if (weapon == nullptr) {
    return;
  }

  bool isAlternate = weapon->isAlternate;
  weapon->isAlternate = false;
  GfObjAcc weaponAcc(weapon->getCurrentHandles()[1]);
  weaponAcc.setDisp(OBJDISP_KOSMOS_ARTS_3, isEnable);
  GfObj *obj = weaponAcc.getObj();
  if (obj != nullptr) {
    obj->setUpdateComponent(isEnable);
  }

  weapon->isAlternate = isAlternate;
}

bool GfGameUtil::isHomuraHoodStyle() { return GfGameCond::isGameCond(GfDataBlade::getSDataBlade(BLADE_HOMURA)->condition); }

bool GfGameUtil::isTrueRex() { return GfGameCond::isGameCond(GfBdatChrDr::get()->getChrDrCondition(DRIVER_REX)); }

bool GfGameUtil::isDriverEquipBlade(u32 driver, u32 blade) {
  if (driver == 0) {
    return false;
  }

  if (!GfDataBlade::isActivateUnuse(blade)) {
    u32 setDriver = GfDataBlade::getSetDriver(blade);
    if (setDriver == 0 || !GfDataDriver::isActivateUnuse(setDriver)) {
      u32 creator = GfDataBlade::getCreator(blade);
      if (creator == 0) {
        return driver == DRIVER_REX;
      }

      if (creator == driver) {
        return true;
      }

      if (GfDataHana::isValid(blade)) {
        return driver == DRIVER_TORA;
      }

      if ((driver == DRIVER_REX_2 || driver == DRIVER_REX) && isTrueRex()) {
        return true;
      }
    }
  }

  return false;
}

GF_OBJ_HANDLE *GfGameUtil::getJijiHandle() {
  GfWeapon *append = GfMountManager::getAppendHandles(GfGameParty::getHandleDriverByBdatID(DRIVER_REX), GFATTACH_APPEND);
  if (append == nullptr) {
    return INVALID_HANDLE;
  }

  GF_OBJ_HANDLE *jiji = INVALID_HANDLE;
  for (u32 index = 0; index < APPEND_HANDLE_MAX; index++) {
    if (append->getCurrentHandles()[index] != INVALID_HANDLE) {
      jiji = append->getCurrentHandles()[index];
      break;
    }
  }

  if (jiji != INVALID_HANDLE) {
    GfObjAcc objAcc(jiji);
    if (!(objAcc.getAlphaNormal() <= 0.0f)) {
      return jiji;
    }
  }

  return INVALID_HANDLE;
}

void GfGameUtil::changeHikariCurrent(bool hikariCurrent) {
  GfDataBlade::setHikariCurrent(hikariCurrent);
  GfEvent::callHikariCurrent(hikariCurrent);
}

u32 GfGameUtil::getObjNumberByEnArrangeId(u32 arrange) {
  u32 number = GfGameObj::get() != nullptr ? GfGameObj::get()->getObjNumberByEnArrangeId(arrange) : 0;
  return GfObjUtil::getSetupObjNumberByEnArrangeId(arrange) + number;
}

void GfGameUtil::setMaxPartyGauge() {
  if (btl::DataManager::get() != nullptr) {
    btl::DataManager::get()->SetPartyGauge(PARTY_GAUGE_MAX, false);
  }
}

GF_OBJ_HANDLE *GfGameUtil::getBlade(GF_OBJ_HANDLE *handle) { return GfMountManager::getHandle(handle, GFATTACH_WEAPON, OPTMNT_BLADE); }

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

void GfGameUtil::execEquipDriverDefaultAcce(u32 driver) {
  if (driver == 0 || GfDataDriver::isEquipDefaultAcce(driver)) {
    return;
  }

  GfDataDriver::getSDataDriver(driver)->equipDefaultAcce = true;
  u32 accessory = GfBdatChrDr::get()->getChrDrDefAcce(driver);
  if (accessory == 0) {
    return;
  }

  if (GfItemUtil::isEnableAddItemBox(accessory, 1)) {
    GfItemUtil::addItemBoxWithSilent(accessory, 1);
  }

  GfEquipUtil::equipDriverAcce(driver, 0, accessory, GfItemHandle(0));
}

void GfGameUtil::execDriverDead(u32 driver) {
  for (u32 slot = 0; slot < DRIVER_ACCESSORY_SLOT_COUNT; slot++) {
    GfEquipUtil::equipDriverAcce(driver, slot, 0, GfItemHandle(0));
  }

  for (int slot = GfDataDriver::getMaxSetBladeNum(driver) - 1; slot >= 0; slot--) {
    u32 blade = GfDataDriver::getBlade(driver, slot);
    if (blade != 0) {
      GfDataDriver::unsetBlade(blade);
    }
  }
}

void GfGameUtil::setPartyChange10020() {
  for (u32 index = 0; index < BLADE_COUNT; index++) {
    u32 blade = GfDataBlade::getBladeID(index);
    if (blade == 0 || !GfDataBlade::isUnselect(blade)) {
      continue;
    }

    if (GfDataBlade::isRegularBlade(blade) && GfDataBlade::isUnselect(blade) && GfDataBlade::isActivateUnuse(blade)) {
      GfDataBlade::setActivateReserver(blade);
    }

    GfDataBlade::setUnselect(blade, false);
  }

  SCOM_PARTY_ADD::addBlade(BLADE_HIKARI, DRIVER_REX, -1);
  SCOM_PARTY_ADD::addBlade(BLADE_HOMURA, DRIVER_REX, -1);
  SCOM_PARTY_ADD::addBlade(BLADE_HOMURI, DRIVER_REX, -1);
  SCOM_PARTY_ADD::addDriver(DRIVER_NIA, -1);
  SCOM_PARTY_ADD::addDriver(DRIVER_TORA, -1);
  SCOM_PARTY_ADD::addDriver(DRIVER_MELEPH, -1);
  SCOM_PARTY_ADD::addDriver(DRIVER_JIKU, -1);
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
