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

  u32 getHintsZoneID(u32 hints) const;
  u32 getHintsFSkillID1(u32 hints) const;
  u32 getHintsFSkillID2(u32 hints) const;
  u32 getHintsFSkillID3(u32 hints) const;
  u32 getTaskTaskType(u32 purpose, u32 index) const;
  u32 getTaskTaskLog(u32 purpose, u32 index) const;
  u32 getTaskTaskCondition(u32 purpose, u32 index) const;
  u32 getTaskTaskID(u32 purpose, u32 index) const;
  u32 getRequestBladeRequestNumber(u32 requestBlade) const;
  u32 getRequestBladeRequestCategory(u32 requestBlade) const;
  u32 getRequestBladeRequestAtr(u32 requestBlade) const;
  u32 getRequestBladeRequestPerformance(u32 requestBlade) const;
  u32 getRequestBladeRequestRace(u32 requestBlade) const;
  u32 getRequestBladeRequestGender(u32 requestBlade) const;
  u32 getRequestBladeRequestArts(u32 requestBlade) const;
  u32 getRequestBladeRequestArtsLevel(u32 requestBlade) const;
  u32 getRequestBladeRequestFSkill(u32 requestBlade) const;
  u32 getRequestBladeRequestFSLevel(u32 requestBlade) const;
  u32 getFLD_AchievementListTitle(u32 achievement) const;
  u32 getFLD_FieldSkillListName(u32 fieldSkill) const;
  u32 getFLD_FieldSkillListCaption(u32 fieldSkill) const;
  u32 getFLD_FieldSkillSettingStart() const;
  u32 getFLD_MercenariesConfigValue(u32 config) const;
  u32 getFLD_MercenariesMissionStart() const;
  u32 getFLD_MercenariesMissionEnd() const;
  u32 getFLD_MercenariesMissionQuestID(u32 mission) const;
  u32 getFLD_MercenariesMissionCategory(u32 mission) const;
  u32 getFLD_MercenariesMissionRepeatable(u32 mission) const;
  u32 getFLD_MercenariesMissionRequestPerformance(u32 mission) const;
};

} // namespace gf
