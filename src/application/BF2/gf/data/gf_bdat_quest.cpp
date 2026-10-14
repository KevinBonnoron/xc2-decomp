#include "gf/data/gf_bdat_quest.h"
#include "bdat.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/gf_allocator.h"

namespace gf {

enum {
  BDAT_FLD_FIELD_SKILL_LIST = 0x5e,
  BDAT_FLD_FIELD_SKILL_RANDOM = 0x5f,
  BDAT_FLD_FIELD_SKILL_SETTING = 0x60,
  BDAT_FLD_MERCENARIES_CONFIG = 0x6b,
  BDAT_FLD_MERCENARIES_MISSION = 0x6d,
  BDAT_FLD_DEVELOPMENT_LEVEL = 0x6e,
  BDAT_FLD_QUEST_LIST = 0xa5,
  BDAT_FLD_QUEST_LIST_NORMAL = 0xa6,
  BDAT_FLD_QUEST_LIST_MINI = 0xa7,
  BDAT_FLD_QUEST_LIST_MERCENARIES = 0xa8,
  BDAT_FLD_QUEST_LIST_ACHIEVEMENT = 0xa9,
  BDAT_FLD_QUEST_LIST_BLADE = 0xaa,
  BDAT_FLD_QUEST_TASK = 0xab,
  BDAT_FLD_QUEST_TASK_NORMAL = 0xac,
  BDAT_FLD_QUEST_TASK_MINI = 0xad,
  BDAT_FLD_QUEST_TASK_MERCENARIES = 0xae,
  BDAT_FLD_QUEST_TASK_ACHIEVEMENT = 0xaf,
  BDAT_FLD_QUEST_TASK_BLADE = 0xb0,
  BDAT_FLD_QUEST_BATTLE = 0xb1,
  BDAT_FLD_REQUEST_ITEM_SET = 0xb2,
  BDAT_FLD_QUEST_COLLECT = 0xb3,
  BDAT_FLD_QUEST_USE = 0xb4,
  BDAT_FLD_QUEST_REACH = 0xb5,
  BDAT_FLD_QUEST_TALK = 0xb6,
  BDAT_FLD_QUEST_TALK_DUMMY_GROUP = 0xb7,
  BDAT_FLD_QUEST_GIMMICK = 0xb8,
  BDAT_FLD_QUEST_FIELD_SKILL_COUNT = 0xb9,
  BDAT_FLD_REQUEST_BLADE = 0xba,
  BDAT_FLD_QUEST_CONDITION = 0xbb,
  BDAT_FLD_QUEST_HINTS = 0xbc,
  BDAT_FLD_QUEST_REWARD = 0xbd,
  BDAT_FLD_QUEST_REWARD_RANDOM = 0xbe,
  BDAT_FLD_QUEST_EVENT = 0xbf,
  BDAT_FLD_ACHIEVEMENT = 0xc1,
  BDAT_FLD_ACHIEVEMENT_SET = 0xc2,
  BDAT_FLD_ACHIEVEMENT_LIST = 0xc3,
};

GfBdatQuest::GfBdatQuest()
    : mFLD_QuestList(nullptr), mFLD_QuestListNormal(nullptr), mFLD_QuestListMini(nullptr), mFLD_QuestListMercenaries(nullptr),
      mFLD_QuestListAchievement(nullptr), mFLD_QuestListBlade(nullptr), mFLD_QuestCollect(nullptr), mFLD_QuestTask(nullptr),
      mFLD_QuestTaskNormal(nullptr), mFLD_QuestTaskMini(nullptr), mFLD_QuestTaskMercenaries(nullptr), mFLD_QuestTaskAchievement(nullptr),
      mFLD_QuestTaskBlade(nullptr), mFLD_QuestBattle(nullptr), mFLD_RequestItemSet(nullptr), mFLD_QuestUse(nullptr), mFLD_QuestReach(nullptr),
      mFLD_QuestTalk(nullptr), mFLD_QuestTalkDummyGroup(nullptr), mFLD_QuestGimmick(nullptr), mFLD_QuestFieldSkillCount(nullptr),
      mFLD_RequestBlade(nullptr), mFLD_QuestCondition(nullptr), mFLD_QuestHints(nullptr), mFLD_QuestEvent(nullptr), mFLD_QuestReward(nullptr),
      mFLD_QuestRewardRandom(nullptr), mFLD_Achievement(nullptr), mFLD_AchievementSet(nullptr), mFLD_AchievementList(nullptr),
      mFLD_MercenariesConfig(nullptr), mFLD_MercenariesMission(nullptr), mFLD_FieldSkillList(nullptr), mFLD_FieldSkillSetting(nullptr),
      mFLD_FieldSkillRandom(nullptr), mFLD_DevelopmentLevel(nullptr) {
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
  if (mFLD_QuestList != nullptr) {
    delete mFLD_QuestList;
    mFLD_QuestList = nullptr;
  }

  if (mFLD_QuestListMini != nullptr) {
    delete mFLD_QuestListMini;
    mFLD_QuestListMini = nullptr;
  }

  if (mFLD_QuestListNormal != nullptr) {
    delete mFLD_QuestListNormal;
    mFLD_QuestListNormal = nullptr;
  }

  if (mFLD_QuestListMercenaries != nullptr) {
    delete mFLD_QuestListMercenaries;
    mFLD_QuestListMercenaries = nullptr;
  }

  if (mFLD_QuestListAchievement != nullptr) {
    delete mFLD_QuestListAchievement;
    mFLD_QuestListAchievement = nullptr;
  }

  if (mFLD_QuestListBlade != nullptr) {
    delete mFLD_QuestListBlade;
    mFLD_QuestListBlade = nullptr;
  }

  if (mFLD_QuestCollect != nullptr) {
    delete mFLD_QuestCollect;
    mFLD_QuestCollect = nullptr;
  }

  if (mFLD_QuestTask != nullptr) {
    delete mFLD_QuestTask;
    mFLD_QuestTask = nullptr;
  }

  if (mFLD_QuestTaskNormal != nullptr) {
    delete mFLD_QuestTaskNormal;
    mFLD_QuestTaskNormal = nullptr;
  }

  if (mFLD_QuestTaskMini != nullptr) {
    delete mFLD_QuestTaskMini;
    mFLD_QuestTaskMini = nullptr;
  }

  if (mFLD_QuestTaskMercenaries != nullptr) {
    delete mFLD_QuestTaskMercenaries;
    mFLD_QuestTaskMercenaries = nullptr;
  }

  if (mFLD_QuestTaskAchievement != nullptr) {
    delete mFLD_QuestTaskAchievement;
    mFLD_QuestTaskAchievement = nullptr;
  }

  if (mFLD_QuestTaskBlade != nullptr) {
    delete mFLD_QuestTaskBlade;
    mFLD_QuestTaskBlade = nullptr;
  }

  if (mFLD_QuestBattle != nullptr) {
    delete mFLD_QuestBattle;
    mFLD_QuestBattle = nullptr;
  }

  if (mFLD_RequestItemSet != nullptr) {
    delete mFLD_RequestItemSet;
    mFLD_RequestItemSet = nullptr;
  }

  if (mFLD_RequestBlade != nullptr) {
    delete mFLD_RequestBlade;
    mFLD_RequestBlade = nullptr;
  }

  if (mFLD_QuestUse != nullptr) {
    delete mFLD_QuestUse;
    mFLD_QuestUse = nullptr;
  }

  if (mFLD_QuestReach != nullptr) {
    delete mFLD_QuestReach;
    mFLD_QuestReach = nullptr;
  }

  if (mFLD_QuestTalk != nullptr) {
    delete mFLD_QuestTalk;
    mFLD_QuestTalk = nullptr;
  }

  if (mFLD_QuestTalkDummyGroup != nullptr) {
    delete mFLD_QuestTalkDummyGroup;
    mFLD_QuestTalkDummyGroup = nullptr;
  }

  if (mFLD_QuestGimmick != nullptr) {
    delete mFLD_QuestGimmick;
    mFLD_QuestGimmick = nullptr;
  }

  if (mFLD_QuestFieldSkillCount != nullptr) {
    delete mFLD_QuestFieldSkillCount;
    mFLD_QuestFieldSkillCount = nullptr;
  }

  if (mFLD_QuestHints != nullptr) {
    delete mFLD_QuestHints;
    mFLD_QuestHints = nullptr;
  }

  if (mFLD_QuestCondition != nullptr) {
    delete mFLD_QuestCondition;
    mFLD_QuestCondition = nullptr;
  }

  if (mFLD_QuestEvent != nullptr) {
    delete mFLD_QuestEvent;
    mFLD_QuestEvent = nullptr;
  }

  if (mFLD_QuestReward != nullptr) {
    delete mFLD_QuestReward;
    mFLD_QuestReward = nullptr;
  }

  if (mFLD_QuestRewardRandom != nullptr) {
    delete mFLD_QuestRewardRandom;
    mFLD_QuestRewardRandom = nullptr;
  }

  if (mFLD_Achievement != nullptr) {
    delete mFLD_Achievement;
    mFLD_Achievement = nullptr;
  }

  if (mFLD_AchievementSet != nullptr) {
    delete mFLD_AchievementSet;
    mFLD_AchievementSet = nullptr;
  }

  if (mFLD_AchievementList != nullptr) {
    delete mFLD_AchievementList;
    mFLD_AchievementList = nullptr;
  }

  if (mFLD_MercenariesConfig != nullptr) {
    delete mFLD_MercenariesConfig;
    mFLD_MercenariesConfig = nullptr;
  }

  if (mFLD_MercenariesMission != nullptr) {
    delete mFLD_MercenariesMission;
    mFLD_MercenariesMission = nullptr;
  }

  if (mFLD_FieldSkillList != nullptr) {
    delete mFLD_FieldSkillList;
    mFLD_FieldSkillList = nullptr;
  }

  if (mFLD_FieldSkillSetting != nullptr) {
    delete mFLD_FieldSkillSetting;
    mFLD_FieldSkillSetting = nullptr;
  }

  if (mFLD_FieldSkillRandom != nullptr) {
    delete mFLD_FieldSkillRandom;
    mFLD_FieldSkillRandom = nullptr;
  }

  if (mFLD_DevelopmentLevel != nullptr) {
    delete mFLD_DevelopmentLevel;
    mFLD_DevelopmentLevel = nullptr;
  }
}

#define NEW_BDAT_WRAPPER(bdat)                                                                                                                       \
  new (getAllocator(ALLOCATOR_SYSTEM), __FILE__, __LINE__, 8) CBdatWrapper { GfDataBdat::getFP(bdat) }

void GfBdatQuest::createFP() {
// The line numbers passed to the allocator decide between mov and orr.
#line 128
  mFLD_QuestList = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST);
  mFLD_QuestListNormal = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_NORMAL);
  mFLD_QuestListMini = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MINI);
  mFLD_QuestListMercenaries = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_MERCENARIES);
  mFLD_QuestListAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_ACHIEVEMENT);
  mFLD_QuestListBlade = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_LIST_BLADE);
  mFLD_QuestCollect = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_COLLECT);
  mFLD_QuestTask = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK);
  mFLD_QuestTaskNormal = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_NORMAL);
  mFLD_QuestTaskMini = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MINI);
  mFLD_QuestTaskMercenaries = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_MERCENARIES);
  mFLD_QuestTaskAchievement = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_ACHIEVEMENT);
  mFLD_QuestTaskBlade = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TASK_BLADE);
  mFLD_QuestBattle = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_BATTLE);
  mFLD_RequestItemSet = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_ITEM_SET);
  mFLD_RequestBlade = NEW_BDAT_WRAPPER(BDAT_FLD_REQUEST_BLADE);
  mFLD_QuestUse = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_USE);
  mFLD_QuestReach = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REACH);
  mFLD_QuestTalk = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK);
  mFLD_QuestTalkDummyGroup = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_TALK_DUMMY_GROUP);
  mFLD_QuestGimmick = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_GIMMICK);
  mFLD_QuestFieldSkillCount = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_FIELD_SKILL_COUNT);
  mFLD_QuestHints = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_HINTS);
  mFLD_QuestCondition = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_CONDITION);
  mFLD_QuestEvent = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_EVENT);
  mFLD_QuestReward = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD);
  mFLD_QuestRewardRandom = NEW_BDAT_WRAPPER(BDAT_FLD_QUEST_REWARD_RANDOM);
  mFLD_Achievement = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT);
  mFLD_AchievementSet = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_SET);
  mFLD_AchievementList = NEW_BDAT_WRAPPER(BDAT_FLD_ACHIEVEMENT_LIST);
  mFLD_MercenariesConfig = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_CONFIG);
  mFLD_MercenariesMission = NEW_BDAT_WRAPPER(BDAT_FLD_MERCENARIES_MISSION);
  mFLD_FieldSkillList = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_LIST);
  mFLD_FieldSkillSetting = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_SETTING);
  mFLD_FieldSkillRandom = NEW_BDAT_WRAPPER(BDAT_FLD_FIELD_SKILL_RANDOM);
  mFLD_DevelopmentLevel = NEW_BDAT_WRAPPER(BDAT_FLD_DEVELOPMENT_LEVEL);
}

} // namespace gf
