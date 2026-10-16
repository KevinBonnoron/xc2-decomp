#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum {
  TASK_TYPE_BATTLE = 1,
  TASK_TYPE_COLLECT = 3,
  TASK_TYPE_USE = 4,
  TASK_TYPE_REACH = 5,
  TASK_TYPE_TALK = 6,
  TASK_TYPE_GIMMICK = 8,
  TASK_TYPE_REQUEST_BLADE = 9,
  TASK_TYPE_CONDITION = 10,
  TASK_TYPE_FIELD_SKILL_COUNT = 11,
  TASK_TYPE_ACHIEVEMENT = 12,
};

enum TASK_STATE {
  TASK_STATE_NONE,
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
  QuestParam(QUEST_PARAM type) : type(type) {}

  QUEST_PARAM type;
};

struct QuestTaskParam : QuestParam {
  QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state);
  QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state);

  QuestID quest;
  u32 purpose;
  u32 taskIndex;
  u32 taskType;
  u32 taskId;
  TASK_STATE state;
  bool isDisp;
};

static_assert(offsetof(QuestTaskParam, quest) == 0x04, "");
static_assert(offsetof(QuestTaskParam, purpose) == 0x08, "");
static_assert(offsetof(QuestTaskParam, taskIndex) == 0x0c, "");
static_assert(offsetof(QuestTaskParam, taskType) == 0x10, "");
static_assert(offsetof(QuestTaskParam, taskId) == 0x14, "");
static_assert(offsetof(QuestTaskParam, state) == 0x18, "");
static_assert(offsetof(QuestTaskParam, isDisp) == 0x1c, "");
static_assert(sizeof(QuestTaskParam) == 0x20, "");

} // namespace gf
