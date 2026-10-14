#pragma once
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfDataEnemy {
public:
  static const char *getName(u32 arrange);
  static bool getName(u8 *&bdat, u32 &textId, u32 arrange);
  static u32 getRscIdByArrangeId(u32 arrange);
  static const char *getVoiceStr(u32 arrange);
  static const char *getAddMotionName(u32 resource);
  static const char *getResourceNameModel(u32 arrange);
  static const char *getResourceNameMotion(u32 arrange);
  static const char *getSePack(u32 resource);
  static u32 getEnemySuppress(u32 enemy);
  static bool incEnemySuppress(u32 enemy);
  static u32 getBladeID(u32 arrange);
  static u32 getEquipBlade(u32 arrange);
  static u32 getEquipBladeEnArrangeID(u32 arrange);
  static u32 getWeaponType(u32 arrange);
  static bool getDriverAddAnim(mm::mtl::FixStr<128> &animName, u32 driver, u32 number);
  static bool getDriverEffect(mm::mtl::FixStr<128> &modelName, mm::mtl::FixStr<128> &effectName, u32 driver, u32 number);
  static const char *getLoopEffect(u32 resource);
  static bool isNamed(u32 arrange);
  static bool isBoss(u32 arrange);
  static bool getExtraParts(u32 resource, u32 part);
  static u32 getSavedHp(u32 savedHpType);
  static void setSavedHp(u32 savedHpType, u32 savedHp);
  static u32 getSavedHpType(u32 arrange);
  static bool isDrTypeHasWeapon(u32 arrange);
};

} // namespace gf
