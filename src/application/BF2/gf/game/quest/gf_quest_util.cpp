#include "gf/game/quest/gf_quest_util.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_game_flag.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/util/gf_item_util.h"

namespace gf {

namespace {

enum {
  TASK_TYPE_COLLECT = 3,
  TASK_TYPE_TALK = 6,
  TASK_TYPE_FIELD_SKILL_COUNT = 11,
};

enum {
  CONDITION_TYPE_PARTY = 6,
};

enum {
  GIMMICK_TYPE_TBOX = 9,
  GIMMICK_TYPE_SALVAGE_POINT = 31,
  GIMMICK_TYPE_MAP = 33,
  GIMMICK_TYPE_JUMP = 37,
  GIMMICK_TYPE_WARP = 38,
  GIMMICK_TYPE_DOOR = 41,
  GIMMICK_TYPE_ELEVATOR = 42,
};

constexpr u32 ORDER_PARENT_QUEST_MAX = 256;
constexpr u32 CONDITION_LIST_COUNT = 8;
constexpr u32 PARTY_CHARACTER_COUNT = 3;
constexpr u32 DUMMY_GROUP_NPC_COUNT = 8;
constexpr u32 ACHIEVEMENT_LINE_COUNT = 10;

} // namespace

u32 GfQuestUtil::getQuestNeedChar(u32 index, QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getCurrentQuest(QTYPE_NONE);
    quest.id = current.id;
    quest.variant = current.variant;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  u32 hints = GfDataQuest::getListHintsID(parent);
  if (hints == 0) {
    return 0;
  }

  return questListAcc->getHintsMainChar(hints, index);
}

void GfQuestUtil::removeQuestItem(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.taskType == TASK_TYPE_COLLECT && questListAcc->getCollectDeduct(param.taskId) != 0) {
    GfItemUtil::addItemBox(questListAcc->getCollectItemID(param.taskId), -questListAcc->getCollectCount(param.taskId));
  }
}

void GfQuestUtil::sendItemLog(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 item = questListAcc->getCollectItemID(param.taskId);
  u32 count = questListAcc->getCollectCount(param.taskId);
  const char *name = GfDataItem::getName(item);
  u32 itemCount = GfItemUtil::getItemBoxCount(item);
  if (name != nullptr) {
    mm::mtl::FixStr<256> log;
    log.format("%s %d / %d", name, itemCount, count);
  }
}

void GfQuestUtil::sendSuppressLog(const QuestTaskParam &param, u32 enemy) {
  if (enemy == 0) {
    return;
  }

  QuestListAcc::get();
  u32 limit = GfQuestInfo::getSuppressLimit(param);
  const char *name = GfDataEnemy::getName(enemy);
  if (name != nullptr) {
    u32 count = GfQuestInfo::getSuppressCount(param);
    mm::mtl::FixStr<256> log;
    log.format("%s %d / %d", name, count, limit);
  }
}

u32 GfQuestUtil::getMsgQuestTitle(QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
    quest.id = current.id;
    quest.variant = current.variant;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  if (parent.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListQuestTitle(parent);
}

u32 GfQuestUtil::getMsgQuestSummary(QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
    quest.id = current.id;
    quest.variant = current.variant;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  if (parent.empty()) {
    return 0;
  }

  return GfDataQuest::getListSummary(parent);
}

u32 GfQuestUtil::getMsgQuestNeedFieldSkill(u32 index, QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getCurrentQuest(QTYPE_NONE);
    quest.id = current.id;
    quest.variant = current.variant;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  u32 hints = GfDataQuest::getListHintsID(parent);
  if (hints == 0) {
    return 0;
  }

  u32 fieldSkill = questListAcc->getHintsFSkillID(hints, index);
  if (fieldSkill == 0) {
    return 0;
  }

  return questListAcc->getFLD_FieldSkillListName(fieldSkill);
}

u32 GfQuestUtil::getMsgQuestResult(QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getPrevCompleteQuest();
    quest.id = current.id;
    quest.variant = current.variant;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.id = quest.id;
    parent.variant = quest.variant;
  }

  if (GfQuestInfo::isQuestFin(parent)) {
    if (GfQuestInfo::getState(parent) == QSTATE_FIN_A) {
      return GfDataQuest::getListResultA(parent);
    }

    if (GfQuestInfo::getState(parent) == QSTATE_FIN_B) {
      return GfDataQuest::getListResultB(parent);
    }
  }

  return 0;
}

bool GfQuestUtil::isCurrentTaskBattle() {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  if (quest.empty()) {
    return false;
  }

  return GfQuestTask::isTaskBattle(quest);
}

bool GfQuestUtil::isReduceHpObj(GF_OBJ_HANDLE *handle) {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_NONE);
  if (quest.empty()) {
    return false;
  }

  return GfQuestTask::isReduceHpObj(quest, handle);
}

void GfQuestUtil::addOrderParentQuest(QuestID quest) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  QuestData orderQuest(quest);
  removeOrderParentQuest(quest);
  if (dataGame->orderParentQuestCount < ORDER_PARENT_QUEST_MAX) {
    dataGame->orderParentQuests[dataGame->orderParentQuestCount++] = orderQuest;
  }
}

void GfQuestUtil::removeOrderParentQuest(QuestID quest) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  for (u32 index = 0; index < dataGame->orderParentQuestCount; index++) {
    if (dataGame->orderParentQuests[index] == QuestData(quest)) {
      for (; index < dataGame->orderParentQuestCount - 1; index++) {
        dataGame->orderParentQuests[index] = dataGame->orderParentQuests[index + 1];
      }

      dataGame->orderParentQuestCount--;
      return;
    }
  }
}

void GfQuestUtil::clearOrderParentQuest() { GfDataManager::getDataGame()->orderParentQuestCount = 0; }

void GfQuestUtil::addTaskHanyouCount(u32 purpose, u32 taskIndex, u32 add) {
  if (purpose == 0) {
    return;
  }

  QuestID none = {0, 0};
  QuestTaskParam param(none, taskIndex, purpose, TASK_STATE_NONE);
  u32 flag;
  u32 flagMin;
  u32 flagMax;
  if (!GfDataQuest::getHanyouFlg(flag, flagMin, flagMax, param)) {
    return;
  }

  u32 count = GfGameFlag::getLocal(8, flag);
  if (count == flagMax) {
    return;
  }

  u32 newCount = count + add > flagMax ? flagMax : count + add;
  if (count == newCount) {
    return;
  }

  GfGameFlag::setLocal(8, flag, newCount);
  QuestID quest = GfQuestManager::getOrderQuestId(purpose);
  param.quest.id = quest.id;
  param.quest.variant = quest.variant;
  GfQuestManager::eventChangeTaskState(param);
}

void GfQuestUtil::questCompleteItem(QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 use = questListAcc->getListItemLost(quest);
  if (use == 0) {
    return;
  }

  u32 item = questListAcc->getUseItemID(use);
  u32 category = questListAcc->getUseCategory(use);
  s32 number = questListAcc->getUseItemNumber(use);
  if (item != 0) {
    GfItemUtil::addItemBox(item, -number);
    if (GfDataItem::isNoMultiple(item) && GfItemUtil::getItemBoxCount(item) == 0) {
      GfDataItem::setNoMultiple(item, false);
    }

    return;
  }

  u32 start;
  u32 end;
  if (category == 0 || !GfDataItem::getItemBdatCount(start, end, static_cast<ItemType::Type>(category))) {
    return;
  }

  for (s32 index = 0; index < number; index++) {
    u32 maxItem = start;
    u32 maxCount = GfItemUtil::getItemBoxCount(start);
    for (u32 id = start + 1; id < end; id++) {
      u32 itemCount = GfItemUtil::getItemBoxCount(id);
      if (itemCount >= maxCount) {
        maxItem = id;
        maxCount = itemCount;
      }
    }

    if (maxCount == 0) {
      return;
    }

    GfItemUtil::addItemBox(maxItem, -1);
  }
}

bool GfQuestUtil::getNeedCharacterByQuestTask(mm::mtl::FixedVector<u16, 32> &characters, QuestID quest, u32 taskIndex) {
  characters.clear();
  if (GfQuestInfo::isParent(quest)) {
    quest = GfQuestInfo::getProgressQuest(quest);
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 condition = questListAcc->getTaskTaskCondition(questListAcc->getListPurposeID(quest), taskIndex);
  QuestListAcc::get();
  if (condition != 0) {
    GfBdatCond *bdatCond = GfBdatCond::get();
    for (u32 index = 0; index < CONDITION_LIST_COUNT; index++) {
      if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_PARTY) {
        continue;
      }

      u32 party = bdatCond->getConditionListCondition(condition, index);
      if (party == 0 || bdatCond->getConditionPTCategory(party) != 0) {
        continue;
      }

      for (u32 member = 0; member < PARTY_CHARACTER_COUNT; member++) {
        u32 character = bdatCond->getConditionPTPCID(party, member);
        if (character != 0) {
          characters.push_back(character);
        }
      }
    }
  }

  return !characters.empty();
}

u16 GfQuestUtil::getBladeID(QuestID quest) {
  AchievQuest *achievQuest = GfDataQuest::getAchievQuest(quest);
  return achievQuest != nullptr ? achievQuest->blade : 0;
}

u32 GfQuestUtil::getGimmickTaskEndCheck(gmk::GmkType type, u32 gimmick) {
  if (gimmick == 0) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 start = questListAcc->getGimmickStart();
  if (start == 0) {
    return 0;
  }

  u32 end = questListAcc->getGimmickEnd();
  for (u32 id = start; id < end; id++) {
    bool isFound = false;
    switch (type) {
    case GIMMICK_TYPE_DOOR:
      isFound = questListAcc->getGimmickDoorGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_ELEVATOR:
      isFound = questListAcc->getGimmickElevatorGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_JUMP:
      isFound = questListAcc->getGimmickJumpGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_MAP:
      isFound = questListAcc->getGimmickMapGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_WARP:
      isFound = questListAcc->getGimmickWarpGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_SALVAGE_POINT:
      isFound = questListAcc->getGimmickSalvagePointID(id) == gimmick;
      break;
    case GIMMICK_TYPE_TBOX:
      isFound = questListAcc->getGimmickTboxPopID(id) == gimmick;
      break;
    default:
      break;
    }

    if (isFound) {
      return questListAcc->getGimmickEndCheck(id);
    }
  }

  return 0;
}

bool GfQuestUtil::getDummyTalkGroup(u32 &group, u32 &npcIndex, u32 map, u32 npc, QuestID quest) {
  if (GfGameManager::getMapID() != map || !GfQuestInfo::isQuestProgress(quest)) {
    return false;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 taskIndex = 0; taskIndex < QUEST_TASK_COUNT; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_NONE);
    if (param.taskType != TASK_TYPE_TALK || !GfQuestTask::isEnableTaskCondition(param)) {
      continue;
    }

    u32 dummyGroup = questListAcc->getTalkDummyGroup(param.taskId);
    if (dummyGroup == 0) {
      continue;
    }

    for (u32 index = 0; index < DUMMY_GROUP_NPC_COUNT; index++) {
      if (questListAcc->getDummyGroupNpcID(dummyGroup, index) == npc) {
        group = dummyGroup;
        npcIndex = index;
        return true;
      }
    }
  }

  return false;
}

bool GfQuestUtil::getTalkNpcInfo(u32 &taskIndex, u32 npc, QuestID quest) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 index = 0; index < QUEST_TASK_COUNT; index++) {
    QuestTaskParam param(quest, index, TASK_STATE_NONE);
    if (param.taskType == TASK_TYPE_TALK && questListAcc->getTalkNpcID(param.taskId) == npc &&
        questListAcc->getTalkMapID(param.taskId) == GfGameManager::getMapID()) {
      taskIndex = index;
      return true;
    }
  }

  return false;
}

void GfQuestUtil::incFieldSkillTask(u32 blade, u32 fieldSkill) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 line = 0; line < ACHIEVEMENT_LINE_COUNT; line++) {
    AchievInfo *achievInfo = GfDataBlade::getAchievInfo(blade, line);
    if (achievInfo->achievement == 0) {
      continue;
    }

    for (u32 level = 1; level <= ACHIEVEMENT_LEVEL_COUNT; level++) {
      AchievQuest &achievQuest = achievInfo->quests[level - 1];
      if (achievQuest.taskType != TASK_TYPE_FIELD_SKILL_COUNT || !GfQuestInfo::isQuestOrder(achievQuest.quest) || achievQuest.isCountComplete()) {
        continue;
      }

      QuestTaskParam param(GfDataQuest::getListNextQuestA(achievQuest.quest), 0, TASK_STATE_NONE);
      if (questListAcc->getFieldSkillCountFieldSkillID(param.taskId) == fieldSkill) {
        achievQuest.incleseCount(1);
        GfQuestTask::updateQuestTask(achievQuest.quest);
        return;
      }
    }
  }
}

void GfQuestUtil::completeCurrentQuestForAutoPilot() {}

} // namespace gf
