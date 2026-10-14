#pragma once
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/bitflag.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataDriverWeapon {
  mm::mtl::FixedArray<u32, 3> slotArts;
  u32 wp;
  u32 totalWp;
};

struct SDataDriverAccessory {
  GfItemHandle handle;
  u16 item;
  u8 _06[0x08 - 0x06];
};

struct SDataPouch {
  GfItemHandle handle;
  u16 item;
  u8 _06;
};

struct SDataDriverSkillRow {
  u16 skills[3];
  u8 _06[0x08 - 0x06];
  u16 level;
};

static_assert(offsetof(SDataDriverSkillRow, level) == 0x08, "");
static_assert(sizeof(SDataDriverSkillRow) == 0x0a, "");

struct SDataDriver {
  u8 _000[0x020 - 0x000];
  u16 activate;
  u16 id;
  s16 bladeSet;
  u16 blades[5];
  SDataDriverSkillRow skillRows[5];
  SDataDriverSkillRow hiddenSkillRows[5];
  u16 level;
  u8 _096[0x0a2 - 0x096];
  u16 pArmor;
  u16 eArmor;
  u8 _0a6[0x0b0 - 0x0a6];
  u32 exp;
  u32 battleExp;
  u32 skillPoint;
  u32 totalSkillPoint;
  SDataDriverWeapon weapons[28];
  u8 artsLevel[0x570 - 0x2f0];
  u8 scenarioMask;
  u8 attachedParty;
  u8 equipDefaultAcce;
  SDataDriverAccessory accessories[2];
  SDataPouch pouches[3];
  mm::mtl::BitFlag<28> activateWeaponTypes;
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
static_assert(offsetof(SDataDriver, activate) == 0x020, "");
static_assert(offsetof(SDataDriver, id) == 0x022, "");
static_assert(offsetof(SDataDriver, bladeSet) == 0x024, "");
static_assert(offsetof(SDataDriver, blades) == 0x026, "");
static_assert(offsetof(SDataDriver, skillRows) == 0x030, "");
static_assert(offsetof(SDataDriver, hiddenSkillRows) == 0x062, "");
static_assert(offsetof(SDataDriver, level) == 0x094, "");
static_assert(offsetof(SDataDriver, pArmor) == 0x0a2, "");
static_assert(offsetof(SDataDriver, eArmor) == 0x0a4, "");
static_assert(offsetof(SDataDriver, exp) == 0x0b0, "");
static_assert(offsetof(SDataDriver, battleExp) == 0x0b4, "");
static_assert(offsetof(SDataDriver, skillPoint) == 0x0b8, "");
static_assert(offsetof(SDataDriver, totalSkillPoint) == 0x0bc, "");
static_assert(offsetof(SDataDriver, weapons) == 0x0c0, "");
static_assert(offsetof(SDataDriver, artsLevel) == 0x2f0, "");
static_assert(offsetof(SDataDriver, scenarioMask) == 0x570, "");
static_assert(offsetof(SDataDriver, attachedParty) == 0x571, "");
static_assert(offsetof(SDataDriver, equipDefaultAcce) == 0x572, "");
static_assert(offsetof(SDataDriver, accessories) == 0x574, "");
static_assert(offsetof(SDataDriver, pouches) == 0x584, "");
static_assert(offsetof(SDataDriver, activateWeaponTypes) == 0x59c, "");
static_assert(sizeof(SDataPouch) == 0x08, "");
static_assert(sizeof(SDataDriver) == 0x5a0, "");

class GfDataDriver {
public:
  static SDataDriver *getSDataDriver(u32 driver);
  static const char *getName(u32 driver);
  static bool getName(u8 *&bdat, u32 &textId, u32 driver);
  static int getRuleSetBlade(u32 driver, u32 blade, int slot);
  static u32 getFavorite(u32 driver, FAVORITE favorite);
  static void setEquipBlade(u32 driver, bool isEquip, int slot);
  static u32 getExpNextLevel(const SDataDriver &dataDriver);
  static u32 getBattleExpNextLevel(const SDataDriver &dataDriver);
  static void calcDriverBaseParamByLevel(SDataDriver &dataDriver);
  static u32 getLevel(u32 driver);
  static bool isActivateParty(u32 driver);
  static int getMaxSetBladeNum(u32 driver);
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
  static u32 getRace(u32 driver);
  static u32 getAiID(u32 driver);
  static bool getDriverAddAnim(mm::mtl::FixStr<128> &animName, u32 driver, u32 weaponType);
  static u32 getDriverID(u32 index);
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
  static u16 getEquipAcce(const SDataDriver &dataDriver, u32 slot);
  static u16 getEquipAcce(u32 driver, u32 slot);
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
