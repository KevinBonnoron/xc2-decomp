#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gmk {
enum GmkType : int;
}

namespace gf {

struct AchievQuest;
struct GF_OBJ_HANDLE;
struct GfQuestScinario;
struct GfQuestTaskLogResult;
struct QuestTaskParam;

struct GfQuestReward {
  struct Param {
    Param() : _44() {}

    u32 getDevelopZone() const;

    mm::mtl::FixStr<64> name;
    u8 _44[0x48 - 0x44];
  };

  Param params[12];
  u16 blade;
  u8 _362[0x368 - 0x362];
};

static_assert(sizeof(GfQuestReward::Param) == 0x48, "");
static_assert(offsetof(GfQuestReward, blade) == 0x360, "");
static_assert(sizeof(GfQuestReward) == 0x368, "");

class GfQuestUtil {
public:
  static void getScenarioTopic(GfQuestScinario &scenario);
  static bool getMsgQuestTaskLog(GfQuestTaskLogResult &result, const QuestTaskParam &param);
  static u32 getCurrentEnemyWithEvent(u32 enemy);
  static bool isExtstActivateEnemy(const QuestTaskParam &param);
  static bool isEnemyGroup(u32 enemy, u32 group);
  static u32 getCurrentItemWithEvent(u32 item);
  static u32 getCurrentTBoxWithEvent(GF_OBJ_HANDLE *handle);
  static u32 getQuestNeedChar(u32 index, QuestID quest);
  static void finishTalkNpc(u32 map, u32 npc, QuestID quest);
  static void removeQuestItem(const QuestTaskParam &param);
  static void sendItemLog(const QuestTaskParam &param);
  static void sendSuppressLog(const QuestTaskParam &param, u32 enemy);
  static u32 getMsgQuestTitle(QuestID quest);
  static u32 getMsgQuestSummary(QuestID quest);
  static u32 getMsgQuestNeedFieldSkill(u32 index, QuestID quest);
  static u32 getMsgQuestResult(QuestID quest);
  static bool getReward(GfQuestReward &reward, u32 rewardSet, bool isRandom);
  static bool isCurrentTaskBattle();
  static bool isReduceHpObj(GF_OBJ_HANDLE *handle);
  static void execReward(const GfQuestReward &reward);
  static void addOrderParentQuest(QuestID quest);
  static void removeOrderParentQuest(QuestID quest);
  static QuestID getLastOrderCategoryQuest(QTYPE type);
  static QuestID getLastOrderInvalidCategoryQuest(QTYPE type);
  static QuestID getLastOrderParentQuest();
  static void clearOrderParentQuest();
  static void addTaskHanyouCount(u32 purpose, u32 taskIndex, u32 add);
  static void questCompleteItem(QuestID quest);
  static bool getNeedCharacterByQuestTask(mm::mtl::FixedVector<u16, 32> &characters, QuestID quest, u32 taskIndex);
  static u16 getBladeID(QuestID quest);
  static u32 getGimmickTaskEndCheck(gmk::GmkType type, u32 gimmick);
  static bool getDummyTalkGroup(u32 &group, u32 &npcIndex, u32 map, u32 npc, QuestID quest);
  static bool getTalkNpcInfo(u32 &taskIndex, u32 npc, QuestID quest);
  static u32 getQuestIconType(QuestID quest);
  static bool getDispCount(u32 &count, u32 &limit, const AchievQuest &achievQuest);
  static void incFieldSkillTask(u32 blade, u32 fieldSkill);
  static bool getTaskInfoForAutoPilot(mm::mtl::FixStr<256> &info);
  static void completeCurrentQuestForAutoPilot();
  static QuestID getClearChildQuest(QuestID quest);
  static u32 getEnemyPopRemainNumber(u32 enemy);
  static void setupNewGameParam();
  static bool isDispCompassQuest(QuestID quest);
  static bool getResultIdea(u32 &category, u32 &value, u32 blade, u32 line, u32 level);
  static bool getTaskMap(mm::mtl::FixedArray<u16, 4> &maps, QuestID quest);
};

} // namespace gf
