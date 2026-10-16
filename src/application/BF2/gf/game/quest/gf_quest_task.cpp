#include "gf/game/quest/gf_quest_task.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_scom.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

enum {
  ACHIEV_FLAG_TASK_PARENT = 4,
  ACHIEV_FLAG_TASK_CHILD = 8,
};

constexpr u32 QUEST_ID_END = 30000;
constexpr u32 QUEST_MAP_CONDITION = 2020;
constexpr u32 QUEST_MAP_CONDITION_MAP = 6;

} // namespace

void GfQuestTask::initializeParams() {}

static inline bool isTaskFlagComplete(const QuestTaskParam &param) {
  u32 purpose = param.purpose;
  if (purpose == 0) {
    return false;
  }

  if (param.quest.variant == 0) {
    u32 taskIndex = param.taskIndex;
    return GfGameFlag::getLocal(1, QuestListAcc::get()->getTaskFlag(purpose, taskIndex)) != 0;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
  if (achievQuest == nullptr) {
    return false;
  }

  u16 flag = GfDataQuest::getListPRTQuestID(param.quest).empty() ? ACHIEV_FLAG_TASK_PARENT : ACHIEV_FLAG_TASK_CHILD;
  return (flag & achievQuest->flags) != 0;
}

bool GfQuestTask::setCompleteFlag(const QuestTaskParam &param, bool isComplete) {
  bool wasComplete = isTaskFlagComplete(param);
  if (param.quest.variant == 0) {
    u32 purpose = param.purpose;
    u32 taskIndex = param.taskIndex;
    GfGameFlag::setLocal(1, QuestListAcc::get()->getTaskFlag(purpose, taskIndex), isComplete);
    if (!wasComplete && isComplete) {
      SCOM_POPUP::createQuest(param.quest);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.quest);
    if (achievQuest == nullptr || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      return false;
    }

    achievQuest->setTaskComplete(GfQuestInfo::isParent(param.quest), isComplete);
    achievQuest->setCountComplete();
  }

  GfQuestManager::eventChangeTaskState(param);
  return isComplete && !wasComplete;
}

bool GfQuestTask::isCompleteFlag(const QuestTaskParam &param) { return isTaskFlagComplete(param); }

void AchievQuest::setTaskComplete(bool isFirst, bool isComplete) {
  u16 flag = isFirst ? ACHIEV_FLAG_TASK_PARENT : ACHIEV_FLAG_TASK_CHILD;
  if (isComplete) {
    flags |= flag;
  } else {
    flags &= ~flag;
  }
}

void AchievQuest::setCountComplete() {
  u32 oldCount = count;
  u32 newCount;
  if (count < targetCount) {
    count = targetCount;
    newCount = targetCount;
  } else {
    if (targetCount != 0) {
      return;
    }

    newCount = count;
  }

  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(quest, oldCount, newCount - oldCount);
  }
}

bool QuestID::empty() const { return id == 0 || id >= QUEST_ID_END; }

bool AchievQuest::isCountComplete() const {
  if (getTargetCount() == 0) {
    return false;
  }

  return getTargetCount() <= getCount();
}

void GfQuestTask::clearTask(QuestID quest) {
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.taskType == TASK_TYPE_BATTLE) {
      GfQuestInfo::resetSuppressCount(param);
    }

    if (isTaskFlagComplete(param)) {
      setCompleteFlag(param, false);
    }
  }
}

bool GfQuestTask::isEnableTaskCondition(const QuestTaskParam &param) {
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.purpose, param.taskIndex);
  if (condition == 0) {
    return true;
  }

  if (param.quest.id == QUEST_MAP_CONDITION) {
    return GfGameCond::isGameCondWithMap(condition, QUEST_MAP_CONDITION_MAP);
  }

  return GfGameCond::isGameCond(condition);
}

void GfQuestTask::completeTask(const QuestTaskParam &param) {
  if (GfQuestInfo::isQuestOrder(param.quest) && param.purpose != 0 && !GfQuestInfo::isCompleteTask(param)) {
    setCompleteFlag(param, true);
  }
}

bool GfQuestTask::getTaskCount(const QuestTaskParam &param, u32 &limit, u32 &count, u32 &item, u32 &itemCategory) {
  limit = 0;
  count = 0;
  item = 0;
  bool isCount = false;
  switch (param.taskType) {
  case TASK_TYPE_COLLECT:
  case TASK_TYPE_USE:
    count = GfQuestInfo::getCollectUseCount(param);
    limit = GfQuestInfo::getCollectUseLimit(param);
    item = GfQuestInfo::getCollectUseItem(param);
    itemCategory = GfQuestInfo::getCollectUseItemCategory(param);
    isCount = true;
    break;
  case TASK_TYPE_BATTLE:
    count = GfQuestInfo::getSuppressCount(param);
    limit = GfQuestInfo::getSuppressLimit(param);
    isCount = true;
    break;
  case TASK_TYPE_CONDITION: {
    u32 flag;
    u32 flagMin;
    u32 flagMax;
    if (GfDataQuest::getHanyouFlg(flag, flagMin, flagMax, param)) {
      count = GfGameFlag::getLocal(8, flag);
      limit = flagMax;
      isCount = true;
    }
    break;
  }
  }

  return isCount;
}

void GfQuestTask::refreshTaskCounters() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (qlist_iterator it = questListAcc->begin(QTYPE_NONE); it != questListAcc->end(QTYPE_NONE); ++it) {
    if (GfDataQuest::getListQuestCategory(it.getQuestID()) == QTYPE_ACHIEVEMENT) {
      return;
    }

    refreshTaskCounter(it.getQuestID());
  }
}

bool GfQuestTask::isEnableTaskConditionWithoutEnv(const QuestTaskParam &param) {
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.purpose, param.taskIndex);
  if (condition == 0) {
    return true;
  }

  return GfGameCond::isGameCondWithoutEnv(condition);
}

bool GfQuestTask::isReduceHpObj(QuestID quest, GF_OBJ_HANDLE *handle) { return getReduceHpObj(quest, handle) != 0; }

u32 GfQuestTask::getReduceHpObjPc(QuestID quest, GF_OBJ_HANDLE *handle) {
  u32 purpose = GfDataQuest::getListPurposeID(quest);
  if (purpose == 0) {
    return 0;
  }

  GfObjAcc objAcc(handle);
  if (GfGameManager::getPartyLeaderDriver() != handle) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_NONE);
    if (param.taskType == TASK_TYPE_BATTLE) {
      u32 reduceHp = questListAcc->getBattleReducePCHP(param.taskId);
      if (reduceHp != 0) {
        return reduceHp;
      }
    }
  }

  return 0;
}

bool GfQuestTask::isReduceHpObjPc(QuestID quest, GF_OBJ_HANDLE *handle) { return getReduceHpObjPc(quest, handle) != 0; }

bool GfQuestTask::isReduceHpQuest(QuestID quest) {
  u32 purpose = GfDataQuest::getListPurposeID(quest);
  if (purpose == 0) {
    return false;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_NONE);
    if (param.taskType != TASK_TYPE_BATTLE) {
      continue;
    }

    if (questListAcc->getBattleEnemyGroupID(param.taskId) != 0 || questListAcc->getBattleEnemyID(param.taskId) != 0 ||
        questListAcc->getBattleReduceEnemyHP(param.taskId) != 0 || questListAcc->getBattleReducePCHP(param.taskId) != 0) {
      return true;
    }
  }

  return false;
}

void GfQuestTask::resetBattleTaskForPlayerDead(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.taskType != TASK_TYPE_BATTLE) {
      continue;
    }

    if (questListAcc->getBattleDeadAll(param.taskId) == 0 && questListAcc->getListCountCancel(quest) == 0) {
      continue;
    }

    if (GfQuestInfo::getSuppressCount(param) != 0) {
      GfQuestInfo::resetSuppressCount(param);
    }
  }
}

bool GfQuestTask::resetBattleTaskForBattleEnd(mm::mtl::FixedVector<u16, 128> &enemies, QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.taskType != TASK_TYPE_BATTLE || questListAcc->getListCountCancel(quest) == 0) {
      continue;
    }

    u32 count = GfQuestInfo::getSuppressCount(param);
    u32 limit = GfQuestInfo::getSuppressLimit(param);
    if (count != 0 && count < limit) {
      GfQuestInfo::resetSuppressCount(param);
      GfQuestInfo::getBattleTaskEnemy(enemies, param);
    }
  }

  return !enemies.empty();
}

u16 GfQuestTask::getTaskMap(const QuestTaskParam &param) {
  u32 map = 0;
  switch (param.taskType) {
  case TASK_TYPE_COLLECT:
    map = QuestListAcc::get()->getCollectMapID(param.taskId);
    break;
  case TASK_TYPE_REACH:
    map = QuestListAcc::get()->getReachMapID(param.taskId);
    break;
  case TASK_TYPE_TALK:
    map = QuestListAcc::get()->getTalkMapID(param.taskId);
    break;
  case TASK_TYPE_GIMMICK:
    map = QuestListAcc::get()->getGimmickMapID(param.taskId);
    break;
  case TASK_TYPE_CONDITION:
    map = QuestListAcc::get()->getConditionMapID(param.taskId);
    break;
  }

  return map;
}

QuestTaskParam::QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state)
    : _00(), quest(quest), taskIndex(taskIndex), taskType(0), taskId(0), state(state), isDisp(false) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  purpose = GfDataQuest::getListPurposeID(quest);
  if (purpose == 0) {
    return;
  }

  taskType = questListAcc->getTaskTaskType(purpose, taskIndex);
  if (taskType != 0) {
    taskId = questListAcc->getTaskTaskID(purpose, taskIndex);
  }

  isDisp = questListAcc->getTaskTaskUI(purpose, taskIndex) != 1;
}

QuestTaskParam::QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state)
    : _00(), quest(quest), purpose(purpose), taskIndex(taskIndex), taskType(0), taskId(0), state(state), isDisp(false) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (!quest.empty() && this->purpose == 0) {
    this->purpose = GfDataQuest::getListPurposeID(quest);
  }

  if (this->purpose == 0) {
    return;
  }

  taskType = questListAcc->getTaskTaskType(this->purpose, taskIndex);
  if (taskType != 0) {
    taskId = questListAcc->getTaskTaskID(this->purpose, taskIndex);
  }

  isDisp = questListAcc->getTaskTaskUI(this->purpose, taskIndex) != 1;
}

bool AchievQuest::setCount(u32 newCount) {
  u32 oldCount = getCount();
  u32 limit = getTargetCount();
  u32 clampedCount = newCount > limit ? limit : newCount;
  u32 add = clampedCount > oldCount ? clampedCount - oldCount : 0;
  count = clampedCount;
  if (getCount() >= getTargetCount()) {
    setCountComplete();
  }

  if (add != 0 && GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(quest, oldCount, add);
  }

  return add != 0;
}

bool AchievQuest::incleseCount(u32 add) {
  if (add == 0) {
    return false;
  }

  u32 oldCount = getCount();
  if (oldCount == COUNT_MASK || oldCount >= getTargetCount()) {
    return false;
  }

  count += add;
  if (getCount() >= getTargetCount()) {
    setCountComplete();
    count = getTargetCount();
  }

  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(quest, oldCount, add);
  }

  return true;
}

bool AchievQuest::decleseCount(u32 sub) {
  if (sub == 0 || getCount() == 0) {
    return false;
  }

  for (u32 index = 0; index < sub; index++) {
    if (getCount() == 0) {
      return true;
    }

    count--;
  }

  return true;
}

} // namespace gf
