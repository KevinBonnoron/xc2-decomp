#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_vector.h"
#include "types.h"

namespace gf {

struct AchievQuest;

constexpr u32 ACHIEVEMENT_PER_BLADE = 50;
constexpr u32 ACHIEVEMENT_LEVEL_COUNT = 5;

class GfDataQuest {
public:
  static void registAchievementBlade(u32 achievement, u16 blade);
  static QuestID getListNextQuestA(QuestID quest);
  static u32 getListPurposeID(QuestID quest);
  static u32 getAchievementLine(u32 achievement);
  static u32 getAchievementLevel(u32 achievement);
  static void setOrderTimming(QuestID quest);
  static bool getOrderTimming(mm::mtl::FixedVector<QuestID, 330> &quests);
  static u16 getAchievementBlade(u32 achievement);
  static u32 getListTalker(QuestID quest);
  static u32 getListRewardSetA(QuestID quest);
  static u32 getListRewardSetB(QuestID quest);
  static bool getListRewardDisp(QuestID quest);
  static u32 getListResultA(QuestID quest);
  static u32 getListResultB(QuestID quest);
  static u32 getListSummary(QuestID quest);
  static bool getListVisible(QuestID quest);
  static u32 getListQuestCategory(QuestID quest);
  static u32 getQuestCategory(QuestID quest);
  static QuestID getListPRTQuestID(QuestID quest);
  static u32 getListFlagPRT(QuestID quest);
  static u32 getListFlagCLD(QuestID quest);
  static QuestID getListNextQuestB(QuestID quest);
  static u32 getListCallEventA(QuestID quest);
  static u32 getListCallEventB(QuestID quest);
  static u32 getListHintsID(QuestID quest);
  static bool getTitle(u8 *&bdat, u32 &textId, QuestID quest);
  static const char *getTitle(QuestID quest);
  static bool getSummary(u8 *&bdat, u32 &textId, QuestID quest);
  static const char *getSummary(QuestID quest);
  static bool getResult(u8 *&bdat, u32 &textId, QuestID quest);
  static const char *getTaskLog(QuestID quest, u32 line);
  static void setScenario(QuestID scenario);
  static QuestID getScenario();
  static void setSelect(QuestID select);
  static QuestID getSelect();
  static AchievQuest *getAchievQuest(QuestID quest);

  static u16 m_achieve2blade[];
};

} // namespace gf
