#pragma once
#include "types.h"

namespace gf {

class GfDataNanakoori {
public:
  static bool setVocalLevel(u32 vocalLevel);
  static u32 getVocalLevel();

  static bool setVisualLevel(u32 visualLevel);
  static u32 getVisualLevel();

  static bool setSoulLevel(u32 soulLevel);
  static u32 getSoulLevel();

  static bool setFan(u32 fan);
  static u32 getFan();

  static u32 getNanakooriMissionClearFlg1Offset(u32 mission);
  static u32 getLevelForNanakoori(u32 stampCount);

  static u64 getItemForVocalLevelUp();
  static u64 getItemForVisualLevelUp();
  static u64 getItemForSoulLevelUp();

  static u32 getClearMissionForSpecial();
  static u32 getClearMissionForLive();
  static u32 getClearMissionForLesson();

  static bool isMissionComplete(u32 mission);
  static void setMissionComplete(u32 mission);
};

} // namespace gf
