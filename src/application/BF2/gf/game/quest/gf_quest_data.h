#pragma once
#include "gf/game/quest/gf_quest_id.h"

namespace gf {

struct QuestData {
  QuestData() = default;
  QuestData(QuestID quest) : m_questID(quest) {}

  QuestData &operator=(const QuestData &other) {
    m_questID.unknown00 = other.m_questID.unknown00;
    m_questID.unknown02 = other.m_questID.unknown02;
    return *this;
  }

  operator QuestID() const { return m_questID; }

  bool operator==(const QuestData &other) const { return m_questID.unknown00 == other.m_questID.unknown00 && m_questID.unknown02 == other.m_questID.unknown02; }

  QuestID m_questID; // Inferred role: quest; original member name unknown.
};

static_assert(sizeof(QuestData) == 4, "");

} // namespace gf
