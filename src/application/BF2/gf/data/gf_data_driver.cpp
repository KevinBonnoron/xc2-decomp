#include "gf/data/gf_data_driver.h"

#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"

namespace gf {

enum {
  FLAG_USED_FAVORITE = 0xf8c,
};

constexpr u32 DRIVER_COUNT = 16;
constexpr u32 SET_BLADE_NUM_NORMAL = 3;
constexpr u32 SET_BLADE_NUM_REX = 5;
constexpr u32 POUCH_COUNT = 3;
constexpr int DEATH_BLOW_PER_SLOT = 5;
constexpr int FILE_INDEX_WEAPON_ANM = 0x30;
constexpr int FILE_INDEX_WEAPON_SWT = 0x65;
constexpr int FILE_INDEX_WEAPON_EAB = 0x9a;
constexpr int FILE_INDEX_DEATH_BLOW_EAB = 0xb4;
constexpr int FILE_INDEX_DEBUG_APPEND_DEATH_BLOW_EAB = 0xb5;
constexpr int FILE_INDEX_WEAPON_EFB = 0x26f;
constexpr int FILE_INDEX_DEATH_BLOW_EFB = 0x289;
constexpr int FILE_INDEX_DEBUG_APPEND_DEATH_BLOW_EFB = 0x28f;

SDataDriver *GfDataDriver::getSDataDriver(u32 driver) {
  u32 index = driver - 1;
  SDataGame *dataGame = GfDataManager::getDataGame();
  return &dataGame->drivers[index < DRIVER_COUNT ? index : 1];
}

u32 GfDataDriver::getLevel(u32 driver) { return getLevel(*getSDataDriver(driver)); }

int GfDataDriver::getMaxSetBladeNum(u32 driver) {
  if (driver == 0) {
    return 0;
  }

  return getMaxSetBladeNum(*getSDataDriver(driver));
}

u32 GfDataDriver::getBlade(u32 driver, int slot) {
  if (driver == 0) {
    return 0;
  }

  return getBlade(*getSDataDriver(driver), slot);
}

SDataPouch *GfDataDriver::getPouchData(u32 driver, u32 slot) { return &getSDataDriver(driver)->pouches[slot]; }

int GfDataDriver::getBladeSet(u32 driver) {
  if (driver == 0) {
    return -1;
  }

  return getBladeSet(*getSDataDriver(driver));
}

void GfDataDriver::setLevel(SDataDriver &dataDriver, u32 level) {
  dataDriver.level = level;
  calcDriverBaseParamByLevel(dataDriver);
}

void GfDataDriver::setLevel(u32 driver, u32 level) { setLevel(*getSDataDriver(driver), level); }

void GfDataDriver::setExp(u32 driver, u32 exp) { getSDataDriver(driver)->exp = exp; }

void GfDataDriver::setBattleExp(u32 driver, u32 battleExp) { getSDataDriver(driver)->battleExp = battleExp; }

u32 GfDataDriver::getBlade(const SDataDriver &dataDriver, int slot) {
  if (slot < 0) {
    slot = dataDriver.bladeSet;
  }

  if (slot < 0) {
    return 0;
  }

  return dataDriver.blades[slot];
}

int GfDataDriver::getBladeSet(const SDataDriver &dataDriver) { return dataDriver.bladeSet; }

int GfDataDriver::getMaxSetBladeNum(const SDataDriver &dataDriver) {
  if (dataDriver.id == 0) {
    return 0;
  }

  return dataDriver.id == DRIVER_REX ? SET_BLADE_NUM_REX : SET_BLADE_NUM_NORMAL;
}

bool GfDataDriver::isEnableEquipWeapon(u32 driver, u32 weaponType) { return isEnableEquipWeapon(*getSDataDriver(driver), weaponType); }

bool GfDataDriver::isEnableEquipWeapon(const SDataDriver &dataDriver, u32 weaponType) {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  if (bdatDriver->getChrDrStart() > dataDriver.id) {
    return false;
  }

  bool isEnable = false;
  switch (bdatDriver->getChrDrWpnType(dataDriver.id, weaponType - 1)) {
  case 0:
    isEnable = false;
    break;
  case 1:
  case 2:
  case 3:
  case 4:
    isEnable = true;
    break;
  }

  return isEnable;
}

u16 GfDataDriver::getDriverWeapon(u32 driver) { return getDriverWeapon(*getSDataDriver(driver)); }

u16 GfDataDriver::getDriverWeapon(const SDataDriver &dataDriver) {
  u32 blade = getBlade(dataDriver, -1);
  if (blade == 0) {
    return 0;
  }

  return GfDataBlade::getSDataBlade(blade)->weapon;
}

u8 GfDataDriver::getDriverWpnType(u32 driver) { return getDriverWpnType(*getSDataDriver(driver)); }

u8 GfDataDriver::getDriverWpnType(const SDataDriver &dataDriver) {
  u32 blade = getBlade(dataDriver, -1);
  if (blade == 0) {
    return 0;
  }

  return GfDataBlade::getSDataBlade(blade)->weaponType;
}

u16 GfDataDriver::getDefaultWpnType(u32 driver) { return getDefaultWpnType(*getSDataDriver(driver)); }

u16 GfDataDriver::getDefaultWpnType(const SDataDriver &dataDriver) {
  u8 weaponType = getDriverWpnType(dataDriver);
  if (weaponType != 0) {
    return weaponType;
  }

  mm::mtl::FixedVector<u16, 32> weaponTypes;
  bool isFound = getDriverEquipWpnType(weaponTypes, dataDriver.id);
  return isFound ? *weaponTypes.begin() : 0;
}

u32 GfDataDriver::getDriverArtsID(u32 driver, u32 blade, u32 index) {
  DataParamAcc dataParamAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  u32 arts = bdatBattle->getArtsDrStart();
  u32 end = bdatBattle->getArtsDrEnd();
  u32 weaponType = dataParamAcc.getWeaponType(-1, false);
  u32 count = 0;
  for (; arts < end; arts++) {
    if (bdatBattle->getArtsDrDriver(arts) == driver && bdatBattle->getArtsDrWpnType(arts) == weaponType) {
      if (count == index) {
        return arts;
      }

      count++;
    }
  }

  return 0;
}

u32 GfDataDriver::getDriverArtsLevel(u32 driver, u32 blade, u32 index) {
  u32 arts = getDriverArtsID(driver, blade, index);
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
  return dataParamAcc.getDriverArtsLevel(arts);
}

u8 GfDataDriver::getDriverArtsLevel(const SDataDriver &dataDriver, u32 arts) { return dataDriver.artsLevel[arts]; }

u32 GfDataDriver::getDriverArtsIcon(u32 arts) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  if (arts < bdatBattle->getArtsDrStart() || arts >= bdatBattle->getArtsDrEnd()) {
    return 0;
  }

  return bdatBattle->getArtsDrUI(arts);
}

const char *GfDataDriver::getModelResourceName(u32 driver) { return GfBdatChrDr::get()->getChrDrModel(driver); }

const char *GfDataDriver::getMotionResourceName(u32 driver) { return GfBdatChrDr::get()->getChrDrMotion(driver); }

const char *GfDataDriver::getDebugName(u32 driver) { return GfBdatChrDr::get()->getChrDrDebugName(driver); }

u32 GfDataDriver::getRace(u32 driver) { return GfBdatChrDr::get()->getChrDrRace(driver); }

u32 GfDataDriver::getAiID(u32 driver) { return GfBdatChrDr::get()->getChrDrAiID(driver); }

bool GfDataDriver::getDriverAddAnim(mm::mtl::FixStr<128> &animName, u32 driver, u32 weaponType) {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
  if (!dataParamAcc.isValid()) {
    return false;
  }

  if (bdatDriver->getChrDrWpnType(driver, weaponType - 1) == 0) {
    return false;
  }

  const char *modelName = dataParamAcc.getModelResourceName();
  if (weaponType >= 10) {
    animName.format("%s_%d", modelName, weaponType);
  } else {
    animName.format("%s_0%d", modelName, weaponType);
  }

  return true;
}

u32 GfDataDriver::getDriverID(u32 index) { return index < DRIVER_COUNT ? index + 1 : 1; }

u32 GfDataDriver::getLevel(const SDataDriver &dataDriver) { return dataDriver.level; }

u32 GfDataDriver::getExp(const SDataDriver &dataDriver) { return dataDriver.exp; }

u32 GfDataDriver::getBattleExp(const SDataDriver &dataDriver) { return dataDriver.battleExp; }

bool GfDataDriver::isEnableLevelUp(u32 driver) { return isEnableLevelUp(*getSDataDriver(driver)); }

bool GfDataDriver::isEnableLevelUp(const SDataDriver &dataDriver) {
  u32 level = dataDriver.level;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  u32 growEnd = bdatBattle->getGrowEnd();
  if (level >= DRIVER_LEVEL_MAX || level >= growEnd - 1) {
    return false;
  }

  u32 totalExp = dataDriver.exp + dataDriver.battleExp;
  return totalExp >= bdatBattle->getGrowLevelExp(level + 1);
}

u32 GfDataDriver::getExp(u32 driver) { return getExp(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExp(u32 driver) { return getBattleExp(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExpNextLevelAll(u32 driver) { return getBattleExpNextLevelAll(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExpNextLevelAll(const SDataDriver &dataDriver) {
  u32 level = dataDriver.level;
  return GfBdatBtl::get()->getGrowLevelExp(level + 1);
}

u32 GfDataDriver::getExpSetLevel(u32 driver, u32 level) { return getExpSetLevel(*getSDataDriver(driver), level); }

u32 GfDataDriver::getExpSetLevel(const SDataDriver &, u32 level) { return GfBdatBtl::get()->getGrowLevelExp(level); }

u32 GfDataDriver::getExpUsed(u32 driver) {
  u32 level = getSDataDriver(driver)->level;
  u32 expUsed = 0;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 usedLevel = 0; usedLevel < level; usedLevel++) {
    expUsed += bdatBattle->getGrowLevelExp(usedLevel + 1);
  }

  return expUsed;
}

u32 GfDataDriver::getExpUsed(const SDataDriver &dataDriver) {
  u32 level = dataDriver.level;
  return GfBdatBtl::get()->getGrowLevelExp(level);
}

bool GfDataDriver::isDummyDriver(u32) { return false; }

bool GfDataDriver::isScenarioMask(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->scenarioMask == 1;
}

void GfDataDriver::setScenarioMask(u32 driver, bool scenarioMask) {
  SDataDriver *dataDriver = getSDataDriver(driver);
  dataDriver->scenarioMask = scenarioMask;
}

u32 GfDataDriver::getHpMaxRev(u32 driver) { return getHpMaxRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getStrengthRev(u32 driver) { return getStrengthRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getPowEtherRev(u32 driver) { return getPowEtherRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getDexRev(u32 driver) { return getDexRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getAgilityRev(u32 driver) { return getAgilityRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getLuckRev(u32 driver) { return getLuckRev(*getSDataDriver(driver)); }

u32 GfDataDriver::getClass(u32 driver) { return getClass(*getSDataDriver(driver)); }

int GfDataDriver::getWeaponEabFileIdx(u32 driver, int slot) {
  {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
    if (!dataParamAcc.isValid()) {
      slot = -1;
    } else if (slot < 0) {
      slot = dataParamAcc.getBladeSet(false);
    }
  }

  return slot < 0 ? -1 : slot + FILE_INDEX_WEAPON_EAB;
}

int GfDataDriver::getWeaponEfbFileIdx(u32 driver, int slot) {
  {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
    if (!dataParamAcc.isValid()) {
      slot = -1;
    } else if (slot < 0) {
      slot = dataParamAcc.getBladeSet(false);
    }
  }

  return getWeaponEfbFileIdx(slot);
}

int GfDataDriver::getWeaponEfbFileIdx(int slot) { return (slot < 0 ? 0 : slot) + FILE_INDEX_WEAPON_EFB; }

int GfDataDriver::getWeaponSwtFileIdx(u32 driver, int slot) {
  {
    DataParamAcc dataParamAcc(OBJECT_TYPE_DRIVER, driver, static_cast<GimmickType>(0));
    if (!dataParamAcc.isValid()) {
      slot = -1;
    } else if (slot < 0) {
      slot = dataParamAcc.getBladeSet(false);
    }
  }

  return slot < 0 ? -1 : slot + FILE_INDEX_WEAPON_SWT;
}

bool GfDataDriver::getEquipAcceEnahnce(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver) {
  return getEquipAcceEnhance(enhances, *getSDataDriver(driver));
}

u32 GfDataDriver::getEquipAcceEnahnce(u32 driver, u32 slot) { return getEquipAcceEnhance(*getSDataDriver(driver), slot); }

u32 GfDataDriver::getEquipAcceEnhance(const SDataDriver &dataDriver, u32 slot) {
  if (dataDriver.accessories[slot].item == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcEquipEnhance1(dataDriver.accessories[slot].item);
}

u32 GfDataDriver::getEquipAcce(const SDataDriver &dataDriver, u32 slot) { return dataDriver.accessories[slot].item; }

u32 GfDataDriver::getEquipAcce(u32 driver, u32 slot) { return getEquipAcce(*getSDataDriver(driver), slot); }

GfItemHandle GfDataDriver::getEquipAcceHandle(u32 driver, u32 slot) { return getEquipAcceHandle(*getSDataDriver(driver), slot); }

GfItemHandle GfDataDriver::getEquipAcceHandle(const SDataDriver &dataDriver, u32 slot) { return dataDriver.accessories[slot].handle; }

void GfDataDriver::setEquipAcce(u32 driver, u32 slot, u32 item) {
  if (driver == 0) {
    return;
  }

  setEquipAcce(*getSDataDriver(driver), slot, item);
}

void GfDataDriver::setEquipAcce(SDataDriver &dataDriver, u32 slot, u32 item) { dataDriver.accessories[slot].item = item; }

void GfDataDriver::setEquipAcceHandle(u32 driver, u32 slot, GfItemHandle handle) {
  if (driver == 0) {
    return;
  }

  setEquipAcceHandle(*getSDataDriver(driver), slot, handle);
}

void GfDataDriver::setEquipAcceHandle(SDataDriver &dataDriver, u32 slot, GfItemHandle handle) { dataDriver.accessories[slot].handle = handle; }

void GfDataDriver::getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, u32 driver) { getEquipWpnType(weaponTypes, *getSDataDriver(driver)); }

void GfDataDriver::getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, const SDataDriver &dataDriver) {
  weaponTypes.clear();
  for (u32 weaponType = 1; weaponType <= WEAPON_TYPE_COUNT; weaponType++) {
    if (isEnableEquipWeapon(dataDriver.id, weaponType)) {
      weaponTypes.push_back(weaponType);
    }
  }
}

const char *GfDataDriver::getVoiceStr(u32 driver) { return getVoiceStr(*getSDataDriver(driver)); }

const char *GfDataDriver::getVoiceStr(const SDataDriver &dataDriver) { return GfBdatChrDr::get()->getChrDrVoice(dataDriver.id); }

u32 GfDataDriver::getSkillPoint(u32 driver) { return getSkillPoint(*getSDataDriver(driver)); }

u32 GfDataDriver::getSkillPoint(const SDataDriver &dataDriver) { return dataDriver.skillPoint; }

void GfDataDriver::addSkillPoint(u32 driver, int skillPoint) { addSkillPoint(*getSDataDriver(driver), skillPoint); }

void GfDataDriver::addSkillPoint(SDataDriver &dataDriver, int skillPoint) {
  dataDriver.skillPoint += skillPoint;
  if (skillPoint > 0) {
    dataDriver.totalSkillPoint += skillPoint;
  }
}

void GfDataDriver::getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver) { getValidEnhance(enhances, *getSDataDriver(driver)); }

u32 GfDataDriver::getExtraMountNpcRsc(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountNpc(driver); }

const char *GfDataDriver::getExtraMountBone(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountBone(driver); }

u32 GfDataDriver::getExtraMountCondition(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountCond(driver); }

int GfDataDriver::getDeathBlowEfbFileIdx(DBSLOT slot, int index) {
  return (index < 0 ? slot + 1 : slot * DEATH_BLOW_PER_SLOT + index) + FILE_INDEX_DEATH_BLOW_EFB;
}

int GfDataDriver::getDebugAppendDeathBlowEfbFileIdx(u32 index) { return index + FILE_INDEX_DEBUG_APPEND_DEATH_BLOW_EFB; }

int GfDataDriver::getWeaponEabFileIdx(int slot) { return (slot < 0 ? 0 : slot) + FILE_INDEX_WEAPON_EAB; }

int GfDataDriver::getDeathBlowEabFileIdx(DBSLOT slot, int index) {
  return (index < 0 ? slot + 1 : slot * DEATH_BLOW_PER_SLOT + index) + FILE_INDEX_DEATH_BLOW_EAB;
}

int GfDataDriver::getDebugAppendDeathBlowEabFileIdx(u32 index) { return index + FILE_INDEX_DEBUG_APPEND_DEATH_BLOW_EAB; }

int GfDataDriver::getWeaponSwtFileIdx(int slot) { return (slot < 0 ? 0 : slot) + FILE_INDEX_WEAPON_SWT; }

int GfDataDriver::getWeaponAnmFileIdx(int slot) { return (slot < 0 ? 0 : slot) + FILE_INDEX_WEAPON_ANM; }

const char *GfDataDriver::getBelongingMountBone() { return "MT_wire"; }

const char *GfDataDriver::getBelongingMountBoneA() { return "EX_wireA"; }

const char *GfDataDriver::getBelongingMountBoneB() { return "EX_wireB"; }

u32 GfDataDriver::getPouchItemNum(u32 driver, u32 item) {
  if (item == 0) {
    return 0;
  }

  u32 itemNum = 0;
  for (u32 slot = 0; slot < POUCH_COUNT; slot++) {
    if (getSDataDriver(driver)->pouches[slot].item == item) {
      itemNum++;
    }
  }

  return itemNum;
}

bool GfDataDriver::isUsedFavorite(u32 driver, FAVORITE favorite) {
  return (GfGameFlag::getLocal(8, FLAG_USED_FAVORITE + driver) & 1 << favorite) != 0;
}

u32 GfDataDriver::getFootStep(u32 driver) { return GfBdatChrDr::get()->getChrDrFootStep(driver); }

u32 GfDataDriver::getFootStepEffect(u32 driver) { return GfBdatChrDr::get()->getChrDrFootStepEffect(driver); }

bool GfDataDriver::isActivateWeaponType(u32 driver, u32 weaponType) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->activateWeaponTypes.test(weaponType);
}

void GfDataDriver::setActivateWeaponType(u32 driver, u32 weaponType) {
  if (driver == 0) {
    return;
  }

  getSDataDriver(driver)->activateWeaponTypes.set(weaponType);
}

bool GfDataDriver::isDriver(u32 driver) { return driver >= DRIVER_REX && driver <= DRIVER_SHIN_2; }

u32 GfDataDriver::getEyeRotControl(u32 driver) {
  if (driver == 0) {
    return 0;
  }

  return GfBdatChrDr::get()->getChrDrEyeRot(driver);
}

bool GfDataDriver::isAttachedParty(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->attachedParty != 0;
}

bool GfDataDriver::isEquipDefaultAcce(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->equipDefaultAcce != 0;
}

} // namespace gf
