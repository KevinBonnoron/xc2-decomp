#include "gf/game/gf_game_cond.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/field/gf_field_time.h"
#include "gf/field/gf_field_weather.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/gf_allocator.h"

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

static GfBdatCond *s_bdatCond;

GfGameCond::GfGameCond(const GfSetupParam &param) { initialize(param); }

void GfGameCond::initialize(const GfSetupParam &) { s_bdatCond = GfBdatCond::get(); }

GfGameCond::~GfGameCond() {}

void GfGameCond::build(const GfSetupParam &param) { new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) GfGameCond(param); }

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

} // namespace gf
