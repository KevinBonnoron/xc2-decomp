#pragma once
#include <stddef.h>

#include "gf/data/gf_item_handle.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace gf {

class GfInitParamDriver;
struct SDataIdea;

constexpr u32 DRIVER_LEVEL_MAX = 99;
constexpr u32 DRIVER_ARTS_LEVEL_MAX = 5;
constexpr u32 SET_BLADE_NUM_MAX = 5;

struct SDataDriverWeapon {
  mm::mtl::FixedArray<u32, 3> unknown00; // Inferred role: slot arts; original member name unknown.
  u32 unknown0c;                         // Inferred role: wp; original member name unknown.
  u32 unknown10;                         // Inferred role: total wp; original member name unknown.
};

struct SDataDriverAccessory {
  GfItemHandle unknown00; // Inferred role: handle; original member name unknown.
  u16 unknown04;          // Inferred role: item; original member name unknown.
  u8 _06[0x08 - 0x06];
};

struct SDataPouch {
  f32 unknown00; // Inferred role: time; original member name unknown.
  u16 unknown04; // Inferred role: item; original member name unknown.
  u8 _06;
};

struct SDataDriverSkillRow {
  u16 unknown00[3]; // Inferred role: skills; original member name unknown.
  u8 _06[0x08 - 0x06];
  u16 unknown08; // Inferred role: level; original member name unknown.
};

static_assert(offsetof(SDataDriverSkillRow, unknown08) == 0x08, "");
static_assert(sizeof(SDataDriverSkillRow) == 0x0a, "");

struct SDataDriver {
  u8 _000[0x020 - 0x000];
  u16 unknown20;                    // Inferred role: activate; original member name unknown.
  u16 unknown22;                    // Inferred role: id; original member name unknown.
  s16 unknown24;                    // Inferred role: blade set; original member name unknown.
  u16 unknown26[5];                 // Inferred role: blades; original member name unknown.
  SDataDriverSkillRow unknown30[5]; // Inferred role: skill rows; original member name unknown.
  SDataDriverSkillRow unknown62[5]; // Inferred role: hidden skill rows; original member name unknown.
  u16 unknown94;                    // Inferred role: level; original member name unknown.
  u16 unknown96;                    // Inferred role: hp max; original member name unknown.
  u16 unknown98;                    // Inferred role: strength; original member name unknown.
  u16 unknown9a;                    // Inferred role: power ether; original member name unknown.
  u16 unknown9c;                    // Inferred role: dex; original member name unknown.
  u16 unknown9e;                    // Inferred role: agility; original member name unknown.
  u16 unknowna0;                    // Inferred role: luck; original member name unknown.
  u16 unknowna2;                    // Inferred role: p armor; original member name unknown.
  u16 unknowna4;                    // Inferred role: e armor; original member name unknown.
  u8 unknowna6;                     // Inferred role: critical rate; original member name unknown.
  u8 unknowna7;                     // Inferred role: guard rate; original member name unknown.
  u8 _0a8[0x0b0 - 0x0a8];
  u32 unknownb0;                      // Inferred role: exp; original member name unknown.
  u32 unknownb4;                      // Inferred role: battle exp; original member name unknown.
  u32 unknownb8;                      // Inferred role: skill point; original member name unknown.
  u32 unknownbc;                      // Inferred role: total skill point; original member name unknown.
  SDataDriverWeapon unknownc0[28];    // Inferred role: weapons; original member name unknown.
  u8 unknown2f0[0x570 - 0x2f0];       // Inferred role: arts level; original member name unknown.
  u8 unknown570;                      // Inferred role: scenario mask; original member name unknown.
  u8 unknown571;                      // Inferred role: attached party; original member name unknown.
  u8 unknown572;                      // Inferred role: equip default acce; original member name unknown.
  SDataDriverAccessory unknown574[2]; // Inferred role: accessories; original member name unknown.
  SDataPouch unknown584[3];           // Inferred role: pouches; original member name unknown.
  mm::mtl::BitFlag<28> unknown59c;    // Inferred role: activate weapon types; original member name unknown.
};

enum DBSLOT {};
enum FAVORITE {
  FAVORITE_CATEGORY_0,
  FAVORITE_CATEGORY_1,
  FAVORITE_ITEM_0,
  FAVORITE_ITEM_1,
};

static_assert(sizeof(SDataDriverWeapon) == 0x14, "");
static_assert(sizeof(SDataDriverAccessory) == 0x08, "");
static_assert(offsetof(SDataDriver, unknown20) == 0x020, "");
static_assert(offsetof(SDataDriver, unknown22) == 0x022, "");
static_assert(offsetof(SDataDriver, unknown24) == 0x024, "");
static_assert(offsetof(SDataDriver, unknown26) == 0x026, "");
static_assert(offsetof(SDataDriver, unknown30) == 0x030, "");
static_assert(offsetof(SDataDriver, unknown62) == 0x062, "");
static_assert(offsetof(SDataDriver, unknown94) == 0x094, "");
static_assert(offsetof(SDataDriver, unknown96) == 0x096, "");
static_assert(offsetof(SDataDriver, unknowna0) == 0x0a0, "");
static_assert(offsetof(SDataDriver, unknowna2) == 0x0a2, "");
static_assert(offsetof(SDataDriver, unknowna4) == 0x0a4, "");
static_assert(offsetof(SDataDriver, unknowna6) == 0x0a6, "");
static_assert(offsetof(SDataDriver, unknowna7) == 0x0a7, "");
static_assert(offsetof(SDataDriver, unknownb0) == 0x0b0, "");
static_assert(offsetof(SDataDriver, unknownb4) == 0x0b4, "");
static_assert(offsetof(SDataDriver, unknownb8) == 0x0b8, "");
static_assert(offsetof(SDataDriver, unknownbc) == 0x0bc, "");
static_assert(offsetof(SDataDriver, unknownc0) == 0x0c0, "");
static_assert(offsetof(SDataDriver, unknown2f0) == 0x2f0, "");
static_assert(offsetof(SDataDriver, unknown570) == 0x570, "");
static_assert(offsetof(SDataDriver, unknown571) == 0x571, "");
static_assert(offsetof(SDataDriver, unknown572) == 0x572, "");
static_assert(offsetof(SDataDriver, unknown574) == 0x574, "");
static_assert(offsetof(SDataDriver, unknown584) == 0x584, "");
static_assert(offsetof(SDataDriver, unknown59c) == 0x59c, "");
static_assert(sizeof(SDataPouch) == 0x08, "");
static_assert(sizeof(SDataDriver) == 0x5a0, "");

class GfDataDriver {
public:
  static SDataDriver *getSDataDriver(u32 driver);
  static SDataIdea *getSDataIdea(u32 driver);
  static const char *getName(u32 driver);
  static bool getName(u8 *&bdat, u32 &textId, u32 driver);
  static int getRuleSetBlade(u32 driver, u32 blade, int slot);
  static u32 getFavorite(u32 driver, FAVORITE favorite);
  static bool isFavoriteCategory(u32 driver, u32 item);
  static void setEquipBlade(u32 driver, bool isEquip, int slot);
  static u32 getExpNextLevel(const SDataDriver &dataDriver);
  static u32 getExpNextLevel(u32 driver);
  static u32 getBattleExpNextLevel(const SDataDriver &dataDriver);
  static u32 getBattleExpNextLevel(u32 driver);
  static u32 getDummyBlade(u32 driver);
  static u32 getDummyBlade(const SDataDriver &dataDriver);
  static const char *getBelongingModelName(const GfInitParamDriver &param);
  static bool isActivatePartyAll(u32 driver);
  static void setPouchData(u32 driver, u32 slot, const SDataPouch &pouch);
  static void calcDriverBaseParamByLevel(SDataDriver &dataDriver);
  static u32 getLevel(u32 driver);
  static bool isActivateParty(u32 driver);
  static u32 getDriverActivateType(u32 driver);
  static u32 getDriverActivateType(const SDataDriver &dataDriver);
  static void setBlade(u32 driver, u32 blade, int slot);
  static int getSetIdByBlade(u32 driver, u32 blade);
  static int getSetIdByBlade(const SDataDriver &dataDriver, u32 blade);
  static int getMaxSetBladeNum(u32 driver);
  static int getSetIdByDummyBlade(u32 driver);
  static u32 getBlade(u32 driver, int slot);
  static void unsetBlade(u32 blade);
  static SDataPouch *getPouchData(u32 driver, u32 slot);
  static int getBladeSet(u32 driver);
  static bool isActivateReserver(u32 driver);
  static bool isActivateUnuse(u32 driver);
  static void setLevel(SDataDriver &dataDriver, u32 level);
  static void setLevel(u32 driver, u32 level);
  static void setExp(u32 driver, u32 exp);
  static void setBattleExp(u32 driver, u32 battleExp);
  static void openDriverArtsForLevelup(u32 driver);
  static u32 getBlade(const SDataDriver &dataDriver, int slot);
  static int getBladeSet(const SDataDriver &dataDriver);
  static int getMaxSetBladeNum(const SDataDriver &dataDriver);
  static u16 getDriverWeapon(u32 driver);
  static u16 getDriverWeapon(const SDataDriver &dataDriver);
  static u8 getDriverWpnType(u32 driver);
  static u8 getDriverWpnType(const SDataDriver &dataDriver);
  static u16 getDefaultWpnType(u32 driver);
  static u16 getDefaultWpnType(const SDataDriver &dataDriver);
  static bool getDriverEquipWpnType(mm::mtl::FixedVector<u16, 32> &weaponTypes, u32 driver);
  static u32 getDriverArtsID(u32 driver, u32 blade, u32 index);
  static u32 getDriverArtsLevel(u32 driver, u32 blade, u32 index);
  static u8 getDriverArtsLevel(const SDataDriver &dataDriver, u32 arts);
  static u32 getDriverArtsIcon(u32 arts);
  static const char *getModelResourceName(u32 driver);
  static const char *getMotionResourceName(u32 driver);
  static const char *getDebugName(u32 driver);
  static bool debugGetNameWithClass(mm::mtl::FixStr<128> &name, u32 driver);
  static u32 getRace(u32 driver);
  static u32 getAiID(u32 driver);
  static bool getDriverAddAnim(mm::mtl::FixStr<128> &animName, u32 driver, u32 weaponType);
  static u32 getDriverID(u32 index);
  static u32 getDriverRelativeID(u32 driver);
  static u32 getLevel(const SDataDriver &dataDriver);
  static u32 getExp(const SDataDriver &dataDriver);
  static u32 getBattleExp(const SDataDriver &dataDriver);
  static bool isEnableLevelUp(u32 driver);
  static bool isEnableLevelUp(const SDataDriver &dataDriver);
  static u32 getExp(u32 driver);
  static u32 getBattleExp(u32 driver);
  static u32 getBattleExpNextLevelAll(u32 driver);
  static u32 getBattleExpNextLevelAll(const SDataDriver &dataDriver);
  static u32 getExpSetLevel(u32 driver, u32 level);
  static u32 getExpSetLevel(const SDataDriver &dataDriver, u32 level);
  static u32 getExpUsed(u32 driver);
  static u32 getExpUsed(const SDataDriver &dataDriver);
  static bool isDummyDriver(u32 driver);
  static bool isScenarioMask(u32 driver);
  static u32 getDriverBySetBlade(u32 blade);
  static void setScenarioMask(u32 driver, bool scenarioMask);
  static bool isEnableEquipWeapon(u32 driver, u32 weaponType);
  static bool isEnableEquipWeapon(const SDataDriver &dataDriver, u32 weaponType);
  static u32 getHpMaxRev(u32 driver);
  static u32 getHpMaxRev(const SDataDriver &dataDriver);
  static u32 getStrengthRev(u32 driver);
  static u32 getStrengthRev(const SDataDriver &dataDriver);
  static u32 getPowEtherRev(u32 driver);
  static u32 getPowEtherRev(const SDataDriver &dataDriver);
  static u32 getDexRev(u32 driver);
  static u32 getDexRev(const SDataDriver &dataDriver);
  static u32 getAgilityRev(u32 driver);
  static u32 getAgilityRev(const SDataDriver &dataDriver);
  static u32 getLuckRev(u32 driver);
  static u32 getLuckRev(const SDataDriver &dataDriver);
  static u32 getClass(u32 driver);
  static u32 getClass(const SDataDriver &dataDriver);
  static int getWeaponEabFileIdx(u32 driver, int slot);
  static int getWeaponEfbFileIdx(u32 driver, int slot);
  static int getWeaponEfbFileIdx(int slot);
  static int getWeaponSwtFileIdx(u32 driver, int slot);
  static bool getEquipAcceEnahnce(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver);
  static bool getEquipAcceEnhance(mm::mtl::FixedVector<u16, 64> &enhances, const SDataDriver &dataDriver);
  static u32 getEquipAcceEnahnce(u32 driver, u32 slot);
  static u32 getEquipAcceEnhance(const SDataDriver &dataDriver, u32 slot);
  static u32 getEquipAcce(const SDataDriver &dataDriver, u32 slot);
  static u32 getEquipAcce(u32 driver, u32 slot);
  static GfItemHandle getEquipAcceHandle(u32 driver, u32 slot);
  static GfItemHandle getEquipAcceHandle(const SDataDriver &dataDriver, u32 slot);
  static void setEquipAcce(u32 driver, u32 slot, u32 item);
  static void setEquipAcce(SDataDriver &dataDriver, u32 slot, u32 item);
  static void setEquipAcceHandle(u32 driver, u32 slot, GfItemHandle handle);
  static void setEquipAcceHandle(SDataDriver &dataDriver, u32 slot, GfItemHandle handle);
  static void getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, u32 driver);
  static void getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, const SDataDriver &dataDriver);
  static const char *getVoiceStr(u32 driver);
  static const char *getVoiceStr(const SDataDriver &dataDriver);
  static u32 getSkillPoint(u32 driver);
  static u32 getSkillPoint(const SDataDriver &dataDriver);
  static void addSkillPoint(u32 driver, int skillPoint);
  static void addSkillPoint(SDataDriver &dataDriver, int skillPoint);
  static void getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver);
  static void getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, const SDataDriver &dataDriver);
  static u32 getExtraMountNpcRsc(u32 driver);
  static const char *getExtraMountBone(u32 driver);
  static u32 getExtraMountCondition(u32 driver);
  static int getDeathBlowEfbFileIdx(DBSLOT slot, int index);
  static int getDebugAppendDeathBlowEfbFileIdx(u32 index);
  static int getWeaponEabFileIdx(int slot);
  static int getDeathBlowEabFileIdx(DBSLOT slot, int index);
  static int getDebugAppendDeathBlowEabFileIdx(u32 index);
  static int getWeaponSwtFileIdx(int slot);
  static int getWeaponAnmFileIdx(int slot);
  static const char *getBelongingMountBone();
  static const char *getBelongingMountBoneA();
  static const char *getBelongingMountBoneB();
  static u32 getPouchItemNum(u32 driver, u32 item);
  static bool isUsedFavorite(u32 driver, FAVORITE favorite);
  static bool getPouchEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver);
  static u8 getFavoritePouchNum(u32 driver, FAVORITE favorite);
  static u32 getFootStep(u32 driver);
  static u32 getFootStepEffect(u32 driver);
  static bool isActivateWeaponType(u32 driver, u32 weaponType);
  static void setActivateWeaponType(u32 driver, u32 weaponType);
  static bool isDriver(u32 driver);
  static u32 getEyeRotControl(u32 driver);
  static bool isAttachedParty(u32 driver);
  static bool isEquipDefaultAcce(u32 driver);
};

} // namespace gf
