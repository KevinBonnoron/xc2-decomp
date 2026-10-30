#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum {
  TASK_TYPE_BATTLE = 1,
  TASK_TYPE_UNKNOWN_2 = 2, // Inferred role: request item set (FLD_RequestItemSet); original name unknown.
  TASK_TYPE_COLLECT = 3,
  TASK_TYPE_USE = 4,
  TASK_TYPE_REACH = 5,
  TASK_TYPE_TALK = 6,
  TASK_TYPE_UNKNOWN_7 = 7, // Inferred role: talk to a dummy group (FLD_QuestTalkDummyGroup); original name unknown.
  TASK_TYPE_GIMMICK = 8,
  TASK_TYPE_REQUEST_BLADE = 9,
  TASK_TYPE_CONDITION = 10,
  TASK_TYPE_FIELD_SKILL_COUNT = 11,
  TASK_TYPE_ACHIEVEMENT = 12,
};

enum TASK_STATE {
  TASK_STATE_NONE,
  TASK_STATE_UNKNOWN_1, // Inferred role: task completed; original name unknown.
};

enum QUEST_PARAM {
  QUEST_PARAM_TASK,
  QUEST_PARAM_COMPLETE,
  QUEST_PARAM_CHANGE,
  QUEST_PARAM_ORDER,
  QUEST_PARAM_COMPLETE_CHILD,
  QUEST_PARAM_PRE_COMPLETE,
  QUEST_PARAM_STATE,
};

struct QuestParam {
  QuestParam(QUEST_PARAM type) : unknown00(type) {}

  QUEST_PARAM unknown00; // Inferred role: type; original member name unknown.
};

struct QuestTaskParam : QuestParam {
  QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state);
  QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state);

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
