#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct AchievQuest {
  void setTaskComplete(bool isFirst, bool isComplete);
  void setCountComplete();
  bool isCountComplete() const;
  bool setCount(u32 count);
  bool incleseCount(u32 count);
  bool decleseCount(u32 count);

  static const u32 COUNT_MASK = 0x3fffffff;

  u32 getCount() const { return count & COUNT_MASK; }
  u32 getTargetCount() const { return targetCount & COUNT_MASK; }

  QuestID quest;
  u32 count;
  u32 targetCount;
  u16 flags;
  u16 stats;
  u16 taskType;
  u16 achievementType;
  u16 sortIndex;
  u16 blade;
  u8 _18[0x1c - 0x18];
};

static_assert(offsetof(AchievQuest, flags) == 0x0c, "");
static_assert(offsetof(AchievQuest, stats) == 0x0e, "");
static_assert(offsetof(AchievQuest, taskType) == 0x10, "");
static_assert(offsetof(AchievQuest, achievementType) == 0x12, "");
static_assert(offsetof(AchievQuest, sortIndex) == 0x14, "");
static_assert(offsetof(AchievQuest, blade) == 0x16, "");
static_assert(sizeof(AchievQuest) == 0x1c, "");

} // namespace gf
