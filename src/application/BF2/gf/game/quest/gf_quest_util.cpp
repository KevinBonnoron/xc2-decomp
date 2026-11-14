#include "gf/game/quest/gf_quest_util.h"

#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_cond.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_data_achievement.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_map.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_quest.h"
#include "gf/data/gf_data_util.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_obj.h"
#include "gf/game/kizunaring/gf_kizunaring_manager.h"
#include "gf/game/quest/gf_achiev_quest.h"
#include "gf/game/quest/gf_quest_data.h"
#include "gf/game/quest/gf_quest_info.h"
#include "gf/game/quest/gf_quest_manager.h"
#include "gf/game/quest/gf_quest_task.h"
#include "gf/game/quest/gf_quest_task_param.h"
#include "gf/game/sequential_play/gf_play_command.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_item_util.h"
#include "gmk/gmk_base.h"
#include "mm_mtl/algorithm.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_list.h"
#include "mm_mtl/fixed_queue.h" // IWYU pragma: keep
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

namespace {

enum {
  GIMMICK_TYPE_UNKNOWN_9 = 9,   // Inferred role: gimmick type tbox; original name unknown.
  GIMMICK_TYPE_UNKNOWN_31 = 31, // Inferred role: gimmick type salvage point; original name unknown.
  GIMMICK_TYPE_UNKNOWN_33 = 33, // Inferred role: gimmick type map; original name unknown.
  GIMMICK_TYPE_UNKNOWN_37 = 37, // Inferred role: gimmick type jump; original name unknown.
  GIMMICK_TYPE_UNKNOWN_38 = 38, // Inferred role: gimmick type warp; original name unknown.
  GIMMICK_TYPE_UNKNOWN_41 = 41, // Inferred role: gimmick type door; original name unknown.
  GIMMICK_TYPE_UNKNOWN_42 = 42, // Inferred role: gimmick type elevator; original name unknown.
};

constexpr u32 QUEST_UNKNOWN_256 = 256; // Inferred role: order parent quest max; original name unknown.
constexpr u32 CHARACTER_UNKNOWN_3 = 3; // Inferred role: party character count; original name unknown.
constexpr u32 NPC_UNKNOWN_8 = 8;       // Inferred role: dummy group npc count; original name unknown.

} // namespace

bool GfQuestUtil::getScenarioTopic(GfQuestScinario &scenario) {
  QuestID current = GfQuestManager::get()->getCurrentQuestScenario();
  if (current.empty()) {
    return false;
  }

  QuestID quest = GfQuestInfo::getProgressQuest(current);
  if (quest.empty()) {
    return false;
  }

  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == 0 || param.unknown10 == TASK_TYPE_UNKNOWN_9) {
      continue;
    }

    GfQuestTaskLogResult result;
    if (!getMsgQuestTaskLog(result, param)) {
      return false;
    }

    scenario.unknown00 = GfDataQuest::getTaskLog(quest, result.unknown00);
    scenario.unknown08 = GfDataQuest::getListTalker(quest);
    return true;
  }

  return false;
}

bool GfQuestUtil::getMsgQuestTaskLog(GfQuestTaskLogResult &result, const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent;
  QuestID quest = param.unknown04;
  if (!quest.empty()) {
    parent = GfDataQuest::getListPRTQuestID(quest);
    if (parent.empty()) {
      parent = quest;
      quest = GfQuestInfo::getProgressQuest(quest);
    }
  }

  if (quest.empty()) {
    if (parent.empty()) {
      return false;
    }

    u32 first = parent.unknown00 + 1;
    quest = QuestID(first, parent.unknown02 == 0 ? first >> 16 : parent.unknown02);
  }

  QuestTaskParam taskParam(quest, param.unknown0c, TASK_STATE_UNKNOWN_0);
  if (taskParam.unknown08 == 0 || GfQuestInfo::getTaskHide(taskParam) == 1) {
    return false;
  }

  result.unknown10 = taskParam.unknown10;
  result.unknown24 = GfQuestInfo::isCompleteTask(taskParam) | (GfPlayComTalk::getQuestTargetNpc(taskParam.unknown0c) != 0);
  result.unknown26 = taskParam.unknown04;
  u32 limit;
  u32 count;
  u32 item;
  u32 itemCategory;
  if (GfQuestTask::getTaskCount(taskParam, limit, count, item, itemCategory)) {
    result.unknown14 = limit;
    result.unknown18 = result.unknown24 ? limit : count;
    result.unknown1c = item;
    result.unknown20 = itemCategory;
  }

  result.unknown00 = questListAcc->getTaskTaskLog(taskParam.unknown08, taskParam.unknown0c);
  result.unknown08 = GfBdatMsg::getFpQuest(quest);
  return result.unknown00 != 0;
}

bool GfQuestUtil::isExtstActivateEnemy(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  const mm::mtl::FixedList<GF_OBJ_HANDLE *, GAME_UNKNOWN_1024> *enemyList = GfGameObj::getList(OBJECT_TYPE_ENEMY);
  GfBdatChrEnParam *chrEnParam = GfBdatChrEnParam::get();
  for (GF_OBJ_HANDLE *const &handle : *enemyList) {
    GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
    if (setup != nullptr && setup->isEvent()) {
      continue;
    }

    DataParamAcc paramAcc(handle);
    mm::mtl::FixedVector<u32, 8> enemies;
    u32 enemy = questListAcc->getBattleEnemyID(param.unknown14);
    if (enemy != 0) {
      enemies.push_back(enemy);
    } else {
      u32 group = questListAcc->getBattleEnemyGroupID(param.unknown14);
      if (group != 0) {
        for (u32 index = 0; index < 8; index++) {
          u32 groupEnemy = chrEnParam->getEnemyGroupEnemyID(group, index);
          if (groupEnemy != 0) {
            enemies.push_back(groupEnemy);
          }
        }
      }
    }

    u32 bdatId = paramAcc.isValid() ? paramAcc.getBdatId() : 0;
    if (mm::mtl::find(enemies.begin(), enemies.end(), bdatId) == enemies.end()) {
      continue;
    }

    if (paramAcc.getHp() != 0) {
      return true;
    }
  }

  return false;
}

bool GfQuestUtil::isEnemyGroup(u32 group, u32 enemy) {
  if (group == 0) {
    return false;
  }

  GfBdatChrEnParam *chrEnParam = GfBdatChrEnParam::get();
  for (u32 index = 0; index < 8; index++) {
    if (chrEnParam->getEnemyGroupEnemyID(group, index) == enemy) {
      return true;
    }
  }

  return false;
}

QuestID GfQuestUtil::getCurrentItemWithEvent(u32 item) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 orderMax = GfQuestManager::getOrderQuestMax();
  for (u32 index = 0; index < orderMax; index++) {
    QuestID quest = GfQuestManager::getOrderQuest(index);
    if (quest.empty() || GfDataQuest::getListCallEventA(quest) == 0) {
      continue;
    }

    u32 purpose = GfDataQuest::getListPurposeID(quest);
    if (purpose == 0) {
      continue;
    }

    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
      if (param.unknown10 == TASK_TYPE_UNKNOWN_3 && !GfQuestInfo::isCompleteTask(param) && questListAcc->getCollectItemID(param.unknown14) == item) {
        return quest;
      }
    }
  }

  return QuestID();
}

QuestID GfQuestUtil::getCurrentTBoxWithEvent(GF_OBJ_HANDLE *handle) {
  gmk::AGmkBase *gmk = gmk::getBindedGmkInst(handle);
  if (gmk == nullptr || gmk->getGmkType() != gmk::GMK_TYPE_TBOX) {
    return QuestID();
  }

  gmk->getBindedBdatFp();
  u32 gimmick = gmk->unknown20.unknown18;
  if (gimmick == 0) {
    return QuestID();
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 orderMax = GfQuestManager::getOrderQuestMax();
  for (u32 index = 0; index < orderMax; index++) {
    QuestID quest = GfQuestManager::getOrderQuest(index);
    if (quest.empty() || GfDataQuest::getListCallEventA(quest) == 0) {
      continue;
    }

    u32 purpose = GfDataQuest::getListPurposeID(quest);
    if (purpose == 0) {
      continue;
    }

    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(quest, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
      if (param.unknown10 == TASK_TYPE_UNKNOWN_8 && !GfQuestInfo::isCompleteTask(param) && questListAcc->getGimmickTboxPopID(param.unknown14) == gimmick) {
        return quest;
      }
    }
  }

  return QuestID();
}

u32 GfQuestUtil::getQuestNeedChar(u32 index, QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0);
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
  }

  u32 hints = GfDataQuest::getListHintsID(parent);
  if (hints == 0) {
    return 0;
  }

  return questListAcc->getHintsMainChar(hints, index);
}

void GfQuestUtil::finishTalkNpc(u32 map, u32 npc, QuestID quest) {
  if (npc == 0) {
    return;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 orderMax = GfQuestManager::getOrderQuestMaxWithAchievement();
  for (u32 index = 0; index < orderMax; index++) {
    QuestID order = GfQuestManager::getOrderQuestWithAchievement(index);
    if (order == quest) {
      continue;
    }

    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(order, taskIndex, TASK_STATE_UNKNOWN_0);
      if (param.unknown10 == TASK_TYPE_UNKNOWN_6 && questListAcc->getTalkMapID(param.unknown14) == map && questListAcc->getTalkNpcID(param.unknown14) == npc) {
        GfQuestTask::completeTalkTask(param.unknown14, quest);
        break;
      }
    }
  }

  for (u32 index = 0; index < orderMax; index++) {
    QuestID order = GfQuestManager::getOrderQuestWithAchievement(index);
    if (order == quest) {
      continue;
    }

    for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
      QuestTaskParam param(order, taskIndex, TASK_STATE_UNKNOWN_0);
      if (param.unknown10 != TASK_TYPE_UNKNOWN_6 || questListAcc->getTalkMapID(param.unknown14) != map) {
        continue;
      }

      u32 dummyGroup = questListAcc->getTalkDummyGroup(param.unknown14);
      if (dummyGroup == 0) {
        continue;
      }

      for (u32 npcIndex = 0; npcIndex < NPC_UNKNOWN_8; npcIndex++) {
        if (questListAcc->getDummyGroupNpcID(dummyGroup, npcIndex) == npc) {
          if (!GfQuestInfo::isDummuTalkGroupFlag(dummyGroup, npcIndex)) {
            GfQuestInfo::setDummuTalkGroupFlag(dummyGroup, npcIndex);
            GfQuestManager::eventChangeTaskState(param);
          }

          return;
        }
      }
    }
  }

  u32 start = questListAcc->getTalkStart();
  u32 end = questListAcc->getTalkEnd();
  for (u32 talk = start; talk < end; talk++) {
    if (questListAcc->getTalkMapID(talk) == map && questListAcc->getTalkNpcID(talk) == npc) {
      GfQuestTask::completeTalkTask(talk, quest);
      return;
    }
  }
}

void GfQuestUtil::removeQuestItem(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  if (param.unknown10 == TASK_TYPE_UNKNOWN_3 && questListAcc->getCollectDeduct(param.unknown14) != 0) {
    GfItemUtil::addItemBox(questListAcc->getCollectItemID(param.unknown14), -questListAcc->getCollectCount(param.unknown14));
  }
}

void GfQuestUtil::sendItemLog(const QuestTaskParam &param) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 item = questListAcc->getCollectItemID(param.unknown14);
  u32 count = questListAcc->getCollectCount(param.unknown14);
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
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
  }

  if (parent.empty()) {
    return 0;
  }

  return QuestListAcc::get()->getListQuestTitle(parent);
}

u32 GfQuestUtil::getMsgQuestSummary(QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
  }

  if (parent.empty()) {
    return 0;
  }

  return GfDataQuest::getListSummary(parent);
}

u32 GfQuestUtil::getMsgQuestNeedFieldSkill(u32 index, QuestID quest) {
  if (quest.empty()) {
    QuestID current = GfQuestManager::getCurrentQuest(QTYPE_UNKNOWN_0);
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
  }

  if (quest.empty()) {
    return 0;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
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
    quest.unknown00 = current.unknown00;
    quest.unknown02 = current.unknown02;
  }

  QuestID parent = GfDataQuest::getListPRTQuestID(quest);
  if (parent.empty()) {
    parent.unknown00 = quest.unknown00;
    parent.unknown02 = quest.unknown02;
  }

  if (GfQuestInfo::isQuestFin(parent)) {
    if (GfQuestInfo::getState(parent) == QSTATE_UNKNOWN_2) {
      return GfDataQuest::getListResultA(parent);
    }

    if (GfQuestInfo::getState(parent) == QSTATE_UNKNOWN_3) {
      return GfDataQuest::getListResultB(parent);
    }
  }

  return 0;
}

bool GfQuestUtil::getReward(GfQuestReward &reward, u32 rewardSet, bool isRandom) {
  GfQuestReward::Param empty;
  for (GfQuestReward::Param &param : reward.unknown00) {
    param = empty;
  }

  reward.unknown360 = 0;
  if (rewardSet == 0) {
    return false;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  u32 gold = questListAcc->getRewardGold(rewardSet);
  if (gold != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_0].unknown00 = "GOLD";
    reward.unknown00[QUEST_REWARD_UNKNOWN_0].unknown44_u32 = gold;
  }

  u32 coin = questListAcc->getRewardCoin(rewardSet);
  if (coin != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_1].unknown00 = "COIN";
    reward.unknown00[QUEST_REWARD_UNKNOWN_1].unknown44_u32 = coin;
  }

  u32 sp = questListAcc->getRewardSp(rewardSet);
  if (sp != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_2].unknown00 = "SP";
    reward.unknown00[QUEST_REWARD_UNKNOWN_2].unknown44_u32 = sp;
  }

  u32 exp = questListAcc->getRewardEXP(rewardSet);
  if (exp != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_3].unknown00 = "EXP";
    reward.unknown00[QUEST_REWARD_UNKNOWN_3].unknown44_u32 = exp;
  }

  u16 developMap = questListAcc->getRewardDevelopZone(rewardSet);
  u16 developZone = GfDataMap::getZoneIdForDevelopPoint(developMap);
  u16 developPoint = questListAcc->getRewardDevelopPoint(rewardSet);
  if (developPoint != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_4].unknown00 = "DEVELOP";
    reward.unknown00[QUEST_REWARD_UNKNOWN_4].unknown44 = developPoint;
    reward.unknown00[QUEST_REWARD_UNKNOWN_4].m_developZone = developZone;
  }

  u16 trust = questListAcc->getRewardTrustPoint(rewardSet);
  if (trust != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_5].unknown00 = "TRUST";
    reward.unknown00[QUEST_REWARD_UNKNOWN_5].unknown44 = trust;
  }

  u16 mercenaries = questListAcc->getRewardMercenariesPoint(rewardSet);
  if (mercenaries != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_7].unknown00 = "MERCE";
    reward.unknown00[QUEST_REWARD_UNKNOWN_7].unknown44 = mercenaries;
  }

  u16 ideaCategory = questListAcc->getRewardIdeaCategory(rewardSet);
  u16 ideaValue = questListAcc->getRewardIdeaValue(rewardSet);
  if (ideaValue != 0) {
    reward.unknown00[QUEST_REWARD_UNKNOWN_6].unknown00 = "IDEA";
    reward.unknown00[QUEST_REWARD_UNKNOWN_6].unknown44 = ideaValue;
    reward.unknown00[QUEST_REWARD_UNKNOWN_6].m_developZone = ideaCategory;
  }

  for (u32 slot = QUEST_REWARD_UNKNOWN_8; slot <= QUEST_REWARD_UNKNOWN_11; slot++) {
    u16 item = questListAcc->getRewardItemID(rewardSet, slot - QUEST_REWARD_UNKNOWN_8);
    u16 number = questListAcc->getRewardItemNumber(rewardSet, slot - QUEST_REWARD_UNKNOWN_8);
    bool isPrecious = isRandom && GfItemUtil::isPrecious(item);
    if (number != 0 && !isPrecious) {
      reward.unknown00[slot].unknown00 = GfDataItem::getName(item);
      reward.unknown00[slot].unknown44 = item;
      reward.unknown00[slot].m_developZone = number;
    }
  }

  return true;
}

bool GfQuestUtil::isCurrentTaskBattle() {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
  if (quest.empty()) {
    return false;
  }

  return GfQuestTask::isTaskBattle(quest);
}

bool GfQuestUtil::isReduceHpObj(GF_OBJ_HANDLE *handle) {
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
  if (quest.empty()) {
    return false;
  }

  return GfQuestTask::isReduceHpObj(quest, handle);
}

void GfQuestUtil::addOrderParentQuest(QuestID quest) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  QuestData orderQuest(quest);
  removeOrderParentQuest(quest);
  if (dataGame->unknown10a538 < QUEST_UNKNOWN_256) {
    dataGame->unknown10a138[dataGame->unknown10a538++] = orderQuest;
  }
}

void GfQuestUtil::removeOrderParentQuest(QuestID quest) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  for (u32 index = 0; index < dataGame->unknown10a538; index++) {
    if (dataGame->unknown10a138[index] == QuestData(quest)) {
      for (; index < dataGame->unknown10a538 - 1; index++) {
        dataGame->unknown10a138[index] = dataGame->unknown10a138[index + 1];
      }

      dataGame->unknown10a538--;
      return;
    }
  }
}

QuestID GfQuestUtil::getLastOrderCategoryQuest(QTYPE type) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  u16 id = 0;
  u16 variant = 0;
  if (dataGame->unknown10a538 != 0) {
    for (s32 index = dataGame->unknown10a538; index > 0; index--) {
      if (GfDataQuest::getListQuestCategory(dataGame->unknown10a138[index - 1]) == type) {
        QuestID quest = dataGame->unknown10a138[index - 1];
        id = quest.unknown00;
        variant = quest.unknown02;
        break;
      }
    }
  }

  return QuestID(id, variant);
}

QuestID GfQuestUtil::getLastOrderInvalidCategoryQuest(QTYPE type) {
  SDataGame *dataGame = GfDataManager::getDataGame();
  u16 id = 0;
  u16 variant = 0;
  if (dataGame->unknown10a538 != 0) {
    for (s32 index = dataGame->unknown10a538; index > 0; index--) {
      if (GfDataQuest::getQuestCategory(dataGame->unknown10a138[index - 1]) != type) {
        QuestID quest = dataGame->unknown10a138[index - 1];
        id = quest.unknown00;
        variant = quest.unknown02;
        break;
      }
    }
  }

  return QuestID(id, variant);
}

QuestID GfQuestUtil::getLastOrderParentQuest() {
  SDataGame *dataGame = GfDataManager::getDataGame();
  u16 id = 0;
  u16 variant = 0;
  if (dataGame->unknown10a538 != 0) {
    QuestID quest = dataGame->unknown10a138[dataGame->unknown10a538 - 1];
    id = quest.unknown00;
    variant = quest.unknown02;
  }

  return QuestID(id, variant);
}

void GfQuestUtil::clearOrderParentQuest() { GfDataManager::getDataGame()->unknown10a538 = 0; }

void GfQuestUtil::addTaskHanyouCount(u32 purpose, u32 taskIndex, u32 add) {
  if (purpose == 0) {
    return;
  }

  QuestID none = {0, 0};
  QuestTaskParam param(none, taskIndex, purpose, TASK_STATE_UNKNOWN_0);
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
  param.unknown04.unknown00 = quest.unknown00;
  param.unknown04.unknown02 = quest.unknown02;
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
    for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
      if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_UNKNOWN_6) {
        continue;
      }

      u32 party = bdatCond->getConditionListCondition(condition, index);
      if (party == 0 || bdatCond->getConditionPTCategory(party) != 0) {
        continue;
      }

      for (u32 member = 0; member < CHARACTER_UNKNOWN_3; member++) {
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
  return achievQuest != nullptr ? achievQuest->unknown16 : 0;
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
    case GIMMICK_TYPE_UNKNOWN_41:
      isFound = questListAcc->getGimmickDoorGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_42:
      isFound = questListAcc->getGimmickElevatorGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_37:
      isFound = questListAcc->getGimmickJumpGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_33:
      isFound = questListAcc->getGimmickMapGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_38:
      isFound = questListAcc->getGimmickWarpGimmickID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_31:
      isFound = questListAcc->getGimmickSalvagePointID(id) == gimmick;
      break;
    case GIMMICK_TYPE_UNKNOWN_9:
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
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 != TASK_TYPE_UNKNOWN_6 || !GfQuestTask::isEnableTaskCondition(param)) {
      continue;
    }

    u32 dummyGroup = questListAcc->getTalkDummyGroup(param.unknown14);
    if (dummyGroup == 0) {
      continue;
    }

    for (u32 index = 0; index < NPC_UNKNOWN_8; index++) {
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
  for (u32 index = 0; index < QUEST_UNKNOWN_4; index++) {
    QuestTaskParam param(quest, index, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == TASK_TYPE_UNKNOWN_6 && questListAcc->getTalkNpcID(param.unknown14) == npc && questListAcc->getTalkMapID(param.unknown14) == GfGameManager::getMapID()) {
      taskIndex = index;
      return true;
    }
  }

  return false;
}

u32 GfQuestUtil::getQuestIconType(QuestID quest) {
  if (GfQuestInfo::isParent(quest)) {
    quest = GfDataQuest::getListNextQuestA(quest);
  }

  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    switch (param.unknown10) {
    case 0:
      continue;
    case TASK_TYPE_UNKNOWN_1:
      return 1;
    case TASK_TYPE_UNKNOWN_2:
    case TASK_TYPE_UNKNOWN_3:
    case TASK_TYPE_UNKNOWN_4:
      return 2;
    case TASK_TYPE_UNKNOWN_5:
    case TASK_TYPE_UNKNOWN_6:
    case TASK_TYPE_UNKNOWN_7:
    case TASK_TYPE_UNKNOWN_8:
      return 3;
    case TASK_TYPE_UNKNOWN_9:
    case TASK_TYPE_UNKNOWN_11:
      return 0;
    case TASK_TYPE_UNKNOWN_10: {
      GfBdatCond *bdatCond = GfBdatCond::get();
      u32 condition = QuestListAcc::get()->getConditionConditionID(param.unknown14);
      if (condition == 0) {
        return 0;
      }

      for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
        switch (bdatCond->getConditionListConditionType(condition, index)) {
        case CONDITION_TYPE_UNKNOWN_0:
          continue;
        case CONDITION_TYPE_UNKNOWN_3:
          return 3;
        case CONDITION_TYPE_UNKNOWN_4: {
          u32 conditionParam = bdatCond->getConditionListCondition(condition, index);
          GfBdatCond *flagCond = GfBdatCond::get();
          u32 flagType = flagCond->getConditionFlagFlagType(conditionParam);
          int flagId = flagCond->getConditionFlagFlagID(conditionParam);
          if ((flagType == 2 && flagId >= 2 && flagId < 102) || (flagType == 1 && flagId >= 0xc328 && flagId < 0xc328 + 1000)) {
            return 3;
          }

          return 0;
        }
        case CONDITION_TYPE_UNKNOWN_7:
          return 4;
        case CONDITION_TYPE_UNKNOWN_5:
          return 2;
        }

        break;
      }

      return 0;
    }
    case TASK_TYPE_UNKNOWN_12: {
      u32 stats = QuestListAcc::get()->getAchievementStatsID(param.unknown14);
      if (stats == 0) {
        return 0;
      }

      return GfDataAchievement::getStatsQuestIcon(stats);
    }
    }

    break;
  }

  return 0;
}

bool GfQuestUtil::getDispCount(u32 &count, u32 &limit, const AchievQuest &achievQuest) {
  count = achievQuest.getCount();
  limit = achievQuest.getTargetCount();
  if (count > limit) {
    count = limit;
  }

  QuestListAcc *questListAcc = QuestListAcc::get();
  if (!achievQuest.unknown00.empty() || achievQuest.unknown0e != 0) {
    bool isComplete = GfKizunaringBlade::isCompleteLevel(achievQuest);
    if (achievQuest.unknown10 != TASK_TYPE_UNKNOWN_5 && achievQuest.unknown10 != TASK_TYPE_UNKNOWN_6) {
      switch (achievQuest.unknown10) {
      case TASK_TYPE_UNKNOWN_10: {
        GfBdatCond *bdatCond = GfBdatCond::get();
        QuestTaskParam param(GfDataQuest::getListNextQuestA(achievQuest.unknown00), 0, TASK_STATE_UNKNOWN_0);
        bool isDisp = false;
        if (param.unknown10 != TASK_TYPE_UNKNOWN_10) {
          count = 0;
          limit = 1;
        } else {
          u32 condition = QuestListAcc::get()->getConditionConditionID(param.unknown14);
          u32 typeCount = 0;
          for (u32 index = 0; index < CONDITION_UNKNOWN_8; index++) {
            if (bdatCond->getConditionListConditionType(condition, index) != CONDITION_TYPE_UNKNOWN_0) {
              typeCount++;
            }
          }

          if (typeCount < 2) {
            u32 conditionType = bdatCond->getConditionListConditionType(condition, 0);
            u32 conditionParam = bdatCond->getConditionListCondition(condition, 0);
            if (conditionType == CONDITION_TYPE_UNKNOWN_4) {
              u32 flagType = bdatCond->getConditionFlagFlagType(conditionParam);
              int flagId = bdatCond->getConditionFlagFlagID(conditionParam);
              u32 flagMin = bdatCond->getConditionFlagFlagMin(conditionParam);
              if (!(flagType == 2 && flagId >= 2 && flagId < 102) && !(flagType == 4 && flagId >= 6 && flagId < 506) && !(flagType == 1 && flagId >= 0xc328 && flagId < 0xc328 + 1000)) {
                count = GfGameFlag::getLocal(flagType, flagId);
                limit = flagMin;
                isDisp = true;
              }
            } else if (conditionType == CONDITION_TYPE_UNKNOWN_7) {
              count = GfDataBlade::getTrustPoint(achievQuest.unknown16);
              limit = bdatCond->getConditionIdeaTrustPoint(conditionParam);
              isDisp = true;
            }
          }
        }

        if (count > limit || !isComplete) {
          count = isComplete ? limit : 0;
        }

        return isDisp;
      }
      case TASK_TYPE_UNKNOWN_11: {
        QuestTaskParam param(GfDataQuest::getListNextQuestA(achievQuest.unknown00), 0, TASK_STATE_UNKNOWN_0);
        limit = questListAcc->getFieldSkillCountCount(param.unknown14);
        if (count > limit || !isComplete) {
          count = isComplete ? limit : 0;
        }

        break;
      }
      default:
        break;
      }

      return true;
    }
  }

  return false;
}

void GfQuestUtil::incFieldSkillTask(u32 blade, u32 fieldSkill) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (u32 line = 0; line < ACHIEVEMENT_UNKNOWN_10; line++) {
    AchievInfo *achievInfo = GfDataBlade::getAchievInfo(blade, line);
    if (achievInfo->unknown00 == 0) {
      continue;
    }

    for (u32 level = 1; level <= ACHIEVEMENT_UNKNOWN_5; level++) {
      AchievQuest &achievQuest = achievInfo->unknown04[level - 1];
      if (achievQuest.unknown10 != TASK_TYPE_UNKNOWN_11 || !GfQuestInfo::isQuestOrder(achievQuest.unknown00) || achievQuest.isCountComplete()) {
        continue;
      }

      QuestTaskParam param(GfDataQuest::getListNextQuestA(achievQuest.unknown00), 0, TASK_STATE_UNKNOWN_0);
      if (questListAcc->getFieldSkillCountFieldSkillID(param.unknown14) == fieldSkill) {
        achievQuest.incleseCount(1);
        GfQuestTask::updateQuestTask(achievQuest.unknown00);
        return;
      }
    }
  }
}

void GfQuestUtil::getTaskInfoForAutoPilot(mm::mtl::FixStr<256> &info) {
  if (GfQuestManager::get() == nullptr) {
    return;
  }

  info.format("Scenario(%4d) Quest[", GfDataUtil::getScenarioFlag());
  QuestID quest = GfQuestManager::getProgressCurrentQuest(QTYPE_UNKNOWN_0);
  for (u32 taskIndex = 0; taskIndex < QUEST_UNKNOWN_4; taskIndex++) {
    mm::mtl::FixStr<64> taskInfo;
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    if (param.unknown10 == 0) {
      continue;
    }

    GfQuestInfo::isCompleteTask(param);
    switch (param.unknown10) {
    case TASK_TYPE_UNKNOWN_1:
      taskInfo.format("%d: BAT(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_2:
      taskInfo.format("%d:ITEM(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_3:
      taskInfo.format("%d:COLE(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_4:
      taskInfo.format("%d: USE(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_5:
      taskInfo.format("%d:REAH(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_6:
      taskInfo.format("%d:TALK(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_7:
      taskInfo.format("%d: EVT(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_8:
      taskInfo.format("%d: GMK(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_9:
      taskInfo.format("%d: BLD(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_10:
      taskInfo.format("%d:COND(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_11:
      taskInfo.format("%d:  FS(%d)", taskIndex, param.unknown14);
      break;
    case TASK_TYPE_UNKNOWN_12:
      taskInfo.format("%d:ACHI(%d)", taskIndex, param.unknown14);
      break;
    default:
      break;
    }

    info += taskInfo.c_str();
  }

  info += "]";
}

void GfQuestUtil::completeCurrentQuestForAutoPilot() {}

// Inferred role: tells whether next or a quest following it in the quest chain links to a blade quest; original name unknown.
static bool unknown001(QuestID quest, QuestID next) {
  if (next.empty()) {
    return false;
  }

  QuestID linked;
  u32 linkedQuest = QuestListAcc::get()->getListLinkedQuestID(next);
  linked.unknown00 = linkedQuest;
  linked.unknown02 = linkedQuest >> 16;
  if (!linked.empty() && GfDataQuest::getListQuestCategory(linked) == QTYPE_UNKNOWN_2) {
    return true;
  }

  if (unknown001(quest, GfDataQuest::getListNextQuestA(next))) {
    return true;
  }
  return unknown001(quest, GfDataQuest::getListNextQuestB(next));
}

// Inferred role: tells whether the quest chain following quest links to a blade quest; original name unknown.
static bool unknown003(QuestID quest) {
  if (unknown001(quest, GfDataQuest::getListNextQuestA(quest))) {
    return true;
  }
  return unknown001(quest, GfDataQuest::getListNextQuestB(quest));
}

// Inferred role: resets the parent quests of a type whose chain links to no blade quest; original name unknown.
static void unknown002(QTYPE type) {
  QuestListAcc *questListAcc = QuestListAcc::get();
  for (qlist_iterator it = questListAcc->begin(type); it != questListAcc->end(type); ++it) {
    if (GfQuestInfo::isParent(it.getQuestID()) && !unknown003(it.getQuestID())) {
      GfQuestManager::resetQuest(it.getQuestID());
    }
  }
}

// Inferred role: counts the finished quests of the chain starting at quest; original name unknown.
static void unknown004(u32 &count, QuestID quest) {
  if (GfQuestInfo::getState(quest) < QSTATE_UNKNOWN_2) {
    return;
  }

  count++;
  QuestID nextA = GfDataQuest::getListNextQuestA(quest);
  if (!nextA.empty()) {
    unknown004(count, nextA);
  }

  QuestID nextB = GfDataQuest::getListNextQuestB(quest);
  if (!nextB.empty()) {
    unknown004(count, nextB);
  }
}

u32 GfQuestUtil::getClearChildQuest(QuestID quest) {
  if (!GfQuestInfo::isParent(quest)) {
    return 0;
  }

  u32 count = 0;
  unknown004(count, GfDataQuest::getListNextQuestA(quest));
  return count;
}

void GfQuestUtil::setupNewGameParam() {
  unknown002(QTYPE_UNKNOWN_1);
  unknown002(QTYPE_UNKNOWN_3);
  unknown002(QTYPE_UNKNOWN_2);
}

bool GfQuestUtil::getResultIdea(u32 &category, u32 &value, u32 blade, u32 line, u32 level) {
  bool isIdea = false;
  SDataBladeAchievement *achievInfo = GfDataBlade::getAchievInfo(blade, line);
  if (achievInfo->unknown00 != 0) {
    GfQuestReward reward;
    if (GfQuestManager::getRewardItem(reward, achievInfo->unknown04[level - 1].unknown00, true)) {
      value = reward.unknown00[QUEST_REWARD_UNKNOWN_6].unknown44;
      if (value != 0) {
        isIdea = true;
        category = reward.unknown00[QUEST_REWARD_UNKNOWN_6].m_developZone;
      }
    }
  }

  return isIdea;
}

bool GfQuestUtil::getTaskMap(mm::mtl::FixedArray<u16, 4> &maps, QuestID quest) {
  if (quest.empty() || GfQuestInfo::isParent(quest)) {
    return false;
  }

  for (u32 taskIndex = 0; taskIndex < maps.size(); taskIndex++) {
    QuestTaskParam param(quest, taskIndex, TASK_STATE_UNKNOWN_0);
    maps[taskIndex] = GfQuestTask::getTaskMap(param);
    if (maps[taskIndex] == 0) {
      mm::mtl::FixedVector<QuestID, 16> linkQuests;
      GfQuestManager::getLinkQuest(linkQuests, quest);
      for (const QuestID &linkQuest : linkQuests) {
        if (!(linkQuest == quest)) {
          maps[taskIndex] = GfQuestTask::getTaskMap(QuestTaskParam(GfDataQuest::getListNextQuestA(linkQuest), taskIndex, TASK_STATE_UNKNOWN_0));
          if (maps[taskIndex] != 0) {
            break;
          }
        }
      }
    }
  }

  return true;
}

} // namespace gf

template mm::mtl::FixedQueue<gf::QuestData, 8000>::iterator mm::mtl::FixedQueue<gf::QuestData, 8000>::insert(mm::mtl::FixedQueue<gf::QuestData, 8000>::fixed_queue_iterator<gf::QuestData, 8000>,
                                                                                                             gf::QuestData const &);

template mm::mtl::FixedQueue<gf::QuestData, 15000>::iterator mm::mtl::FixedQueue<gf::QuestData, 15000>::insert(mm::mtl::FixedQueue<gf::QuestData, 15000>::fixed_queue_iterator<gf::QuestData, 15000>,
                                                                                                               gf::QuestData const &);
