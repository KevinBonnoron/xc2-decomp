#pragma once
#include "gf/data/gf_bdat_quest.h"
#include "gf/game/quest/gf_quest_id.h"

namespace gf {

class GfQuestManager {
public:
  static QuestID getCurrentQuest(QTYPE type);
};

} // namespace gf
