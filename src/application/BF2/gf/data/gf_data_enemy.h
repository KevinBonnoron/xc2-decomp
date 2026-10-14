#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataEnemy {
  u16 arrange;
  u8 _002[0x004 - 0x002];
  u8 : 4;
  u8 linkGenus : 1;
  u8 guardFront : 1;
  u8 guardLeft : 1;
  u8 guardRight : 1;
  u8 guardBack : 1;
  u8 fieldDamage : 1;
  u8 : 1;
  u8 noCameraFade : 1;
  u8 weaponDrawDisp : 1;
  u8 : 3;
  u8 _006[0x012 - 0x006];
  u16 goldRev;
  u8 _014[0x01f - 0x014];
  u8 linkRadius;
  u8 _020[0x034 - 0x020];
  u16 param;
  u8 _036[0x042 - 0x036];
  u8 extraParts;
  u8 _043[0x044 - 0x043];
  u16 resource;
  u8 _046[0x05c - 0x046];
  u16 pArmor;
  u16 eArmor;
  u8 resistancePower;
  u8 resistanceEther;
  u8 bladeAttribute;
  u8 criticalRate;
  u8 guardRate;
  u8 _065[0x066 - 0x065];
  u16 resistanceCombo;
  u16 invincibleCombo;
  u8 _06a[0x099 - 0x06a];
  u8 genus;
  u8 _09a[0x09e - 0x09a];
  u16 equipWeapons[5];
  u16 level;
  u8 _0aa[0x0ac - 0x0aa];
  u32 hpMax;
  u16 strength;
  u16 powerEther;
  u16 dex;
  u16 agility;
  u16 luck;
  u8 _0ba[0x0bc - 0x0ba];

  SDataEnemy();
  SDataEnemy(u32 arrange, u32 level);
  void clear();
};

static_assert(offsetof(SDataEnemy, goldRev) == 0x012, "");
static_assert(offsetof(SDataEnemy, linkRadius) == 0x01f, "");
static_assert(offsetof(SDataEnemy, param) == 0x034, "");
static_assert(offsetof(SDataEnemy, extraParts) == 0x042, "");
static_assert(offsetof(SDataEnemy, resource) == 0x044, "");
static_assert(offsetof(SDataEnemy, pArmor) == 0x05c, "");
static_assert(offsetof(SDataEnemy, resistancePower) == 0x060, "");
static_assert(offsetof(SDataEnemy, bladeAttribute) == 0x062, "");
static_assert(offsetof(SDataEnemy, guardRate) == 0x064, "");
static_assert(offsetof(SDataEnemy, resistanceCombo) == 0x066, "");
static_assert(offsetof(SDataEnemy, invincibleCombo) == 0x068, "");
static_assert(offsetof(SDataEnemy, genus) == 0x099, "");
static_assert(offsetof(SDataEnemy, equipWeapons) == 0x09e, "");
static_assert(offsetof(SDataEnemy, level) == 0x0a8, "");
static_assert(offsetof(SDataEnemy, hpMax) == 0x0ac, "");
static_assert(offsetof(SDataEnemy, strength) == 0x0b0, "");
static_assert(offsetof(SDataEnemy, luck) == 0x0b8, "");
static_assert(sizeof(SDataEnemy) == 0x0bc, "");

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
  static void getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 arrange);
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
