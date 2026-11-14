#include "gf/game/gf_game_cond.h"

#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/gf_allocator.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

enum {
  QUEST_UNKNOWN_2 = 2, // Inferred role: quest flag count; original name unknown.
};

enum {
  CLOUD_HEIGHT_UNKNOWN_0, // Inferred role: cloud height any; original name unknown.
  CLOUD_HEIGHT_UNKNOWN_1, // Inferred role: cloud height low; original name unknown.
  CLOUD_HEIGHT_UNKNOWN_2, // Inferred role: cloud height high; original name unknown.
};

enum {
  WEATHER_UNKNOWN_32 = 32, // Inferred role: weather bit count; original name unknown.
};

enum {
  IDEA_UNKNOWN_4 = 4, // Inferred role: idea count; original name unknown.
  IDEA_UNKNOWN_5 = 5, // Inferred role: idea result count; original name unknown.
};

enum {
  ACHIEVEMENT_UNKNOWN_6 = 6, // Inferred role: achievement line field skill first; original name unknown.
};

enum {
  PARTY_CONDITION_UNKNOWN_0 = 0, // Inferred role: party condition activate; original name unknown.
  PARTY_CONDITION_UNKNOWN_1 = 1, // Inferred role: party condition member; original name unknown.
  PARTY_CONDITION_UNKNOWN_2 = 2, // Inferred role: party condition leader; original name unknown.
  PARTY_CONDITION_UNKNOWN_5 = 5, // Inferred role: party condition activate unuse; original name unknown.
  PARTY_CONDITION_UNKNOWN_3 = 3, // Inferred role: party condition character count; original name unknown.
};

enum {
  FIELD_UNKNOWN_3 = 3, // Inferred role: field skill count; original name unknown.
};

static GfBdatCond *s_bdatCond;

GfGameCond::GfGameCond(const GfSetupParam &param) { initialize(param); }

void GfGameCond::initialize(const GfSetupParam &) { s_bdatCond = GfBdatCond::get(); }

GfGameCond::~GfGameCond() {}

void GfGameCond::build(const GfSetupParam &param) {
  // __LINE__ must be 87 as in the original file: its value changes the instruction order.
#line 87
  new (getAllocator(ALLOCATOR_UNKNOWN_1), __FILE__, __LINE__, 8) GfGameCond(param);
}

void GfGameCond::destroy() {
  GfGameCond *gameCond = get();
  finalize();
  delete gameCond;
}

void GfGameCond::finalize() { s_bdatCond = nullptr; }

bool GfGameCond::isQuest(u32 condition) {
  u32 emptyCount = 0;
  {
    u32 notQuestFlag;
    QuestID notQuest;
    notQuestFlag = s_bdatCond->getConditionQuestNotQuestFlag(condition, 0);
    notQuest.unknown00 = notQuestFlag;
    notQuest.unknown02 = notQuestFlag >> 16;
    if (notQuest.empty()) {
      emptyCount++;
    } else {
      u32 state = GfQuestInfo::getState(notQuest);
      u32 min = s_bdatCond->getConditionQuestNotQuestFlagMin(condition, 0);
      u32 max = s_bdatCond->getConditionQuestNotQuestFlagMax(condition, 0);
      if (min <= state && state <= max) {
        return false;
      }
    }
    notQuestFlag = s_bdatCond->getConditionQuestNotQuestFlag(condition, 1);
    notQuest.unknown00 = notQuestFlag;
    notQuest.unknown02 = notQuestFlag >> 16;
    if (notQuest.empty()) {
      emptyCount++;
    } else {
      u32 state = GfQuestInfo::getState(notQuest);
      u32 min = s_bdatCond->getConditionQuestNotQuestFlagMin(condition, 1);
      u32 max = s_bdatCond->getConditionQuestNotQuestFlagMax(condition, 1);
      if (min <= state && state <= max) {
        return false;
      }
    }
  }
  {
    u32 questFlag;
    QuestID quest;
    questFlag = s_bdatCond->getConditionQuestQuestFlag(condition, 0);
    quest.unknown00 = questFlag;
    quest.unknown02 = questFlag >> 16;
    if (quest.empty()) {
      emptyCount++;
    } else {
      u32 state = GfQuestInfo::getState(quest);
      u32 min = s_bdatCond->getConditionQuestQuestFlagMin(condition, 0);
      u32 max = s_bdatCond->getConditionQuestQuestFlagMax(condition, 0);
      if (min > state || state > max) {
        return false;
      }
    }
    questFlag = s_bdatCond->getConditionQuestQuestFlag(condition, 1);
    quest.unknown00 = questFlag;
    quest.unknown02 = questFlag >> 16;
    if (quest.empty()) {
      emptyCount++;
    } else {
      u32 state = GfQuestInfo::getState(quest);
      u32 min = s_bdatCond->getConditionQuestQuestFlagMin(condition, 1);
      u32 max = s_bdatCond->getConditionQuestQuestFlagMax(condition, 1);
      if (min > state || state > max) {
        return false;
      }
    }
  }

  return emptyCount != QUEST_UNKNOWN_2 * 2;
}

bool GfGameCond::isScenario(u32 condition) {
  u16 scenario = GfDataUtil::getScenarioFlag();
  u16 scenarioMin = s_bdatCond->getConditionScenarioScenarioMin(condition);
  u16 scenarioMax = s_bdatCond->getConditionScenarioScenarioMax(condition);
  if (scenarioMax != 0 && (scenarioMin > scenario || scenario > scenarioMax)) {
    return false;
  }

  u16 notScenarioMin = s_bdatCond->getConditionScenarioNotScenarioMin(condition);
  u16 notScenarioMax = s_bdatCond->getConditionScenarioNotScenarioMax(condition);
  if (notScenarioMax != 0 && notScenarioMin <= scenario && scenario <= notScenarioMax) {
    return false;
  }

  return scenarioMin != 0 || scenarioMax != 0 || notScenarioMin != 0 || notScenarioMax != 0;
}

void GfGameCond::applyScenario(u32 condition) {
  if (!isScenario(condition)) {
    GfDataUtil::setScenarioFlag(s_bdatCond->getConditionScenarioScenarioMin(condition));
  }
}

bool GfGameCond::isGameEnv(u32 condition, u32 weatherBits, u32 timeRangeBits, CLOUD_SEA cloudSea) {
  u32 timeRange = s_bdatCond->getConditionEnvTimeRange(condition);
  if (timeRange != 0 && (timeRange & timeRangeBits) == 0) {
    return false;
  }

  u32 weather = s_bdatCond->getConditionEnvWeather(condition);
  if (weather != 0 && (weather & weatherBits) == 0) {
    return false;
  }

  u32 cloudHeight = s_bdatCond->getConditionEnvCloudHeight(condition);
  if (cloudHeight != CLOUD_HEIGHT_UNKNOWN_0) {
    if (cloudSea != 0 && cloudHeight == CLOUD_HEIGHT_UNKNOWN_1) {
      return false;
    }
    if (cloudSea != 1 && cloudHeight == CLOUD_HEIGHT_UNKNOWN_2) {
      return false;
    }
  }

  return true;
}

bool GfGameCond::isGameEnv(u32 condition, u32 map) {
  u32 timeRangeBits = 0;
  if (GfFieldTime::get() != nullptr) {
    timeRangeBits = GfFieldTime::get()->getTimeRangeBits();
  }
  u32 weatherBits = GfFieldWeather::getCurrentMapWeatherBit(false);
  CLOUD_SEA cloudSea = GfFieldWeather::getCloudSea(map);
  return isGameEnv(condition, weatherBits, timeRangeBits, cloudSea);
}

void GfGameCond::applyGameEnv(u32 condition) {
  u32 timeRange = s_bdatCond->getConditionEnvTimeRange(condition);
  if (timeRange != 0 && GfFieldTime::get() != nullptr) {
    GfFieldTime::get()->setTimeRangeBit(timeRange);
  }

  u32 weatherBits = s_bdatCond->getConditionEnvWeather(condition);
  if (weatherBits != 0) {
    u32 weather = WEATHER_A;
    for (u32 bit = 0; bit < WEATHER_UNKNOWN_32; bit++, weather++) {
      if ((weatherBits & (1 << bit)) != 0) {
        break;
      }
    }
    if (weather >= WEATHER_A && weather <= WEATHER_F) {
      GfFieldWeather::setMapWeatherID(static_cast<WEATHERID>(weather));
    }
  }
}

static bool isInRange(u32 value, u32 min, u32 max) { return min <= value && max >= value; }

bool GfGameCond::isFlag(u32 condition, bool *isAboveMin, bool *isBelowMax) {
  u32 flagType = s_bdatCond->getConditionFlagFlagType(condition);
  u32 flagId = s_bdatCond->getConditionFlagFlagID(condition);
  u32 flagMin = s_bdatCond->getConditionFlagFlagMin(condition);
  u32 flagMax = s_bdatCond->getConditionFlagFlagMax(condition);
  u32 value;
  switch (flagType) {
  case 1:
    value = GfGameFlag::getLocal(1, flagId);
    break;
  case 2:
    value = GfGameFlag::getLocal(2, flagId);
    break;
  case 4:
    value = GfGameFlag::getLocal(4, flagId);
    break;
  case 8:
    value = GfGameFlag::getLocal(8, flagId);
    break;
  case 16:
    value = GfGameFlag::getLocal(16, flagId);
    break;
  case 32:
    value = GfGameFlag::getLocal(32, flagId);
    break;
  default:
    return false;
  }

  if (isAboveMin != nullptr) {
    *isAboveMin = flagMin <= value;
  }
  if (isBelowMax != nullptr) {
    *isBelowMax = flagMax >= value;
  }
  return isInRange(value, flagMin, flagMax);
}

void GfGameCond::applyFlag(u32 condition) {
  if (isFlag(condition, nullptr, nullptr)) {
    return;
  }

  u32 flagType = s_bdatCond->getConditionFlagFlagType(condition);
  u32 flagId = s_bdatCond->getConditionFlagFlagID(condition);
  u32 flagMin = s_bdatCond->getConditionFlagFlagMin(condition);
  switch (flagType) {
  case 1:
    GfGameFlag::setLocal(1, flagId, flagMin);
    break;
  case 2:
    GfGameFlag::setLocal(2, flagId, flagMin);
    break;
  case 4:
    GfGameFlag::setLocal(4, flagId, flagMin);
    break;
  case 8:
    GfGameFlag::setLocal(8, flagId, flagMin);
    break;
  case 16:
    GfGameFlag::setLocal(16, flagId, flagMin);
    break;
  case 32:
    GfGameFlag::setLocal(32, flagId, flagMin);
    break;
  }
}

bool GfGameCond::isGameCondParam(u32 condition, u32 index, u32 &conditionType, u32 &conditionParam) {
  conditionType = 0;
  conditionParam = 0;
  if (condition == 0) {
    return false;
  }

  conditionType = s_bdatCond->getConditionListConditionType(condition, index);
  if (conditionType == 0) {
    return false;
  }

  conditionParam = s_bdatCond->getConditionListCondition(condition, index);
  return conditionParam != 0;
}

bool GfGameCond::isLevel(u32 condition) {
  u32 driver = s_bdatCond->getConditionLevelPCID(condition);
  u32 level = s_bdatCond->getConditionLevelLevel(condition);
  DataParamAcc dataParamAcc(OBJECT_TYPE_PC, driver, static_cast<GimmickType>(0));
  if (!dataParamAcc.isValid()) {
    return false;
  }

  return dataParamAcc.getLevel(false) >= level;
}

void GfGameCond::applyLevel(u32 condition) {
  if (!isLevel(condition)) {
    GfDataDriver::setLevel(s_bdatCond->getConditionLevelPCID(condition), s_bdatCond->getConditionLevelLevel(condition));
  }
}

void GfGameCond::applyParty(u32 condition) {
  mm::mtl::FixedList<u32, PARTY_CONDITION_UNKNOWN_3> activateDrivers;
  mm::mtl::FixedList<u32, PARTY_CONDITION_UNKNOWN_3> activateBlades;
  mm::mtl::FixedList<u32, PARTY_CONDITION_UNKNOWN_3> removeDrivers;
  mm::mtl::FixedList<u32, PARTY_CONDITION_UNKNOWN_3> removeBlades;

  u32 category = s_bdatCond->getConditionPTCategory(condition);
  u32 index = 0;
  u32 leader = 0;
  for (; index < PARTY_CONDITION_UNKNOWN_3; index++) {
    u32 character = s_bdatCond->getConditionPTPCID(condition, index);
    if (character == 0) {
      break;
    }

    switch (category) {
    case PARTY_CONDITION_UNKNOWN_2:
      leader = character;
    case PARTY_CONDITION_UNKNOWN_0:
      if (character < BLADE_ID_UNKNOWN_1001) {
        activateDrivers.push_back(character);
      } else {
        activateBlades.push_back(character);
      }
      break;
    case PARTY_CONDITION_UNKNOWN_1:
      if (character < BLADE_ID_UNKNOWN_1001) {
        removeDrivers.push_back(character);
      } else {
        removeBlades.push_back(character);
      }
      break;
    case PARTY_CONDITION_UNKNOWN_5:
      if (GfDataBlade::isBladeID(character)) {
        activateBlades.push_back(character);
      }
      break;
    }
  }

  for (u32 driver : removeDrivers) {
    SCOM_PARTY_ADD::removeDriver(driver, false);
  }
  for (u32 blade : removeBlades) {
    SCOM_PARTY_ADD::removeDriver(blade, false);
  }
  for (const u32 &blade : activateBlades) {
    if (GfDataBlade::getSetDriver(blade) != 0) {
      continue;
    }

    u32 driver = GfDataBlade::getCreator(blade);
    if (driver == 0 || GfDataDriver::isActivateUnuse(driver)) {
      driver = DRIVER_UNKNOWN_1;
    }
    GfReqCommand::reqPartyBlade(blade, driver);
  }

  if (leader != 0) {
    SCOM_PARTY_LEADER::create(leader < BLADE_ID_UNKNOWN_1001 ? OBJECT_TYPE_PC : OBJECT_TYPE_BLADE, leader);
  }
}

bool GfGameCond::isItem(u32 condition) {
  u32 item = s_bdatCond->getConditionItemItemID(condition);
  u32 category = s_bdatCond->getConditionItemItemCategory(condition);
  u32 number = s_bdatCond->getConditionItemNumber(condition);
  u32 count;
  if (item != 0) {
    count = GfItemUtil::getItemBoxCount(item);
  } else {
    count = GfItemUtil::getCountByItemCategory(category);
  }

  if (number == 0) {
    return count == 0;
  }
  return number <= count;
}

void GfGameCond::applyItem(u32 condition) {
  u32 item = s_bdatCond->getConditionItemItemID(condition);
  u32 category = s_bdatCond->getConditionItemItemCategory(condition);
  u32 number = s_bdatCond->getConditionItemNumber(condition);
  if (item != 0) {
    u32 count = GfItemUtil::getItemBoxCount(item);
    if (number > count) {
      GfItemUtil::addItemBox(item, number - count);
    }
    return;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 count = GfItemUtil::getCountByItemCategory(category);
  if (number <= count) {
    return;
  }

  u32 rest = number - count;
  ItemType::Type type = GfDataItem::getTypeByItemCategory(category);
  u32 start;
  u32 end;
  if (!GfDataItem::getItemBdatCount(start, end, type)) {
    return;
  }

  for (u32 id = start; id < end; id++) {
    u32 itemCategory;
    if (type == ItemType::ITEM_TYPE_UNKNOWN_7) {
      itemCategory = bdatItem->getCollectionListCategory(id);
    } else {
      itemCategory = bdatItem->getFavoriteCategory(id);
    }
    if (itemCategory != category) {
      continue;
    }

    u32 boxCount = GfItemUtil::getItemBoxCount(id);
    u32 space = GfItemUtil::getEnableStock(id) - boxCount;
    if (rest < space) {
      GfItemUtil::addItemBox(id, rest);
      return;
    }

    GfItemUtil::addItemBox(id, space);
    rest -= space;
    if (rest == 0) {
      return;
    }
  }
}

bool GfGameCond::isIdea(u32 condition, u32 blade, mm::mtl::FixedArray<bool, IDEA_UNKNOWN_5> *results) {
  if (results != nullptr) {
    for (u32 i = 0; i < IDEA_UNKNOWN_5; i++) {
      (*results)[i] = false;
    }
  }

  u32 chara = s_bdatCond->getConditionIdeaPCID(condition);
  if (chara == 0) {
    chara = blade;
  }
  if (chara == 0) {
    return false;
  }

  bool isFailed = false;
  if (chara < BLADE_ID_UNKNOWN_1001) {
    bool isValid = false;
    DataParamAcc dataParamAcc(OBJECT_TYPE_PC, chara, static_cast<GimmickType>(0));
    if (dataParamAcc.isValid()) {
      DataIdeaAcc dataIdeaAcc(dataParamAcc);
      for (u32 idea = 0; idea < IDEA_UNKNOWN_4; idea++) {
        int level = dataIdeaAcc.getLevel(idea);
        if (level < static_cast<int>(s_bdatCond->getConditionIdeaIdeaLevel(condition, idea))) {
          isFailed = true;
        } else if (results != nullptr) {
          (*results)[idea] = true;
        }
      }
      isValid = true;
    }
    if (!isValid) {
      return false;
    }
  }

  if (!isFailed && chara >= BLADE_ID_UNKNOWN_1001) {
    u32 compatibility = s_bdatCond->getConditionIdeaCompatibility(condition);
    if (compatibility != 0) {
      isFailed |= compatibility > GfGameUtil::getTrustRank(chara);
    }
  }

  if (!isFailed && chara >= BLADE_ID_UNKNOWN_1001) {
    u32 trustPoint = s_bdatCond->getConditionIdeaTrustPoint(condition);
    if (trustPoint != 0) {
      isFailed = trustPoint > GfDataBlade::getTrustPoint(blade);
      if (results != nullptr) {
        (*results)[IDEA_UNKNOWN_4] = true;
      }
    }
  }

  return !isFailed;
}

bool GfGameCond::isAchievement(u32 condition, u32 blade) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 achievementSet = s_bdatCond->getConditionAchievementAchievementSetID(condition);
  if (achievementSet == 0) {
    return false;
  }

  mm::mtl::FixedVector<u16, 422> blades;
  if (blade == 0) {
    GfAchievManager *achievManager = GfAchievManager::get();
    if (achievManager != nullptr && !achievManager->getBladeByAchievementSet(blades, achievementSet)) {
      return true;
    }
  } else {
    blades.push_back(blade);
  }

  u32 value = s_bdatCond->getConditionAchievementValue(condition);
  if (value == 0) {
    return false;
  }

  u32 index = value - 1;
  u32 achievement = questListAcc->getFLD_AchievementSetAchievementID(achievementSet, index);
  if (achievement == 0) {
    return false;
  }

  u32 task = questListAcc->getFLD_AchievementListTask(achievement);
  if (task == 0) {
    return false;
  }

  for (u16 *candidate = blades.begin(), *end = blades.end(); candidate != end; candidate++) {
    for (u32 line = 0; line < ACHIEVEMENT_UNKNOWN_10; line++) {
      SDataBladeAchievement *achievInfo = GfDataBlade::getAchievInfo(*candidate, line);
      if (achievInfo->unknown00 == achievementSet && achievInfo->unknown04[index].unknown00.unknown00 == task && (achievInfo->unknown04[index].unknown0c & 1) != 0) {
        return true;
      }
    }
  }

  return false;
}

static bool isBladeFieldSkillLevel(u32 blade, u32 fieldSkill, u32 level) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  for (u32 index = 0; index < FIELD_UNKNOWN_3; index++) {
    if (dataParamAcc.getFieldSkill(index, false) == fieldSkill) {
      return dataParamAcc.getFieldSkillLevel(index, false) >= level;
    }
  }
  return false;
}

bool GfGameCond::isFieldSkillLevel(u32 condition, u32 blade) {
  mm::mtl::FixedVector<u16, 422> blades;
  if (blade != 0) {
    blades.push_back(blade);
  } else {
    GfDataBlade::getListForFieldSkill(blades);
  }

  u32 fieldSkill = s_bdatCond->getConditionFieldSkiiLevelFieldSkillID(condition);
  if (fieldSkill == 0) {
    return false;
  }

  u32 level = s_bdatCond->getConditionFieldSkiiLevelLevel(condition);
  if (level == 0) {
    return false;
  }

  if (blades.size() != 0) {
    u16 *candidate = blades.begin();
    u16 *end = blades.end();
    do {
      if (isBladeFieldSkillLevel(*candidate, fieldSkill, level)) {
        return true;
      }
    } while (++candidate != end);
  }

  return false;
}

void GfGameCond::applyIdea(u32 condition, u32 blade) {
  u32 driver = s_bdatCond->getConditionIdeaPCID(condition);
  if (driver == 0) {
    return;
  }

  DataParamAcc dataParamAcc(OBJECT_TYPE_PC, driver, static_cast<GimmickType>(0));
  if (!dataParamAcc.isValid()) {
    return;
  }

  DataIdeaAcc dataIdeaAcc(dataParamAcc);
  for (u32 idea = 0; idea < IDEA_UNKNOWN_4; idea++) {
    u32 level = s_bdatCond->getConditionIdeaIdeaLevel(condition, idea);
    if (dataIdeaAcc.getLevel(idea) < static_cast<int>(level)) {
      dataIdeaAcc.setLevel(idea, level);
    }
  }

  if (blade == 0) {
    return;
  }

  u32 compatibility = s_bdatCond->getConditionIdeaCompatibility(condition);
  if (compatibility != 0) {
    u32 trustRank = GfGameUtil::getTrustRank(blade);
    if (compatibility == RANK_UNKNOWN_6) {
      if (static_cast<int>(trustRank) < RANK_UNKNOWN_6) {
        GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(RANK_UNKNOWN_6));
      }
    } else if (trustRank < compatibility) {
      GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(compatibility));
    }
  }

  u32 trustPoint = s_bdatCond->getConditionIdeaTrustPoint(condition);
  if (trustPoint != 0 && trustPoint > GfDataBlade::getTrustPoint(blade)) {
    GfGameUtil::addTrustPoint(blade, trustPoint - GfDataBlade::getTrustPoint(blade));
  }
}

void GfGameCond::applyAchievement(u32 condition, u32 blade) {
  if (blade == 0) {
    return;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 achievementSet = s_bdatCond->getConditionAchievementAchievementSetID(condition);
  if (achievementSet == 0) {
    return;
  }

  u32 value = s_bdatCond->getConditionAchievementValue(condition);
  if (value == 0) {
    return;
  }

  u32 achievement = questListAcc->getFLD_AchievementSetAchievementID(achievementSet, value - 1);
  if (achievement == 0) {
    return;
  }

  u32 task = questListAcc->getFLD_AchievementListTask(achievement);
  for (u32 line = 0; line < ACHIEVEMENT_UNKNOWN_10; line++) {
    SDataBladeAchievement *achievInfo = GfDataBlade::getAchievInfo(blade, line);
    if (achievInfo->unknown00 != achievementSet) {
      continue;
    }

    for (u32 level = 0; level < ACHIEVEMENT_UNKNOWN_5; level++) {
      AchievQuest &achievQuest = achievInfo->unknown04[level];
      if (achievQuest.unknown00.unknown00 == task && (achievQuest.unknown0c & 1) == 0) {
        achievQuest.setCountComplete();
        achievQuest.setTaskComplete(false, true);
        achievQuest.setTaskComplete(true, true);
        achievQuest.unknown0c |= 1;
        GfDataBlade::setAchievReleaseLevel(blade, line, level + 1);
        GfQuestInfo::setState(achievQuest.unknown00, QSTATE_UNKNOWN_2);
        return;
      }
    }
  }
}

void GfGameCond::applyFieldSkillLevel(u32 condition, u32 blade) {
  if (blade == 0) {
    return;
  }

  u32 fieldSkill = s_bdatCond->getConditionFieldSkiiLevelFieldSkillID(condition);
  if (fieldSkill == 0) {
    return;
  }

  u32 level = s_bdatCond->getConditionFieldSkiiLevelLevel(condition);
  if (level == 0) {
    return;
  }

  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  u32 index = 0;
  for (; index < FIELD_UNKNOWN_3; index++) {
    if (dataParamAcc.getFieldSkill(index, false) == fieldSkill) {
      break;
    }
  }
  if (index == FIELD_UNKNOWN_3) {
    return;
  }

  if (dataParamAcc.getFieldSkillLevel(index, false) < level) {
    GfGameUtil::setAchievementReleaseLevel(blade, ACHIEVEMENT_UNKNOWN_6 + index, level);
  }
}

void GfGameCond::applyCond(u32 condition, u32 blade) {
  if (condition == 0) {
    return;
  }

  for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
    u32 conditionType = s_bdatCond->getConditionListConditionType(condition, index);
    u32 conditionParam = s_bdatCond->getConditionListCondition(condition, index);
    if (conditionParam == 0) {
      return;
    }

    switch (conditionType) {
    case CONDITION_TYPE_UNKNOWN_1:
      applyScenario(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_2:
      applyQuest(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_3:
      applyGameEnv(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_4:
      applyFlag(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_5:
      applyItem(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_6:
      applyParty(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_7:
      applyIdea(conditionParam, blade);
      break;
    case CONDITION_TYPE_UNKNOWN_8:
      applyLevel(conditionParam);
      break;
    case CONDITION_TYPE_UNKNOWN_9:
      applyAchievement(conditionParam, blade);
      break;
    case CONDITION_TYPE_UNKNOWN_10:
      applyFieldSkillLevel(conditionParam, blade);
      break;
    }
  }
}

} // namespace gf
