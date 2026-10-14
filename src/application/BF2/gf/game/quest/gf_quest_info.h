#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct AchievInfo;
struct QuestTaskParam;

enum QSTATE {
  QSTATE_NOT_ORDER,
  QSTATE_ORDER,
  QSTATE_FIN_A,
  QSTATE_FIN_B,
};

class GfQuestInfo {
public:
  static bool isQuestOrder(QuestID quest);
  static bool isQuestProgress(QuestID quest);
  static bool isQuestFin(QuestID quest);
  static QSTATE getState(QuestID quest);
  static bool isQuestNotOrder(QuestID quest);
  static u32 getQuestFlag2No(QuestID quest);
  static void setState(QuestID quest, QSTATE state);
  static QuestID getParentQuest(QuestID quest);
  static u32 getPlayEvent(QuestID quest, QSTATE state);
  static QuestID getProgressQuest(QuestID quest);
  static bool isParent(QuestID quest);
  static QuestID getChildQuestID(QuestID quest);
  static bool incSuppressCount(const QuestTaskParam &param);
  static void resetSuppressCount(const QuestTaskParam &param);
  static u32 getSuppressCount(const QuestTaskParam &param);
  static u32 getSuppressLimit(const QuestTaskParam &param);
  static bool incCollectUseCount(const QuestTaskParam &param);
  static bool decCollectUseCount(const QuestTaskParam &param);
  static u32 getCollectUseCount(const QuestTaskParam &param);
  static u32 getCollectUseLimit(const QuestTaskParam &param);
  static u32 getCollectUseItem(const QuestTaskParam &param);
  static u32 getCollectUseItemCategory(const QuestTaskParam &param);
  static void resetCollectUseCount(const QuestTaskParam &param);
  static void setupAchievementCount(const QuestTaskParam &param);
  static u32 getTaskHide(const QuestTaskParam &param);
  static bool isCompletePrevQuest(QuestID quest);
  static bool canQuestOrder(QuestID quest);
  static bool isScenarioQuest(QuestID quest);
  static bool isCompleteTask(const QuestTaskParam &param);
  static bool isDispUI(QuestID quest);
  static bool getQuestNeedTaskCond(QuestID quest);
  static bool isCollectCond(u32 collect);
  static u32 getListCategoryCount(QTYPE type, bool isParentOnly);
  static u32 getAchievCountByStats(u32 stats);
  static bool getBattleTaskEnemy(mm::mtl::FixedVector<u16, 128> &enemies, const QuestTaskParam &param);
  static bool getTaskLog(u8 *&bdat, u32 &textId, u32 purpose, u32 taskIndex);
  static const char *getTaskLog(u32 purpose, u32 taskIndex);
  static bool getTaskCount(u32 &count, u32 &limit, u32 &item, u32 &itemCategory, u32 purpose, u32 taskIndex);
  static bool isDummuTalkGroupFlag(u32 group, u32 npcIndex);
  static void setDummuTalkGroupFlag(u32 group, u32 npcIndex);
  static bool isEnableSetupCount(const AchievInfo &info, u32 level);
  static void getQuestTaskInfo(u32 &taskCount, u32 &completeCount, QuestID quest);
  static s32 getQuestTaskWeatherInfo(const QuestTaskParam &param);
  static s32 getQuestTaskTimeInfo(const QuestTaskParam &param);
};

} // namespace gf
