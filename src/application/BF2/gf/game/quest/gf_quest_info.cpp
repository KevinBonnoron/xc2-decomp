#include "gf/game/quest/gf_quest_info.h"
#include "bdat.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/util/gf_item_util.h"

namespace gf {

namespace {

enum {
  CONDITION_TYPE_ENVIRONMENT = 3,
};

constexpr u32 COLLECT_USE_FLAG_OFFSET = 0x5ef;
constexpr u32 DUMMY_TALK_GROUP_FLAG_OFFSET = 0xe8b;
constexpr u32 COUNT_FLAG_MAX = 0xff;
constexpr u32 CONDITION_LIST_COUNT = 8;
constexpr u32 ENEMY_GROUP_COUNT = 8;
constexpr u32 WEATHER_NONE = 4;

} // namespace

bool GfQuestInfo::isQuestOrder(QuestID quest) { return getState(quest) == QSTATE_ORDER; }

bool GfQuestInfo::isQuestProgress(QuestID quest) { return getState(quest) == QSTATE_ORDER; }

bool GfQuestInfo::isQuestFin(QuestID quest) { return getState(quest) > QSTATE_ORDER; }

bool GfQuestInfo::isQuestNotOrder(QuestID quest) { return getState(quest) == QSTATE_NOT_ORDER; }

QuestID GfQuestInfo::getParentQuest(QuestID quest) {
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  return parent;
}

u32 GfQuestInfo::getPlayEvent(QuestID quest, QSTATE state) {
  if (state == QSTATE_FIN_A) {
    return GfDataQuest::getListCallEventA(quest);
  }

  return GfDataQuest::getListCallEventB(quest);
}

bool GfQuestInfo::isParent(QuestID quest) { return GfDataQuest::getListPRTQuestID(quest).empty(); }

QuestID GfQuestInfo::getChildQuestID(QuestID quest) {
  QSTATE state = getState(quest);
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  bool isChildQuest = !parent.empty();
  bool isNextB = state == QSTATE_FIN_B && isChildQuest;
  if (isNextB) {
    QuestID child = GfDataQuest::getListNextQuestB(quest);
    if (!child.empty()) {
      return child;
    }
  }

  return GfDataQuest::getListNextQuestA(quest);
}

bool GfQuestInfo::incSuppressCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    u32 flag = QuestListAcc::get()->getBattleCountFlag(param.taskId);
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count < COUNT_FLAG_MAX) {
      GfGameFlag::setLocal(8, flag, count + 1);
    }

    return true;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
  if (achievQuest == nullptr || !GfDataBlade::isBattleMember(achievQuest->blade) || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
    return false;
  }

  achievQuest->incleseCount(1);
  return true;
}

void GfQuestInfo::resetSuppressCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    if (GfDataQuest::getListQuestCategory(param.quest) != QTYPE_ACHIEVEMENT) {
      GfGameFlag::setLocal(8, QuestListAcc::get()->getBattleCountFlag(param.taskId), 0);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    if (achievQuest != nullptr) {
      achievQuest->count = 0;
    }
  }
}

u32 GfQuestInfo::getSuppressCount(const QuestTaskParam &param) {
  if (param.quest.variant != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    return achievQuest != nullptr ? achievQuest->getCount() : 0;
  }

  return GfGameFlag::getLocal(8, QuestListAcc::get()->getBattleCountFlag(param.taskId));
}

u32 GfQuestInfo::getSuppressLimit(const QuestTaskParam &param) {
  if (param.quest.variant != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    return achievQuest != nullptr ? achievQuest->getTargetCount() : 0;
  }

  return QuestListAcc::get()->getBattleCount(param.taskId);
}

bool GfQuestInfo::incCollectUseCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    u32 flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_OFFSET;
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count >= COUNT_FLAG_MAX) {
      return false;
    }

    GfGameFlag::setLocal(8, flag, count + 1);
    return true;
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    if (achievQuest != nullptr && GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      return achievQuest->incleseCount(1);
    }
  }

  return false;
}

bool GfQuestInfo::decCollectUseCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    u32 flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_OFFSET;
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count != 0) {
      GfGameFlag::setLocal(8, flag, count - 1);
      return true;
    }

    return false;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
  if (achievQuest != nullptr) {
    return achievQuest->decleseCount(1);
  }

  return false;
}

u32 GfQuestInfo::getCollectUseCount(const QuestTaskParam &param) {
  if (param.quest.variant != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    return achievQuest != nullptr ? achievQuest->getCount() : 0;
  }

  return GfGameFlag::getLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_OFFSET);
}

u32 GfQuestInfo::getCollectUseLimit(const QuestTaskParam &param) {
  if (param.quest.variant != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    return achievQuest != nullptr ? achievQuest->getTargetCount() : 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.taskType == TASK_TYPE_COLLECT) {
    return questListAcc->getCollectCount(param.taskId);
  }

  if (param.taskType == TASK_TYPE_USE) {
    return questListAcc->getUseItemNumber(param.taskId);
  }

  return 0;
}

u32 GfQuestInfo::getCollectUseItem(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.taskType == TASK_TYPE_COLLECT) {
    return questListAcc->getCollectItemID(param.taskId);
  }

  if (param.taskType == TASK_TYPE_USE) {
    return questListAcc->getUseItemID(param.taskId);
  }

  return 0;
}

u32 GfQuestInfo::getCollectUseItemCategory(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.taskType == TASK_TYPE_COLLECT) {
    return questListAcc->getCollectCategory(param.taskId);
  }

  if (param.taskType == TASK_TYPE_USE) {
    return questListAcc->getUseCategory(param.taskId);
  }

  return 0;
}

void GfQuestInfo::resetCollectUseCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    if (GfDataQuest::getListQuestCategory(param.quest) != QTYPE_ACHIEVEMENT) {
      GfGameFlag::setLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_OFFSET, 0);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    if (achievQuest != nullptr) {
      achievQuest->count = 0;
    }
  }
}

void GfQuestInfo::setupAchievementCount(const QuestTaskParam &param) {
  if (param.quest.variant == 0) {
    return;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
  if (achievQuest == nullptr || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
    return;
  }

  s32 totalCount = GfAchievStats::getAchievementTotalCount(*achievQuest);
  if (totalCount < 0) {
    GfDataAchievement::setupTotalCount(*achievQuest);
  } else {
    achievQuest->setCount(totalCount);
  }

  if ((achievQuest->flags & 2) == 0 && achievQuest->isCountComplete()) {
    achievQuest->flags |= 2;
  }
}

u32 GfQuestInfo::getTaskHide(const QuestTaskParam &param) { return QuestListAcc::get()->getTaskTaskUI(param.purpose, param.taskIndex); }

bool GfQuestInfo::canQuestOrder(QuestID quest) { return getState(quest) == QSTATE_NOT_ORDER && !isQuestProgress(quest); }

bool GfQuestInfo::isScenarioQuest(QuestID quest) { return GfDataQuest::getQuestCategory(quest) == QTYPE_MAIN; }

bool GfQuestInfo::isCompleteTask(const QuestTaskParam &param) {
  if (param.purpose == 0) {
    return false;
  }

  return GfQuestTask::isCompleteFlag(param);
}

bool GfQuestInfo::isDispUI(QuestID quest) { return QuestListAcc::get()->getListVisible(quest) != 0; }

bool GfQuestInfo::getQuestNeedTaskCond(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (quest.empty()) {
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
    quest.id = current.id;
    quest.variant = current.variant;
  }

  if (quest.empty()) {
    return true;
  }

  u32 hints = GfDataQuest::getListHintsID(quest);
  if (hints == 0) {
    return true;
  }

  return questListAcc->getTaskPreCondition(hints) == 0;
}

bool GfQuestInfo::isCollectCond(u32 collect) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 count = questListAcc->getCollectCount(collect);
  u32 item = questListAcc->getCollectItemID(collect);
  u32 itemCount;
  if (item != 0) {
    itemCount = GfItemUtil::getItemBoxCount(item);
  } else {
    u32 category = questListAcc->getCollectCategory(collect);
    if (category == 0) {
      return true;
    }

    itemCount = GfItemUtil::getCountByItemCategory(category);
  }

  return itemCount >= count;
}

u32 GfQuestInfo::getListCategoryCount(QTYPE type, bool isParentOnly) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 count = questListAcc->getQuestListCount(type);
  if (isParentOnly) {
    count = 0;
    for (qlist_iterator it = questListAcc->begin(type); it != questListAcc->end(type); ++it) {
      count += isParent(it.getQuestID());
    }
  }

  return count;
}

u32 GfQuestInfo::getAchievCountByStats(u32 stats) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 start = questListAcc->getAchievementStart();
  u32 end = questListAcc->getAchievementEnd();
  for (u32 id = start; id < end; id++) {
    if (questListAcc->getAchievementStatsID(id) == stats) {
      return questListAcc->getAchievementCount(id);
    }
  }

  return 0;
}

bool GfQuestInfo::getBattleTaskEnemy(mm::mtl::FixedVector<u16, 128> &enemies, const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 enemy = questListAcc->getBattleEnemyID(param.taskId);
  if (enemy != 0) {
    if (enemies.size() != enemies.capacity()) {
      enemies.push_back(enemy);
    }
  } else {
    u32 group = questListAcc->getBattleEnemyGroupID(param.taskId);
    if (group != 0) {
      GfBdatChrEnParam *chrEnParam = GfBdatChrEnParam::get();
      for (u32 index = 0; index < ENEMY_GROUP_COUNT; index++) {
        u32 groupEnemy = chrEnParam->getEnemyGroupEnemyID(group, index);
        if (groupEnemy != 0 && enemies.size() != enemies.capacity()) {
          enemies.push_back(groupEnemy);
        }
      }
    } else {
      questListAcc->getBattleEnemySpeciesID(param.taskId);
    }
  }

  return !enemies.empty();
}

bool GfQuestInfo::getTaskLog(u8 *&bdat, u32 &textId, u32 purpose, u32 taskIndex) {
  if (purpose == 0) {
    return false;
  }

  textId = QuestListAcc::get()->getTaskTaskLog(purpose, taskIndex);
  bdat = GfBdatMsg::getFpQuest(purpose);
  return textId != 0;
}

const char *GfQuestInfo::getTaskLog(u32 purpose, u32 taskIndex) {
  if (purpose == 0) {
    return "";
  }

  u32 textId = QuestListAcc::get()->getTaskTaskLog(purpose, taskIndex);
  u8 *bdat = GfBdatMsg::getFpQuest(purpose);
  const char *text = "";
  if (textId != 0) {
    const char *message = Bdat::getMSText(bdat, textId);
    if (message != nullptr) {
      text = message;
    }
  }

  return text;
}

bool GfQuestInfo::getTaskCount(u32 &count, u32 &limit, u32 &item, u32 &itemCategory, u32 purpose, u32 taskIndex) {
  QuestTaskParam param(GfQuestManager::getOrderQuestId(purpose), taskIndex, purpose, TASK_STATE_NONE);
  return GfQuestTask::getTaskCount(param, limit, count, item, itemCategory);
}

bool GfQuestInfo::isDummuTalkGroupFlag(u32 group, u32 npcIndex) {
  return (GfGameFlag::getLocal(8, group + DUMMY_TALK_GROUP_FLAG_OFFSET) & 1 << npcIndex) != 0;
}

void GfQuestInfo::setDummuTalkGroupFlag(u32 group, u32 npcIndex) {
  u8 flags = GfGameFlag::getLocal(8, group + DUMMY_TALK_GROUP_FLAG_OFFSET);
  GfGameFlag::setLocal(8, group + DUMMY_TALK_GROUP_FLAG_OFFSET, flags | 1 << npcIndex);
}

bool GfQuestInfo::isEnableSetupCount(const AchievInfo &info, u32 level) {
  for (u32 index = 2; index < level; index++) {
    if (isQuestOrder(info.quests[index - 1].quest)) {
      return false;
    }
  }

  return true;
}

void GfQuestInfo::getQuestTaskInfo(u32 &taskCount, u32 &completeCount, QuestID quest) {
  if (isParent(quest)) {
    quest = getProgressQuest(quest);
  }

  taskCount = 0;
  completeCount = 0;
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.taskId == 0) {
      continue;
    }

    taskCount++;
    if (isCompleteTask(param)) {
      completeCount++;
    }
  }
}

static s32 unknown001(const QuestTaskParam &param, u32 condition) { // Inferred role: getConditionWeather; original function name unknown.
  if (condition == 0) {
    return -1;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  GfBdatCond *bdatCond = GfBdatCond::get();
  u32 map = questListAcc->getConditionMapID(param.taskId);
  if (map == 0) {
    return -1;
  }

  for (u32 index = 0; index < CONDITION_LIST_COUNT; index++) {
    if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_ENVIRONMENT) {
      continue;
    }

    u32 environment = bdatCond->getConditionListCondition(condition, index);
    if (environment == 0) {
      continue;
    }

    u32 weathers = bdatCond->getConditionEnvWeather(environment);
    if (weathers == 0) {
      continue;
    }

    for (u32 weather = 0; weather < 32; weather++) {
      if ((weathers & 1 << weather) != 0) {
        if (weather == WEATHER_NONE) {
          return 0;
        }

        return GfBdatMaplist::get()->getMaplistw_type(map, weather);
      }
    }
  }

  return -1;
}

s32 GfQuestInfo::getQuestTaskWeatherInfo(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  s32 weather = unknown001(param, questListAcc->getTaskTaskCondition(param.purpose, param.taskIndex));
  if (weather >= 0) {
    return weather;
  }

  if (param.taskType == TASK_TYPE_CONDITION) {
    return unknown001(param, questListAcc->getConditionConditionID(param.taskId));
  }

  return -1;
}

static s32 getConditionTimeRange(u32 condition) {
  if (condition == 0) {
    return -1;
  }

  QuestListAcc::get();
  GfBdatCond *bdatCond = GfBdatCond::get();
  for (u32 index = 0; index < CONDITION_LIST_COUNT; index++) {
    if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_ENVIRONMENT) {
      continue;
    }

    u32 environment = bdatCond->getConditionListCondition(condition, index);
    if (environment == 0) {
      continue;
    }

    u32 timeRanges = bdatCond->getConditionEnvTimeRange(environment);
    if (timeRanges == 0) {
      continue;
    }

    for (u32 timeRange = 0; timeRange < 32; timeRange++) {
      if ((timeRanges & 1 << timeRange) != 0) {
        return timeRange;
      }
    }
  }

  return -1;
}

s32 GfQuestInfo::getQuestTaskTimeInfo(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  s32 timeRange = getConditionTimeRange(questListAcc->getTaskTaskCondition(param.purpose, param.taskIndex));
  if (timeRange >= 0) {
    return timeRange;
  }

  if (param.taskType == TASK_TYPE_CONDITION) {
    return getConditionTimeRange(questListAcc->getConditionConditionID(param.taskId));
  }

  return -1;
}

} // namespace gf
