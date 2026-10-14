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
  static u8 *getFpChrDr();
  static u8 *getFpAchievement();
  static u8 *getFpPcWpnChip();
  static u8 *getFpPcEquip();
  static u8 *getFpOrb();
  static u8 *getFpSalvage();
  static u8 *getFpPrecious();
  static u8 *getFpCollection();
  static u8 *getFpTresure();
  static u8 *getFpFavorite();
  static u8 *getFpCrystal();
  static u8 *getFpBooster();
  static u8 *getFpInfo();
  static u8 *getFpEvent();
  static u8 *getFpBtlHanaRole();
  static u8 *getFpBtlHanaAtr();
  static u8 *getFpBtlHanaNArts();
  static u8 *getFpFieldSkill();
  static u8 *getFpBtlEnhanceCap();
  static u8 *getFpBtlClass();
  static u8 *getFpBlSkill();
  static u8 *getFpBlBuffMs();
  static u8 *getFpBlBuffCap();
  static u8 *getFpLandmark();
  static u8 *getFpBlArtsMs();
  static u8 *getFpBlSpArtsMs();
  static u8 *getFpBtlSkillDr();
};

} // namespace gf
