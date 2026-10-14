#pragma once
#include "types.h"

namespace gf {

struct QuestID {
  u16 id;
  u16 variant;

  bool empty() const;
};

static_assert(sizeof(QuestID) == 4, "");

inline QuestID toQuestID(u32 quest) {
  QuestID questID = {static_cast<u16>(quest), static_cast<u16>(quest >> 16)};
  return questID;
}

} // namespace gf
