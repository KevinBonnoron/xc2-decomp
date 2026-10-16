#pragma once
#include "types.h"

namespace gf {

constexpr u32 QUEST_ID_END = 30000;

struct QuestID {
  bool empty() const;
  bool operator==(const QuestID &other) const { return id == other.id && variant == other.variant; }

  u16 id;
  u16 variant;
};

static_assert(sizeof(QuestID) == 4, "");

inline QuestID toQuestID(u32 quest) {
  QuestID questID = {static_cast<u16>(quest), static_cast<u16>(quest >> 16)};
  return questID;
}

} // namespace gf
