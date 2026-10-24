#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

constexpr u32 EXTRA_PARTS_COUNT = 4;

struct SDataEnemy {
  u16 unknown00; // Inferred role: arrange; original member name unknown.
  u8 _002[0x004 - 0x002];
  u8 unknown04_0 : 1; // Inferred role: named; original member name unknown.
  u8 unknown04_1 : 1; // Inferred role: boss; original member name unknown.
  u8 : 2;
  u8 unknown04_4 : 1; // Inferred role: link genus; original member name unknown.
  u8 unknown04_5 : 1; // Inferred role: guard front; original member name unknown.
  u8 unknown04_6 : 1; // Inferred role: guard left; original member name unknown.
  u8 unknown04_7 : 1; // Inferred role: guard right; original member name unknown.
  u8 unknown05_0 : 1; // Inferred role: guard back; original member name unknown.
  u8 unknown05_1 : 1; // Inferred role: field damage; original member name unknown.
  u8 : 1;
  u8 unknown05_3 : 1; // Inferred role: no camera fade; original member name unknown.
  u8 unknown05_4 : 1; // Inferred role: weapon draw disp; original member name unknown.
  u8 : 3;
  u8 _006[0x012 - 0x006];
  u16 unknown12; // Inferred role: gold rev; original member name unknown.
  u8 _014[0x01f - 0x014];
  u8 unknown1f; // Inferred role: link radius; original member name unknown.
  u8 _020[0x034 - 0x020];
  u16 unknown34; // Inferred role: param; original member name unknown.
  u8 _036[0x042 - 0x036];
  u8 unknown42; // Inferred role: extra parts; original member name unknown.
  u8 _043[0x044 - 0x043];
  u16 unknown44; // Inferred role: resource; original member name unknown.
  u8 _046[0x05c - 0x046];
  u16 unknown5c; // Inferred role: p armor; original member name unknown.
  u16 unknown5e; // Inferred role: e armor; original member name unknown.
  u8 unknown60;  // Inferred role: resistance power; original member name unknown.
  u8 unknown61;  // Inferred role: resistance ether; original member name unknown.
  u8 unknown62;  // Inferred role: blade attribute; original member name unknown.
  u8 unknown63;  // Inferred role: critical rate; original member name unknown.
  u8 unknown64;  // Inferred role: guard rate; original member name unknown.
  u8 _065[0x066 - 0x065];
  u16 unknown66; // Inferred role: resistance combo; original member name unknown.
  u16 unknown68; // Inferred role: invincible combo; original member name unknown.
  u8 _06a[0x099 - 0x06a];
  u8 unknown99; // Inferred role: genus; original member name unknown.
  u8 _09a[0x09e - 0x09a];
  u16 unknown9e[5]; // Inferred role: equip weapons; original member name unknown.
  u16 unknowna8;    // Inferred role: level; original member name unknown.
  u8 _0aa[0x0ac - 0x0aa];
  u32 unknownac; // Inferred role: hp max; original member name unknown.
  u16 unknownb0; // Inferred role: strength; original member name unknown.
  u16 unknownb2; // Inferred role: power ether; original member name unknown.
  u16 unknownb4; // Inferred role: dex; original member name unknown.
  u16 unknownb6; // Inferred role: agility; original member name unknown.
  u16 unknownb8; // Inferred role: luck; original member name unknown.
  u8 _0ba[0x0bc - 0x0ba];

  SDataEnemy();
  SDataEnemy(u32 arrange, u32 level);
  void clear();
};

static_assert(offsetof(SDataEnemy, unknown12) == 0x012, "");
static_assert(offsetof(SDataEnemy, unknown1f) == 0x01f, "");
static_assert(offsetof(SDataEnemy, unknown34) == 0x034, "");
static_assert(offsetof(SDataEnemy, unknown42) == 0x042, "");
static_assert(offsetof(SDataEnemy, unknown44) == 0x044, "");
static_assert(offsetof(SDataEnemy, unknown5c) == 0x05c, "");
static_assert(offsetof(SDataEnemy, unknown60) == 0x060, "");
static_assert(offsetof(SDataEnemy, unknown62) == 0x062, "");
static_assert(offsetof(SDataEnemy, unknown64) == 0x064, "");
static_assert(offsetof(SDataEnemy, unknown66) == 0x066, "");
static_assert(offsetof(SDataEnemy, unknown68) == 0x068, "");
static_assert(offsetof(SDataEnemy, unknown99) == 0x099, "");
static_assert(offsetof(SDataEnemy, unknown9e) == 0x09e, "");
static_assert(offsetof(SDataEnemy, unknowna8) == 0x0a8, "");
static_assert(offsetof(SDataEnemy, unknownac) == 0x0ac, "");
static_assert(offsetof(SDataEnemy, unknownb0) == 0x0b0, "");
static_assert(offsetof(SDataEnemy, unknownb8) == 0x0b8, "");
static_assert(sizeof(SDataEnemy) == 0x0bc, "");

class GfDataEnemy {
public:
  static void setupGameParamForLevel(SDataEnemy &dataEnemy, u32 level);
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
