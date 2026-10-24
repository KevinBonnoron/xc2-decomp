#pragma once
#include "types.h"

namespace gf {

constexpr u32 QUEST_ID_END = 30000;

struct QuestID {
  bool empty() const;
  bool operator==(const QuestID &other) const { return unknown00 == other.unknown00 && unknown02 == other.unknown02; }

  u16 unknown00; // Inferred role: id; original member name unknown.
  u16 unknown02; // Inferred role: variant; original member name unknown.
};

static_assert(sizeof(QuestID) == 4, "");

inline QuestID toQuestID(u32 quest) {
  QuestID questID = {static_cast<u16>(quest), static_cast<u16>(quest >> 16)};
  return questID;
}

} // namespace gf
