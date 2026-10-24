#include "gf/data/gf_bdat_quest.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {

GfBdatQuest::GfBdatQuest()
    : m_FLD_QuestList(nullptr), m_FLD_QuestListNormal(nullptr), m_FLD_QuestListMini(nullptr), m_FLD_QuestListMercenaries(nullptr), m_FLD_QuestListAchievement(nullptr), m_FLD_QuestListBlade(nullptr),
      m_FLD_QuestCollect(nullptr), m_FLD_QuestTask(nullptr), m_FLD_QuestTaskNormal(nullptr), m_FLD_QuestTaskMini(nullptr), m_FLD_QuestTaskMercenaries(nullptr), m_FLD_QuestTaskAchievement(nullptr),
      m_FLD_QuestTaskBlade(nullptr), m_FLD_QuestBattle(nullptr), m_FLD_RequestItemSet(nullptr), m_FLD_QuestUse(nullptr), m_FLD_QuestReach(nullptr), m_FLD_QuestTalk(nullptr),
      m_FLD_QuestTalkDummyGroup(nullptr), m_FLD_QuestGimmick(nullptr), m_FLD_QuestFieldSkillCount(nullptr), m_FLD_RequestBlade(nullptr), m_FLD_QuestCondition(nullptr), m_FLD_QuestHints(nullptr),
      m_FLD_QuestEvent(nullptr), m_FLD_QuestReward(nullptr), m_FLD_QuestRewardRandom(nullptr), m_FLD_Achievement(nullptr), m_FLD_AchievementSet(nullptr), m_FLD_AchievementList(nullptr),
      m_FLD_MercenariesConfig(nullptr), m_FLD_MercenariesMission(nullptr), m_FLD_FieldSkillList(nullptr), m_FLD_FieldSkillSetting(nullptr), m_FLD_FieldSkillRandom(nullptr),
      m_FLD_DevelopmentLevel(nullptr) {
  mQuestListAcc = new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) QuestListAcc();
  bdatRefresh();
}

GfBdatQuest::~GfBdatQuest() {
  if (mQuestListAcc != nullptr) {
    delete mQuestListAcc;
    mQuestListAcc = nullptr;
  }

  destroyFP();
}

void GfBdatQuest::destroyFP() {
  if (m_FLD_QuestList != nullptr) {
    delete m_FLD_QuestList;
    m_FLD_QuestList = nullptr;
  }

  if (m_FLD_QuestListMini != nullptr) {
    delete m_FLD_QuestListMini;
    m_FLD_QuestListMini = nullptr;
  }

  if (m_FLD_QuestListNormal != nullptr) {
    delete m_FLD_QuestListNormal;
    m_FLD_QuestListNormal = nullptr;
  }

  if (m_FLD_QuestListMercenaries != nullptr) {
    delete m_FLD_QuestListMercenaries;
    m_FLD_QuestListMercenaries = nullptr;
  }

  if (m_FLD_QuestListAchievement != nullptr) {
    delete m_FLD_QuestListAchievement;
    m_FLD_QuestListAchievement = nullptr;
  }

  if (m_FLD_QuestListBlade != nullptr) {
    delete m_FLD_QuestListBlade;
    m_FLD_QuestListBlade = nullptr;
  }

  if (m_FLD_QuestCollect != nullptr) {
    delete m_FLD_QuestCollect;
    m_FLD_QuestCollect = nullptr;
  }

  if (m_FLD_QuestTask != nullptr) {
    delete m_FLD_QuestTask;
    m_FLD_QuestTask = nullptr;
  }

  if (m_FLD_QuestTaskNormal != nullptr) {
    delete m_FLD_QuestTaskNormal;
    m_FLD_QuestTaskNormal = nullptr;
  }

  if (m_FLD_QuestTaskMini != nullptr) {
    delete m_FLD_QuestTaskMini;
    m_FLD_QuestTaskMini = nullptr;
  }

  if (m_FLD_QuestTaskMercenaries != nullptr) {
    delete m_FLD_QuestTaskMercenaries;
    m_FLD_QuestTaskMercenaries = nullptr;
  }

  if (m_FLD_QuestTaskAchievement != nullptr) {
    delete m_FLD_QuestTaskAchievement;
    m_FLD_QuestTaskAchievement = nullptr;
  }

  if (m_FLD_QuestTaskBlade != nullptr) {
    delete m_FLD_QuestTaskBlade;
    m_FLD_QuestTaskBlade = nullptr;
  }

  if (m_FLD_QuestBattle != nullptr) {
    delete m_FLD_QuestBattle;
    m_FLD_QuestBattle = nullptr;
  }

  if (m_FLD_RequestItemSet != nullptr) {
    delete m_FLD_RequestItemSet;
    m_FLD_RequestItemSet = nullptr;
  }

  if (m_FLD_RequestBlade != nullptr) {
    delete m_FLD_RequestBlade;
    m_FLD_RequestBlade = nullptr;
  }

  if (m_FLD_QuestUse != nullptr) {
    delete m_FLD_QuestUse;
    m_FLD_QuestUse = nullptr;
  }

  if (m_FLD_QuestReach != nullptr) {
    delete m_FLD_QuestReach;
    m_FLD_QuestReach = nullptr;
  }

  if (m_FLD_QuestTalk != nullptr) {
    delete m_FLD_QuestTalk;
    m_FLD_QuestTalk = nullptr;
  }

  if (m_FLD_QuestTalkDummyGroup != nullptr) {
    delete m_FLD_QuestTalkDummyGroup;
    m_FLD_QuestTalkDummyGroup = nullptr;
  }

  if (m_FLD_QuestGimmick != nullptr) {
    delete m_FLD_QuestGimmick;
    m_FLD_QuestGimmick = nullptr;
  }

  if (m_FLD_QuestFieldSkillCount != nullptr) {
    delete m_FLD_QuestFieldSkillCount;
    m_FLD_QuestFieldSkillCount = nullptr;
  }

  if (m_FLD_QuestHints != nullptr) {
    delete m_FLD_QuestHints;
    m_FLD_QuestHints = nullptr;
  }

  if (m_FLD_QuestCondition != nullptr) {
    delete m_FLD_QuestCondition;
    m_FLD_QuestCondition = nullptr;
  }

  if (m_FLD_QuestEvent != nullptr) {
    delete m_FLD_QuestEvent;
    m_FLD_QuestEvent = nullptr;
  }

  if (m_FLD_QuestReward != nullptr) {
    delete m_FLD_QuestReward;
    m_FLD_QuestReward = nullptr;
  }

  if (m_FLD_QuestRewardRandom != nullptr) {
    delete m_FLD_QuestRewardRandom;
    m_FLD_QuestRewardRandom = nullptr;
  }

  if (m_FLD_Achievement != nullptr) {
    delete m_FLD_Achievement;
    m_FLD_Achievement = nullptr;
  }

  if (m_FLD_AchievementSet != nullptr) {
    delete m_FLD_AchievementSet;
    m_FLD_AchievementSet = nullptr;
  }

  if (m_FLD_AchievementList != nullptr) {
    delete m_FLD_AchievementList;
    m_FLD_AchievementList = nullptr;
  }

  if (m_FLD_MercenariesConfig != nullptr) {
    delete m_FLD_MercenariesConfig;
    m_FLD_MercenariesConfig = nullptr;
  }

  if (m_FLD_MercenariesMission != nullptr) {
    delete m_FLD_MercenariesMission;
    m_FLD_MercenariesMission = nullptr;
  }

  if (m_FLD_FieldSkillList != nullptr) {
    delete m_FLD_FieldSkillList;
    m_FLD_FieldSkillList = nullptr;
  }

  if (m_FLD_FieldSkillSetting != nullptr) {
    delete m_FLD_FieldSkillSetting;
    m_FLD_FieldSkillSetting = nullptr;
  }

  if (m_FLD_FieldSkillRandom != nullptr) {
    delete m_FLD_FieldSkillRandom;
    m_FLD_FieldSkillRandom = nullptr;
  }

  if (m_FLD_DevelopmentLevel != nullptr) {
    delete m_FLD_DevelopmentLevel;
    m_FLD_DevelopmentLevel = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                                                                         \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatQuest::createFP() {
// The line numbers passed to the allocator decide between mov and orr.
#line 128
  m_FLD_QuestList = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST);
  m_FLD_QuestListNormal = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_NORMAL);
  m_FLD_QuestListMini = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MINI);
  m_FLD_QuestListMercenaries = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MERCENARIES);
  m_FLD_QuestListAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_ACHIEVEMENT);
  m_FLD_QuestListBlade = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_BLADE);
  m_FLD_QuestCollect = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_COLLECT);
  m_FLD_QuestTask = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK);
  m_FLD_QuestTaskNormal = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_NORMAL);
  m_FLD_QuestTaskMini = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MINI);
  m_FLD_QuestTaskMercenaries = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MERCENARIES);
  m_FLD_QuestTaskAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_ACHIEVEMENT);
  m_FLD_QuestTaskBlade = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_BLADE);
  m_FLD_QuestBattle = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_BATTLE);
  m_FLD_RequestItemSet = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_ITEM_SET);
  m_FLD_RequestBlade = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_BLADE);
  m_FLD_QuestUse = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_USE);
  m_FLD_QuestReach = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REACH);
  m_FLD_QuestTalk = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK);
  m_FLD_QuestTalkDummyGroup = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK_DUMMY_GROUP);
  m_FLD_QuestGimmick = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_GIMMICK);
  m_FLD_QuestFieldSkillCount = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_FIELD_SKILL_COUNT);
  m_FLD_QuestHints = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_HINTS);
  m_FLD_QuestCondition = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_CONDITION);
  m_FLD_QuestEvent = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_EVENT);
  m_FLD_QuestReward = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD);
  m_FLD_QuestRewardRandom = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD_RANDOM);
  m_FLD_Achievement = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT);
  m_FLD_AchievementSet = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_SET);
  m_FLD_AchievementList = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_LIST);
  m_FLD_MercenariesConfig = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_CONFIG);
  m_FLD_MercenariesMission = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_MISSION);
  m_FLD_FieldSkillList = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_LIST);
  m_FLD_FieldSkillSetting = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_SETTING);
  m_FLD_FieldSkillRandom = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_RANDOM);
  m_FLD_DevelopmentLevel = NEW_BDAT_WRAPPER(BDAT_FLD_DEVELOPMENT_LEVEL);
}

} // namespace gf
