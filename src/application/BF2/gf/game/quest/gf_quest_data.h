#pragma once
#include "gf/game/quest/gf_quest_id.h"

namespace gf {

struct QuestData {
  QuestData() = default;
  QuestData(QuestID quest) : unknown00(quest) {}

  QuestData &operator=(const QuestData &other) {
    unknown00.unknown00 = other.unknown00.unknown00;
    unknown00.unknown02 = other.unknown00.unknown02;
    return *this;
  }

  operator QuestID() const { return unknown00; }

  bool operator==(const QuestData &other) const { return unknown00.unknown00 == other.unknown00.unknown00 && unknown00.unknown02 == other.unknown00.unknown02; }

  QuestID unknown00; // Inferred role: quest; original member name unknown.
};

static_assert(sizeof(QuestData) == 4, "");

} // namespace gf
