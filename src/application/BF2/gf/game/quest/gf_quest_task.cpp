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

constexpr u32 QUEST_MAP_CONDITION = 2020;
constexpr u32 QUEST_MAP_CONDITION_MAP = 6;

} // namespace

void GfQuestTask::initializeParams() {}

static inline bool isTaskFlagComplete(const QuestTaskParam &param) {
  u32 purpose = param.unknown08;
  if (purpose == 0) {
    return false;
  }

  if (param.unknown04.unknown02 == 0) {
    u32 taskIndex = param.unknown0c;
    return GfGameFlag::getLocal(1, QuestListAcc::get()->getTaskFlag(purpose, taskIndex)) != 0;
  }

  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
  if (achievQuest == nullptr) {
    return false;
  }

  u16 flag = GfDataQuest::getListPRTQuestID(param.unknown04).empty() ? ACHIEV_FLAG_TASK_PARENT : ACHIEV_FLAG_TASK_CHILD;
  return (flag & achievQuest->unknown0c) != 0;
}

bool GfQuestTask::setCompleteFlag(const QuestTaskParam &param, bool isComplete) {
  bool wasComplete = isTaskFlagComplete(param);
  if (param.unknown04.unknown02 == 0) {
    u32 purpose = param.unknown08;
    u32 taskIndex = param.unknown0c;
    GfGameFlag::setLocal(1, QuestListAcc::get()->getTaskFlag(purpose, taskIndex), isComplete);
    if (!wasComplete && isComplete) {
      SCOM_POPUP::createQuest(param.unknown04);
    }
  } else {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest == nullptr || !GfKizunaringBlade::isCompleteLevel(*achievQuest)) {
      return false;
    }

    achievQuest->setTaskComplete(GfQuestInfo::isParent(param.unknown04), isComplete);
    achievQuest->setCountComplete();
  }

  GfQuestManager::eventChangeTaskState(param);
  return isComplete && !wasComplete;
}

bool GfQuestTask::isCompleteFlag(const QuestTaskParam &param) { return isTaskFlagComplete(param); }

void AchievQuest::setTaskComplete(bool isFirst, bool isComplete) {
  u16 flag = isFirst ? ACHIEV_FLAG_TASK_PARENT : ACHIEV_FLAG_TASK_CHILD;
  if (isComplete) {
    unknown0c |= flag;
  } else {
    unknown0c &= ~flag;
  }
}

void AchievQuest::setCountComplete() {
  u32 oldCount = unknown04;
  u32 newCount;
  if (unknown04 < unknown08) {
    unknown04 = unknown08;
    newCount = unknown08;
  } else {
    if (unknown08 != 0) {
      return;
    }

    newCount = unknown04;
  }

  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(unknown00, oldCount, newCount - oldCount);
  }
}

bool QuestID::empty() const { return unknown00 == 0 || unknown00 >= QUEST_ID_END; }

bool AchievQuest::isCountComplete() const {
  if (getTargetCount() == 0) {
    return false;
  }

  return getTargetCount() <= getCount();
}

void GfQuestTask::clearTask(QuestID quest) {
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.unknown10 == TASK_TYPE_BATTLE) {
      GfQuestInfo::resetSuppressCount(param);
    }

    if (isTaskFlagComplete(param)) {
      setCompleteFlag(param, false);
    }
  }
}

bool GfQuestTask::isEnableTaskCondition(const QuestTaskParam &param) {
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.unknown08, param.unknown0c);
  if (condition == 0) {
    return true;
  }

  if (param.unknown04.unknown00 == QUEST_MAP_CONDITION) {
    return GfGameCond::isGameCondWithMap(condition, QUEST_MAP_CONDITION_MAP);
  }

  return GfGameCond::isGameCond(condition);
}

void GfQuestTask::completeTask(const QuestTaskParam &param) {
  if (GfQuestInfo::isQuestOrder(param.unknown04) && param.unknown08 != 0 && !GfQuestInfo::isCompleteTask(param)) {
    setCompleteFlag(param, true);
  }
}

bool GfQuestTask::getTaskCount(const QuestTaskParam &param, u32 &limit, u32 &count, u32 &item, u32 &itemCategory) {
  limit = 0;
  count = 0;
  item = 0;
  bool isCount = false;
  switch (param.unknown10) {
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
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.unknown08, param.unknown0c);
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
    if (param.unknown10 == TASK_TYPE_BATTLE) {
      u32 reduceHp = questListAcc->getBattleReducePCHP(param.unknown14);
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
    if (param.unknown10 != TASK_TYPE_BATTLE) {
      continue;
    }

    if (questListAcc->getBattleEnemyGroupID(param.unknown14) != 0 || questListAcc->getBattleEnemyID(param.unknown14) != 0 || questListAcc->getBattleReduceEnemyHP(param.unknown14) != 0 ||
        questListAcc->getBattleReducePCHP(param.unknown14) != 0) {
      return true;
    }
  }

  return false;
}

void GfQuestTask::resetBattleTaskForPlayerDead(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.unknown10 != TASK_TYPE_BATTLE) {
      continue;
    }

    if (questListAcc->getBattleDeadAll(param.unknown14) == 0 && questListAcc->getListCountCancel(quest) == 0) {
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
    if (param.unknown10 != TASK_TYPE_BATTLE || questListAcc->getListCountCancel(quest) == 0) {
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
  switch (param.unknown10) {
  case TASK_TYPE_COLLECT:
    map = QuestListAcc::get()->getCollectMapID(param.unknown14);
    break;
  case TASK_TYPE_REACH:
    map = QuestListAcc::get()->getReachMapID(param.unknown14);
    break;
  case TASK_TYPE_TALK:
    map = QuestListAcc::get()->getTalkMapID(param.unknown14);
    break;
  case TASK_TYPE_GIMMICK:
    map = QuestListAcc::get()->getGimmickMapID(param.unknown14);
    break;
  case TASK_TYPE_CONDITION:
    map = QuestListAcc::get()->getConditionMapID(param.unknown14);
    break;
  }

  return map;
}

QuestTaskParam::QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state)
    : QuestParam(QUEST_PARAM_TASK), unknown04(quest), unknown0c(taskIndex), unknown10(0), unknown14(0), unknown18(state), unknown1c(false) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  unknown08 = GfDataQuest::getListPurposeID(quest);
  if (unknown08 == 0) {
    return;
  }

  unknown10 = questListAcc->getTaskTaskType(unknown08, taskIndex);
  if (unknown10 != 0) {
    unknown14 = questListAcc->getTaskTaskID(unknown08, taskIndex);
  }

  unknown1c = questListAcc->getTaskTaskUI(unknown08, taskIndex) != 1;
}

QuestTaskParam::QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state)
    : QuestParam(QUEST_PARAM_TASK), unknown04(quest), unknown08(purpose), unknown0c(taskIndex), unknown10(0), unknown14(0), unknown18(state), unknown1c(false) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (!quest.empty() && this->unknown08 == 0) {
    this->unknown08 = GfDataQuest::getListPurposeID(quest);
  }

  if (this->unknown08 == 0) {
    return;
  }

  unknown10 = questListAcc->getTaskTaskType(this->unknown08, taskIndex);
  if (unknown10 != 0) {
    unknown14 = questListAcc->getTaskTaskID(this->unknown08, taskIndex);
  }

  unknown1c = questListAcc->getTaskTaskUI(this->unknown08, taskIndex) != 1;
}

bool AchievQuest::setCount(u32 newCount) {
  u32 oldCount = getCount();
  u32 limit = getTargetCount();
  u32 clampedCount = newCount > limit ? limit : newCount;
  u32 add = clampedCount > oldCount ? clampedCount - oldCount : 0;
  unknown04 = clampedCount;
  if (getCount() >= getTargetCount()) {
    setCountComplete();
  }

  if (add != 0 && GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(unknown00, oldCount, add);
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

  unknown04 += add;
  if (getCount() >= getTargetCount()) {
    setCountComplete();
    unknown04 = getTargetCount();
  }

  if (GfAchievManager::get() != nullptr) {
    GfAchievManager::get()->incleaseAchievCount(unknown00, oldCount, add);
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

    unknown04--;
  }

  return true;
}

} // namespace gf
