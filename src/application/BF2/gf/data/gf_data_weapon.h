#pragma once
#include "types.h"

namespace gf {

class GfDataWeapon {
public:
  static const char *getName(u32 weapon);
  static bool getName(u8 *&bdat, u32 &textId, u32 weapon);
  static const char *getModelName(u32 weapon);
  static const char *getMotionName(u32 weapon);
  static u32 getNewWeapon(u32 weapon, u32 chip);
  static u32 getDamage(u32 weapon);
  static u32 getGuardRatio(u32 weapon);
  static u32 getCriticalRatio(u32 weapon);
  static u32 getStability(u32 weapon);
  static u32 getEnhance(u32 weapon);
  static u32 getRank(u32 weapon);
  static bool getWeaponTypeName(u8 *&bdat, u32 &textId, u32 weaponType);
  static bool getWeaponTypeNameByItem(u8 *&bdat, u32 &textId, u32 weapon);
  static const char *getWeaponTypeName(u32 weaponType);
  static u32 getAsmWeaponType(u32 weaponType);
  static u32 getEffWeaponType(u32 weaponType);
};

} // namespace gf
