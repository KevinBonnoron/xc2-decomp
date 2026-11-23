#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct AchievQuest {
  // Evidence: GfBladeCreateInfo::GfBladeCreateInfo (0x71003011a4) zeroes the 0x1a bytes from the quest to the achievement of each of the 50 quests of its ten achievements (0x404-0x41e, ...) and not
  // the padding after them.
  AchievQuest() : unknown04(0), unknown08(0), unknown0c(0), unknown0e(0), unknown10(0), unknown12(0), unknown14(0), unknown16(0), unknown18(0) {}

  void setTaskComplete(bool isFirst, bool isComplete);
  void setCountComplete();
  bool isCountComplete() const;
  bool setCount(u32 count);
  bool incleseCount(u32 count);
  bool decleseCount(u32 count);

  static const u32 MASK_UNKNOWN_1073741823 = 0x3fffffff; // Inferred role: count mask; original name unknown.

  u32 getCount() const { return unknown04 & MASK_UNKNOWN_1073741823; }
  u32 getTargetCount() const { return unknown08 & MASK_UNKNOWN_1073741823; }

  QuestID m_questID; // Inferred role: quest; original member name unknown.
  u32 unknown04;     // Inferred role: count; original member name unknown.
  u32 unknown08;     // Inferred role: target count; original member name unknown.
  u16 unknown0c;     // Inferred role: flags; original member name unknown.
  u16 unknown0e;     // Inferred role: stats; original member name unknown.
  u16 unknown10;     // Inferred role: task type; original member name unknown.
  u16 unknown12;     // Inferred role: achievement type; original member name unknown.
  u16 unknown14;     // Inferred role: sort index; original member name unknown.
  u16 unknown16;     // Inferred role: blade; original member name unknown.
  u16 unknown18; // Inferred role: achievement; original member name unknown. Evidence: GfDataBlade::setupAchievInfo stores the achievement id at +0x18 of each quest and GfDataBlade::getKizunaringMax
                 // tests it.
  // The two padding bytes after unknown18 are no member: the game copies the quest in 0x1a bytes (GfBladeCreate::setupSDataBlade, 0x7100301fd4).
};

static_assert(offsetof(AchievQuest, unknown0c) == 0x0c, "");
static_assert(offsetof(AchievQuest, unknown0e) == 0x0e, "");
static_assert(offsetof(AchievQuest, unknown10) == 0x10, "");
static_assert(offsetof(AchievQuest, unknown12) == 0x12, "");
static_assert(offsetof(AchievQuest, unknown14) == 0x14, "");
static_assert(offsetof(AchievQuest, unknown16) == 0x16, "");
static_assert(offsetof(AchievQuest, unknown18) == 0x18, "");
static_assert(sizeof(AchievQuest) == 0x1c, "");

} // namespace gf
