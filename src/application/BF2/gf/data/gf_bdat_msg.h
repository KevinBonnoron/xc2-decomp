#pragma once
#include "gf/game/quest/gf_quest_id.h"
#include "types.h"

namespace gf {

class GfBdatMsg {
public:
  static u8 *getFpPcWpn();
  static u8 *getFpPcWpnType();
  static u8 *getFpMapInfo();
  static u8 *getFpQuest(QuestID quest);
  static const char *getNameQuest(QuestID quest, u32 line);
  static u8 *getFpEnemy();
};

} // namespace gf
