#include "gf/data/gf_data_driver.h"

#include "bdat.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_character_id.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_game.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_manager.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/data/gf_data_party.h"
#include "gf/data/gf_data_weapon.h"
#include "gf/data/gf_game_flag.h"
#include "gf/data/gf_object_type.h"
#include "gf/object/gf_init_param.h"
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
  return &dataGame->unknown2c[index < DRIVER_COUNT ? index : 1];
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

SDataPouch *GfDataDriver::getPouchData(u32 driver, u32 slot) { return &getSDataDriver(driver)->unknown584[slot]; }

int GfDataDriver::getBladeSet(u32 driver) {
  if (driver == 0) {
    return -1;
  }

  return getBladeSet(*getSDataDriver(driver));
}

void GfDataDriver::setLevel(SDataDriver &dataDriver, u32 level) {
  dataDriver.unknown94 = level;
  calcDriverBaseParamByLevel(dataDriver);
}

void GfDataDriver::setLevel(u32 driver, u32 level) { setLevel(*getSDataDriver(driver), level); }

void GfDataDriver::setExp(u32 driver, u32 exp) { getSDataDriver(driver)->unknownb0 = exp; }

void GfDataDriver::setBattleExp(u32 driver, u32 battleExp) { getSDataDriver(driver)->unknownb4 = battleExp; }

u32 GfDataDriver::getBlade(const SDataDriver &dataDriver, int slot) {
  if (slot < 0) {
    slot = dataDriver.unknown24;
  }

  if (slot < 0) {
    return 0;
  }

  return dataDriver.unknown26[slot];
}

int GfDataDriver::getBladeSet(const SDataDriver &dataDriver) { return dataDriver.unknown24; }

int GfDataDriver::getMaxSetBladeNum(const SDataDriver &dataDriver) {
  if (dataDriver.unknown22 == 0) {
    return 0;
  }

  return dataDriver.unknown22 == DRIVER_REX ? SET_BLADE_NUM_REX : SET_BLADE_NUM_NORMAL;
}

bool GfDataDriver::isEnableEquipWeapon(u32 driver, u32 weaponType) { return isEnableEquipWeapon(*getSDataDriver(driver), weaponType); }

bool GfDataDriver::isEnableEquipWeapon(const SDataDriver &dataDriver, u32 weaponType) {
  GfBdatChrDr *bdatDriver = GfBdatChrDr::get();
  if (bdatDriver->getChrDrStart() > dataDriver.unknown22) {
    return false;
  }

  bool isEnable = false;
  switch (bdatDriver->getChrDrWpnType(dataDriver.unknown22, weaponType - 1)) {
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

  return GfDataBlade::getSDataBlade(blade)->unknown82c;
}

u8 GfDataDriver::getDriverWpnType(u32 driver) { return getDriverWpnType(*getSDataDriver(driver)); }

u8 GfDataDriver::getDriverWpnType(const SDataDriver &dataDriver) {
  u32 blade = getBlade(dataDriver, -1);
  if (blade == 0) {
    return 0;
  }

  return GfDataBlade::getSDataBlade(blade)->unknown821;
}

u16 GfDataDriver::getDefaultWpnType(u32 driver) { return getDefaultWpnType(*getSDataDriver(driver)); }

u16 GfDataDriver::getDefaultWpnType(const SDataDriver &dataDriver) {
  u8 weaponType = getDriverWpnType(dataDriver);
  if (weaponType != 0) {
    return weaponType;
  }

  mm::mtl::FixedVector<u16, 32> weaponTypes;
  bool isFound = getDriverEquipWpnType(weaponTypes, dataDriver.unknown22);
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

u8 GfDataDriver::getDriverArtsLevel(const SDataDriver &dataDriver, u32 arts) { return dataDriver.unknown2f0[arts]; }

u32 GfDataDriver::getDriverArtsIcon(u32 arts) {
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  if (arts < bdatBattle->getArtsDrStart() || arts >= bdatBattle->getArtsDrEnd()) {
    return 0;
  }

  return bdatBattle->getArtsDrUI(arts);
}

const char *GfDataDriver::getModelResourceName(u32 driver) { return GfBdatChrDr::get()->getChrDrModel(driver); }

const char *GfDataDriver::getName(u32 driver) {
  u32 nameId = GfBdatChrDr::get()->getChrDrName(driver);
  u8 *bdat = GfBdatMsg::getFpChrDr();
  if (nameId != 0) {
    return Bdat::getMSText(bdat, nameId);
  }
  return nullptr;
}

bool GfDataDriver::getName(u8 *&bdat, u32 &textId, u32 driver) {
  textId = GfBdatChrDr::get()->getChrDrName(driver);
  bdat = GfBdatMsg::getFpChrDr();
  return textId != 0;
}

const char *GfDataDriver::getMotionResourceName(u32 driver) { return GfBdatChrDr::get()->getChrDrMotion(driver); }

const char *GfDataDriver::getDebugName(u32 driver) { return GfBdatChrDr::get()->getChrDrDebugName(driver); }

bool GfDataDriver::debugGetNameWithClass(mm::mtl::FixStr<128> &, u32) { return false; }

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

u32 GfDataDriver::getDriverRelativeID(u32 driver) {
  u32 relativeID = driver - 1;
  return relativeID < DRIVER_COUNT ? relativeID : 1;
}

u32 GfDataDriver::getLevel(const SDataDriver &dataDriver) { return dataDriver.unknown94; }

u32 GfDataDriver::getExp(const SDataDriver &dataDriver) { return dataDriver.unknownb0; }

u32 GfDataDriver::getBattleExp(const SDataDriver &dataDriver) { return dataDriver.unknownb4; }

bool GfDataDriver::isEnableLevelUp(u32 driver) { return isEnableLevelUp(*getSDataDriver(driver)); }

bool GfDataDriver::isEnableLevelUp(const SDataDriver &dataDriver) {
  u32 level = dataDriver.unknown94;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  u32 growEnd = bdatBattle->getGrowEnd();
  if (level >= DRIVER_LEVEL_MAX || level >= growEnd - 1) {
    return false;
  }

  u32 totalExp = dataDriver.unknownb0 + dataDriver.unknownb4;
  return totalExp >= bdatBattle->getGrowLevelExp(level + 1);
}

u32 GfDataDriver::getExp(u32 driver) { return getExp(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExp(u32 driver) { return getBattleExp(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExpNextLevelAll(u32 driver) { return getBattleExpNextLevelAll(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExpNextLevelAll(const SDataDriver &dataDriver) {
  u32 level = dataDriver.unknown94;
  return GfBdatBtl::get()->getGrowLevelExp(level + 1);
}

u32 GfDataDriver::getExpSetLevel(u32 driver, u32 level) { return getExpSetLevel(*getSDataDriver(driver), level); }

u32 GfDataDriver::getExpSetLevel(const SDataDriver &, u32 level) { return GfBdatBtl::get()->getGrowLevelExp(level); }

u32 GfDataDriver::getExpUsed(u32 driver) {
  u32 level = getSDataDriver(driver)->unknown94;
  u32 expUsed = 0;
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  for (u32 usedLevel = 0; usedLevel < level; usedLevel++) {
    expUsed += bdatBattle->getGrowLevelExp(usedLevel + 1);
  }

  return expUsed;
}

u32 GfDataDriver::getExpUsed(const SDataDriver &dataDriver) {
  u32 level = dataDriver.unknown94;
  return GfBdatBtl::get()->getGrowLevelExp(level);
}

bool GfDataDriver::isDummyDriver(u32) { return false; }

bool GfDataDriver::isScenarioMask(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->unknown570 == 1;
}

void GfDataDriver::setScenarioMask(u32 driver, bool scenarioMask) {
  SDataDriver *dataDriver = getSDataDriver(driver);
  dataDriver->unknown570 = scenarioMask;
}

u32 GfDataDriver::getHpMaxRev(const SDataDriver &dataDriver) {
  u32 hpMaxRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      hpMaxRev += GfDataBlade::getHpMaxRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    hpMaxRev += GfDataBlade::getHpMaxRev(BLADE_HIKARI);
  }

  return hpMaxRev;
}

u32 GfDataDriver::getStrengthRev(const SDataDriver &dataDriver) {
  u32 strengthRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      strengthRev += GfDataBlade::getStrengthRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    strengthRev += GfDataBlade::getStrengthRev(BLADE_HIKARI);
  }

  return strengthRev;
}

u32 GfDataDriver::getPowEtherRev(const SDataDriver &dataDriver) {
  u32 powEtherRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      powEtherRev += GfDataBlade::getPowerEtherRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    powEtherRev += GfDataBlade::getPowerEtherRev(BLADE_HIKARI);
  }

  return powEtherRev;
}

u32 GfDataDriver::getDexRev(const SDataDriver &dataDriver) {
  u32 dexRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      dexRev += GfDataBlade::getDexRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    dexRev += GfDataBlade::getDexRev(BLADE_HIKARI);
  }

  return dexRev;
}

u32 GfDataDriver::getAgilityRev(const SDataDriver &dataDriver) {
  u32 agilityRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      agilityRev += GfDataBlade::getAgilityRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    agilityRev += GfDataBlade::getAgilityRev(BLADE_HIKARI);
  }

  return agilityRev;
}

u32 GfDataDriver::getLuckRev(const SDataDriver &dataDriver) {
  u32 luckRev = 0;
  bool hasHikari = false;
  for (int slot = 0; slot < getMaxSetBladeNum(dataDriver); slot++) {
    u32 blade = getBlade(dataDriver, slot);
    if (blade != 0) {
      luckRev += GfDataBlade::getLuckRev(blade);
      if (blade == BLADE_HIKARI) {
        hasHikari = true;
      }
    }
  }

  if (dataDriver.unknown22 == DRIVER_REX && GfDataBlade::getSDataBlade(BLADE_HIKARI)->unknown00 != 0 && !hasHikari) {
    luckRev += GfDataBlade::getLuckRev(BLADE_HIKARI);
  }

  return luckRev;
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

bool GfDataDriver::getEquipAcceEnahnce(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver) { return getEquipAcceEnhance(enhances, *getSDataDriver(driver)); }

u32 GfDataDriver::getEquipAcceEnahnce(u32 driver, u32 slot) { return getEquipAcceEnhance(*getSDataDriver(driver), slot); }

u32 GfDataDriver::getEquipAcceEnhance(const SDataDriver &dataDriver, u32 slot) {
  if (dataDriver.unknown574[slot].unknown04 == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcEquipEnhance1(dataDriver.unknown574[slot].unknown04);
}

u32 GfDataDriver::getEquipAcce(const SDataDriver &dataDriver, u32 slot) { return dataDriver.unknown574[slot].unknown04; }

u32 GfDataDriver::getEquipAcce(u32 driver, u32 slot) { return getEquipAcce(*getSDataDriver(driver), slot); }

GfItemHandle GfDataDriver::getEquipAcceHandle(u32 driver, u32 slot) { return getEquipAcceHandle(*getSDataDriver(driver), slot); }

GfItemHandle GfDataDriver::getEquipAcceHandle(const SDataDriver &dataDriver, u32 slot) { return dataDriver.unknown574[slot].unknown00; }

void GfDataDriver::setEquipAcce(u32 driver, u32 slot, u32 item) {
  if (driver == 0) {
    return;
  }

  setEquipAcce(*getSDataDriver(driver), slot, item);
}

void GfDataDriver::setEquipAcce(SDataDriver &dataDriver, u32 slot, u32 item) { dataDriver.unknown574[slot].unknown04 = item; }

void GfDataDriver::setEquipAcceHandle(u32 driver, u32 slot, GfItemHandle handle) {
  if (driver == 0) {
    return;
  }

  setEquipAcceHandle(*getSDataDriver(driver), slot, handle);
}

void GfDataDriver::setEquipAcceHandle(SDataDriver &dataDriver, u32 slot, GfItemHandle handle) { dataDriver.unknown574[slot].unknown00.value = handle.value; }

void GfDataDriver::getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, u32 driver) { getEquipWpnType(weaponTypes, *getSDataDriver(driver)); }

void GfDataDriver::getEquipWpnType(mm::mtl::FixedVector<u32, 27> &weaponTypes, const SDataDriver &dataDriver) {
  weaponTypes.clear();
  for (u32 weaponType = 1; weaponType <= WEAPON_TYPE_COUNT; weaponType++) {
    if (isEnableEquipWeapon(dataDriver.unknown22, weaponType)) {
      weaponTypes.push_back(weaponType);
    }
  }
}

const char *GfDataDriver::getVoiceStr(u32 driver) { return getVoiceStr(*getSDataDriver(driver)); }

const char *GfDataDriver::getVoiceStr(const SDataDriver &dataDriver) { return GfBdatChrDr::get()->getChrDrVoice(dataDriver.unknown22); }

u32 GfDataDriver::getSkillPoint(u32 driver) { return getSkillPoint(*getSDataDriver(driver)); }

u32 GfDataDriver::getSkillPoint(const SDataDriver &dataDriver) { return dataDriver.unknownb8; }

void GfDataDriver::addSkillPoint(u32 driver, int skillPoint) { addSkillPoint(*getSDataDriver(driver), skillPoint); }

void GfDataDriver::addSkillPoint(SDataDriver &dataDriver, int skillPoint) {
  dataDriver.unknownb8 += skillPoint;
  if (skillPoint > 0) {
    dataDriver.unknownbc += skillPoint;
  }
}

void GfDataDriver::getValidEnhance(mm::mtl::FixedVector<u16, 64> &enhances, u32 driver) { getValidEnhance(enhances, *getSDataDriver(driver)); }

u32 GfDataDriver::getExtraMountNpcRsc(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountNpc(driver); }

const char *GfDataDriver::getExtraMountBone(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountBone(driver); }

u32 GfDataDriver::getExtraMountCondition(u32 driver) { return GfBdatRsc::get()->getDriverParamExtMountCond(driver); }

int GfDataDriver::getDeathBlowEfbFileIdx(DBSLOT slot, int index) { return (index < 0 ? slot + 1 : slot * DEATH_BLOW_PER_SLOT + index) + FILE_INDEX_DEATH_BLOW_EFB; }

int GfDataDriver::getDebugAppendDeathBlowEfbFileIdx(u32 index) { return index + FILE_INDEX_DEBUG_APPEND_DEATH_BLOW_EFB; }

int GfDataDriver::getWeaponEabFileIdx(int slot) { return (slot < 0 ? 0 : slot) + FILE_INDEX_WEAPON_EAB; }

int GfDataDriver::getDeathBlowEabFileIdx(DBSLOT slot, int index) { return (index < 0 ? slot + 1 : slot * DEATH_BLOW_PER_SLOT + index) + FILE_INDEX_DEATH_BLOW_EAB; }

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
    if (getSDataDriver(driver)->unknown584[slot].unknown04 == item) {
      itemNum++;
    }
  }

  return itemNum;
}

bool GfDataDriver::isUsedFavorite(u32 driver, FAVORITE favorite) { return (GfGameFlag::getLocal(8, FLAG_USED_FAVORITE + driver) & 1 << favorite) != 0; }

u32 GfDataDriver::getFootStep(u32 driver) { return GfBdatChrDr::get()->getChrDrFootStep(driver); }

u32 GfDataDriver::getFootStepEffect(u32 driver) { return GfBdatChrDr::get()->getChrDrFootStepEffect(driver); }

bool GfDataDriver::isActivateWeaponType(u32 driver, u32 weaponType) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->unknown59c.test(weaponType);
}

void GfDataDriver::setActivateWeaponType(u32 driver, u32 weaponType) {
  if (driver == 0) {
    return;
  }

  getSDataDriver(driver)->unknown59c.set(weaponType);
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

  return getSDataDriver(driver)->unknown571 != 0;
}

bool GfDataDriver::isEquipDefaultAcce(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->unknown572 != 0;
}

u32 GfDataDriver::getExpNextLevel(const SDataDriver &dataDriver) {
  u32 level = dataDriver.unknown94;
  u32 exp = dataDriver.unknownb4;
  u32 growExp = GfBdatBtl::get()->getGrowLevelExp(level + 1);
  if (exp > growExp) {
    return growExp;
  }
  if (level >= DRIVER_LEVEL_MAX) {
    return 0;
  }
  return growExp - exp;
}

u32 GfDataDriver::getExpNextLevel(u32 driver) { return getExpNextLevel(*getSDataDriver(driver)); }

u32 GfDataDriver::getBattleExpNextLevel(u32 driver) { return getExpNextLevel(*getSDataDriver(driver)); }

int GfDataDriver::getSetIdByBlade(const SDataDriver &dataDriver, u32 blade) {
  int count = getMaxSetBladeNum(dataDriver);
  for (int slot = 0; slot < count; slot++) {
    if (getBlade(dataDriver, slot) == blade) {
      return slot;
    }
  }

  return -1;
}

int GfDataDriver::getSetIdByBlade(u32 driver, u32 blade) { return getSetIdByBlade(*getSDataDriver(driver), blade); }

u32 GfDataDriver::getDriverBySetBlade(u32 blade) { return GfDataBlade::getSDataBlade(blade)->unknown04; }

u32 GfDataDriver::getDummyBlade(const SDataDriver &dataDriver) {
  if (dataDriver.unknown22 == DRIVER_REX) {
    return BLADE_REX_DUMMY;
  }

  if (dataDriver.unknown22 != DRIVER_SHIN_2) {
    if (dataDriver.unknown22 == DRIVER_SHIN) {
      return BLADE_SHIN_DUMMY;
    }
    return 0;
  }

  return BLADE_UNKNOWN_1073;
}

u32 GfDataDriver::getDummyBlade(u32 driver) {
  if (driver == DRIVER_REX) {
    return 0x3f4;
  }

  if (driver != 9) {
    if (driver == 7) {
      return 0x3f5;
    }
    return 0;
  }

  return 0x431;
}

const char *GfDataDriver::getBelongingModelName(const GfInitParamDriver &param) {
  if (param.m_bladeID == 1) {
    return (param.unknown08 | 4) == 0xd ? "oj/oj300002" : "oj/oj300001";
  }

  return nullptr;
}

u32 GfDataDriver::getDriverActivateType(const SDataDriver &dataDriver) {
  if (dataDriver.unknown20 != 1) {
    return 0;
  }

  if (GfDataParty::isExistDriver(dataDriver.unknown22)) {
    return 2;
  }

  return 1;
}

u32 GfDataDriver::getDriverActivateType(u32 driver) {
  if (driver == 0) {
    return 0;
  }

  return getDriverActivateType(*getSDataDriver(driver));
}

bool GfDataDriver::isActivateParty(u32 driver) {
  if (driver == 0) {
    return false;
  }

  if (getSDataDriver(driver)->unknown20 != 1) {
    return false;
  }

  return static_cast<u32>(GfDataParty::getDriverPartyID(driver)) < 3;
}

bool GfDataDriver::isActivateReserver(u32 driver) {
  if (getSDataDriver(driver)->unknown20 != 1) {
    return false;
  }

  return static_cast<u32>(GfDataParty::getDriverPartyID(driver) - 3) < 7;
}

bool GfDataDriver::isActivateUnuse(u32 driver) { return getSDataDriver(driver)->unknown20 == 0; }

bool GfDataDriver::isActivatePartyAll(u32 driver) {
  if (driver == 0) {
    return false;
  }

  return getSDataDriver(driver)->unknown20 == 1;
}

bool GfDataDriver::isFavoriteCategory(u32 driver, u32 item) {
  if (item == 0) {
    return false;
  }

  u32 category = GfDataItem::getCategory(item);
  if (driver == 0) {
    return category == 0;
  }

  if (GfBdatChrDr::get()->getChrDrFavoriteCategory(driver, 0) == category) {
    return true;
  }

  return GfBdatChrDr::get()->getChrDrFavoriteCategory(driver, 1) == category;
}

u32 GfDataDriver::getFavorite(u32 driver, FAVORITE favorite) {
  if (driver != 0) {
    if (static_cast<u32>(favorite) < 2) {
      return GfBdatChrDr::get()->getChrDrFavoriteCategory(driver, favorite);
    }
    if ((static_cast<u32>(favorite) & 0xfffffffe) == 2) {
      return GfBdatChrDr::get()->getChrDrFavoriteItem(driver, static_cast<u32>(favorite) - 2);
    }
  }

  return 0;
}

void GfDataDriver::setPouchData(u32 driver, u32 slot, const SDataPouch &pouch) {
  SDataPouch *dataPouch = &getSDataDriver(driver)->unknown584[slot];
  dataPouch->_06 = pouch._06;
  dataPouch->unknown04 = pouch.unknown04;
  dataPouch->unknown00 = pouch.unknown00;
}

int GfDataDriver::getSetIdByDummyBlade(u32 driver) {
  SDataDriver *dataDriver = getSDataDriver(driver);
  if (driver != 0) {
    for (int slot = 0; slot < getMaxSetBladeNum(driver); slot++) {
      if (GfDataBlade::isDummyBlade(dataDriver->unknown26[slot])) {
        return slot;
      }
    }
  }

  return -1;
}

} // namespace gf
