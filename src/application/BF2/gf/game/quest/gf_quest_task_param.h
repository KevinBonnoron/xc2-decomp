#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

enum TASK_STATE {
  TASK_STATE_NONE,
};

struct QuestTaskParam {
  QuestTaskParam(QuestID quest, u32 taskIndex, TASK_STATE state);
  QuestTaskParam(QuestID quest, u32 taskIndex, u32 purpose, TASK_STATE state);

  u8 _00[0x04 - 0x00];
  QuestID quest;
  u32 purpose;
  u32 taskIndex;
  u32 taskType;
  u32 taskId;
  TASK_STATE state;
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(QuestTaskParam, quest) == 0x04, "");
static_assert(offsetof(QuestTaskParam, purpose) == 0x08, "");
static_assert(offsetof(QuestTaskParam, taskIndex) == 0x0c, "");
static_assert(offsetof(QuestTaskParam, taskType) == 0x10, "");
static_assert(offsetof(QuestTaskParam, taskId) == 0x14, "");
static_assert(offsetof(QuestTaskParam, state) == 0x18, "");
static_assert(sizeof(QuestTaskParam) == 0x20, "");

} // namespace gf
