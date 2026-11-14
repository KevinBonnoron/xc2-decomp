#include "gf/game/quest/gf_quest_task.h"

#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/quest/gf_quest_util.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixed_vector.h"

namespace gf {

namespace {

enum {
  ACHIEV_FLAG_TASK_UNKNOWN_2 = 4, // Inferred role: achiev flag task parent; original name unknown.
  ACHIEV_FLAG_TASK_UNKNOWN_3 = 8, // Inferred role: achiev flag task child; original name unknown.
};

constexpr u32 QUEST_MAP_UNKNOWN_2020 = 2020; // Inferred role: quest map condition; original name unknown.
constexpr u32 QUEST_MAP_UNKNOWN_6 = 6;       // Inferred role: quest map condition map; original name unknown.

} // namespace

void GfQuestTask::initializeParams() {}

static inline bool isTaskFlagComplete(const QuestTaskParam &param) {
  u32 purpose = param.unknown08;
  if (purpose == 0) {
    return false;
  }

  if (param.unknown04.unknown02 != 0) {
    AchievQuest *achievQuest = GfDataQuest::getAchievQuest(param.unknown04);
    if (achievQuest == nullptr) {
      return false;
    }

    u16 flag = GfDataQuest::getListPRTQuestID(param.unknown04).empty() ? ACHIEV_FLAG_TASK_UNKNOWN_2 : ACHIEV_FLAG_TASK_UNKNOWN_3;
    return (flag & achievQuest->unknown0c) != 0;
  }

  u32 taskIndex = param.unknown0c;
  return GfGameFlag::getLocal(1, QuestListAcc::get()->getTaskFlag(purpose, taskIndex)) != 0;
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
  u16 flag = isFirst ? ACHIEV_FLAG_TASK_UNKNOWN_2 : ACHIEV_FLAG_TASK_UNKNOWN_3;
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

bool QuestID::empty() const { return unknown00 == 0 || unknown00 >= QUEST_ID_UNKNOWN_30000; }

bool AchievQuest::isCountComplete() const {
  if (getTargetCount() == 0) {
    return false;
  }

  return getTargetCount() <= getCount();
}

void GfQuestTask::clearTask(QuestID quest) {
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_1) {
      GfQuestInfo::resetSuppressCount(param);
    }

    if (isTaskFlagComplete(param)) {
      setCompleteFlag(param, false);
    }
  }
}

void GfQuestTask::incSuppressEnemy(u32 enemy) {
  GfBdatRsc *rsc = GfBdatRsc::get();
  GfBdatChrEnArrange *arrange = GfBdatChrEnArrange::get();
  GfBdatChrEnParam *enParam = GfBdatChrEnParam::get();
  u32 paramId = arrange->getChrEnArrangeParamID(enemy);
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 resource = enParam->getChrEnParamResourceID(paramId);
  rsc->getRscEnTypeFamily(resource);
  u32 genus = rsc->getRscEnTypeGenus(resource);
  GfDataEnemy::getName(enemy);
  u32 questMax = GfQuestManager::getOrderQuestMaxWithAchievement();
  for (u32 i = 0; i < questMax; i++) {
    QuestID quest = GfQuestManager::getOrderQuestWithAchievement(i);
    u32 purpose = GfDataQuest::getListPurposeID(quest);
    if (purpose == 0) {
      continue;
    }

    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_2);
      if (param.unknown10 != TASK_TYPE_UNKNOWN_1 || !isEnableTaskCondition(param)) {
        continue;
      }

      u32 targetEnemy = questListAcc->getBattleEnemyID(param.unknown14);
      u32 targetGroup = questListAcc->getBattleEnemyGroupID(param.unknown14);
      u32 targetSpecies = questListAcc->getBattleEnemySpeciesID(param.unknown14);
      bool isTarget;
      if (targetEnemy != 0) {
        isTarget = targetEnemy == enemy;
      } else if (targetGroup != 0) {
        isTarget = GfQuestUtil::isEnemyGroup(targetGroup, enemy);
      } else {
        isTarget = genus == targetSpecies && targetSpecies != 0;
      }

      if (isTarget && GfQuestInfo::incSuppressCount(param)) {
        QuestID parent = GfDataQuest::getListPRTQuestID(quest);
        bool isVisible = GfDataQuest::getListVisible(parent);
        u32 taskUi = questListAcc->getTaskTaskUI(purpose, taskIndex);
        if (isVisible && taskUi != 1 && taskUi != 3) {
          GfQuestUtil::sendSuppressLog(param, enemy);
        }

        GfQuestManager::eventChangeTaskState(param);
      }
    }
  }
}

bool GfQuestTask::isEnableTaskCondition(const QuestTaskParam &param) {
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.unknown08, param.unknown0c);
  if (condition == 0) {
    return true;
  }

  if (param.unknown04.unknown00 == QUEST_MAP_UNKNOWN_2020) {
    return GfGameCond::isGameCondWithMap(condition, QUEST_MAP_UNKNOWN_6);
  }

  return GfGameCond::isGameCond(condition);
}

void GfQuestTask::completeTask(const QuestTaskParam &param) {
  if (GfQuestInfo::isQuestOrder(param.unknown04) && param.unknown08 != 0 && !GfQuestInfo::isCompleteTask(param)) {
    setCompleteFlag(param, true);
  }
}

void GfQuestTask::completeEventTask(u32 event) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_7 && questListAcc->getEventEventID(param.unknown14) == event) {
      if (!isTaskFlagComplete(param)) {
        setCompleteFlag(param, true);
      }
      return;
    }
  }
}

void GfQuestTask::completeGimmickTask(gmk::GmkType type, u32 gimmick) {
  if (gimmick == 0) {
    return;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 map = GfGameManager::getMapID();
  u32 orderMax = GfQuestManager::getOrderQuestMax();
  for (u32 index = 0; index < orderMax; index++) {
    QuestID quest = GfQuestManager::getOrderQuest(index);
    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
      if (param.unknown10 != TASK_TYPE_UNKNOWN_8 || map != questListAcc->getGimmickMapID(param.unknown14) || !isEnableTaskCondition(param)) {
        continue;
      }

      u32 taskGimmick;
      switch (type) {
      case gmk::GMK_TYPE_TBOX:
        taskGimmick = questListAcc->getGimmickTboxPopID(param.unknown14);
        break;
      case gmk::GMK_TYPE_SALVAGE:
        taskGimmick = questListAcc->getGimmickSalvagePointID(param.unknown14);
        break;
      case gmk::GMK_TYPE_MAP_GIMMICK:
        taskGimmick = questListAcc->getGimmickMapGimmickID(param.unknown14);
        break;
      case gmk::GMK_TYPE_JUMP:
        taskGimmick = questListAcc->getGimmickJumpGimmickID(param.unknown14);
        break;
      case gmk::GMK_TYPE_WARP:
        taskGimmick = questListAcc->getGimmickWarpGimmickID(param.unknown14);
        break;
      case gmk::GMK_TYPE_DOOR:
        taskGimmick = questListAcc->getGimmickDoorGimmickID(param.unknown14);
        break;
      case gmk::GMK_TYPE_ELEVATOR:
        taskGimmick = questListAcc->getGimmickElevatorGimmickID(param.unknown14);
        break;
      default:
        continue;
      }

      if (taskGimmick == gimmick && !isTaskFlagComplete(param)) {
        setCompleteFlag(param, true);
        return;
      }
    }
  }
}

void GfQuestTask::destroyTaskAchieve(QuestID quest) {
  u32 purpose = GfDataQuest::getListPurposeID(quest);
  if (purpose == 0) {
    return;
  }

  mm::mtl::FixedVector<unknown106, 128> &achieves = GfDataQuest::getTaskAchieve();
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_12) {
      unknown106 achieve = {quest.unknown00, static_cast<u16>(purpose), static_cast<u16>(taskIndex)};
      unknown106 *it = mm::mtl::find(achieves.begin(), achieves.end(), achieve);
      if (it != achieves.end()) {
        achieves.erase(it);
      }
    }
  }
}

bool GfQuestTask::getTaskCount(const QuestTaskParam &param, u32 &limit, u32 &count, u32 &item, u32 &itemCategory) {
  limit = 0;
  count = 0;
  item = 0;
  bool isCount = false;
  switch (param.unknown10) {
  case TASK_TYPE_UNKNOWN_3:
  case TASK_TYPE_UNKNOWN_4:
    count = GfQuestInfo::getCollectUseCount(param);
    limit = GfQuestInfo::getCollectUseLimit(param);
    item = GfQuestInfo::getCollectUseItem(param);
    itemCategory = GfQuestInfo::getCollectUseItemCategory(param);
    isCount = true;
    break;
  case TASK_TYPE_UNKNOWN_1:
    count = GfQuestInfo::getSuppressCount(param);
    limit = GfQuestInfo::getSuppressLimit(param);
    isCount = true;
    break;
  case TASK_TYPE_UNKNOWN_10: {
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

bool GfQuestTask::isTaskBattle(QuestID quest) {
  u32 purpose = GfDataQuest::getListPurposeID(quest);
  if (purpose == 0) {
    return false;
  }

  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_1) {
      return true;
    }
  }

  return false;
}

void GfQuestTask::refreshTaskParam(QuestID quest) {
  if (GfQuestInfo::isParent(quest)) {
    quest = GfDataQuest::getListNextQuestA(quest);
  }

  if (GfDataQuest::getListPurposeID(quest) == 0) {
    return;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    switch (param.unknown10) {
    case TASK_TYPE_UNKNOWN_3: {
      u32 limit = questListAcc->getCollectCount(param.unknown14);
      u32 item = questListAcc->getCollectItemID(param.unknown14);
      u32 count;
      if (item != 0) {
        count = GfItemUtil::getItemBoxCount(item);
      } else {
        u32 category = questListAcc->getCollectCategory(param.unknown14);
        if (category == 0) {
          break;
        }

        count = GfItemUtil::getCountByItemCategory(category);
      }

      for (u32 i = 0; i != count && i < limit; i++) {
        GfQuestInfo::incCollectUseCount(param);
      }
      break;
    }
    case TASK_TYPE_UNKNOWN_12:
      GfQuestInfo::setupAchievementCount(param);
      break;
    default:
      break;
    }
  }
}

void GfQuestTask::refreshTaskCounters() {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (qlist_iterator it = questListAcc->begin(QTYPE_UNKNOWN_0); it != questListAcc->end(QTYPE_UNKNOWN_0); ++it) {
    if (GfDataQuest::getListQuestCategory(it.getQuestID()) == QTYPE_UNKNOWN_6) {
      return;
    }

    refreshTaskCounter(it.getQuestID());
  }
}

void GfQuestTask::refreshTaskCounter(QuestID quest) {
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    switch (param.unknown10) {
    case TASK_TYPE_UNKNOWN_3:
      if (!isTaskFlagComplete(param)) {
        GfQuestInfo::resetCollectUseCount(param);
      }
      break;
    case TASK_TYPE_UNKNOWN_4:
      if (!isTaskFlagComplete(param)) {
        GfQuestInfo::resetCollectUseCount(param);
      }
      break;
    case TASK_TYPE_UNKNOWN_1:
      if (!isTaskFlagComplete(param)) {
        GfQuestInfo::resetSuppressCount(param);
      }
      break;
    }
  }
}

// Inferred role: completes the reach task of a quest at the given map and place; original name unknown.
static void unknown001(QuestID quest, u32 map, u32 place) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_5) {
      continue;
    }

    u32 reachPlace = questListAcc->getReachPlaceID(param.unknown14);
    u32 reachCategory = questListAcc->getReachCategory(param.unknown14);
    if (reachPlace == place && reachCategory == map && GfQuestTask::isEnableTaskConditionWithoutEnv(param) && !isTaskFlagComplete(param)) {
      GfQuestTask::setCompleteFlag(param, true);
      return;
    }
  }
}

void GfQuestTask::completeReachTask(u32 map, u32 place) {
  mm::mtl::FixedQueue<QuestData, 8000> *orderQuest = GfQuestManager::getOrderQuest();
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = orderQuest->begin(), last = orderQuest->end(); it != last; ++it) {
    unknown001((*it).unknown00, map, place);
  }

  mm::mtl::FixedQueue<QuestData, 15000> *orderAchievementQuest = GfQuestManager::getOrderAchievementQuest();
  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = orderAchievementQuest->begin(), last = orderAchievementQuest->end(); it != last; ++it) {
    unknown001((*it).unknown00, map, place);
  }
}

bool GfQuestTask::isEnableTaskConditionWithoutEnv(const QuestTaskParam &param) {
  u32 condition = QuestListAcc::get()->getTaskTaskCondition(param.unknown08, param.unknown0c);
  if (condition == 0) {
    return true;
  }

  return GfGameCond::isGameCondWithoutEnv(condition);
}

// Inferred role: counts an item use for the use tasks of a quest; original name unknown.
static void unknown002(QuestID quest, u32 item, u32 itemCategory, mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> &blades) {
  if (item == 0) {
    return;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_4) {
      continue;
    }

    if (!blades.empty()) {
      u32 blade = questListAcc->getUsebladeID(param.unknown14);
      if (blade != 0 && mm::mtl::find(blades.begin(), blades.end(), static_cast<u16>(blade)) == blades.end()) {
        continue;
      }
    }

    if (!GfQuestTask::isEnableTaskCondition(param)) {
      continue;
    }

    u32 useItem = questListAcc->getUseItemID(param.unknown14);
    u32 useCategory = questListAcc->getUseCategory(param.unknown14);
    if (useItem == item || (itemCategory != 0 && useCategory == itemCategory)) {
      if (GfQuestInfo::getCollectUseCount(param) < GfQuestInfo::getCollectUseLimit(param)) {
        GfQuestInfo::incCollectUseCount(param);
        if (GfQuestInfo::getCollectUseCount(param) >= GfQuestInfo::getCollectUseLimit(param)) {
          GfQuestTask::setCompleteFlag(param, true);
        }
        return;
      }
    }
  }
}

void GfQuestTask::completeItemUseTask(u32 item, u32 driver) {
  u32 category = GfDataItem::getCategory(item);
  mm::mtl::FixedVector<u16, BLADE_UNKNOWN_422> blades;
  mm::mtl::FixedQueue<QuestData, 8000> *orderQuest = GfQuestManager::getOrderQuest();
  for (mm::mtl::FixedQueue<QuestData, 8000>::iterator it = orderQuest->begin(), last = orderQuest->end(); it != last; ++it) {
    unknown002((*it).unknown00, item, category, blades);
  }

  GfDataDriver::getListBlade(blades, driver);
  mm::mtl::FixedQueue<QuestData, 15000> *orderAchievementQuest = GfQuestManager::getOrderAchievementQuest();
  for (mm::mtl::FixedQueue<QuestData, 15000>::iterator it = orderAchievementQuest->begin(), last = orderAchievementQuest->end(); it != last; ++it) {
    unknown002((*it).unknown00, item, category, blades);
  }
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_1) {
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_1) {
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_1) {
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_1 || questListAcc->getListCountCancel(quest) == 0) {
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
  case TASK_TYPE_UNKNOWN_3:
    map = QuestListAcc::get()->getCollectMapID(param.unknown14);
    break;
  case TASK_TYPE_UNKNOWN_5:
    map = QuestListAcc::get()->getReachMapID(param.unknown14);
    break;
  case TASK_TYPE_UNKNOWN_6:
    map = QuestListAcc::get()->getTalkMapID(param.unknown14);
    break;
  case TASK_TYPE_UNKNOWN_8:
    map = QuestListAcc::get()->getGimmickMapID(param.unknown14);
    break;
  case TASK_TYPE_UNKNOWN_10:
    map = QuestListAcc::get()->getConditionMapID(param.unknown14);
    break;
  }

  return map;
}

QuestTaskParam::QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state)
    : QuestParam(QUEST_PARAM_UNKNOWN_0), unknown04(quest), unknown0c(taskIndex), unknown10(0), unknown14(0), unknown18(state), unknown1c(false) {
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
    : QuestParam(QUEST_PARAM_UNKNOWN_0), unknown04(quest), unknown08(purpose), unknown0c(taskIndex), unknown10(0), unknown14(0), unknown18(state), unknown1c(false) {
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
  if (oldCount == MASK_UNKNOWN_1073741823 || oldCount >= getTargetCount()) {
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
