#pragma once
#include "gf/game/quest/gf_quest_id.h"

namespace gf {

struct QuestData {
  QuestData() = default;
  QuestData(QuestID quest) : quest(quest) {}

  QuestData &operator=(const QuestData &other) {
    quest.id = other.quest.id;
    quest.variant = other.quest.variant;
    return *this;
  }

  operator QuestID() const { return quest; }

  bool operator==(const QuestData &other) const { return quest.id == other.quest.id && quest.variant == other.quest.variant; }

  QuestID quest;
};

static_assert(sizeof(QuestData) == 4, "");

} // namespace gf
