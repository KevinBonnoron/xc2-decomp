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

  u32 getCount() const { return unknown04 & COUNT_MASK; }
  u32 getTargetCount() const { return unknown08 & COUNT_MASK; }

  QuestID unknown00; // Inferred role: quest; original member name unknown.
  u32 unknown04;     // Inferred role: count; original member name unknown.
  u32 unknown08;     // Inferred role: target count; original member name unknown.
  u16 unknown0c;     // Inferred role: flags; original member name unknown.
  u16 unknown0e;     // Inferred role: stats; original member name unknown.
  u16 unknown10;     // Inferred role: task type; original member name unknown.
  u16 unknown12;     // Inferred role: achievement type; original member name unknown.
  u16 unknown14;     // Inferred role: sort index; original member name unknown.
  u16 unknown16;     // Inferred role: blade; original member name unknown.
  u8 _18[0x1c - 0x18];
};

static_assert(offsetof(AchievQuest, unknown0c) == 0x0c, "");
static_assert(offsetof(AchievQuest, unknown0e) == 0x0e, "");
static_assert(offsetof(AchievQuest, unknown10) == 0x10, "");
static_assert(offsetof(AchievQuest, unknown12) == 0x12, "");
static_assert(offsetof(AchievQuest, unknown14) == 0x14, "");
static_assert(offsetof(AchievQuest, unknown16) == 0x16, "");
static_assert(sizeof(AchievQuest) == 0x1c, "");

} // namespace gf
