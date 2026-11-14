#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum {
  TASK_TYPE_UNKNOWN_1 = 1,   // Inferred role: task type battle; original name unknown.
  TASK_TYPE_UNKNOWN_2 = 2,   // Inferred role: request item set (FLD_RequestItemSet); original name unknown.
  TASK_TYPE_UNKNOWN_3 = 3,   // Inferred role: task type collect; original name unknown.
  TASK_TYPE_UNKNOWN_4 = 4,   // Inferred role: task type use; original name unknown.
  TASK_TYPE_UNKNOWN_5 = 5,   // Inferred role: task type reach; original name unknown.
  TASK_TYPE_UNKNOWN_6 = 6,   // Inferred role: task type talk; original name unknown.
  TASK_TYPE_UNKNOWN_7 = 7,   // Inferred role: talk to a dummy group (FLD_QuestTalkDummyGroup); original name unknown.
  TASK_TYPE_UNKNOWN_8 = 8,   // Inferred role: task type gimmick; original name unknown.
  TASK_TYPE_UNKNOWN_9 = 9,   // Inferred role: task type request blade; original name unknown.
  TASK_TYPE_UNKNOWN_10 = 10, // Inferred role: task type condition; original name unknown.
  TASK_TYPE_UNKNOWN_11 = 11, // Inferred role: task type field skill count; original name unknown.
  TASK_TYPE_UNKNOWN_12 = 12, // Inferred role: task type achievement; original name unknown.
};

enum TASK_STATE {
  TASK_STATE_UNKNOWN_0, // Inferred role: task state none; original name unknown.
  TASK_STATE_UNKNOWN_1, // Inferred role: task completed; original name unknown.
  TASK_STATE_UNKNOWN_2, // Inferred role: task state of the suppress count; original name unknown.
};

enum QUEST_PARAM {
  QUEST_PARAM_UNKNOWN_0, // Inferred role: quest param task; original name unknown.
  QUEST_PARAM_UNKNOWN_1, // Inferred role: quest param complete; original name unknown.
  QUEST_PARAM_UNKNOWN_2, // Inferred role: quest param change; original name unknown.
  QUEST_PARAM_UNKNOWN_3, // Inferred role: quest param order; original name unknown.
  QUEST_PARAM_UNKNOWN_4, // Inferred role: quest param complete child; original name unknown.
  QUEST_PARAM_UNKNOWN_5, // Inferred role: quest param pre complete; original name unknown.
  QUEST_PARAM_UNKNOWN_6, // Inferred role: quest param state; original name unknown.
};

struct QuestParam {
  QuestParam(QUEST_PARAM type) : unknown00(type) {}

  QUEST_PARAM unknown00; // Inferred role: type; original member name unknown.
};

struct QuestTaskParam : QuestParam {
  QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state);
  QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state);
  // The game gives QuestTaskParam a non-trivial destructor (no out-of-line symbol: it is empty and inline): with a trivial one
  // the exits of the task loops in GfQuestUtil::getScenarioTopic and getQuestIconType lose their cleanup destination flag.
  ~QuestTaskParam() {}

  QuestID unknown04;    // Inferred role: quest; original member name unknown.
  u32 unknown08;        // Inferred role: purpose; original member name unknown.
  u32 unknown0c;        // Inferred role: task index; original member name unknown.
  u32 unknown10;        // Inferred role: task type; original member name unknown.
  u32 unknown14;        // Inferred role: task id; original member name unknown.
  TASK_STATE unknown18; // Inferred role: state; original member name unknown.
  bool unknown1c;       // Inferred role: display; original member name unknown.
};

static_assert(offsetof(QuestTaskParam, unknown04) == 0x04, "");
static_assert(offsetof(QuestTaskParam, unknown08) == 0x08, "");
static_assert(offsetof(QuestTaskParam, unknown0c) == 0x0c, "");
static_assert(offsetof(QuestTaskParam, unknown10) == 0x10, "");
static_assert(offsetof(QuestTaskParam, unknown14) == 0x14, "");
static_assert(offsetof(QuestTaskParam, unknown18) == 0x18, "");
static_assert(offsetof(QuestTaskParam, unknown1c) == 0x1c, "");
static_assert(sizeof(QuestTaskParam) == 0x20, "");

} // namespace gf
