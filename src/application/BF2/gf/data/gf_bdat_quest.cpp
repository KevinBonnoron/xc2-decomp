#include "gf/data/gf_bdat_quest.h"
#include "bdat.h"
#include "gf/data/gf_bdat_wrapper.h"

namespace gf {
namespace _gfbqa {

enum {
  BattleRefer,
  BattleEnemyID,
  BattleEnemyGroupID,
  BattleEnemySpeciesID,
  BattleCount,
  BattleCountFlag,
  BattleDeadAll,
  BattleTimeCount,
  BattleTimeCountFlag,
  BattleReduceEnemyHP,
  BattleReducePCHP,
  RequestItemSetItemID1,
  RequestItemSetItemID2,
  RequestItemSetItemID3,
  RequestItemSetItemID4,
  RequestItemSetItemID5,
  RequestItemSetCount1,
  RequestItemSetCount2,
  RequestItemSetCount3,
  RequestItemSetCount4,
  RequestItemSetCount5,
  RequestItemSetMapID,
  RequestItemSetNpcID,
  CollectItemID,
  CollectCategory,
  CollectCount,
  CollectDeduct,
  CollectTresureID,
  CollectEnemyID,
  CollectMapID,
  CollectNpcID,
  UseItemID,
  UseCategory,
  UseItemNumber,
  UsePartyInPC,
  UsebladeID,
  ReachCategory,
  ReachMapID,
  ReachPlaceID,
  TalkMapID,
  TalkNpcID,
  TalkDummyGroup,
  DummyGroupNpcID1,
  DummyGroupNpcID2,
  DummyGroupNpcID3,
  DummyGroupNpcID4,
  DummyGroupNpcID5,
  DummyGroupNpcID6,
  DummyGroupNpcID7,
  DummyGroupNpcID8,
  GimmickMapID,
  GimmickDoorGimmickID,
  GimmickElevatorGimmickID,
  GimmickJumpGimmickID,
  GimmickMapGimmickID,
  GimmickMapGmkIconOff,
  GimmickWarpGimmickID,
  GimmickSalvagePointID,
  GimmickTboxPopID,
  GimmickEndCheck,
  FieldSkillCountFieldSkillID,
  FieldSkillCountCount,
  RequestBladeRequestCategory,
  RequestBladeRequestAtr,
  RequestBladeRequestPerformance,
  RequestBladeRequestRace,
  RequestBladeRequestGender,
  RequestBladeRequestArts,
  RequestBladeRequestArtsLevel,
  RequestBladeRequestFSkill,
  RequestBladeRequestFSLevel,
  RequestBladeRequestNumber,
  ConditionConditionID,
  ConditionMapID,
  ConditionNpcID,
  AchievementStatsID,
  AchievementCount,
  AchievementDebugName,
  HintsMainChar1,
  HintsMainChar2,
  HintsMainChar3,
  HintsMainChar4,
  HintsFSkillID1,
  HintsFSkillID2,
  HintsFSkillID3,
  HintsClientNpc,
  HintsZoneID,
  EventEventID,
  RewardGold,
  RewardEXP,
  RewardSp,
  RewardCoin,
  RewardDevelopZone,
  RewardDevelopPoint,
  RewardTrustPoint,
  RewardMercenariesPoint,
  RewardIdeaCategory,
  RewardIdeaValue,
  RewardItemID1,
  RewardItemNumber1,
  RewardItemID2,
  RewardItemNumber2,
  RewardItemID3,
  RewardItemNumber3,
  RewardItemID4,
  RewardItemNumber4,
  FLD_AchievementSetCategory,
  FLD_AchievementSetAbilityLevel,
  FLD_AchievementSetAchievementID1,
  FLD_AchievementSetAchievementID2,
  FLD_AchievementSetAchievementID3,
  FLD_AchievementSetAchievementID4,
  FLD_AchievementSetAchievementID5,
  FLD_AchievementListTitle,
  FLD_AchievementListCategory,
  FLD_AchievementListIcon,
  FLD_AchievementListTask,
  FLD_AchievementListVoiceCategory,
  FLD_AchievementListAfterVoice,
  FLD_AchievementListDifficulty,
  FLD_AchievementListIdeaCategory,
  FLD_AchievementListIdeaValue,
  FLD_MercenariesConfigValue,
  FLD_MercenariesMissionQuestID,
  FLD_MercenariesMissionCategory,
  FLD_MercenariesMissionRequestPerformance,
  FLD_MercenariesMissionRepeatable,
  FLD_MercenariesMissionAutoStart,
  FLD_FieldSkillListName,
  FLD_FieldSkillListCaption,
  FLD_FieldSkillListType,
  FLD_FieldSkillListRandomID,
  FLD_FieldSkillListMinLevel,
  FLD_FieldSkillListMaxLevel,
  FLD_FieldSkillListCategory,
  FLD_FieldSkillListRarity,
  FLD_FieldSkillListIcon,
  FLD_FieldSkillListVoiceCategory,
  FLD_FieldSkillListAttirbute,
  FLD_FieldSkillSettingName,
  FLD_FieldSkillSettingFieldSkillID1,
  FLD_FieldSkillSettingFieldSkillLevel1,
  FLD_FieldSkillSettingFieldSkillID2,
  FLD_FieldSkillSettingFieldSkillLevel2,
  FLD_FieldSkillSettingSuccessVoiceCategory,
  FLD_FieldSkillSettingMissVoiceCategory,
  FLD_FieldSkillRandomLevel1Chance,
  FLD_FieldSkillRandomLevel2Chance,
  FLD_FieldSkillRandomLevel3Chance,
  FLD_DevelopmentLevelValue,
  ListQuestTitle,
  ListQuestCategory,
  ListVisible,
  ListTalker,
  ListSummary,
  ListResultA,
  ListResultB,
  ListSortNo,
  ListRewardDisp,
  ListRewardSetA,
  ListRewardSetB,
  ListPRTQuestID,
  ListFlagPRT,
  ListFlagCLD,
  ListPurposeID,
  ListCountCancel,
  ListNextQuestA,
  ListCallEventA,
  ListNextQuestB,
  ListCallEventB,
  ListHintsID,
  ListClearVoice,
  ListAutoStart,
  ListItemLost,
  ListCancelCondition,
  ListQuestIcon,
  ListLinkedQuestID,
  TaskPreCondition,
  TaskTaskType1,
  TaskTaskType2,
  TaskTaskType3,
  TaskTaskType4,
  TaskTaskID1,
  TaskTaskID2,
  TaskTaskID3,
  TaskTaskID4,
  TaskBranch1,
  TaskBranch2,
  TaskBranch3,
  TaskBranch4,
  TaskTaskLog1,
  TaskTaskLog2,
  TaskTaskLog3,
  TaskTaskLog4,
  TaskTaskUI1,
  TaskTaskUI2,
  TaskTaskUI3,
  TaskTaskUI4,
  TaskTaskCondition1,
  TaskTaskCondition2,
  TaskTaskCondition3,
  TaskTaskCondition4,
  MEMBER_COUNT,
};

static u8 *s_members[MEMBER_COUNT];

void initBattleRefer(const CBdatWrapper &wrapper) { s_members[BattleRefer] = Bdat::getMember(wrapper.data, "Refer"); }

u32 getBattleRefer(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleRefer] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleRefer], id, 1).valueU8;
}

void initBattleEnemyID(const CBdatWrapper &wrapper) { s_members[BattleEnemyID] = Bdat::getMember(wrapper.data, "EnemyID"); }

u32 getBattleEnemyID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleEnemyID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleEnemyID], id, 2).valueU16;
}

void initBattleEnemyGroupID(const CBdatWrapper &wrapper) { s_members[BattleEnemyGroupID] = Bdat::getMember(wrapper.data, "EnemyGroupID"); }

u32 getBattleEnemyGroupID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleEnemyGroupID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleEnemyGroupID], id, 2).valueU16;
}

void initBattleEnemySpeciesID(const CBdatWrapper &wrapper) { s_members[BattleEnemySpeciesID] = Bdat::getMember(wrapper.data, "EnemySpeciesID"); }

u32 getBattleEnemySpeciesID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleEnemySpeciesID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleEnemySpeciesID], id, 2).valueU16;
}

void initBattleCount(const CBdatWrapper &wrapper) { s_members[BattleCount] = Bdat::getMember(wrapper.data, "Count"); }

u32 getBattleCount(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleCount] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleCount], id, 1).valueU8;
}

void initBattleCountFlag(const CBdatWrapper &wrapper) { s_members[BattleCountFlag] = Bdat::getMember(wrapper.data, "CountFlag"); }

u32 getBattleCountFlag(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleCountFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleCountFlag], id, 2).valueU16;
}

void initBattleDeadAll(const CBdatWrapper &wrapper) { s_members[BattleDeadAll] = Bdat::getMember(wrapper.data, "DeadAll"); }

u32 getBattleDeadAll(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleDeadAll] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleDeadAll], id, 1).valueU8;
}

void initBattleTimeCount(const CBdatWrapper &wrapper) { s_members[BattleTimeCount] = Bdat::getMember(wrapper.data, "TimeCount"); }

u32 getBattleTimeCount(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleTimeCount] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleTimeCount], id, 2).valueU16;
}

void initBattleTimeCountFlag(const CBdatWrapper &wrapper) { s_members[BattleTimeCountFlag] = Bdat::getMember(wrapper.data, "TimeCountFlag"); }

u32 getBattleTimeCountFlag(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleTimeCountFlag] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleTimeCountFlag], id, 1).valueU8;
}

void initBattleReduceEnemyHP(const CBdatWrapper &wrapper) { s_members[BattleReduceEnemyHP] = Bdat::getMember(wrapper.data, "ReduceEnemyHP"); }

u32 getBattleReduceEnemyHP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleReduceEnemyHP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleReduceEnemyHP], id, 2).valueU16;
}

void initBattleReducePCHP(const CBdatWrapper &wrapper) { s_members[BattleReducePCHP] = Bdat::getMember(wrapper.data, "ReducePCHP"); }

u32 getBattleReducePCHP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[BattleReducePCHP] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[BattleReducePCHP], id, 2).valueU16;
}

void initRequestItemSetItemID1(const CBdatWrapper &wrapper) { s_members[RequestItemSetItemID1] = Bdat::getMember(wrapper.data, "ItemID1"); }

u32 getRequestItemSetItemID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetItemID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetItemID1], id, 2).valueU16;
}

void initRequestItemSetItemID2(const CBdatWrapper &wrapper) { s_members[RequestItemSetItemID2] = Bdat::getMember(wrapper.data, "ItemID2"); }

u32 getRequestItemSetItemID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetItemID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetItemID2], id, 2).valueU16;
}

void initRequestItemSetItemID3(const CBdatWrapper &wrapper) { s_members[RequestItemSetItemID3] = Bdat::getMember(wrapper.data, "ItemID3"); }

u32 getRequestItemSetItemID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetItemID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetItemID3], id, 2).valueU16;
}

void initRequestItemSetItemID4(const CBdatWrapper &wrapper) { s_members[RequestItemSetItemID4] = Bdat::getMember(wrapper.data, "ItemID4"); }

u32 getRequestItemSetItemID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetItemID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetItemID4], id, 2).valueU16;
}

void initRequestItemSetItemID5(const CBdatWrapper &wrapper) { s_members[RequestItemSetItemID5] = Bdat::getMember(wrapper.data, "ItemID5"); }

u32 getRequestItemSetItemID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetItemID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetItemID5], id, 2).valueU16;
}

void initRequestItemSetCount1(const CBdatWrapper &wrapper) { s_members[RequestItemSetCount1] = Bdat::getMember(wrapper.data, "Count1"); }

u32 getRequestItemSetCount1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetCount1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetCount1], id, 1).valueU8;
}

void initRequestItemSetCount2(const CBdatWrapper &wrapper) { s_members[RequestItemSetCount2] = Bdat::getMember(wrapper.data, "Count2"); }

u32 getRequestItemSetCount2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetCount2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetCount2], id, 1).valueU8;
}

void initRequestItemSetCount3(const CBdatWrapper &wrapper) { s_members[RequestItemSetCount3] = Bdat::getMember(wrapper.data, "Count3"); }

u32 getRequestItemSetCount3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetCount3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetCount3], id, 1).valueU8;
}

void initRequestItemSetCount4(const CBdatWrapper &wrapper) { s_members[RequestItemSetCount4] = Bdat::getMember(wrapper.data, "Count4"); }

u32 getRequestItemSetCount4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetCount4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetCount4], id, 1).valueU8;
}

void initRequestItemSetCount5(const CBdatWrapper &wrapper) { s_members[RequestItemSetCount5] = Bdat::getMember(wrapper.data, "Count5"); }

u32 getRequestItemSetCount5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetCount5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetCount5], id, 1).valueU8;
}

void initRequestItemSetMapID(const CBdatWrapper &wrapper) { s_members[RequestItemSetMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getRequestItemSetMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetMapID], id, 2).valueU16;
}

void initRequestItemSetNpcID(const CBdatWrapper &wrapper) { s_members[RequestItemSetNpcID] = Bdat::getMember(wrapper.data, "NpcID"); }

u32 getRequestItemSetNpcID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestItemSetNpcID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestItemSetNpcID], id, 2).valueU16;
}

void initCollectItemID(const CBdatWrapper &wrapper) { s_members[CollectItemID] = Bdat::getMember(wrapper.data, "ItemID"); }

u32 getCollectItemID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectItemID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectItemID], id, 2).valueU16;
}

void initCollectCategory(const CBdatWrapper &wrapper) { s_members[CollectCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getCollectCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectCategory], id, 1).valueU8;
}

void initCollectCount(const CBdatWrapper &wrapper) { s_members[CollectCount] = Bdat::getMember(wrapper.data, "Count"); }

u32 getCollectCount(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectCount] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectCount], id, 1).valueU8;
}

void initCollectDeduct(const CBdatWrapper &wrapper) { s_members[CollectDeduct] = Bdat::getMember(wrapper.data, "Deduct"); }

u32 getCollectDeduct(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectDeduct] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectDeduct], id, 1).valueU8;
}

void initCollectTresureID(const CBdatWrapper &wrapper) { s_members[CollectTresureID] = Bdat::getMember(wrapper.data, "TresureID"); }

u32 getCollectTresureID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectTresureID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectTresureID], id, 2).valueU16;
}

void initCollectEnemyID(const CBdatWrapper &wrapper) { s_members[CollectEnemyID] = Bdat::getMember(wrapper.data, "EnemyID"); }

u32 getCollectEnemyID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectEnemyID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectEnemyID], id, 2).valueU16;
}

void initCollectMapID(const CBdatWrapper &wrapper) { s_members[CollectMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getCollectMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectMapID], id, 2).valueU16;
}

void initCollectNpcID(const CBdatWrapper &wrapper) { s_members[CollectNpcID] = Bdat::getMember(wrapper.data, "NpcID"); }

u32 getCollectNpcID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[CollectNpcID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[CollectNpcID], id, 2).valueU16;
}

void initUseItemID(const CBdatWrapper &wrapper) { s_members[UseItemID] = Bdat::getMember(wrapper.data, "ItemID"); }

u32 getUseItemID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[UseItemID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[UseItemID], id, 2).valueU16;
}

void initUseCategory(const CBdatWrapper &wrapper) { s_members[UseCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getUseCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[UseCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[UseCategory], id, 1).valueU8;
}

void initUseItemNumber(const CBdatWrapper &wrapper) { s_members[UseItemNumber] = Bdat::getMember(wrapper.data, "ItemNumber"); }

u32 getUseItemNumber(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[UseItemNumber] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[UseItemNumber], id, 1).valueU8;
}

void initUsePartyInPC(const CBdatWrapper &wrapper) { s_members[UsePartyInPC] = Bdat::getMember(wrapper.data, "PartyInPC"); }

u32 getUsePartyInPC(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[UsePartyInPC] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[UsePartyInPC], id, 2).valueU16;
}

void initUsebladeID(const CBdatWrapper &wrapper) { s_members[UsebladeID] = Bdat::getMember(wrapper.data, "bladeID"); }

u32 getUsebladeID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[UsebladeID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[UsebladeID], id, 2).valueU16;
}

void initReachCategory(const CBdatWrapper &wrapper) { s_members[ReachCategory] = Bdat::getMember(wrapper.data, "Category"); }

u32 getReachCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ReachCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ReachCategory], id, 1).valueU8;
}

void initReachMapID(const CBdatWrapper &wrapper) { s_members[ReachMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getReachMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ReachMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ReachMapID], id, 2).valueU16;
}

void initReachPlaceID(const CBdatWrapper &wrapper) { s_members[ReachPlaceID] = Bdat::getMember(wrapper.data, "PlaceID"); }

u32 getReachPlaceID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ReachPlaceID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ReachPlaceID], id, 2).valueU16;
}

void initTalkMapID(const CBdatWrapper &wrapper) { s_members[TalkMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getTalkMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TalkMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TalkMapID], id, 2).valueU16;
}

void initTalkNpcID(const CBdatWrapper &wrapper) { s_members[TalkNpcID] = Bdat::getMember(wrapper.data, "NpcID"); }

u32 getTalkNpcID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TalkNpcID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TalkNpcID], id, 2).valueU16;
}

void initTalkDummyGroup(const CBdatWrapper &wrapper) { s_members[TalkDummyGroup] = Bdat::getMember(wrapper.data, "DummyGroup"); }

u32 getTalkDummyGroup(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TalkDummyGroup] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TalkDummyGroup], id, 2).valueU16;
}

void initDummyGroupNpcID1(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID1] = Bdat::getMember(wrapper.data, "NpcID1"); }

u32 getDummyGroupNpcID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID1], id, 2).valueU16;
}

void initDummyGroupNpcID2(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID2] = Bdat::getMember(wrapper.data, "NpcID2"); }

u32 getDummyGroupNpcID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID2], id, 2).valueU16;
}

void initDummyGroupNpcID3(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID3] = Bdat::getMember(wrapper.data, "NpcID3"); }

u32 getDummyGroupNpcID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID3], id, 2).valueU16;
}

void initDummyGroupNpcID4(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID4] = Bdat::getMember(wrapper.data, "NpcID4"); }

u32 getDummyGroupNpcID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID4], id, 2).valueU16;
}

void initDummyGroupNpcID5(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID5] = Bdat::getMember(wrapper.data, "NpcID5"); }

u32 getDummyGroupNpcID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID5], id, 2).valueU16;
}

void initDummyGroupNpcID6(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID6] = Bdat::getMember(wrapper.data, "NpcID6"); }

u32 getDummyGroupNpcID6(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID6] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID6], id, 2).valueU16;
}

void initDummyGroupNpcID7(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID7] = Bdat::getMember(wrapper.data, "NpcID7"); }

u32 getDummyGroupNpcID7(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID7] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID7], id, 2).valueU16;
}

void initDummyGroupNpcID8(const CBdatWrapper &wrapper) { s_members[DummyGroupNpcID8] = Bdat::getMember(wrapper.data, "NpcID8"); }

u32 getDummyGroupNpcID8(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[DummyGroupNpcID8] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[DummyGroupNpcID8], id, 2).valueU16;
}

void initGimmickMapID(const CBdatWrapper &wrapper) { s_members[GimmickMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getGimmickMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickMapID], id, 2).valueU16;
}

void initGimmickDoorGimmickID(const CBdatWrapper &wrapper) { s_members[GimmickDoorGimmickID] = Bdat::getMember(wrapper.data, "DoorGimmickID"); }

u32 getGimmickDoorGimmickID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickDoorGimmickID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickDoorGimmickID], id, 2).valueU16;
}

void initGimmickElevatorGimmickID(const CBdatWrapper &wrapper) {
  s_members[GimmickElevatorGimmickID] = Bdat::getMember(wrapper.data, "ElevatorGimmickID");
}

u32 getGimmickElevatorGimmickID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickElevatorGimmickID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickElevatorGimmickID], id, 2).valueU16;
}

void initGimmickJumpGimmickID(const CBdatWrapper &wrapper) { s_members[GimmickJumpGimmickID] = Bdat::getMember(wrapper.data, "JumpGimmickID"); }

u32 getGimmickJumpGimmickID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickJumpGimmickID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickJumpGimmickID], id, 2).valueU16;
}

void initGimmickMapGimmickID(const CBdatWrapper &wrapper) { s_members[GimmickMapGimmickID] = Bdat::getMember(wrapper.data, "MapGimmickID"); }

u32 getGimmickMapGimmickID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickMapGimmickID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickMapGimmickID], id, 2).valueU16;
}

void initGimmickMapGmkIconOff(const CBdatWrapper &wrapper) { s_members[GimmickMapGmkIconOff] = Bdat::getMember(wrapper.data, "MapGmkIconOff"); }

u32 getGimmickMapGmkIconOff(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickMapGmkIconOff] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickMapGmkIconOff], id, 1).valueU8;
}

void initGimmickWarpGimmickID(const CBdatWrapper &wrapper) { s_members[GimmickWarpGimmickID] = Bdat::getMember(wrapper.data, "WarpGimmickID"); }

u32 getGimmickWarpGimmickID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickWarpGimmickID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickWarpGimmickID], id, 2).valueU16;
}

void initGimmickSalvagePointID(const CBdatWrapper &wrapper) { s_members[GimmickSalvagePointID] = Bdat::getMember(wrapper.data, "SalvagePointID"); }

u32 getGimmickSalvagePointID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickSalvagePointID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickSalvagePointID], id, 2).valueU16;
}

void initGimmickTboxPopID(const CBdatWrapper &wrapper) { s_members[GimmickTboxPopID] = Bdat::getMember(wrapper.data, "TboxPopID"); }

u32 getGimmickTboxPopID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickTboxPopID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickTboxPopID], id, 2).valueU16;
}

void initGimmickEndCheck(const CBdatWrapper &wrapper) { s_members[GimmickEndCheck] = Bdat::getMember(wrapper.data, "EndCheck"); }

u32 getGimmickEndCheck(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[GimmickEndCheck] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[GimmickEndCheck], id, 1).valueU8;
}

void initFieldSkillCountFieldSkillID(const CBdatWrapper &wrapper) {
  s_members[FieldSkillCountFieldSkillID] = Bdat::getMember(wrapper.data, "FieldSkillID");
}

u32 getFieldSkillCountFieldSkillID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FieldSkillCountFieldSkillID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FieldSkillCountFieldSkillID], id, 1).valueU8;
}

void initFieldSkillCountCount(const CBdatWrapper &wrapper) { s_members[FieldSkillCountCount] = Bdat::getMember(wrapper.data, "Count"); }

u32 getFieldSkillCountCount(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FieldSkillCountCount] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FieldSkillCountCount], id, 2).valueU16;
}

void initRequestBladeRequestCategory(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestCategory] = Bdat::getMember(wrapper.data, "RequestCategory");
}

u32 getRequestBladeRequestCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestCategory], id, 1).valueU8;
}

void initRequestBladeRequestAtr(const CBdatWrapper &wrapper) { s_members[RequestBladeRequestAtr] = Bdat::getMember(wrapper.data, "RequestAtr"); }

u32 getRequestBladeRequestAtr(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestAtr] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestAtr], id, 1).valueU8;
}

void initRequestBladeRequestPerformance(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestPerformance] = Bdat::getMember(wrapper.data, "RequestPerformance");
}

u32 getRequestBladeRequestPerformance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestPerformance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestPerformance], id, 2).valueU16;
}

void initRequestBladeRequestRace(const CBdatWrapper &wrapper) { s_members[RequestBladeRequestRace] = Bdat::getMember(wrapper.data, "RequestRace"); }

u32 getRequestBladeRequestRace(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestRace] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestRace], id, 2).valueU16;
}

void initRequestBladeRequestGender(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestGender] = Bdat::getMember(wrapper.data, "RequestGender");
}

u32 getRequestBladeRequestGender(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestGender] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestGender], id, 2).valueU16;
}

void initRequestBladeRequestArts(const CBdatWrapper &wrapper) { s_members[RequestBladeRequestArts] = Bdat::getMember(wrapper.data, "RequestArts"); }

u32 getRequestBladeRequestArts(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestArts] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestArts], id, 2).valueU16;
}

void initRequestBladeRequestArtsLevel(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestArtsLevel] = Bdat::getMember(wrapper.data, "RequestArtsLevel");
}

u32 getRequestBladeRequestArtsLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestArtsLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestArtsLevel], id, 1).valueU8;
}

void initRequestBladeRequestFSkill(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestFSkill] = Bdat::getMember(wrapper.data, "RequestFSkill");
}

u32 getRequestBladeRequestFSkill(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestFSkill] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestFSkill], id, 2).valueU16;
}

void initRequestBladeRequestFSLevel(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestFSLevel] = Bdat::getMember(wrapper.data, "RequestFSLevel");
}

u32 getRequestBladeRequestFSLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestFSLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestFSLevel], id, 1).valueU8;
}

void initRequestBladeRequestNumber(const CBdatWrapper &wrapper) {
  s_members[RequestBladeRequestNumber] = Bdat::getMember(wrapper.data, "RequestNumber");
}

u32 getRequestBladeRequestNumber(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RequestBladeRequestNumber] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RequestBladeRequestNumber], id, 1).valueU8;
}

void initConditionConditionID(const CBdatWrapper &wrapper) { s_members[ConditionConditionID] = Bdat::getMember(wrapper.data, "ConditionID"); }

u32 getConditionConditionID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionConditionID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionConditionID], id, 2).valueU16;
}

void initConditionMapID(const CBdatWrapper &wrapper) { s_members[ConditionMapID] = Bdat::getMember(wrapper.data, "MapID"); }

u32 getConditionMapID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionMapID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionMapID], id, 2).valueU16;
}

void initConditionNpcID(const CBdatWrapper &wrapper) { s_members[ConditionNpcID] = Bdat::getMember(wrapper.data, "NpcID"); }

u32 getConditionNpcID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ConditionNpcID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ConditionNpcID], id, 2).valueU16;
}

void initAchievementStatsID(const CBdatWrapper &wrapper) { s_members[AchievementStatsID] = Bdat::getMember(wrapper.data, "StatsID"); }

u32 getAchievementStatsID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[AchievementStatsID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[AchievementStatsID], id, 2).valueU16;
}

void initAchievementCount(const CBdatWrapper &wrapper) { s_members[AchievementCount] = Bdat::getMember(wrapper.data, "Count"); }

u32 getAchievementCount(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[AchievementCount] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[AchievementCount], id, 3).valueU32;
}

void initAchievementDebugName(const CBdatWrapper &wrapper) { s_members[AchievementDebugName] = Bdat::getMember(wrapper.data, "DebugName"); }

const char *getAchievementDebugName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[AchievementDebugName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return nullptr;
  }

  return wrapper.getValCheck(s_members[AchievementDebugName], id, 7).valueString;
}

void initHintsMainChar1(const CBdatWrapper &wrapper) { s_members[HintsMainChar1] = Bdat::getMember(wrapper.data, "MainChar1"); }

u32 getHintsMainChar1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsMainChar1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsMainChar1], id, 2).valueU16;
}

void initHintsMainChar2(const CBdatWrapper &wrapper) { s_members[HintsMainChar2] = Bdat::getMember(wrapper.data, "MainChar2"); }

u32 getHintsMainChar2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsMainChar2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsMainChar2], id, 2).valueU16;
}

void initHintsMainChar3(const CBdatWrapper &wrapper) { s_members[HintsMainChar3] = Bdat::getMember(wrapper.data, "MainChar3"); }

u32 getHintsMainChar3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsMainChar3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsMainChar3], id, 2).valueU16;
}

void initHintsMainChar4(const CBdatWrapper &wrapper) { s_members[HintsMainChar4] = Bdat::getMember(wrapper.data, "MainChar4"); }

u32 getHintsMainChar4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsMainChar4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsMainChar4], id, 2).valueU16;
}

void initHintsFSkillID1(const CBdatWrapper &wrapper) { s_members[HintsFSkillID1] = Bdat::getMember(wrapper.data, "FSkillID1"); }

u32 getHintsFSkillID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsFSkillID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsFSkillID1], id, 2).valueU16;
}

void initHintsFSkillID2(const CBdatWrapper &wrapper) { s_members[HintsFSkillID2] = Bdat::getMember(wrapper.data, "FSkillID2"); }

u32 getHintsFSkillID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsFSkillID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsFSkillID2], id, 2).valueU16;
}

void initHintsFSkillID3(const CBdatWrapper &wrapper) { s_members[HintsFSkillID3] = Bdat::getMember(wrapper.data, "FSkillID3"); }

u32 getHintsFSkillID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsFSkillID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsFSkillID3], id, 2).valueU16;
}

void initHintsClientNpc(const CBdatWrapper &wrapper) { s_members[HintsClientNpc] = Bdat::getMember(wrapper.data, "ClientNpc"); }

u32 getHintsClientNpc(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsClientNpc] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsClientNpc], id, 2).valueU16;
}

void initHintsZoneID(const CBdatWrapper &wrapper) { s_members[HintsZoneID] = Bdat::getMember(wrapper.data, "ZoneID"); }

u32 getHintsZoneID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[HintsZoneID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[HintsZoneID], id, 2).valueU16;
}

void initEventEventID(const CBdatWrapper &wrapper) { s_members[EventEventID] = Bdat::getMember(wrapper.data, "EventID"); }

u32 getEventEventID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[EventEventID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[EventEventID], id, 2).valueU16;
}

void initRewardGold(const CBdatWrapper &wrapper) { s_members[RewardGold] = Bdat::getMember(wrapper.data, "Gold"); }

u32 getRewardGold(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardGold] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardGold], id, 3).valueU32;
}

void initRewardEXP(const CBdatWrapper &wrapper) { s_members[RewardEXP] = Bdat::getMember(wrapper.data, "EXP"); }

u32 getRewardEXP(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardEXP] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardEXP], id, 3).valueU32;
}

void initRewardSp(const CBdatWrapper &wrapper) { s_members[RewardSp] = Bdat::getMember(wrapper.data, "Sp"); }

u32 getRewardSp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardSp] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardSp], id, 2).valueU16;
}

void initRewardCoin(const CBdatWrapper &wrapper) { s_members[RewardCoin] = Bdat::getMember(wrapper.data, "Coin"); }

u32 getRewardCoin(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardCoin] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardCoin], id, 2).valueU16;
}

void initRewardDevelopZone(const CBdatWrapper &wrapper) { s_members[RewardDevelopZone] = Bdat::getMember(wrapper.data, "DevelopZone"); }

u32 getRewardDevelopZone(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardDevelopZone] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardDevelopZone], id, 1).valueU8;
}

void initRewardDevelopPoint(const CBdatWrapper &wrapper) { s_members[RewardDevelopPoint] = Bdat::getMember(wrapper.data, "DevelopPoint"); }

u32 getRewardDevelopPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardDevelopPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardDevelopPoint], id, 2).valueU16;
}

void initRewardTrustPoint(const CBdatWrapper &wrapper) { s_members[RewardTrustPoint] = Bdat::getMember(wrapper.data, "TrustPoint"); }

u32 getRewardTrustPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardTrustPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardTrustPoint], id, 2).valueU16;
}

void initRewardMercenariesPoint(const CBdatWrapper &wrapper) {
  s_members[RewardMercenariesPoint] = Bdat::getMember(wrapper.data, "MercenariesPoint");
}

u32 getRewardMercenariesPoint(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardMercenariesPoint] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardMercenariesPoint], id, 2).valueU16;
}

void initRewardIdeaCategory(const CBdatWrapper &wrapper) { s_members[RewardIdeaCategory] = Bdat::getMember(wrapper.data, "IdeaCategory"); }

u32 getRewardIdeaCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardIdeaCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardIdeaCategory], id, 1).valueU8;
}

void initRewardIdeaValue(const CBdatWrapper &wrapper) { s_members[RewardIdeaValue] = Bdat::getMember(wrapper.data, "IdeaValue"); }

u32 getRewardIdeaValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardIdeaValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardIdeaValue], id, 2).valueU16;
}

void initRewardItemID1(const CBdatWrapper &wrapper) { s_members[RewardItemID1] = Bdat::getMember(wrapper.data, "ItemID1"); }

u32 getRewardItemID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemID1], id, 2).valueU16;
}

void initRewardItemNumber1(const CBdatWrapper &wrapper) { s_members[RewardItemNumber1] = Bdat::getMember(wrapper.data, "ItemNumber1"); }

u32 getRewardItemNumber1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemNumber1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemNumber1], id, 1).valueU8;
}

void initRewardItemID2(const CBdatWrapper &wrapper) { s_members[RewardItemID2] = Bdat::getMember(wrapper.data, "ItemID2"); }

u32 getRewardItemID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemID2], id, 2).valueU16;
}

void initRewardItemNumber2(const CBdatWrapper &wrapper) { s_members[RewardItemNumber2] = Bdat::getMember(wrapper.data, "ItemNumber2"); }

u32 getRewardItemNumber2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemNumber2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemNumber2], id, 1).valueU8;
}

void initRewardItemID3(const CBdatWrapper &wrapper) { s_members[RewardItemID3] = Bdat::getMember(wrapper.data, "ItemID3"); }

u32 getRewardItemID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemID3], id, 2).valueU16;
}

void initRewardItemNumber3(const CBdatWrapper &wrapper) { s_members[RewardItemNumber3] = Bdat::getMember(wrapper.data, "ItemNumber3"); }

u32 getRewardItemNumber3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemNumber3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemNumber3], id, 1).valueU8;
}

void initRewardItemID4(const CBdatWrapper &wrapper) { s_members[RewardItemID4] = Bdat::getMember(wrapper.data, "ItemID4"); }

u32 getRewardItemID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemID4], id, 2).valueU16;
}

void initRewardItemNumber4(const CBdatWrapper &wrapper) { s_members[RewardItemNumber4] = Bdat::getMember(wrapper.data, "ItemNumber4"); }

u32 getRewardItemNumber4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[RewardItemNumber4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[RewardItemNumber4], id, 1).valueU8;
}

void initFLD_AchievementSetCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetCategory] = Bdat::getMember(wrapper.data, "Category");
}

u32 getFLD_AchievementSetCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetCategory], id, 1).valueU8;
}

void initFLD_AchievementSetAbilityLevel(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAbilityLevel] = Bdat::getMember(wrapper.data, "AbilityLevel");
}

u32 getFLD_AchievementSetAbilityLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAbilityLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAbilityLevel], id, 1).valueU8;
}

void initFLD_AchievementSetAchievementID1(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAchievementID1] = Bdat::getMember(wrapper.data, "AchievementID1");
}

u32 getFLD_AchievementSetAchievementID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAchievementID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAchievementID1], id, 2).valueU16;
}

void initFLD_AchievementSetAchievementID2(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAchievementID2] = Bdat::getMember(wrapper.data, "AchievementID2");
}

u32 getFLD_AchievementSetAchievementID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAchievementID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAchievementID2], id, 2).valueU16;
}

void initFLD_AchievementSetAchievementID3(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAchievementID3] = Bdat::getMember(wrapper.data, "AchievementID3");
}

u32 getFLD_AchievementSetAchievementID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAchievementID3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAchievementID3], id, 2).valueU16;
}

void initFLD_AchievementSetAchievementID4(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAchievementID4] = Bdat::getMember(wrapper.data, "AchievementID4");
}

u32 getFLD_AchievementSetAchievementID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAchievementID4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAchievementID4], id, 2).valueU16;
}

void initFLD_AchievementSetAchievementID5(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementSetAchievementID5] = Bdat::getMember(wrapper.data, "AchievementID5");
}

u32 getFLD_AchievementSetAchievementID5(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementSetAchievementID5] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementSetAchievementID5], id, 2).valueU16;
}

void initFLD_AchievementListTitle(const CBdatWrapper &wrapper) { s_members[FLD_AchievementListTitle] = Bdat::getMember(wrapper.data, "Title"); }

u32 getFLD_AchievementListTitle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListTitle] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListTitle], id, 2).valueU16;
}

void initFLD_AchievementListCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListCategory] = Bdat::getMember(wrapper.data, "Category");
}

u32 getFLD_AchievementListCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListCategory], id, 1).valueU8;
}

void initFLD_AchievementListIcon(const CBdatWrapper &wrapper) { s_members[FLD_AchievementListIcon] = Bdat::getMember(wrapper.data, "Icon"); }

u32 getFLD_AchievementListIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListIcon], id, 2).valueU16;
}

void initFLD_AchievementListTask(const CBdatWrapper &wrapper) { s_members[FLD_AchievementListTask] = Bdat::getMember(wrapper.data, "Task"); }

u32 getFLD_AchievementListTask(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListTask] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListTask], id, 2).valueU16;
}

void initFLD_AchievementListVoiceCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListVoiceCategory] = Bdat::getMember(wrapper.data, "VoiceCategory");
}

u32 getFLD_AchievementListVoiceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListVoiceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListVoiceCategory], id, 2).valueU16;
}

void initFLD_AchievementListAfterVoice(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListAfterVoice] = Bdat::getMember(wrapper.data, "AfterVoice");
}

u32 getFLD_AchievementListAfterVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListAfterVoice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListAfterVoice], id, 2).valueU16;
}

void initFLD_AchievementListDifficulty(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListDifficulty] = Bdat::getMember(wrapper.data, "Difficulty");
}

u32 getFLD_AchievementListDifficulty(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListDifficulty] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListDifficulty], id, 1).valueU8;
}

void initFLD_AchievementListIdeaCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListIdeaCategory] = Bdat::getMember(wrapper.data, "IdeaCategory");
}

u32 getFLD_AchievementListIdeaCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListIdeaCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListIdeaCategory], id, 1).valueU8;
}

void initFLD_AchievementListIdeaValue(const CBdatWrapper &wrapper) {
  s_members[FLD_AchievementListIdeaValue] = Bdat::getMember(wrapper.data, "IdeaValue");
}

u32 getFLD_AchievementListIdeaValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_AchievementListIdeaValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_AchievementListIdeaValue], id, 2).valueU16;
}

void initFLD_MercenariesConfigValue(const CBdatWrapper &wrapper) { s_members[FLD_MercenariesConfigValue] = Bdat::getMember(wrapper.data, "Value"); }

u32 getFLD_MercenariesConfigValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesConfigValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesConfigValue], id, 3).valueU32;
}

void initFLD_MercenariesMissionQuestID(const CBdatWrapper &wrapper) {
  s_members[FLD_MercenariesMissionQuestID] = Bdat::getMember(wrapper.data, "QuestID");
}

u32 getFLD_MercenariesMissionQuestID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesMissionQuestID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesMissionQuestID], id, 2).valueU16;
}

void initFLD_MercenariesMissionCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_MercenariesMissionCategory] = Bdat::getMember(wrapper.data, "Category");
}

u32 getFLD_MercenariesMissionCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesMissionCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesMissionCategory], id, 1).valueU8;
}

void initFLD_MercenariesMissionRequestPerformance(const CBdatWrapper &wrapper) {
  s_members[FLD_MercenariesMissionRequestPerformance] = Bdat::getMember(wrapper.data, "RequestPerformance");
}

u32 getFLD_MercenariesMissionRequestPerformance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesMissionRequestPerformance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesMissionRequestPerformance], id, 2).valueU16;
}

void initFLD_MercenariesMissionRepeatable(const CBdatWrapper &wrapper) {
  s_members[FLD_MercenariesMissionRepeatable] = Bdat::getMember(wrapper.data, "Repeatable");
}

u32 getFLD_MercenariesMissionRepeatable(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesMissionRepeatable] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesMissionRepeatable], id, 1).valueU8;
}

void initFLD_MercenariesMissionAutoStart(const CBdatWrapper &wrapper) {
  s_members[FLD_MercenariesMissionAutoStart] = Bdat::getMember(wrapper.data, "AutoStart");
}

u32 getFLD_MercenariesMissionAutoStart(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_MercenariesMissionAutoStart] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_MercenariesMissionAutoStart], id, 2).valueU16;
}

void initFLD_FieldSkillListName(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillListName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getFLD_FieldSkillListName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListName], id, 2).valueU16;
}

void initFLD_FieldSkillListCaption(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillListCaption] = Bdat::getMember(wrapper.data, "Caption"); }

u32 getFLD_FieldSkillListCaption(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListCaption] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListCaption], id, 2).valueU16;
}

void initFLD_FieldSkillListType(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillListType] = Bdat::getMember(wrapper.data, "Type"); }

u32 getFLD_FieldSkillListType(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListType] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListType], id, 1).valueU8;
}

void initFLD_FieldSkillListRandomID(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListRandomID] = Bdat::getMember(wrapper.data, "RandomID");
}

u32 getFLD_FieldSkillListRandomID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListRandomID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListRandomID], id, 2).valueU16;
}

void initFLD_FieldSkillListMinLevel(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListMinLevel] = Bdat::getMember(wrapper.data, "MinLevel");
}

u32 getFLD_FieldSkillListMinLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListMinLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListMinLevel], id, 1).valueU8;
}

void initFLD_FieldSkillListMaxLevel(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListMaxLevel] = Bdat::getMember(wrapper.data, "MaxLevel");
}

u32 getFLD_FieldSkillListMaxLevel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListMaxLevel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListMaxLevel], id, 1).valueU8;
}

void initFLD_FieldSkillListCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListCategory] = Bdat::getMember(wrapper.data, "Category");
}

u32 getFLD_FieldSkillListCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListCategory], id, 1).valueU8;
}

void initFLD_FieldSkillListRarity(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillListRarity] = Bdat::getMember(wrapper.data, "Rarity"); }

u32 getFLD_FieldSkillListRarity(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListRarity] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListRarity], id, 1).valueU8;
}

void initFLD_FieldSkillListIcon(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillListIcon] = Bdat::getMember(wrapper.data, "Icon"); }

u32 getFLD_FieldSkillListIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListIcon], id, 2).valueU16;
}

void initFLD_FieldSkillListVoiceCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListVoiceCategory] = Bdat::getMember(wrapper.data, "VoiceCategory");
}

u32 getFLD_FieldSkillListVoiceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListVoiceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListVoiceCategory], id, 2).valueU16;
}

void initFLD_FieldSkillListAttirbute(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillListAttirbute] = Bdat::getMember(wrapper.data, "Attirbute");
}

u32 getFLD_FieldSkillListAttirbute(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillListAttirbute] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillListAttirbute], id, 1).valueU8;
}

void initFLD_FieldSkillSettingName(const CBdatWrapper &wrapper) { s_members[FLD_FieldSkillSettingName] = Bdat::getMember(wrapper.data, "Name"); }

u32 getFLD_FieldSkillSettingName(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingName] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingName], id, 2).valueU16;
}

void initFLD_FieldSkillSettingFieldSkillID1(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingFieldSkillID1] = Bdat::getMember(wrapper.data, "FieldSkillID1");
}

u32 getFLD_FieldSkillSettingFieldSkillID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingFieldSkillID1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingFieldSkillID1], id, 2).valueU16;
}

void initFLD_FieldSkillSettingFieldSkillLevel1(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingFieldSkillLevel1] = Bdat::getMember(wrapper.data, "FieldSkillLevel1");
}

u32 getFLD_FieldSkillSettingFieldSkillLevel1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingFieldSkillLevel1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingFieldSkillLevel1], id, 1).valueU8;
}

void initFLD_FieldSkillSettingFieldSkillID2(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingFieldSkillID2] = Bdat::getMember(wrapper.data, "FieldSkillID2");
}

u32 getFLD_FieldSkillSettingFieldSkillID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingFieldSkillID2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingFieldSkillID2], id, 2).valueU16;
}

void initFLD_FieldSkillSettingFieldSkillLevel2(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingFieldSkillLevel2] = Bdat::getMember(wrapper.data, "FieldSkillLevel2");
}

u32 getFLD_FieldSkillSettingFieldSkillLevel2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingFieldSkillLevel2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingFieldSkillLevel2], id, 1).valueU8;
}

void initFLD_FieldSkillSettingSuccessVoiceCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingSuccessVoiceCategory] = Bdat::getMember(wrapper.data, "SuccessVoiceCategory");
}

u32 getFLD_FieldSkillSettingSuccessVoiceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingSuccessVoiceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingSuccessVoiceCategory], id, 2).valueU16;
}

void initFLD_FieldSkillSettingMissVoiceCategory(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillSettingMissVoiceCategory] = Bdat::getMember(wrapper.data, "MissVoiceCategory");
}

u32 getFLD_FieldSkillSettingMissVoiceCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillSettingMissVoiceCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillSettingMissVoiceCategory], id, 2).valueU16;
}

void initFLD_FieldSkillRandomLevel1Chance(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillRandomLevel1Chance] = Bdat::getMember(wrapper.data, "Level1Chance");
}

u32 getFLD_FieldSkillRandomLevel1Chance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillRandomLevel1Chance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillRandomLevel1Chance], id, 1).valueU8;
}

void initFLD_FieldSkillRandomLevel2Chance(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillRandomLevel2Chance] = Bdat::getMember(wrapper.data, "Level2Chance");
}

u32 getFLD_FieldSkillRandomLevel2Chance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillRandomLevel2Chance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillRandomLevel2Chance], id, 1).valueU8;
}

void initFLD_FieldSkillRandomLevel3Chance(const CBdatWrapper &wrapper) {
  s_members[FLD_FieldSkillRandomLevel3Chance] = Bdat::getMember(wrapper.data, "Level3Chance");
}

u32 getFLD_FieldSkillRandomLevel3Chance(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_FieldSkillRandomLevel3Chance] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_FieldSkillRandomLevel3Chance], id, 1).valueU8;
}

void initFLD_DevelopmentLevelValue(const CBdatWrapper &wrapper) { s_members[FLD_DevelopmentLevelValue] = Bdat::getMember(wrapper.data, "Value"); }

u32 getFLD_DevelopmentLevelValue(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[FLD_DevelopmentLevelValue] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[FLD_DevelopmentLevelValue], id, 3).valueU32;
}

void initListQuestTitle(const CBdatWrapper &wrapper) { s_members[ListQuestTitle] = Bdat::getMember(wrapper.data, "QuestTitle"); }

u32 getListQuestTitle(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListQuestTitle] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListQuestTitle], id, 2).valueU16;
}

void initListQuestCategory(const CBdatWrapper &wrapper) { s_members[ListQuestCategory] = Bdat::getMember(wrapper.data, "QuestCategory"); }

u32 getListQuestCategory(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListQuestCategory] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListQuestCategory], id, 1).valueU8;
}

void initListVisible(const CBdatWrapper &wrapper) { s_members[ListVisible] = Bdat::getMember(wrapper.data, "Visible"); }

u32 getListVisible(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListVisible] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListVisible], id, 1).valueU8;
}

void initListTalker(const CBdatWrapper &wrapper) { s_members[ListTalker] = Bdat::getMember(wrapper.data, "Talker"); }

u32 getListTalker(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListTalker] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListTalker], id, 2).valueU16;
}

void initListSummary(const CBdatWrapper &wrapper) { s_members[ListSummary] = Bdat::getMember(wrapper.data, "Summary"); }

u32 getListSummary(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListSummary] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListSummary], id, 2).valueU16;
}

void initListResultA(const CBdatWrapper &wrapper) { s_members[ListResultA] = Bdat::getMember(wrapper.data, "ResultA"); }

u32 getListResultA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListResultA] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListResultA], id, 2).valueU16;
}

void initListResultB(const CBdatWrapper &wrapper) { s_members[ListResultB] = Bdat::getMember(wrapper.data, "ResultB"); }

u32 getListResultB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListResultB] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListResultB], id, 2).valueU16;
}

void initListSortNo(const CBdatWrapper &wrapper) { s_members[ListSortNo] = Bdat::getMember(wrapper.data, "SortNo"); }

u32 getListSortNo(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListSortNo] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListSortNo], id, 2).valueU16;
}

void initListRewardDisp(const CBdatWrapper &wrapper) { s_members[ListRewardDisp] = Bdat::getMember(wrapper.data, "RewardDisp"); }

u32 getListRewardDisp(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListRewardDisp] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListRewardDisp], id, 1).valueU8;
}

void initListRewardSetA(const CBdatWrapper &wrapper) { s_members[ListRewardSetA] = Bdat::getMember(wrapper.data, "RewardSetA"); }

u32 getListRewardSetA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListRewardSetA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListRewardSetA], id, 2).valueU16;
}

void initListRewardSetB(const CBdatWrapper &wrapper) { s_members[ListRewardSetB] = Bdat::getMember(wrapper.data, "RewardSetB"); }

u32 getListRewardSetB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListRewardSetB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListRewardSetB], id, 2).valueU16;
}

void initListPRTQuestID(const CBdatWrapper &wrapper) { s_members[ListPRTQuestID] = Bdat::getMember(wrapper.data, "PRTQuestID"); }

u32 getListPRTQuestID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListPRTQuestID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListPRTQuestID], id, 2).valueU16;
}

void initListFlagPRT(const CBdatWrapper &wrapper) { s_members[ListFlagPRT] = Bdat::getMember(wrapper.data, "FlagPRT"); }

u32 getListFlagPRT(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListFlagPRT] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListFlagPRT], id, 2).valueU16;
}

void initListFlagCLD(const CBdatWrapper &wrapper) { s_members[ListFlagCLD] = Bdat::getMember(wrapper.data, "FlagCLD"); }

u32 getListFlagCLD(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListFlagCLD] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListFlagCLD], id, 2).valueU16;
}

void initListPurposeID(const CBdatWrapper &wrapper) { s_members[ListPurposeID] = Bdat::getMember(wrapper.data, "PurposeID"); }

u32 getListPurposeID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListPurposeID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListPurposeID], id, 2).valueU16;
}

void initListCountCancel(const CBdatWrapper &wrapper) { s_members[ListCountCancel] = Bdat::getMember(wrapper.data, "CountCancel"); }

u32 getListCountCancel(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListCountCancel] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListCountCancel], id, 1).valueU8;
}

void initListNextQuestA(const CBdatWrapper &wrapper) { s_members[ListNextQuestA] = Bdat::getMember(wrapper.data, "NextQuestA"); }

u32 getListNextQuestA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListNextQuestA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListNextQuestA], id, 2).valueU16;
}

void initListCallEventA(const CBdatWrapper &wrapper) { s_members[ListCallEventA] = Bdat::getMember(wrapper.data, "CallEventA"); }

u32 getListCallEventA(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListCallEventA] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListCallEventA], id, 2).valueU16;
}

void initListNextQuestB(const CBdatWrapper &wrapper) { s_members[ListNextQuestB] = Bdat::getMember(wrapper.data, "NextQuestB"); }

u32 getListNextQuestB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListNextQuestB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListNextQuestB], id, 2).valueU16;
}

void initListCallEventB(const CBdatWrapper &wrapper) { s_members[ListCallEventB] = Bdat::getMember(wrapper.data, "CallEventB"); }

u32 getListCallEventB(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListCallEventB] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListCallEventB], id, 2).valueU16;
}

void initListHintsID(const CBdatWrapper &wrapper) { s_members[ListHintsID] = Bdat::getMember(wrapper.data, "HintsID"); }

u32 getListHintsID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListHintsID] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListHintsID], id, 2).valueU16;
}

void initListClearVoice(const CBdatWrapper &wrapper) { s_members[ListClearVoice] = Bdat::getMember(wrapper.data, "ClearVoice"); }

u32 getListClearVoice(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListClearVoice] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListClearVoice], id, 2).valueU16;
}

void initListAutoStart(const CBdatWrapper &wrapper) { s_members[ListAutoStart] = Bdat::getMember(wrapper.data, "AutoStart"); }

u32 getListAutoStart(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListAutoStart] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListAutoStart], id, 1).valueU8;
}

void initListItemLost(const CBdatWrapper &wrapper) { s_members[ListItemLost] = Bdat::getMember(wrapper.data, "ItemLost"); }

u32 getListItemLost(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListItemLost] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListItemLost], id, 2).valueU16;
}

void initListCancelCondition(const CBdatWrapper &wrapper) { s_members[ListCancelCondition] = Bdat::getMember(wrapper.data, "CancelCondition"); }

u32 getListCancelCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListCancelCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListCancelCondition], id, 2).valueU16;
}

void initListQuestIcon(const CBdatWrapper &wrapper) { s_members[ListQuestIcon] = Bdat::getMember(wrapper.data, "QuestIcon"); }

u32 getListQuestIcon(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListQuestIcon] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListQuestIcon], id, 2).valueU16;
}

void initListLinkedQuestID(const CBdatWrapper &wrapper) { s_members[ListLinkedQuestID] = Bdat::getMember(wrapper.data, "LinkedQuestID"); }

u32 getListLinkedQuestID(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[ListLinkedQuestID] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[ListLinkedQuestID], id, 2).valueU16;
}

void initTaskPreCondition(const CBdatWrapper &wrapper) { s_members[TaskPreCondition] = Bdat::getMember(wrapper.data, "PreCondition"); }

u32 getTaskPreCondition(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskPreCondition] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskPreCondition], id, 1).valueU8;
}

void initTaskTaskType1(const CBdatWrapper &wrapper) { s_members[TaskTaskType1] = Bdat::getMember(wrapper.data, "TaskType1"); }

u32 getTaskTaskType1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskType1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskType1], id, 1).valueU8;
}

void initTaskTaskType2(const CBdatWrapper &wrapper) { s_members[TaskTaskType2] = Bdat::getMember(wrapper.data, "TaskType2"); }

u32 getTaskTaskType2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskType2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskType2], id, 1).valueU8;
}

void initTaskTaskType3(const CBdatWrapper &wrapper) { s_members[TaskTaskType3] = Bdat::getMember(wrapper.data, "TaskType3"); }

u32 getTaskTaskType3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskType3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskType3], id, 1).valueU8;
}

void initTaskTaskType4(const CBdatWrapper &wrapper) { s_members[TaskTaskType4] = Bdat::getMember(wrapper.data, "TaskType4"); }

u32 getTaskTaskType4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskType4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskType4], id, 1).valueU8;
}

void initTaskTaskID1(const CBdatWrapper &wrapper) { s_members[TaskTaskID1] = Bdat::getMember(wrapper.data, "TaskID1"); }

u32 getTaskTaskID1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskID1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskID1], id, 2).valueU16;
}

void initTaskTaskID2(const CBdatWrapper &wrapper) { s_members[TaskTaskID2] = Bdat::getMember(wrapper.data, "TaskID2"); }

u32 getTaskTaskID2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskID2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskID2], id, 2).valueU16;
}

void initTaskTaskID3(const CBdatWrapper &wrapper) { s_members[TaskTaskID3] = Bdat::getMember(wrapper.data, "TaskID3"); }

u32 getTaskTaskID3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskID3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskID3], id, 2).valueU16;
}

void initTaskTaskID4(const CBdatWrapper &wrapper) { s_members[TaskTaskID4] = Bdat::getMember(wrapper.data, "TaskID4"); }

u32 getTaskTaskID4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskID4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskID4], id, 2).valueU16;
}

void initTaskBranch1(const CBdatWrapper &wrapper) { s_members[TaskBranch1] = Bdat::getMember(wrapper.data, "Branch1"); }

u32 getTaskBranch1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskBranch1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskBranch1], id, 1).valueU8;
}

void initTaskBranch2(const CBdatWrapper &wrapper) { s_members[TaskBranch2] = Bdat::getMember(wrapper.data, "Branch2"); }

u32 getTaskBranch2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskBranch2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskBranch2], id, 1).valueU8;
}

void initTaskBranch3(const CBdatWrapper &wrapper) { s_members[TaskBranch3] = Bdat::getMember(wrapper.data, "Branch3"); }

u32 getTaskBranch3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskBranch3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskBranch3], id, 1).valueU8;
}

void initTaskBranch4(const CBdatWrapper &wrapper) { s_members[TaskBranch4] = Bdat::getMember(wrapper.data, "Branch4"); }

u32 getTaskBranch4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskBranch4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskBranch4], id, 1).valueU8;
}

void initTaskTaskLog1(const CBdatWrapper &wrapper) { s_members[TaskTaskLog1] = Bdat::getMember(wrapper.data, "TaskLog1"); }

u32 getTaskTaskLog1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskLog1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskLog1], id, 2).valueU16;
}

void initTaskTaskLog2(const CBdatWrapper &wrapper) { s_members[TaskTaskLog2] = Bdat::getMember(wrapper.data, "TaskLog2"); }

u32 getTaskTaskLog2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskLog2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskLog2], id, 2).valueU16;
}

void initTaskTaskLog3(const CBdatWrapper &wrapper) { s_members[TaskTaskLog3] = Bdat::getMember(wrapper.data, "TaskLog3"); }

u32 getTaskTaskLog3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskLog3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskLog3], id, 2).valueU16;
}

void initTaskTaskLog4(const CBdatWrapper &wrapper) { s_members[TaskTaskLog4] = Bdat::getMember(wrapper.data, "TaskLog4"); }

u32 getTaskTaskLog4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskLog4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskLog4], id, 2).valueU16;
}

void initTaskTaskUI1(const CBdatWrapper &wrapper) { s_members[TaskTaskUI1] = Bdat::getMember(wrapper.data, "TaskUI1"); }

u32 getTaskTaskUI1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskUI1] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskUI1], id, 1).valueU8;
}

void initTaskTaskUI2(const CBdatWrapper &wrapper) { s_members[TaskTaskUI2] = Bdat::getMember(wrapper.data, "TaskUI2"); }

u32 getTaskTaskUI2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskUI2] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskUI2], id, 1).valueU8;
}

void initTaskTaskUI3(const CBdatWrapper &wrapper) { s_members[TaskTaskUI3] = Bdat::getMember(wrapper.data, "TaskUI3"); }

u32 getTaskTaskUI3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskUI3] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskUI3], id, 1).valueU8;
}

void initTaskTaskUI4(const CBdatWrapper &wrapper) { s_members[TaskTaskUI4] = Bdat::getMember(wrapper.data, "TaskUI4"); }

u32 getTaskTaskUI4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskUI4] == nullptr || id < Bdat::getIdTop(wrapper.data) || id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskUI4], id, 1).valueU8;
}

void initTaskTaskCondition1(const CBdatWrapper &wrapper) { s_members[TaskTaskCondition1] = Bdat::getMember(wrapper.data, "TaskCondition1"); }

u32 getTaskTaskCondition1(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskCondition1] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskCondition1], id, 2).valueU16;
}

void initTaskTaskCondition2(const CBdatWrapper &wrapper) { s_members[TaskTaskCondition2] = Bdat::getMember(wrapper.data, "TaskCondition2"); }

u32 getTaskTaskCondition2(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskCondition2] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskCondition2], id, 2).valueU16;
}

void initTaskTaskCondition3(const CBdatWrapper &wrapper) { s_members[TaskTaskCondition3] = Bdat::getMember(wrapper.data, "TaskCondition3"); }

u32 getTaskTaskCondition3(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskCondition3] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskCondition3], id, 2).valueU16;
}

void initTaskTaskCondition4(const CBdatWrapper &wrapper) { s_members[TaskTaskCondition4] = Bdat::getMember(wrapper.data, "TaskCondition4"); }

u32 getTaskTaskCondition4(const CBdatWrapper &wrapper, u32 id) {
  if (s_members[TaskTaskCondition4] == nullptr || id < Bdat::getIdTop(wrapper.data) ||
      id >= Bdat::getIdTop(wrapper.data) + Bdat::getIdCount(wrapper.data)) {
    return 0;
  }

  return wrapper.getValCheck(s_members[TaskTaskCondition4], id, 2).valueU16;
}

} // namespace _gfbqa

} // namespace gf
