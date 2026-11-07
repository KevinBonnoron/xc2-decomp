#pragma once
#include "types.h"

namespace gf {

constexpr u32 QUEST_ID_END = 30000;

struct QuestID {
  // User-provided: the game returns a QuestID as two separately merged halves (and/orr of 32-bit words) as soon as a
  // constructor zeroes it (GfQuestManager::getOrderQuest, getReduceHpQuest, getListNextQuestA).
  QuestID() : unknown00(0), unknown02(0) {}
  QuestID(u16 id, u16 variant) : unknown00(id), unknown02(variant) {}
  bool empty() const;
  bool operator==(const QuestID &other) const { return unknown00 == other.unknown00 && unknown02 == other.unknown02; }
  // User-provided: the game assigns a QuestID member as two halfwords (GfFieldLocator::createByQuest, Locator*::create)
  // while copy construction stays a single word.
  QuestID &operator=(const QuestID &other) {
    unknown00 = other.unknown00;
    unknown02 = other.unknown02;
    return *this;
  }

  u16 unknown00; // Inferred role: id; original member name unknown.
  u16 unknown02; // Inferred role: variant; original member name unknown.
};

static_assert(sizeof(QuestID) == 4, "");

inline QuestID toQuestID(u32 quest) {
  QuestID questID = {static_cast<u16>(quest), static_cast<u16>(quest >> 16)};
  return questID;
}

} // namespace gf
