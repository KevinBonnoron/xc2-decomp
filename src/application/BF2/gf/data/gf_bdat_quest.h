#pragma once
#include "gf/data/gf_bdat_wrapper.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct QuestTaskParam;
class QuestListAcc;

enum QTYPE {
  QTYPE_NONE,
  QTYPE_MAIN,
  QTYPE_BLADE,
  QTYPE_NORMAL,
  QTYPE_UNUSED,
  QTYPE_MERCENARIES,
  QTYPE_ACHIEVEMENT,
};

constexpr u32 QTYPE_COUNT = 6;
constexpr u32 QUEST_ID_COUNT = 16000;
constexpr u32 QUEST_TASK_COUNT = 4;

struct QIDXINFO {
  QIDXINFO(QuestID quest) : purpose(0), quest(quest) {}
  QIDXINFO(u32 purpose) : purpose(purpose), quest() {}

  u32 index;
  u32 categoryBegin;
  QTYPE category;
  u32 purpose;
  QuestID quest;
};

static_assert(sizeof(QIDXINFO) == 0x14, "");

template <size_t N> struct QuestCategory {
  CBdatWrapper *getFp(u32 index) const { return index >= secondBegin ? secondFp : fp; }

  void clear() {
    begin = 0;
    end = 0;
    secondFp = nullptr;
    fp = nullptr;
    secondBegin = 0xffff;
    ids.clear();
  }

  mm::mtl::FixedVector<u16, N> ids;
  CBdatWrapper *fp;
  CBdatWrapper *secondFp;
  u16 begin;
  u16 end;
  u16 secondBegin;
};

typedef QuestCategory<0x1fa0> QuestListCategory;
typedef QuestCategory<0x1000> QuestTaskCategory;

static_assert(sizeof(QuestListCategory) == 0x3f60, "");
static_assert(sizeof(QuestTaskCategory) == 0x2020, "");

struct QuestIndexTable {
  u32 indices[QUEST_ID_COUNT];
  u32 count;
};

class qlist_iterator {
public:
  qlist_iterator(QTYPE type);

  QuestID getQuestID() const;
  qlist_iterator operator++();
  bool operator!=(const qlist_iterator &other) const { return index != other.index; }

  QuestListAcc *questListAcc;
  QTYPE type;
  s32 index;
  const QuestListCategory *category;
};

class tlist_iterator {
public:
  tlist_iterator(QTYPE type);

  tlist_iterator operator++();
  u16 getPurposeID() const;
  bool operator!=(const tlist_iterator &other) const { return index != other.index; }

  QuestListAcc *questListAcc;
  QTYPE type;
  s32 index;
  const QuestTaskCategory *category;
};

class QuestListAcc {
public:
  u32 getListQuestTitle(QuestID quest) const;
  CBdatWrapper *getFp(QuestID &quest) const;
  u32 getListQuestCategory(QuestID quest) const;
  u32 getListVisible(QuestID quest) const;
  u32 getListTalker(QuestID quest) const;
  u32 getListSummary(QuestID quest) const;
  u32 getListResultA(QuestID quest) const;
  u32 getListResultB(QuestID quest) const;
  u32 getListSortNo(QuestID quest) const;
  u32 getListRewardDisp(QuestID quest) const;
  u32 getListRewardSetA(QuestID quest) const;
  u32 getListRewardSetB(QuestID quest) const;
  u32 getListPRTQuestID(QuestID quest) const;
  u32 getListFlagPRT(QuestID quest) const;
  u32 getListFlagCLD(QuestID quest) const;
  u32 getListPurposeID(QuestID quest) const;
  u32 getListCountCancel(QuestID quest) const;
  u32 getListNextQuestA(QuestID quest) const;
  u32 getListCallEventA(QuestID quest) const;
  u32 getListNextQuestB(QuestID quest) const;
  u32 getListCallEventB(QuestID quest) const;
  u32 getListHintsID(QuestID quest) const;
  u32 getListClearVoice(QuestID quest) const;
  u32 getListAutoStart(QuestID quest) const;
  u32 getListItemLost(QuestID quest) const;
  u32 getListCancelCondition(QuestID quest) const;
  u32 getListQuestIcon(QuestID quest) const;
  u32 getListLinkedQuestID(QuestID quest) const;
  u32 getTaskPreCondition(u32 purpose) const;
  CBdatWrapper *getTaskFp(u32 purpose) const;
  u32 getTaskTaskType1(u32 purpose) const;
  u32 getTaskTaskType2(u32 purpose) const;
  u32 getTaskTaskType3(u32 purpose) const;
  u32 getTaskTaskType4(u32 purpose) const;
  u32 getTaskTaskID1(u32 purpose) const;
  u32 getTaskTaskID2(u32 purpose) const;
  u32 getTaskTaskID3(u32 purpose) const;
  u32 getTaskTaskID4(u32 purpose) const;
  u32 getTaskBranch1(u32 purpose) const;
  u32 getTaskBranch2(u32 purpose) const;
  u32 getTaskBranch3(u32 purpose) const;
  u32 getTaskBranch4(u32 purpose) const;
  u32 getTaskTaskLog1(u32 purpose) const;
  u32 getTaskTaskLog2(u32 purpose) const;
  u32 getTaskTaskLog3(u32 purpose) const;
  u32 getTaskTaskLog4(u32 purpose) const;
  u32 getTaskTaskUI1(u32 purpose) const;
  u32 getTaskTaskUI2(u32 purpose) const;
  u32 getTaskTaskUI3(u32 purpose) const;
  u32 getTaskTaskUI4(u32 purpose) const;
  u32 getTaskTaskCondition1(u32 purpose) const;
  u32 getTaskTaskCondition2(u32 purpose) const;
  u32 getTaskTaskCondition3(u32 purpose) const;
  u32 getTaskTaskCondition4(u32 purpose) const;
  u32 getTaskTaskID(u32 purpose, u32 index) const;
  u32 getTaskTaskUI(u32 purpose, u32 index) const;
  u32 getTaskTaskType(u32 purpose, u32 index) const;
  u32 getTaskTaskBranch(u32 purpose, u32 index) const;
  u32 getTaskTaskLog(u32 purpose, u32 index) const;
  u32 getTaskTaskCondition(u32 purpose, u32 index) const;
  u32 getBattleStart() const;
  u32 getBattleEnd() const;
  u32 getBattleRefer(u32 id) const;
  u32 getBattleEnemyID(u32 id) const;
  u32 getBattleEnemyGroupID(u32 id) const;
  u32 getBattleEnemySpeciesID(u32 id) const;
  u32 getBattleCount(u32 id) const;
  u32 getBattleCountFlag(u32 id) const;
  u32 getBattleDeadAll(u32 id) const;
  u32 getBattleTimeCount(u32 id) const;
  u32 getBattleTimeCountFlag(u32 id) const;
  u32 getBattleReduceEnemyHP(u32 id) const;
  u32 getBattleReducePCHP(u32 id) const;
  u32 getRequestItemSetStart() const;
  u32 getRequestItemSetEnd() const;
  u32 getRequestItemSetItemID1(u32 id) const;
  u32 getRequestItemSetItemID2(u32 id) const;
  u32 getRequestItemSetItemID3(u32 id) const;
  u32 getRequestItemSetItemID4(u32 id) const;
  u32 getRequestItemSetItemID5(u32 id) const;
  u32 getRequestItemSetCount1(u32 id) const;
  u32 getRequestItemSetCount2(u32 id) const;
  u32 getRequestItemSetCount3(u32 id) const;
  u32 getRequestItemSetCount4(u32 id) const;
  u32 getRequestItemSetCount5(u32 id) const;
  u32 getRequestItemSetMapID(u32 id) const;
  u32 getRequestItemSetNpcID(u32 id) const;
  u32 getRequestItemSetItemID(u32 id, u32 index) const;
  u32 getRequestItemSetCount(u32 id, u32 index) const;
  u32 getCollectStart() const;
  u32 getCollectEnd() const;
  u32 getCollectItemID(u32 id) const;
  u32 getCollectCategory(u32 id) const;
  u32 getCollectCount(u32 id) const;
  u32 getCollectDeduct(u32 id) const;
  u32 getCollectTresureID(u32 id) const;
  u32 getCollectEnemyID(u32 id) const;
  u32 getCollectMapID(u32 id) const;
  u32 getCollectNpcID(u32 id) const;
  u32 getUseStart() const;
  u32 getUseEnd() const;
  u32 getUseItemID(u32 id) const;
  u32 getUseCategory(u32 id) const;
  u32 getUseItemNumber(u32 id) const;
  u32 getUsePartyInPC(u32 id) const;
  u32 getUsebladeID(u32 id) const;
  u32 getReachStart() const;
  u32 getReachEnd() const;
  u32 getReachCategory(u32 id) const;
  u32 getReachMapID(u32 id) const;
  u32 getReachPlaceID(u32 id) const;
  u32 getTalkStart() const;
  u32 getTalkEnd() const;
  u32 getTalkMapID(u32 id) const;
  u32 getTalkNpcID(u32 id) const;
  u32 getTalkDummyGroup(u32 id) const;
  u32 getDummyGroupStart() const;
  u32 getDummyGroupEnd() const;
  u32 getDummyGroupNpcID1(u32 id) const;
  u32 getDummyGroupNpcID2(u32 id) const;
  u32 getDummyGroupNpcID3(u32 id) const;
  u32 getDummyGroupNpcID4(u32 id) const;
  u32 getDummyGroupNpcID5(u32 id) const;
  u32 getDummyGroupNpcID6(u32 id) const;
  u32 getDummyGroupNpcID7(u32 id) const;
  u32 getDummyGroupNpcID8(u32 id) const;
  u32 getDummyGroupNpcID(u32 id, u32 index) const;
  u32 getGimmickStart() const;
  u32 getGimmickEnd() const;
  u32 getGimmickMapID(u32 id) const;
  u32 getGimmickDoorGimmickID(u32 id) const;
  u32 getGimmickElevatorGimmickID(u32 id) const;
  u32 getGimmickJumpGimmickID(u32 id) const;
  u32 getGimmickMapGimmickID(u32 id) const;
  u32 getGimmickMapGmkIconOff(u32 id) const;
  u32 getGimmickWarpGimmickID(u32 id) const;
  u32 getGimmickSalvagePointID(u32 id) const;
  u32 getGimmickTboxPopID(u32 id) const;
  u32 getGimmickEndCheck(u32 id) const;
  u32 getFieldSkillCountStart() const;
  u32 getFieldSkillCountEnd() const;
  u32 getFieldSkillCountFieldSkillID(u32 id) const;
  u32 getFieldSkillCountCount(u32 id) const;
  u32 getRequestBladeStart() const;
  u32 getRequestBladeEnd() const;
  u32 getRequestBladeRequestCategory(u32 id) const;
  u32 getRequestBladeRequestAtr(u32 id) const;
  u32 getRequestBladeRequestPerformance(u32 id) const;
  u32 getRequestBladeRequestRace(u32 id) const;
  u32 getRequestBladeRequestGender(u32 id) const;
  u32 getRequestBladeRequestArts(u32 id) const;
  u32 getRequestBladeRequestArtsLevel(u32 id) const;
  u32 getRequestBladeRequestFSkill(u32 id) const;
  u32 getRequestBladeRequestFSLevel(u32 id) const;
  u32 getRequestBladeRequestNumber(u32 id) const;
  u32 getConditionStart() const;
  u32 getConditionEnd() const;
  u32 getConditionConditionID(u32 id) const;
  u32 getConditionMapID(u32 id) const;
  u32 getConditionNpcID(u32 id) const;
  u32 getAchievementStart() const;
  u32 getAchievementEnd() const;
  u32 getAchievementStatsID(u32 id) const;
  u32 getAchievementCount(u32 id) const;
  const char *getAchievementDebugName(u32 id) const;
  u32 getHintsStart() const;
  u32 getHintsEnd() const;
  u32 getHintsMainChar1(u32 id) const;
  u32 getHintsMainChar2(u32 id) const;
  u32 getHintsMainChar3(u32 id) const;
  u32 getHintsMainChar4(u32 id) const;
  u32 getHintsFSkillID1(u32 id) const;
  u32 getHintsFSkillID2(u32 id) const;
  u32 getHintsFSkillID3(u32 id) const;
  u32 getHintsClientNpc(u32 id) const;
  u32 getHintsZoneID(u32 id) const;
  u32 getHintsMainChar(u32 id, u32 index) const;
  u32 getHintsFSkillID(u32 id, u32 index) const;
  u32 getEventStart() const;
  u32 getEventEnd() const;
  u32 getEventEventID(u32 id) const;
  u32 getRewardStart() const;
  u32 getRewardEnd() const;
  u32 getRewardGold(u32 id) const;
  u32 getRewardEXP(u32 id) const;
  u32 getRewardSp(u32 id) const;
  u32 getRewardCoin(u32 id) const;
  u32 getRewardDevelopZone(u32 id) const;
  u32 getRewardDevelopPoint(u32 id) const;
  u32 getRewardTrustPoint(u32 id) const;
  u32 getRewardMercenariesPoint(u32 id) const;
  u32 getRewardIdeaCategory(u32 id) const;
  u32 getRewardIdeaValue(u32 id) const;
  u32 getRewardItemID1(u32 id) const;
  u32 getRewardItemNumber1(u32 id) const;
  u32 getRewardItemID2(u32 id) const;
  u32 getRewardItemNumber2(u32 id) const;
  u32 getRewardItemID3(u32 id) const;
  u32 getRewardItemNumber3(u32 id) const;
  u32 getRewardItemID4(u32 id) const;
  u32 getRewardItemNumber4(u32 id) const;
  u32 getRewardItemID(u32 id, u32 index) const;
  u32 getRewardItemNumber(u32 id, u32 index) const;
  u32 getFLD_AchievementSetStart() const;
  u32 getFLD_AchievementSetEnd() const;
  u32 getFLD_AchievementSetCategory(u32 id) const;
  u32 getFLD_AchievementSetAbilityLevel(u32 id) const;
  u32 getFLD_AchievementSetAchievementID1(u32 id) const;
  u32 getFLD_AchievementSetAchievementID2(u32 id) const;
  u32 getFLD_AchievementSetAchievementID3(u32 id) const;
  u32 getFLD_AchievementSetAchievementID4(u32 id) const;
  u32 getFLD_AchievementSetAchievementID5(u32 id) const;
  u32 getFLD_AchievementSetAchievementID(u32 id, u32 index) const;
  u32 getFLD_AchievementListStart() const;
  u32 getFLD_AchievementListEnd() const;
  u32 getFLD_AchievementListTitle(u32 id) const;
  u32 getFLD_AchievementListCategory(u32 id) const;
  u32 getFLD_AchievementListIcon(u32 id) const;
  u32 getFLD_AchievementListTask(u32 id) const;
  u32 getFLD_AchievementListVoiceCategory(u32 id) const;
  u32 getFLD_AchievementListAfterVoice(u32 id) const;
  u32 getFLD_AchievementListDifficulty(u32 id) const;
  u32 getFLD_AchievementListIdeaCategory(u32 id) const;
  u32 getFLD_AchievementListIdeaValue(u32 id) const;
  u32 getFLD_MercenariesConfigStart() const;
  u32 getFLD_MercenariesConfigEnd() const;
  u32 getFLD_MercenariesConfigValue(u32 id) const;
  u32 getFLD_MercenariesMissionStart() const;
  u32 getFLD_MercenariesMissionEnd() const;
  u32 getFLD_MercenariesMissionQuestID(u32 id) const;
  u32 getFLD_MercenariesMissionCategory(u32 id) const;
  u32 getFLD_MercenariesMissionRequestPerformance(u32 id) const;
  u32 getFLD_MercenariesMissionRepeatable(u32 id) const;
  u32 getFLD_MercenariesMissionAutoStart(u32 id) const;
  u32 getFLD_FieldSkillListStart() const;
  u32 getFLD_FieldSkillListEnd() const;
  u32 getFLD_FieldSkillListName(u32 id) const;
  u32 getFLD_FieldSkillListCaption(u32 id) const;
  u32 getFLD_FieldSkillListType(u32 id) const;
  u32 getFLD_FieldSkillListRandomID(u32 id) const;
  u32 getFLD_FieldSkillListMinLevel(u32 id) const;
  u32 getFLD_FieldSkillListMaxLevel(u32 id) const;
  u32 getFLD_FieldSkillListCategory(u32 id) const;
  u32 getFLD_FieldSkillListRarity(u32 id) const;
  u32 getFLD_FieldSkillListIcon(u32 id) const;
  u32 getFLD_FieldSkillListVoiceCategory(u32 id) const;
  u32 getFLD_FieldSkillListAttirbute(u32 id) const;
  u32 getFLD_FieldSkillSettingStart() const;
  u32 getFLD_FieldSkillSettingEnd() const;
  u32 getFLD_FieldSkillSettingName(u32 id) const;
  u32 getFLD_FieldSkillSettingFieldSkillID1(u32 id) const;
  u32 getFLD_FieldSkillSettingFieldSkillLevel1(u32 id) const;
  u32 getFLD_FieldSkillSettingFieldSkillID2(u32 id) const;
  u32 getFLD_FieldSkillSettingFieldSkillLevel2(u32 id) const;
  u32 getFLD_FieldSkillSettingSuccessVoiceCategory(u32 id) const;
  u32 getFLD_FieldSkillSettingMissVoiceCategory(u32 id) const;
  u32 getFLD_FieldSkillSettingFieldSkillID(u32 id, u32 index) const;
  u32 getFLD_FieldSkillSettingFieldSkillLevel(u32 id, u32 index) const;
  u32 getFLD_FieldSkillRandomStart() const;
  u32 getFLD_FieldSkillRandomEnd() const;
  u32 getFLD_FieldSkillRandomLevel1Chance(u32 id) const;
  u32 getFLD_FieldSkillRandomLevel2Chance(u32 id) const;
  u32 getFLD_FieldSkillRandomLevel3Chance(u32 id) const;
  u32 getFLD_FieldSkillRandomLevelChance(u32 id, u32 index) const;
  u32 getFLD_DevelopmentLevelStart() const;
  u32 getFLD_DevelopmentLevelEnd() const;
  u32 getFLD_DevelopmentLevelValue(u32 level) const;

  QuestListAcc();
  void clear();
  ~QuestListAcc();
  static QuestListAcc *get();
  QuestID getQuestID(u32 index) const;
  bool getQuestListByIndex(CBdatWrapper *&fp, u16 &id, u32 index) const;
  u16 getPurposeID(u32 index) const;
  bool getTaskInfoByIndex(CBdatWrapper *&fp, u16 &purpose, u32 index) const;
  void getQuestInfo(QIDXINFO &info) const;
  u32 getQuestListCount(QTYPE type) const;
  const QuestListCategory *getCategory(QTYPE type) const;
  const QuestTaskCategory *getTaskCategory(QTYPE type) const;
  qlist_iterator begin(QTYPE type) const;
  qlist_iterator end(QTYPE type) const;
  tlist_iterator beginTask(QTYPE type) const;
  tlist_iterator endTask(QTYPE type) const;
  void addListCategory(u16 id, u32 type, CBdatWrapper *fp);
  void addTaskCategory(u16 purpose, u32 type, CBdatWrapper *fp);
  void makeQuestTaskInfo();
  u32 getCollectUseFlagIndex(const QuestTaskParam &param) const;
  u32 getCollectUseFlagIndexNewVersion(const QuestTaskParam &param) const;
  u32 getCollectUseFlagIndexOldVersion(const QuestTaskParam &param) const;
  void dispCapacityQuestList();
  void dispCapacityQuestTask();
  void rebuild();
  u32 getQuestIdx(QuestID quest) const;
  u32 getTaskFlag(u32 purpose, u32 taskIndex) const;

private:
  QuestListCategory mListCategories[QTYPE_COUNT];
  QuestIndexTable mListIndices;
  QuestTaskCategory mTaskCategories[QTYPE_COUNT];
  QuestIndexTable mTaskIndices;
  u16 mCollectFlagIndices[QUEST_ID_COUNT * QUEST_TASK_COUNT];
  mm::mtl::FixedVector<u16, 0x400> mCollectFlags;

  friend struct QuestListAccLayout;
};

struct QuestListAccLayout {
  static_assert(offsetof(QuestListAcc, mListIndices) == 0x17c40, "");
  static_assert(offsetof(QuestListAcc, mTaskCategories) == 0x27648, "");
  static_assert(offsetof(QuestListAcc, mTaskIndices) == 0x33708, "");
  static_assert(offsetof(QuestListAcc, mCollectFlagIndices) == 0x4310c, "");
  static_assert(offsetof(QuestListAcc, mCollectFlags) == 0x62510, "");
  static_assert(sizeof(QuestListAcc) == 0x62d18, "");
};

class GfBdatQuest : public mm::mtl::PtrSingleton<GfBdatQuest>, public GfBdatRefresh {
public:
  GfBdatQuest();
  virtual ~GfBdatQuest();
  void destroyFP();
  void createFP();
  void bdatRefresh() override;

private:
  CBdatWrapper *m_FLD_QuestList;
  CBdatWrapper *m_FLD_QuestListNormal;
  CBdatWrapper *m_FLD_QuestListMini;
  CBdatWrapper *m_FLD_QuestListMercenaries;
  CBdatWrapper *m_FLD_QuestListAchievement;
  CBdatWrapper *m_FLD_QuestListBlade;
  CBdatWrapper *m_FLD_QuestCollect;
  CBdatWrapper *m_FLD_QuestTask;
  CBdatWrapper *m_FLD_QuestTaskNormal;
  CBdatWrapper *m_FLD_QuestTaskMini;
  CBdatWrapper *m_FLD_QuestTaskMercenaries;
  CBdatWrapper *m_FLD_QuestTaskAchievement;
  CBdatWrapper *m_FLD_QuestTaskBlade;
  CBdatWrapper *m_FLD_QuestBattle;
  CBdatWrapper *m_FLD_RequestItemSet;
  CBdatWrapper *m_FLD_QuestUse;
  CBdatWrapper *m_FLD_QuestReach;
  CBdatWrapper *m_FLD_QuestTalk;
  CBdatWrapper *m_FLD_QuestTalkDummyGroup;
  CBdatWrapper *m_FLD_QuestGimmick;
  CBdatWrapper *m_FLD_QuestFieldSkillCount;
  CBdatWrapper *m_FLD_RequestBlade;
  CBdatWrapper *m_FLD_QuestCondition;
  CBdatWrapper *m_FLD_QuestHints;
  CBdatWrapper *m_FLD_QuestEvent;
  CBdatWrapper *m_FLD_QuestReward;
  CBdatWrapper *m_FLD_QuestRewardRandom;
  CBdatWrapper *m_FLD_Achievement;
  CBdatWrapper *m_FLD_AchievementSet;
  CBdatWrapper *m_FLD_AchievementList;
  CBdatWrapper *m_FLD_MercenariesConfig;
  CBdatWrapper *m_FLD_MercenariesMission;
  CBdatWrapper *m_FLD_FieldSkillList;
  CBdatWrapper *m_FLD_FieldSkillSetting;
  CBdatWrapper *m_FLD_FieldSkillRandom;
  CBdatWrapper *m_FLD_DevelopmentLevel;
  QuestListAcc *mQuestListAcc;

  friend class GfQuestManager;
  friend class QuestListAcc;
  friend struct GfBdatQuestLayout;
};

struct GfBdatQuestLayout {
  static_assert(offsetof(GfBdatQuest, m_FLD_QuestList) == 0x10, "");
  static_assert(offsetof(GfBdatQuest, m_FLD_QuestBattle) == 0x78, "");
  static_assert(offsetof(GfBdatQuest, m_FLD_QuestEvent) == 0xd0, "");
  static_assert(offsetof(GfBdatQuest, mQuestListAcc) == 0x130, "");
};

} // namespace gf
