#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"

namespace gf {

class QuestListAcc {
public:
  static QuestListAcc *get();

  u32 getListQuestTitle(QuestID quest) const;
  u32 getListPurposeID(QuestID quest) const;
  u32 getListTalker(QuestID quest) const;
  u32 getListRewardSetA(QuestID quest) const;
  u32 getListRewardSetB(QuestID quest) const;
  u32 getListRewardDisp(QuestID quest) const;
  u32 getListResultA(QuestID quest) const;
  u32 getListResultB(QuestID quest) const;
  u32 getListSummary(QuestID quest) const;
  u32 getListVisible(QuestID quest) const;
  u32 getListQuestCategory(QuestID quest) const;
  u32 getListPRTQuestID(QuestID quest) const;
  u32 getListFlagPRT(QuestID quest) const;
  u32 getListFlagCLD(QuestID quest) const;
  u32 getListNextQuestA(QuestID quest) const;
  u32 getListNextQuestB(QuestID quest) const;
  u32 getListCallEventA(QuestID quest) const;
  u32 getListCallEventB(QuestID quest) const;
  u32 getListHintsID(QuestID quest) const;
  u32 getListAutoStart(QuestID quest) const;
};

} // namespace gf
