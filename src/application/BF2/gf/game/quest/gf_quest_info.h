#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"

namespace gf {

enum QSTATE {
  QSTATE_NOT_ORDER,
  QSTATE_ORDER,
  QSTATE_FIN_A,
  QSTATE_FIN_B,
};

class GfQuestInfo {
public:
  static QSTATE getState(QuestID quest);
  static void setState(QuestID quest, QSTATE state);
  static bool isDispUI(QuestID quest);
};

} // namespace gf
