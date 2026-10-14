#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct AchievQuest {
  void setTaskComplete(bool isFirst, bool isComplete);
  void setCountComplete();
  void setCount(u32 count);

  QuestID quest;
  u32 count : 30;
  u32 : 2;
  u8 _08[0x0c - 0x08];
  u16 flags;
  u16 stats;
  u8 _10[0x1c - 0x10];
};

static_assert(offsetof(AchievQuest, flags) == 0x0c, "");
static_assert(offsetof(AchievQuest, stats) == 0x0e, "");
static_assert(sizeof(AchievQuest) == 0x1c, "");

} // namespace gf
