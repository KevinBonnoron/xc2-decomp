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
#include "gf/game/gf_game_cond.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

constexpr u32 COLLECT_USE_FLAG_UNKNOWN_1519 = 0x5ef;      // Inferred role: collect use flag offset; original name unknown.
constexpr u32 DUMMY_TALK_GROUP_FLAG_UNKNOWN_3723 = 0xe8b; // Inferred role: dummy talk group flag offset; original name unknown.
constexpr u32 COUNT_FLAG_UNKNOWN_255 = 0xff;              // Inferred role: count flag max; original name unknown.
constexpr u32 GROUP_UNKNOWN_8 = 8;                        // Inferred role: enemy group count; original name unknown.
constexpr u32 WEATHER_UNKNOWN_4 = 4;                      // Inferred role: weather none; original name unknown.

} // namespace

bool GfQuestInfo::isQuestOrder(QuestID quest) { return getState(quest) == QSTATE_UNKNOWN_1; }

bool GfQuestInfo::isQuestProgress(QuestID quest) { return getState(quest) == QSTATE_UNKNOWN_1; }

bool GfQuestInfo::isQuestFin(QuestID quest) { return getState(quest) > QSTATE_UNKNOWN_1; }

bool GfQuestInfo::isQuestNotOrder(QuestID quest) { return getState(quest) == QSTATE_UNKNOWN_0; }

QuestID GfQuestInfo::getParentQuest(QuestID quest) {
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
  }

  return parent;
}

u32 GfQuestInfo::getPlayEvent(QuestID quest, QSTATE state) {
  if (state == QSTATE_UNKNOWN_2) {
    return GfDataQuest::getListCallEventA(quest);
  }

  return GfDataQuest::getListCallEventB(quest);
}

QuestID GfQuestInfo::getProgressQuest(QuestID quest) {
  if (quest.empty()) {
    return quest;
  }

  if (!isParent(quest)) {
    quest = getParentQuest(quest);
  }

  if (getState(quest) != QSTATE_UNKNOWN_1) {
    return QuestID();
  }

  QuestID child = GfDataQuest::getListNextQuestA(quest);
  while (GfDataQuest::getListPRTQuestID(child) == quest) {
    if (getState(child) == QSTATE_UNKNOWN_1) {
      return child;
    }

    QuestID current = child;
    child = GfDataQuest::getListNextQuestA(current);
    if (child.empty() || isQuestNotOrder(child)) {
      child = GfDataQuest::getListNextQuestB(current);
    }
  }

  return QuestID();
}

bool GfQuestInfo::isParent(QuestID quest) { return GfDataQuest::getListPRTQuestID(quest).empty(); }

QuestID GfQuestInfo::getChildQuestID(QuestID quest) {
  QSTATE state = getState(quest);
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  bool isChildQuest = !parent.empty();
  bool isNextB = state == QSTATE_UNKNOWN_3 && isChildQuest;
  if (isNextB) {
    QuestID child = GfDataQuest::getListNextQuestB(quest);
    if (!child.empty()) {
      return child;
    }
  }

  return GfDataQuest::getListNextQuestA(quest);
}

bool GfQuestInfo::incSuppressCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    u32 flag = QuestListAcc::get()->getBattleCountFlag(param.unknown14);
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count < COUNT_FLAG_UNKNOWN_255) {
      GfGameFlag::setLocal(8, flag, count + 1);
    }

    return true;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
  if (achievQuest == nullptr || !GfDataBlade::isBattleMember(achievQuest->unknown16) || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
    return false;
  }

  achievQuest->incleseCount(1);
  return true;
}

void GfQuestInfo::resetSuppressCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    if (GfDataQuest::getListQuestCategory(param.unknown04) != QTYPE_UNKNOWN_6) {
      GfGameFlag::setLocal(8, QuestListAcc::get()->getBattleCountFlag(param.unknown14), 0);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest != nullptr) {
      achievQuest->unknown04 = 0;
    }
  }
}

u32 GfQuestInfo::getSuppressCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    return achievQuest != nullptr ? achievQuest->getCount() : 0;
  }

  return GfGameFlag::getLocal(8, QuestListAcc::get()->getBattleCountFlag(param.unknown14));
}

u32 GfQuestInfo::getSuppressLimit(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    return achievQuest != nullptr ? achievQuest->getTargetCount() : 0;
  }

  return QuestListAcc::get()->getBattleCount(param.unknown14);
}

bool GfQuestInfo::incCollectUseCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    u32 flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_UNKNOWN_1519;
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count >= COUNT_FLAG_UNKNOWN_255) {
      return false;
    }

    GfGameFlag::setLocal(8, flag, count + 1);
    return true;
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest != nullptr && GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      return achievQuest->incleseCount(1);
    }
  }

  return false;
}

bool GfQuestInfo::decCollectUseCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    u32 flag = QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_UNKNOWN_1519;
    u32 count = GfGameFlag::getLocal(8, flag);
    if (count != 0) {
      GfGameFlag::setLocal(8, flag, count - 1);
      return true;
    }

    return false;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
  if (achievQuest != nullptr) {
    return achievQuest->decleseCount(1);
  }

  return false;
}

u32 GfQuestInfo::getCollectUseCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    return achievQuest != nullptr ? achievQuest->getCount() : 0;
  }

  return GfGameFlag::getLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_UNKNOWN_1519);
}

u32 GfQuestInfo::getCollectUseLimit(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    return achievQuest != nullptr ? achievQuest->getTargetCount() : 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.unknown10 == TASK_TYPE_UNKNOWN_3) {
    return questListAcc->getCollectCount(param.unknown14);
  }

  if (param.unknown10 == TASK_TYPE_UNKNOWN_4) {
    return questListAcc->getUseItemNumber(param.unknown14);
  }

  return 0;
}

u32 GfQuestInfo::getCollectUseItem(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.unknown10 == TASK_TYPE_UNKNOWN_3) {
    return questListAcc->getCollectItemID(param.unknown14);
  }

  if (param.unknown10 == TASK_TYPE_UNKNOWN_4) {
    return questListAcc->getUseItemID(param.unknown14);
  }

  return 0;
}

u32 GfQuestInfo::getCollectUseItemCategory(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.unknown10 == TASK_TYPE_UNKNOWN_3) {
    return questListAcc->getCollectCategory(param.unknown14);
  }

  if (param.unknown10 == TASK_TYPE_UNKNOWN_4) {
    return questListAcc->getUseCategory(param.unknown14);
  }

  return 0;
}

void GfQuestInfo::resetCollectUseCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    if (GfDataQuest::getListQuestCategory(param.unknown04) != QTYPE_UNKNOWN_6) {
      GfGameFlag::setLocal(8, QuestListAcc::get()->getCollectUseFlagIndex(param) + COLLECT_USE_FLAG_UNKNOWN_1519, 0);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest != nullptr) {
      achievQuest->unknown04 = 0;
    }
  }
}

void GfQuestInfo::setupAchievementCount(const QuestTaskParam &param) {
  if (param.unknown04.unknown02 == 0) {
    return;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
  if (achievQuest == nullptr || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
    return;
  }

  s32 totalCount = GfAchievStats::getAchievementTotalCount(*achievQuest);
  if (totalCount < 0) {
    GfDataAchievement::setupTotalCount(*achievQuest);
  } else {
    achievQuest->setCount(totalCount);
  }

  if ((achievQuest->unknown0c & 2) == 0 && achievQuest->isCountComplete()) {
    achievQuest->unknown0c |= 2;
  }
}

u32 GfQuestInfo::getTaskHide(const QuestTaskParam &param) { return QuestListAcc::get()->getTaskTaskUI(param.unknown08, param.unknown0c); }

bool GfQuestInfo::isCompletePrevQuest(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (qlist_iterator it = questListAcc->begin(QTYPE_UNKNOWN_0); it != questListAcc->end(QTYPE_UNKNOWN_0); ++it) {
    QuestID prev(it.getQuestID().unknown00, quest.unknown02);
    if (GfDataQuest::getListFlagPRT(prev) == 0) {
      if (GfDataQuest::getListNextQuestA(prev) == quest && getState(prev) < QSTATE_UNKNOWN_2) {
        return false;
      }
      if (GfDataQuest::getListNextQuestB(prev) == quest && getState(prev) < QSTATE_UNKNOWN_2) {
        return false;
      }
    }
  }

  return true;
}

bool GfQuestInfo::canQuestOrder(QuestID quest) { return getState(quest) == QSTATE_UNKNOWN_0 && !isQuestProgress(quest); }

bool GfQuestInfo::isScenarioQuest(QuestID quest) { return GfDataQuest::getQuestCategory(quest) == QTYPE_UNKNOWN_1; }

bool GfQuestInfo::isCompleteTask(const QuestTaskParam &param) {
  if (param.unknown08 == 0) {
    return false;
  }

  return GfQuestTask::isCompleteFlag(param);
}

bool GfQuestInfo::isDispUI(QuestID quest) { return QuestListAcc::get()->getListVisible(quest) != 0; }

bool GfQuestInfo::getQuestNeedTaskCond(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (quest.empty()) {
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
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
  u32 enemy = questListAcc->getBattleEnemyID(param.unknown14);
  if (enemy != 0) {
    if (enemies.size() != enemies.capacity()) {
      enemies.push_back(enemy);
    }
  } else {
    u32 group = questListAcc->getBattleEnemyGroupID(param.unknown14);
    if (group != 0) {
      GfBdatChrEnParam *chrEnParam = GfBdatChrEnParam::get();
      for (u32 index = 0; index < GROUP_UNKNOWN_8; index++) {
        u32 groupEnemy = chrEnParam->getEnemyGroupEnemyID(group, index);
        if (groupEnemy != 0 && enemies.size() != enemies.capacity()) {
          enemies.push_back(groupEnemy);
        }
      }
    } else {
      questListAcc->getBattleEnemySpeciesID(param.unknown14);
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
  QuestTaskParam param(GfQuestManager::getOrderQuestId(purpose), taskIndex, purpose, TASK_STATE_UNKNOWN_0);
  return GfQuestTask::getTaskCount(param, limit, count, item, itemCategory);
}

bool GfQuestInfo::isDummuTalkGroupFlag(u32 group, u32 npcIndex) { return (GfGameFlag::getLocal(8, group + DUMMY_TALK_GROUP_FLAG_UNKNOWN_3723) & 1 << npcIndex) != 0; }

void GfQuestInfo::setDummuTalkGroupFlag(u32 group, u32 npcIndex) {
  u8 flags = GfGameFlag::getLocal(8, group + DUMMY_TALK_GROUP_FLAG_UNKNOWN_3723);
  GfGameFlag::setLocal(8, group + DUMMY_TALK_GROUP_FLAG_UNKNOWN_3723, flags | 1 << npcIndex);
}

bool GfQuestInfo::isEnableSetupCount(const AchievInfo &info, u32 level) {
  for (u32 index = 2; index < level; index++) {
    if (isQuestOrder(info.unknown04[index - 1].unknown00)) {
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown14 == 0) {
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
  u32 map = questListAcc->getConditionMapID(param.unknown14);
  if (map == 0) {
    return -1;
  }

  for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
    if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_UNKNOWN_3) {
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
        if (weather == WEATHER_UNKNOWN_4) {
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
  s32 weather = unknown001(param, questListAcc->getTaskTaskCondition(param.unknown08, param.unknown0c));
  if (weather >= 0) {
    return weather;
  }

  if (param.unknown10 == TASK_TYPE_UNKNOWN_10) {
    return unknown001(param, questListAcc->getConditionConditionID(param.unknown14));
  }

  return -1;
}

static s32 getConditionTimeRange(u32 condition) {
  if (condition == 0) {
    return -1;
  }

  QuestListAcc::get();
  GfBdatCond *bdatCond = GfBdatCond::get();
  for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
    if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_UNKNOWN_3) {
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
  s32 timeRange = getConditionTimeRange(questListAcc->getTaskTaskCondition(param.unknown08, param.unknown0c));
  if (timeRange >= 0) {
    return timeRange;
  }

  if (param.unknown10 == TASK_TYPE_UNKNOWN_10) {
    return getConditionTimeRange(questListAcc->getConditionConditionID(param.unknown14));
  }

  return -1;
}

} // namespace gf
