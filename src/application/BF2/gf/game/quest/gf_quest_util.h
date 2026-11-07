#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct AchievQuest;
struct GF_OBJ_HANDLE;
struct GfQuestScinario;
struct QuestTaskParam;

// Index of GfQuestReward::unknown00.
enum QUEST_REWARD {
  QUEST_REWARD_UNKNOWN_0 = 0,   // Inferred role: gold.
  QUEST_REWARD_UNKNOWN_1 = 1,   // Role unknown.
  QUEST_REWARD_UNKNOWN_2 = 2,   // Role unknown.
  QUEST_REWARD_UNKNOWN_3 = 3,   // Inferred role: experience.
  QUEST_REWARD_UNKNOWN_4 = 4,   // Inferred role: development.
  QUEST_REWARD_UNKNOWN_5 = 5,   // Inferred role: trust.
  QUEST_REWARD_UNKNOWN_6 = 6,   // Inferred role: idea.
  QUEST_REWARD_UNKNOWN_7 = 7,   // Inferred role: mercenaries point.
  QUEST_REWARD_UNKNOWN_8 = 8,   // Inferred role: first item.
  QUEST_REWARD_UNKNOWN_9 = 9,   // Inferred role: second item.
  QUEST_REWARD_UNKNOWN_10 = 10, // Inferred role: third item.
  QUEST_REWARD_UNKNOWN_11 = 11, // Inferred role: fourth item.
};

struct GfQuestReward {
  struct Param {
    Param() : _44() {}

    u32 getDevelopZone() const;

    mm::mtl::FixStr<64> unknown00; // Inferred role: name; original member name unknown.
    // Param() value-initializes these 4 bytes as one array: initializing the two u16 members instead reorders the
    // zeroing stores in GfQuestManager::execReward, setCompleteQuest and checkQuestComplete.
    union {
      u8 _44[0x48 - 0x44];
      struct {
        u16 unknown44; // Role and original member name unknown.
        u16 m_developZone;
      };
      u32 unknown44_u32; // Inferred role: whole value of gold and exp rewards; original member name unknown.
    };
  };

  Param unknown00[12]; // Inferred role: params; original member name unknown.
  u16 unknown360;      // Inferred role: blade; original member name unknown.
  u8 _362[0x364 - 0x362];
};

static_assert(offsetof(GfQuestReward::Param, m_developZone) == 0x46, "");
static_assert(offsetof(GfQuestReward::Param, unknown44_u32) == 0x44, "");
static_assert(sizeof(GfQuestReward::Param) == 0x48, "");
static_assert(offsetof(GfQuestReward, unknown360) == 0x360, "");
static_assert(sizeof(GfQuestReward) == 0x364, "");

struct GfQuestTaskLogResult {
  GfQuestTaskLogResult() : unknown00(0), unknown08(nullptr), unknown10(0), unknown14(0), unknown18(0), unknown1c(0), unknown20(0), unknown24(false), unknown26() {}

  u32 unknown00; // Inferred role: task log text id; original member name unknown.
  u8 _04[0x08 - 0x04];
  u8 *unknown08;     // Inferred role: quest message bdat; original member name unknown.
  u32 unknown10;     // Role and original member name unknown.
  u32 unknown14;     // Inferred role: count; original member name unknown.
  u32 unknown18;     // Inferred role: displayed count; original member name unknown.
  u32 unknown1c;     // Inferred role: item; original member name unknown.
  u32 unknown20;     // Inferred role: item category; original member name unknown.
  bool unknown24;    // Inferred role: task completed or npc target; original member name unknown.
  QuestID unknown26; // Inferred role: quest of the task; original member name unknown.
};

static_assert(offsetof(GfQuestTaskLogResult, unknown08) == 0x08, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown10) == 0x10, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown14) == 0x14, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown18) == 0x18, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown1c) == 0x1c, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown20) == 0x20, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown24) == 0x24, "");
static_assert(offsetof(GfQuestTaskLogResult, unknown26) == 0x26, "");
static_assert(sizeof(GfQuestTaskLogResult) == 0x30, "");

class GfQuestUtil {
public:
  static void getScenarioTopic(GfQuestScinario &scenario);
  static bool getMsgQuestTaskLog(GfQuestTaskLogResult &result, const QuestTaskParam &param);
  static QuestID getCurrentEnemyWithEvent(u32 enemy);
  static bool isExtstActivateEnemy(const QuestTaskParam &param);
  static bool isEnemyGroup(u32 group, u32 enemy);
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
  static u32 getClearChildQuest(QuestID quest);
  static u32 getEnemyPopRemainNumber(u32 enemy);
  static void setupNewGameParam();
  static bool isDispCompassQuest(QuestID quest);
  static bool getResultIdea(u32 &category, u32 &value, u32 blade, u32 line, u32 level);
  static bool getTaskMap(mm::mtl::FixedArray<u16, 4> &maps, QuestID quest);
};

} // namespace gf
