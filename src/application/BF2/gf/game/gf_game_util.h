#pragma once
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "types.h"

namespace mm {
struct Vec3;
}

namespace gf {

struct GF_OBJ_HANDLE;
struct SDataBlade;

enum GAMELOG_PRIO {};

enum DriverSkillLevelUpResult {
  DRIVER_SKILL_LEVEL_UP_OK,
  DRIVER_SKILL_LEVEL_UP_MAX_LEVEL,
  DRIVER_SKILL_LEVEL_UP_INVALID_LEVEL,
  DRIVER_SKILL_LEVEL_UP_NOT_ENOUGH_POINT,
  DRIVER_SKILL_LEVEL_UP_LOCKED,
};

class GfGameUtil {
public:
  static bool isUiGfObjHandleValid(GF_OBJ_HANDLE *handle);
  static u32 getFsLevelSum(u32 fieldSkill);
  static void addCoin(int coin);
  static void addEther(int ether);
  static void execLevelUpForDebug(u32 driver, u32 level);
  static void execDriverArtsLevelUp(u32 driver, u32 arts, u32 level);
  static DriverSkillLevelUpResult execDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden);
  static DriverSkillLevelUpResult checkDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden);
  static void addWp(u32 driver, u32 weaponType, int weaponPoint);
  static void addWpForReserve(int weaponPoint);
  static void addWpForObject(u32 driver, u32 weaponType, int weaponPoint);
  static void addSP(u32 driver, int skillPoint);
  static void setDevelopLevelForDebug(u32 nation, u32 level);
  static u16 getAntiBladeAreaBdatId();
  static bool getGmkTargetPointPos(mm::Vec3 &position, u32 gimmick);
  static bool getGmkTargetPointPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle);
  static bool incEnemySuppress(u32 enemy);
  static bool isEnableDeleteObject(GF_OBJ_HANDLE *handle);
  static const char *getBladeModel(u32 blade, bool isDefault);
  static bool isCondBladeModel(u32 blade);
  static const char *getBladeMotion(u32 blade, bool isDefault);
  static const char *getDriverModel(u32 driver);
  static bool isCondDriverModel(u32 driver);
  static const char *getSalvageDriverModel(u32 driver);
  static void incGameClearCount();
  static void makeWeaponStateIdle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isBattle);
  static void makeWeaponStateIdle(mm::mtl::FixStr<32> &state, u32 driver, bool isBattle);
  static void makeWeaponStateStartBattle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle);
  static void makeStateIdle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isBattle);
  static void makeStateIdleByBlade(mm::mtl::FixStr<32> &state, u32 blade, bool isBattle);
  static void makeWeaponCommandBattle(mm::mtl::FixStr<32> &command, GF_OBJ_HANDLE *handle, bool isStart, bool isMotion);
  static void makeWeaponCommandBattle(mm::mtl::FixStr<32> &command, u32 driver, bool isStart, bool isMotion);
  static void makeWeaponRecieveStateForUiModel(mm::mtl::FixStr<32> &state, u32 weaponType);
  static u32 getKizunaLink(u32 blade);
  static void makeCommandBattle(mm::mtl::FixStr<32> &command, bool isStart);
  static void makeStateBattle(mm::mtl::FixStr<32> &state, GF_OBJ_HANDLE *handle, bool isStart);
  static void makeStateBattleByBlade(mm::mtl::FixStr<32> &state, u32 blade, bool isStart);
  static void requestFieldDamage(GF_OBJ_HANDLE *handle);
  static u32 getObjAttribute(GF_OBJ_HANDLE *handle);
  static void addInGameLog(GAMELOG_PRIO priority, const char *format, ...);
  static GF_OBJ_HANDLE *getDebugPickObj();
  static bool isGameObjWait(GF_OBJ_HANDLE *handle);
  static bool isPlayVoice(GF_OBJ_HANDLE *handle);
  static bool isDispWorldMap(u32 map);
  static bool execActivateMercenaryTeamForBlade(u32 blade);
  static bool execActivateReserverForBlade(u32 blade);
  static void execEquipMercenariesBlade(u32 driver, u32 blade);
  static u32 execAddRareBlade(const SDataBlade &dataBlade);
  static void setWatchedEvent(u32 event);
  static u32 execAddCommonBlade(const SDataBlade &dataBlade);
  static void execAddDevelopPointArcadia2Iyasaki();
  static void dispRexCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static void dispHomuraCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static void dispMetsuCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static bool isDummyBlade(GF_OBJ_HANDLE *handle);
  static bool isHomuraHoodStyle();
  static bool isTrueRex();
  static void changeHikariCurrent(bool hikariCurrent);
  static void setMaxPartyGauge();
  static bool getDriverAcceList(mm::mtl::FixedVector<u16, 16> &drivers);
  static bool isDispRexCrystal();
  static bool isDispHomuraCrystal();
  static bool isDispMetsuCrystal();
  static bool isBladeInVillage(u32 blade);
  static bool setupSaveAchievementPopup(u32 blade, u32 achievement, u32 level);
  static void execSaveAchievementPopup(u32 blade);
};

} // namespace gf
