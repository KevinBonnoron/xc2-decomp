#pragma once
#include "gf/game/quest/gf_quest_info.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gmk {
enum GmkType : int;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct QuestTaskParam;
struct QuestID;

class GfQuestTask {
public:
  static void initializeParams();
  static bool setCompleteFlag(const QuestTaskParam &param, bool isComplete);
  static bool isCompleteFlag(const QuestTaskParam &param);
  static QSTATE updateQuestTask(QuestID quest);
  static void clearTask(QuestID quest);
  static void completeEventTask(u32 event);
  static void completeTalkTask(u32 npc, QuestID quest);
  static bool isEnableTaskCondition(const QuestTaskParam &param);
  static void completeReachTask(u32 map, u32 place);
  static void completeItemUseTask(u32 item, u32 count);
  static void completeGimmickTask(gmk::GmkType type, u32 gimmick);
  static void destroyTaskAchieve(QuestID quest);
  static void refreshTaskParam(QuestID quest);
  static void setupOrderTask(QuestID quest);
  static void setupOrderTaskForInitialize(QuestID quest);
  static void completeTask(const QuestTaskParam &param);
  static void incSuppressEnemy(u32 enemy);
  static void applyGetItem(u32 item, bool isAdd);
  static void refreshTaskCounter(QuestID quest);
  static bool getTaskCount(const QuestTaskParam &param, u32 &limit, u32 &count, u32 &item, u32 &itemCategory);
  static void refreshTaskCounters();
  static bool isEnableTaskConditionWithoutEnv(const QuestTaskParam &param);
  static bool isTaskBattle(QuestID quest);
  static u32 getReduceHpObj(QuestID quest, GF_OBJ_HANDLE *handle);
  static bool isReduceHpObj(QuestID quest, GF_OBJ_HANDLE *handle);
  static u32 getReduceHpObjPc(QuestID quest, GF_OBJ_HANDLE *handle);
  static bool isReduceHpObjPc(QuestID quest, GF_OBJ_HANDLE *handle);
  static bool isReduceHpQuest(QuestID quest);
  static void resetBattleTaskForPlayerDead(QuestID quest);
  static bool resetBattleTaskForBattleEnd(mm::mtl::FixedVector<u16, 128> &enemies, QuestID quest);
  static u16 getTaskMap(const QuestTaskParam &param);
};

} // namespace gf
