#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

constexpr u32 PARTS_UNKNOWN_4 = 4; // Inferred role: extra parts count; original name unknown.

// Inferred role: bit 9 of SDataEnemy::unknown04 (field damage, unknown05_1), read through the 32-bit word by GmkDmgPhantomManager::listenerGfObj; original name unknown.
constexpr u32 ENEMY_FLAG_UNKNOWN_9 = 1 << 9;

// Inferred role: bit 10 of SDataEnemy::unknown04, set by setupSDataEnemy from GfBdatRsc::isRscEnGenusFlaggimmicktype; original name unknown.
constexpr u32 ENEMY_FLAG_UNKNOWN_10 = 1 << 10;

// Layout from GfDataEnemy::setupSDataEnemy (0x7100299478), which fills each member from a CHR_EnArrange,
// CHR_EnParam or RSC_En column, and from the zeroing stores of SDataEnemy::clear (0x710029285c).
struct SDataEnemy {
  u16 unknown00; // Inferred role: arrange; original member name unknown.
  u8 _002[0x004 - 0x002];
  // setupSDataEnemy sets and clears these flags through the 32-bit word; the accessors read single bits.
  union {
    u32 unknown04; // Inferred role: flags; original member name unknown.
    struct {
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
    };
  };
  u16 unknown08;     // Inferred role: param id; original member name unknown.
  u16 unknown0a;     // Inferred role: blade id; original member name unknown.
  u16 unknown0c;     // Inferred role: name; original member name unknown.
  u8 unknown0e;      // Inferred role: level; original member name unknown.
  u16 unknown10;     // Inferred role: exp rev; original member name unknown.
  u16 unknown12;     // Inferred role: gold rev; original member name unknown.
  u16 unknown14;     // Inferred role: drop table id; original member name unknown.
  u16 unknown16;     // Inferred role: drop table id 2; original member name unknown.
  u16 unknown18;     // Inferred role: drop table id 3; original member name unknown.
  u16 unknown1a;     // Inferred role: precious id; original member name unknown.
  u16 unknown1c;     // Inferred role: scale; original member name unknown.
  u8 unknown1e;      // Inferred role: chr size; original member name unknown.
  u8 unknown1f;      // Inferred role: link radius; original member name unknown.
  u8 unknown20;      // Inferred role: detects; original member name unknown.
  u16 unknown22;     // Inferred role: search range; original member name unknown.
  u16 unknown24;     // Inferred role: search angle; original member name unknown.
  u8 unknown26;      // Inferred role: search radius; original member name unknown.
  u8 unknown27;      // Inferred role: battle area; original member name unknown.
  u8 unknown28;      // Role and original member name unknown.
  u8 unknown29;      // Inferred role: ai group; original member name unknown.
  u8 unknown2a;      // Inferred role: ai group num; original member name unknown.
  u16 unknown2c;     // Inferred role: book id; original member name unknown.
  u16 unknown2e;     // Inferred role: enhance id 1; original member name unknown.
  u16 unknown30;     // Inferred role: enhance id 2; original member name unknown.
  u16 unknown32;     // Inferred role: enhance id 3; original member name unknown.
  u16 unknown34;     // Inferred role: param; original member name unknown.
  u16 unknown36;     // Inferred role: rst debuff rev; original member name unknown.
  u16 unknown38;     // Inferred role: heal pot type rev; original member name unknown.
  u16 unknown3a;     // Inferred role: summon id; original member name unknown.
  u8 unknown3c;      // Inferred role: bgm id; original member name unknown.
  u8 unknown3d;      // Inferred role: se env id; original member name unknown.
  u8 unknown3e;      // Inferred role: zone id; original member name unknown.
  u8 unknown3f;      // Role and original member name unknown.
  u8 unknown40;      // Role and original member name unknown.
  u8 unknown41;      // Inferred role: blade attribute; original member name unknown.
  u8 unknown42;      // Inferred role: extra parts; original member name unknown.
  u16 unknown44;     // Inferred role: resource; original member name unknown.
  u16 unknown46;     // Inferred role: ai id; original member name unknown.
  u8 unknown48;      // Inferred role: enemy role; original member name unknown.
  u8 unknown49;      // Inferred role: walk speed; original member name unknown.
  u8 unknown4a;      // Inferred role: run speed; original member name unknown.
  u8 unknown4b;      // Inferred role: battle speed; original member name unknown.
  u8 unknown4c;      // Inferred role: hp default; original member name unknown.
  u8 unknown4d;      // Inferred role: hp limit; original member name unknown.
  u8 unknown4e;      // Inferred role: scout start hp; original member name unknown.
  u8 unknown4f;      // Inferred role: scout end hp; original member name unknown.
  u16 unknown50;     // Inferred role: hp max rev; original member name unknown.
  u16 unknown52;     // Inferred role: strength rev; original member name unknown.
  u16 unknown54;     // Inferred role: power ether rev; original member name unknown.
  u16 unknown56;     // Inferred role: dex rev; original member name unknown.
  u16 unknown58;     // Inferred role: agility rev; original member name unknown.
  u16 unknown5a;     // Inferred role: luck rev; original member name unknown.
  u16 unknown5c;     // Inferred role: p armor; original member name unknown.
  u16 unknown5e;     // Inferred role: e armor; original member name unknown.
  u8 unknown60;      // Inferred role: resistance power; original member name unknown.
  u8 unknown61;      // Inferred role: resistance ether; original member name unknown.
  u8 unknown62;      // Inferred role: blade attribute; original member name unknown.
  u8 unknown63;      // Inferred role: critical rate; original member name unknown.
  u8 unknown64;      // Inferred role: guard rate; original member name unknown.
  u8 unknown65;      // Inferred role: heal pot drop; original member name unknown.
  u16 unknown66;     // Inferred role: resistance combo; original member name unknown.
  u16 unknown68;     // Inferred role: invincible combo; original member name unknown.
  u16 unknown6a;     // Inferred role: aura; original member name unknown.
  u8 unknown6c;      // Inferred role: dying hp; original member name unknown.
  u8 unknown6d;      // Inferred role: wt normal; original member name unknown.
  u8 unknown6e;      // Inferred role: wt dying; original member name unknown.
  u8 unknown6f;      // Inferred role: hate 0 target; original member name unknown.
  u16 unknown70;     // Inferred role: death arts; original member name unknown.
  u32 unknown74;     // Inferred role: death arts stop; original member name unknown.
  u16 unknown78[16]; // Inferred role: arts; original member name unknown.
  u8 unknown98;      // Inferred role: family; original member name unknown.
  u8 unknown99;      // Inferred role: genus; original member name unknown.
  u8 unknown9a;      // Inferred role: move type; original member name unknown.
  u8 unknown9b;      // Inferred role: field move type; original member name unknown.
  u8 unknown9c;      // Inferred role: memory slot; original member name unknown.
  u16 unknown9e[5];  // Inferred role: equip weapons; original member name unknown.
  u16 unknowna8;     // Inferred role: level; original member name unknown.
  u32 unknownac;     // Inferred role: hp max; original member name unknown.
  u16 unknownb0;     // Inferred role: strength; original member name unknown.
  u16 unknownb2;     // Inferred role: power ether; original member name unknown.
  u16 unknownb4;     // Inferred role: dex; original member name unknown.
  u16 unknownb6;     // Inferred role: agility; original member name unknown.
  u16 unknownb8;     // Inferred role: luck; original member name unknown.

  SDataEnemy();
  SDataEnemy(u32 arrange, u32 level);
  void clear();
};

static_assert(offsetof(SDataEnemy, unknown04) == 0x004, "");
static_assert(offsetof(SDataEnemy, unknown08) == 0x008, "");
static_assert(offsetof(SDataEnemy, unknown0e) == 0x00e, "");
static_assert(offsetof(SDataEnemy, unknown10) == 0x010, "");
static_assert(offsetof(SDataEnemy, unknown12) == 0x012, "");
static_assert(offsetof(SDataEnemy, unknown1e) == 0x01e, "");
static_assert(offsetof(SDataEnemy, unknown1f) == 0x01f, "");
static_assert(offsetof(SDataEnemy, unknown22) == 0x022, "");
static_assert(offsetof(SDataEnemy, unknown28) == 0x028, "");
static_assert(offsetof(SDataEnemy, unknown2a) == 0x02a, "");
static_assert(offsetof(SDataEnemy, unknown2c) == 0x02c, "");
static_assert(offsetof(SDataEnemy, unknown34) == 0x034, "");
static_assert(offsetof(SDataEnemy, unknown3f) == 0x03f, "");
static_assert(offsetof(SDataEnemy, unknown42) == 0x042, "");
static_assert(offsetof(SDataEnemy, unknown44) == 0x044, "");
static_assert(offsetof(SDataEnemy, unknown49) == 0x049, "");
static_assert(offsetof(SDataEnemy, unknown4a) == 0x04a, "");
static_assert(offsetof(SDataEnemy, unknown5c) == 0x05c, "");
static_assert(offsetof(SDataEnemy, unknown60) == 0x060, "");
static_assert(offsetof(SDataEnemy, unknown62) == 0x062, "");
static_assert(offsetof(SDataEnemy, unknown64) == 0x064, "");
static_assert(offsetof(SDataEnemy, unknown66) == 0x066, "");
static_assert(offsetof(SDataEnemy, unknown68) == 0x068, "");
static_assert(offsetof(SDataEnemy, unknown70) == 0x070, "");
static_assert(offsetof(SDataEnemy, unknown74) == 0x074, "");
static_assert(offsetof(SDataEnemy, unknown78) == 0x078, "");
static_assert(offsetof(SDataEnemy, unknown98) == 0x098, "");
static_assert(offsetof(SDataEnemy, unknown99) == 0x099, "");
static_assert(offsetof(SDataEnemy, unknown9a) == 0x09a, "");
static_assert(offsetof(SDataEnemy, unknown9c) == 0x09c, "");
static_assert(offsetof(SDataEnemy, unknown9e) == 0x09e, "");
static_assert(offsetof(SDataEnemy, unknowna8) == 0x0a8, "");
static_assert(offsetof(SDataEnemy, unknownac) == 0x0ac, "");
static_assert(offsetof(SDataEnemy, unknownb0) == 0x0b0, "");
static_assert(offsetof(SDataEnemy, unknownb8) == 0x0b8, "");
static_assert(sizeof(SDataEnemy) == 0x0bc, "");

class GfDataEnemy {
public:
  static void setupGameParamForLevel(SDataEnemy &dataEnemy, u32 level);
  static void setupSDataEnemy(SDataEnemy &dataEnemy, u32 arrange, u32 level);
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
