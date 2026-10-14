#include "gf/game/gf_game_cond.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/gf_game_util.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/gf_allocator.h"
#include "gf/util/gf_item_util.h"

namespace gf {

enum {
  QUEST_FLAG_COUNT = 2,
};

enum {
  CLOUD_HEIGHT_ANY,
  CLOUD_HEIGHT_LOW,
  CLOUD_HEIGHT_HIGH,
};

enum {
  WEATHER_BIT_COUNT = 32,
};

enum {
  IDEA_COUNT = 4,
  IDEA_RESULT_COUNT = 5,
};

enum {
  TRUST_RANK_MAX = 6,
};

enum {
  ACHIEVEMENT_LINE_FIELD_SKILL_FIRST = 6,
  ACHIEVEMENT_LINE_COUNT = 10,
  ACHIEVEMENT_LEVEL_COUNT = 5,
};

enum {
  FIELD_SKILL_COUNT = 3,
};

constexpr u32 BLADE_ID_FIRST = 1001;

static GfBdatCond *s_bdatCond;

GfGameCond::GfGameCond(const GfSetupParam &param) { initialize(param); }

void GfGameCond::initialize(const GfSetupParam &) { s_bdatCond = GfBdatCond::get(); }

GfGameCond::~GfGameCond() {}

void GfGameCond::build(const GfSetupParam &param) {
  // __LINE__ must be 87 as in the original file: its value changes the instruction order.
#line 87
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameCond(param);
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
    notQuest.id = notQuestFlag;
    notQuest.variant = notQuestFlag >> 16;
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
    notQuest.id = notQuestFlag;
    notQuest.variant = notQuestFlag >> 16;
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
    quest.id = questFlag;
    quest.variant = questFlag >> 16;
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
    quest.id = questFlag;
    quest.variant = questFlag >> 16;
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

  return emptyCount != QUEST_FLAG_COUNT * 2;
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
  if (cloudHeight != CLOUD_HEIGHT_ANY) {
    if (cloudSea != 0 && cloudHeight == CLOUD_HEIGHT_LOW) {
      return false;
    }
    if (cloudSea != 1 && cloudHeight == CLOUD_HEIGHT_HIGH) {
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
    for (u32 bit = 0; bit < WEATHER_BIT_COUNT; bit++, weather++) {
      if ((weatherBits & (1 << bit)) != 0) {
        break;
      }
    }
    if (weather >= WEATHER_A && weather <= WEATHER_F) {
      GfFieldWeather::setMapWeatherID(static_cast<WEATHERID>(weather));
    }
  }
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
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
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
    if (type == ItemType::COLLECTION_LIST) {
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

bool GfGameCond::isIdea(u32 condition, u32 blade, mm::mtl::FixedArray<bool, IDEA_RESULT_COUNT> *results) {
  if (results != nullptr) {
    for (u32 i = 0; i < IDEA_RESULT_COUNT; i++) {
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
  if (chara < BLADE_ID_FIRST) {
    bool isValid = false;
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, chara, static_cast<GimmickType>(0));
    if (dataParamAcc.isValid()) {
      DataIdeaAcc dataIdeaAcc(dataParamAcc);
      for (u32 idea = 0; idea < IDEA_COUNT; idea++) {
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

  if (!isFailed && chara >= BLADE_ID_FIRST) {
    u32 compatibility = s_bdatCond->getConditionIdeaCompatibility(condition);
    if (compatibility != 0) {
      isFailed |= compatibility > GfGameUtil::getTrustRank(chara);
    }
  }

  if (!isFailed && chara >= BLADE_ID_FIRST) {
    u32 trustPoint = s_bdatCond->getConditionIdeaTrustPoint(condition);
    if (trustPoint != 0) {
      isFailed = trustPoint > GfDataBlade::getTrustPoint(blade);
      if (results != nullptr) {
        (*results)[IDEA_COUNT] = true;
      }
    }
  }

  return !isFailed;
}

static bool isBladeFieldSkillLevel(u32 blade, u32 fieldSkill, u32 level) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  for (u32 index = 0; index < FIELD_SKILL_COUNT; index++) {
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

  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
  if (!dataParamAcc.isValid()) {
    return;
  }

  DataIdeaAcc dataIdeaAcc(dataParamAcc);
  for (u32 idea = 0; idea < IDEA_COUNT; idea++) {
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
    if (compatibility == TRUST_RANK_MAX) {
      if (static_cast<int>(trustRank) < TRUST_RANK_MAX) {
        GfDataBlade::setTrustRank(blade, static_cast<GfIdea>(TRUST_RANK_MAX));
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
  for (u32 line = 0; line < ACHIEVEMENT_LINE_COUNT; line++) {
    SDataBladeAchievement *achievInfo = GfDataBlade::getAchievInfo(blade, line);
    if (achievInfo->achievement != achievementSet) {
      continue;
    }

    for (u32 level = 0; level < ACHIEVEMENT_LEVEL_COUNT; level++) {
      AchievQuest &achievQuest = achievInfo->quests[level];
      if (achievQuest.quest.id == task && (achievQuest.flags & 1) == 0) {
        achievQuest.setCountComplete();
        achievQuest.setTaskComplete(false, true);
        achievQuest.setTaskComplete(true, true);
        achievQuest.flags |= 1;
        GfDataBlade::setAchievReleaseLevel(blade, line, level + 1);
        GfQuestInfo::setState(achievQuest.quest, QSTATE_FIN_A);
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
  for (; index < FIELD_SKILL_COUNT; index++) {
    if (dataParamAcc.getFieldSkill(index, false) == fieldSkill) {
      break;
    }
  }
  if (index == FIELD_SKILL_COUNT) {
    return;
  }

  if (dataParamAcc.getFieldSkillLevel(index, false) < level) {
    GfGameUtil::setAchievementReleaseLevel(blade, ACHIEVEMENT_LINE_FIELD_SKILL_FIRST + index, level);
  }
}

} // namespace gf
