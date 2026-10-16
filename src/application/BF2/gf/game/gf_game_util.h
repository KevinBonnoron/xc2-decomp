#pragma once
#include "gf/data/gf_data_map.h"
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
  static void addMoney(int money);
  static void addCoin(int coin);
  static void addEther(int ether);
  static void execLevelUp(u32 driver, u32 level);
  static void execLevelUpForDebug(u32 driver, u32 level);
  static void execDriverArtsLevelUp(u32 driver, u32 arts, u32 level);
  static DriverSkillLevelUpResult execDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden);
  static DriverSkillLevelUpResult checkDriverSkillLevelUp(u32 driver, u32 row, u32 level, bool isHidden);
  static void addWp(u32 driver, u32 weaponType, int weaponPoint);
  static void addWpForReserve(int weaponPoint);
  static void addWpForObject(u32 driver, u32 weaponType, int weaponPoint);
  static void addSP(u32 driver, int skillPoint);
  static void addIdeaPoint(u32 driver, u32 idea, int point);
  static void setIdeaPointForDebug(u32 driver, u32 idea, int point);
  static void addDevelopPoint(u32 nation, u32 point);
  static void execDevelopLevelUp();
  static void setDevelopLevelForDebug(u32 nation, u32 level);
  static u32 getTrustRank(u32 blade);
  static void addTrustRankForKizunaRing(u32 blade);
  static void addTrustPoint(u32 blade, u32 trustPoint);
  static void setTrustPointForDebug(u32 blade, u32 trustPoint);
  static void setAchievementReleaseLevel(u32 blade, u32 line, u32 level);
  static u16 getAntiBladeAreaBdatId();
  static bool getGmkTargetPointPos(mm::Vec3 &position, u32 gimmick);
  static bool getGmkTargetPointPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle);
  static bool incEnemySuppress(u32 enemy);
  static bool isEnableDeleteObject(GF_OBJ_HANDLE *handle);
  static u32 getFormationPlayerID(GF_OBJ_HANDLE *handle);
  static void setHp(GF_OBJ_HANDLE *handle, u32 hp);
  static void debugHpZero(GF_OBJ_HANDLE *handle);
  static void debugFallDead(GF_OBJ_HANDLE *handle);
  static const char *getBladeModel(u32 blade, bool isDefault);
  static bool isCondBladeModel(u32 blade);
  static const char *getBladeMotion(u32 blade, bool isDefault);
  static const char *getDriverModel(u32 driver);
  static bool isCondDriverModel(u32 driver);
  static const char *getSalvageDriverModel(u32 driver);
  static u32 getNowHp(GF_OBJ_HANDLE *handle, u32 objectType, u32 id);
  static u32 getMaxHp(GF_OBJ_HANDLE *handle, u32 objectType, u32 id);
  static bool getNowHpForUi(GF_OBJ_HANDLE *handle, u32 *hp);
  static bool getMaxHpForUi(GF_OBJ_HANDLE *handle, u32 *maxHp);
  static void incGameClearCount();
  static void refreshEnhanceState(u32 driver);
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
  static void changeObjAttribute(GF_OBJ_HANDLE *handle, u32 attribute);
  static u32 getObjAttribute(GF_OBJ_HANDLE *handle);
  static void addInGameLog(GAMELOG_PRIO priority, const char *format, ...);
  static void setBladeSelect(GF_OBJ_HANDLE *handle, int slot);
  static GF_OBJ_HANDLE *getDebugPickObj();
  static void startWire(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time);
  static void startWireWithClose(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, f32 time, f32 closeTime, f32 closeDistance);
  static void startWireWithBone(GF_OBJ_HANDLE *handle, GF_OBJ_HANDLE *target, const char *bone, f32 time);
  static void endWire(GF_OBJ_HANDLE *handle, f32 time);
  static void setGameObjWait(GF_OBJ_HANDLE *handle, bool isWait);
  static bool isGameObjWait(GF_OBJ_HANDLE *handle);
  static bool isPlayVoice(GF_OBJ_HANDLE *handle);
  static bool isDispWorldMap(u32 map);
  static u32 getBladeOnBookedItem(u32 blade);
  static bool execActivateUnuseForBlade(u32 blade, bool isRelease);
  static bool execActivateMercenaryTeamForBlade(u32 blade);
  static bool execActivateReserverForBlade(u32 blade);
  static void execEquipMercenariesBlade(u32 driver, u32 blade);
  static u32 execAddRareBlade(const SDataBlade &dataBlade);
  static void setWatchedEvent(u32 event);
  static u32 execAddCommonBlade(const SDataBlade &dataBlade);
  static void changeAlphaBelonging(GF_OBJ_HANDLE *handle, u32 belonging, f32 alpha, f32 time);
  static bool hasBelonging(GF_OBJ_HANDLE *handle, u32 belonging);
  static void execAddDevelopPointArcadia2Iyasaki();
  static void dispRexCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static void dispHomuraCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static void dispMetsuCrystal(GF_OBJ_HANDLE *handle, bool isDisp);
  static void setSaikaLensOff(GF_OBJ_HANDLE *handle);
  static void setSaikaLensOff();
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

class GfGameUtilCloudSea {
public:
  static void setInnCloudSea(CLOUD_SEA cloudSea);
};

} // namespace gf
