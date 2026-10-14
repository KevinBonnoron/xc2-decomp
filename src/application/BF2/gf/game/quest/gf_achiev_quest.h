#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct AchievQuest {
  void setCount(u32 count);

  QuestID quest;
  u32 count : 30;
  u32 : 2;
  u8 _08[0x0e - 0x08];
  u16 stats;
};

static_assert(offsetof(AchievQuest, stats) == 0x0e, "");

} // namespace gf
