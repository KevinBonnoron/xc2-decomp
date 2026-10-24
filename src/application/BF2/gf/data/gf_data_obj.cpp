#include "gf/data/gf_data_obj.h"

#include "gf/data/gf_bdat_blade.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_chrdr.h"
#include "gf/data/gf_bdat_chrenarrange.h"
#include "gf/data/gf_bdat_chrenparam.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_maplist.h"
#include "gf/data/gf_bdat_rsc.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_mob.h"
#include "gf/data/gf_data_npc.h"
#include "gf/data/gf_data_party.h"
#include "gf/event/gf_event.h"
#include "gf/game/gf_game_party.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/fixstr.h"
#include "mm_mtl/rtti.h"

namespace gf {

constexpr int SLOT_ARTS_COUNT = 3;
constexpr u32 ARMOR_MAX = 100;
constexpr f32 PERCENT = 0.01f;
constexpr f32 PERCENT_SCALE = 100.0f;
constexpr u32 DRIVER_HP_MAX = 9999;
constexpr u32 DRIVER_STATUS_MAX = 999;
constexpr u32 RATE_MAX = 100;
constexpr f32 ENEMY_HP_MAX = 100000000.0f;
constexpr f32 ENEMY_STATUS_MAX = 9999.0f;
constexpr f32 ENEMY_AGILITY_MAX = 999.0f;
constexpr f32 ENEMY_LUCK_MAX = 999.0f;
constexpr f32 PERMILLE = 0.001f;

enum {
  ENHANCE_EFFECT_NONE,
  ENHANCE_EFFECT_HP_MAX_PERCENT,
  ENHANCE_EFFECT_STRENGTH_PERCENT,
  ENHANCE_EFFECT_POWER_ETHER_PERCENT,
  ENHANCE_EFFECT_DEX_PERCENT,
  ENHANCE_EFFECT_AGILITY_PERCENT,
  ENHANCE_EFFECT_LUCK_PERCENT,
  ENHANCE_EFFECT_CRITICAL_RATE_PERCENT,
  ENHANCE_EFFECT_P_ARMOR_PERCENT,
  ENHANCE_EFFECT_E_ARMOR_PERCENT,
  ENHANCE_EFFECT_GUARD_RATE_PERCENT,
  ENHANCE_EFFECT_HP_MAX_ADD,
  ENHANCE_EFFECT_STRENGTH_ADD,
  ENHANCE_EFFECT_POWER_ETHER_ADD,
  ENHANCE_EFFECT_DEX_ADD,
  ENHANCE_EFFECT_AGILITY_ADD,
  ENHANCE_EFFECT_LUCK_ADD,
  ENHANCE_EFFECT_CRITICAL_RATE_ADD,
  ENHANCE_EFFECT_P_ARMOR_ADD,
  ENHANCE_EFFECT_E_ARMOR_ADD,
  ENHANCE_EFFECT_GUARD_RATE_ADD,
  ENHANCE_EFFECT_ARMOR_ADD = 146,
};

DataObjDriver::DataObjDriver(u32 id) : unknown10(nullptr), unknown18(INVALID_HANDLE), unknown20(nullptr), unknown28(), unknown3c(false) { setup(id); }

void DataObjDriver::setup(u32 id) {
  this->m_bdatId = id;
  if (id != 0) {
    unknown10 = GfDataDriver::getSDataDriver(id);
  }
}

DataObjDriver::DataObjDriver(GF_OBJ_HANDLE *handle) : m_bdatId(0), unknown10(nullptr), unknown18(handle), unknown20(nullptr), unknown28(), unknown3c(false) {
  GfObjAcc objAcc(handle);
  setup(objAcc.getDriverId());
}

DataObjDriver::~DataObjDriver() {
  if (unknown20 != nullptr) {
    delete unknown20;
    unknown20 = nullptr;
  }
}

void DataObjDriver::setVirtualLevel(u32 level) {
  setupVirtualParam();
  SDataDriver &dataDriver = *unknown10;
  GfDataDriver::setLevel(dataDriver, level);
  GfDataDriver::calcDriverBaseParamByLevel(dataDriver);
}

void DataObjDriver::setVirtualEquipWpn(u32 weapon, int slot) {
  setupVirtualParam();
  if (slot < 0) {
    slot = getBladeSet(false);
  }

  if (slot >= 0) {
    unknown28[slot] = weapon;
  }
}

void DataObjDriver::setVirtualEquipAcc(u32 slot, u32 accessory) {
  setupVirtualParam();
  if (GfDataItem::getItemType(accessory) == ItemType::PC_EQUIP) {
    GfDataDriver::setEquipAcce(*unknown10, slot, accessory);
  }
}

void DataObjDriver::setVirtualSetBlade(u32 blade, int slot) {
  setupVirtualParam();
  SDataDriver *dataDriver = unknown10;
  int ruleSlot = GfDataDriver::getRuleSetBlade(getBdatId(), blade, slot);
  int maxSetBladeNum = GfDataDriver::getMaxSetBladeNum(*dataDriver);
  for (int i = 0; i < maxSetBladeNum; i++) {
    if (getBlade(true, i) == blade) {
      dataDriver->unknown26[ruleSlot] = 0;
      break;
    }
  }

  dataDriver->unknown26[ruleSlot] = blade;
  if (dataDriver->unknown24 < 0) {
    dataDriver->unknown24 = ruleSlot;
  }
}

bool DataObjDriver::isVirtualSetting() const { return unknown20 != nullptr; }

u32 DataObjDriver::getMenuOffset() const { return GfBdatChrDr::get()->getChrDrOffsetID(getBdatId()); }

const char *DataObjDriver::getCenterBone() const { return GfBdatChrDr::get()->getChrDrCenterBone(getBdatId()); }

const char *DataObjDriver::getCamBone() const { return GfBdatChrDr::get()->getChrDrCamBone(getBdatId()); }

u32 DataObjDriver::getEyeRotControl() const { return GfDataDriver::getEyeRotControl(getBdatId()); }

bool DataObjDriver::isValid() const { return unknown10 != nullptr && unknown10->unknown22 != 0; }

const char *DataObjDriver::getModelResourceName() const {
  const char *name = GfBdatChrDr::get()->getChrDrModel(getBdatId());
  if (name != nullptr && name[0] == '\0') {
    name = nullptr;
  }

  return name;
}

const char *DataObjDriver::getMotionResourceName() const {
  const char *name = GfBdatChrDr::get()->getChrDrMotion(getBdatId());
  if (name != nullptr && name[0] == '\0') {
    name = nullptr;
  }

  return name;
}

const char *DataObjDriver::getEffectResourceName() const {
  const char *name = GfBdatChrDr::get()->getChrDrCom_Eff(getBdatId());
  if (name != nullptr && name[0] == '\0') {
    name = nullptr;
  }

  return name;
}

const char *DataObjDriver::getName() const { return GfDataDriver::getName(getBdatId()); }

bool DataObjDriver::getName(u8 *&bdat, u32 &textId) const { return GfDataDriver::getName(bdat, textId, getBdatId()); }

u32 DataObjDriver::getBdatId() const { return m_bdatId; }

u32 DataObjDriver::getDataType() const { return unknown10->unknown20; }

u32 DataObjDriver::getHp() const { return GfObjUtil::getHp(unknown18); }

static void unknown001(u32 &value, const SDataDriver &dataDriver, u32 percentEffect,
                       u32 addEffect) { // Inferred role: applyDriverEnhance; original function name unknown.
  mm::mtl::FixedVector<u16, 64> enhances;
  GfDataDriver::getValidEnhance(enhances, dataDriver);
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  f32 base = value;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    u16 *end = enhances.end();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == addEffect) {
        base += bdatBattle->getBTL_EnhanceParam1(*enhance);
      }
    } while (++enhance != end);
  }

  f32 percent = 0.0f;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    u16 *end = enhances.end();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == percentEffect) {
        percent += bdatBattle->getBTL_EnhanceParam1(*enhance) * PERCENT;
      }
    } while (++enhance != end);
  }

  value = base + base * percent;
}

u32 DataObjDriver::getHpMax(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 hpMax = dataDriver->unknown96;
  unknown001(hpMax, *dataDriver, ENHANCE_EFFECT_HP_MAX_PERCENT, ENHANCE_EFFECT_HP_MAX_ADD);
  f32 rate = GfDataDriver::getHpMaxRev(*dataDriver) * PERCENT;
  hpMax += static_cast<u32>(hpMax * rate);
  return hpMax > DRIVER_HP_MAX ? DRIVER_HP_MAX : hpMax;
}

u32 DataObjDriver::getLevel(bool isVirtual) const {
  u32 level = GfDataDriver::getLevel(*get(isVirtual));
  return level > DRIVER_LEVEL_MAX ? DRIVER_LEVEL_MAX : level;
}

u32 DataObjDriver::getExp() const { return GfDataDriver::getExp(*get(false)); }

u32 DataObjDriver::getBattleExp() const { return GfDataDriver::getBattleExp(*get(false)); }

u32 DataObjDriver::getExpNext(bool isVirtual) const { return GfDataDriver::getExpNextLevel(*get(isVirtual)); }

u32 DataObjDriver::getBattleExpNext(bool isVirtual) const { return GfDataDriver::getBattleExpNextLevel(*get(isVirtual)); }

u32 DataObjDriver::getWeaponPoint(u32 weaponType) const {
  if (weaponType == 0) {
    u32 blade = getBlade(false, -1);
    if (blade == 0) {
      return 0;
    }

    weaponType = GfDataBlade::getSDataBlade(blade)->unknown821;
  }

  return get(false)->unknownc0[weaponType].unknown0c;
}

void DataObjDriver::addWeaponPoint(u32 weaponType, int weaponPoint) {
  if (weaponType == 0) {
    u32 blade = getBlade(false, -1);
    if (blade == 0) {
      return;
    }

    DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
    weaponType = paramAcc.getWeaponType(-1, false);
  }

  GfDataDriverArts::addWp(getBdatId(), weaponType, weaponPoint);
}

u32 DataObjDriver::getSkillPoint() const { return GfDataDriver::getSkillPoint(*get(false)); }

void DataObjDriver::addSkillPoint(int skillPoint) { GfDataDriver::addSkillPoint(*get(false), skillPoint); }

u32 DataObjDriver::getBladeArts(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArts(index, false);
}

u32 DataObjDriver::getBladeArtsEnhance(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsEnhance(index, false);
}

u32 DataObjDriver::getBladeArtsLevel(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsLevel(index, false);
}

u32 DataObjDriver::getBladeArtsH(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsH(index, false);
}

u32 DataObjDriver::getBladeArtsN(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsN(index, false);
}

u32 DataObjDriver::getBladeArtsNH(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsNH(index, false);
}

u32 DataObjDriver::getBladeArtsEx(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsEx(false);
}

u32 DataObjDriver::getBladeArtsExH(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsExH(false);
}

u32 DataObjDriver::getBladeArtsEx2(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsEx2(false);
}

u32 DataObjDriver::getBladeArtsEx2H(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeArtsEx2H(false);
}

u32 DataObjDriver::getBladeSkill(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeSkill(index, false);
}

u32 DataObjDriver::getBladeSkillLevel(bool isVirtual, u32 index) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataParamAcc paramAcc(OBJECT_TYPE_BLADE, blade, static_cast<GimmickType>(0));
  return paramAcc.getBladeSkillLevel(index, false);
}

u32 DataObjDriver::getDriverArts(u32 weaponType, u32 index) const { return get(false)->unknownc0[weaponType].unknown00[index]; }

u32 DataObjDriver::getDriverArtsLevel(u32 arts) const { return get(false)->unknown2f0[arts]; }

void DataObjDriver::setDriverArtsLevel(u32 arts, u32 level) {
  if (level > DRIVER_ARTS_LEVEL_MAX) {
    level = DRIVER_ARTS_LEVEL_MAX;
  }

  get(false)->unknown2f0[arts] = level;
}

u32 DataObjDriver::getClass(bool isVirtual) const { return GfDataDriver::getClass(*get(isVirtual)); }

u32 DataObjDriver::getStrength(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 strength = get(isVirtual)->unknown98;
  unknown001(strength, *dataDriver, ENHANCE_EFFECT_STRENGTH_PERCENT, ENHANCE_EFFECT_STRENGTH_ADD);
  f32 rate = GfDataDriver::getStrengthRev(*dataDriver) * PERCENT;
  strength += static_cast<u32>(strength * rate);
  if (strength > DRIVER_STATUS_MAX) {
    strength = DRIVER_STATUS_MAX;
  }

  return strength;
}

u32 DataObjDriver::getPowerEther(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 powerEther = get(isVirtual)->unknown9a;
  unknown001(powerEther, *dataDriver, ENHANCE_EFFECT_POWER_ETHER_PERCENT, ENHANCE_EFFECT_POWER_ETHER_ADD);
  f32 rate = GfDataDriver::getPowEtherRev(*dataDriver) * PERCENT;
  powerEther += static_cast<u32>(powerEther * rate);
  if (powerEther > DRIVER_STATUS_MAX) {
    powerEther = DRIVER_STATUS_MAX;
  }

  return powerEther;
}

u32 DataObjDriver::getDex(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 dex = get(isVirtual)->unknown9c;
  unknown001(dex, *dataDriver, ENHANCE_EFFECT_DEX_PERCENT, ENHANCE_EFFECT_DEX_ADD);
  f32 rate = GfDataDriver::getDexRev(*dataDriver) * PERCENT;
  dex += static_cast<u32>(dex * rate);
  if (dex > DRIVER_STATUS_MAX) {
    dex = DRIVER_STATUS_MAX;
  }

  return dex;
}

u32 DataObjDriver::getAgility(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 agility = get(isVirtual)->unknown9e;
  unknown001(agility, *dataDriver, ENHANCE_EFFECT_AGILITY_PERCENT, ENHANCE_EFFECT_AGILITY_ADD);
  f32 rate = GfDataDriver::getAgilityRev(*dataDriver) * PERCENT;
  agility += static_cast<u32>(agility * rate);
  if (agility > DRIVER_STATUS_MAX) {
    agility = DRIVER_STATUS_MAX;
  }

  return agility;
}

u32 DataObjDriver::getLuck(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 luck = get(isVirtual)->unknowna0;
  unknown001(luck, *dataDriver, ENHANCE_EFFECT_LUCK_PERCENT, ENHANCE_EFFECT_LUCK_ADD);
  f32 rate = GfDataDriver::getLuckRev(*dataDriver) * PERCENT;
  luck += static_cast<u32>(luck * rate);
  if (luck > DRIVER_STATUS_MAX) {
    luck = DRIVER_STATUS_MAX;
  }

  return luck;
}

u32 DataObjDriver::getPArmor(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
    return dataDriver->unknowna2;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && unknown28[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
  }

  u32 bladePArmor = dataObjBlade.getPArmor(isVirtual);
  u32 pArmor = get(isVirtual)->unknowna2 + bladePArmor;
  return pArmor > ARMOR_MAX ? ARMOR_MAX : pArmor;
}

bool DataObjBlade::isValid() const { return unknown08 != nullptr && unknown08->unknown06 != 0; }

void DataObjBlade::setVirtualEquipWpn(u32 weapon, int) {
  if (weapon != 0) {
    setupVirtualParam();
    unknown18->unknown82c = weapon;
  }
}

static void unknown002(u32 &value, SDataBlade &dataBlade, u32 percentEffect, u32 addEffect,
                       bool isVirtual) { // Inferred role: applyBladeEnhance; original function name unknown.
  mm::mtl::FixedVector<u16, 64> enhances;
  GfDataBlade::getValidEnhance(enhances, dataBlade, isVirtual);
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  f32 base = value;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    u16 *end = enhances.end();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == addEffect) {
        base += bdatBattle->getBTL_EnhanceParam1(*enhance);
      }
    } while (++enhance != end);
  }

  f32 percent = 0.0f;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    u16 *end = enhances.end();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == percentEffect) {
        percent += bdatBattle->getBTL_EnhanceParam1(*enhance) * PERCENT;
      }
    } while (++enhance != end);
  }

  value = base + base * percent;
}

u32 DataObjBlade::getPArmor(bool isVirtual) const {
  u32 pArmor = GfDataBlade::getParmor(getBdatId());
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    pArmor += bdatItem->getPcWpnPArmor(weapon);
  }

  unknown002(pArmor, *get(isVirtual), ENHANCE_EFFECT_P_ARMOR_PERCENT, ENHANCE_EFFECT_P_ARMOR_ADD, isVirtualSetting() | unknown24);
  unknown002(pArmor, *get(isVirtual), ENHANCE_EFFECT_NONE, ENHANCE_EFFECT_ARMOR_ADD, isVirtualSetting() | unknown24);
  return pArmor;
}

u32 DataObjDriver::getEArmor(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
    return dataDriver->unknowna4;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && unknown28[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
  }

  u32 bladeEArmor = dataObjBlade.getEArmor(isVirtual);
  u32 eArmor = dataDriver->unknowna4 + bladeEArmor;
  return eArmor > ARMOR_MAX ? ARMOR_MAX : eArmor;
}

u32 DataObjBlade::getEArmor(bool isVirtual) const {
  u32 eArmor = GfDataBlade::getEarmor(getBdatId());
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    eArmor += bdatItem->getPcWpnEArmor(weapon);
  }

  unknown002(eArmor, *get(isVirtual), ENHANCE_EFFECT_E_ARMOR_PERCENT, ENHANCE_EFFECT_E_ARMOR_ADD, isVirtualSetting() | unknown24);
  unknown002(eArmor, *get(isVirtual), ENHANCE_EFFECT_NONE, ENHANCE_EFFECT_ARMOR_ADD, isVirtualSetting() | unknown24);
  return eArmor;
}

u32 DataObjDriver::getCriticalRate(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 criticalRate = get(isVirtual)->unknowna6;
  u32 blade = getBlade(isVirtual, -1);
  {
    DataObjBlade dataObjBlade(blade);
    if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
      return criticalRate;
    }

    int slot = getBladeSet(isVirtual);
    if (slot >= 0 && unknown28[slot] != 0) {
      dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
    }

    criticalRate += dataObjBlade.getCriticalRate(isVirtual);
  }

  if (criticalRate > RATE_MAX) {
    criticalRate = RATE_MAX;
  }

  return criticalRate;
}

u32 DataObjBlade::getCriticalRate(bool isVirtual) const {
  u32 criticalRate = 0;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    criticalRate = bdatItem->getPcWpnCriRate(weapon);
  }

  unknown002(criticalRate, *get(isVirtual), ENHANCE_EFFECT_CRITICAL_RATE_PERCENT, ENHANCE_EFFECT_CRITICAL_RATE_ADD, isVirtualSetting() | unknown24);
  return criticalRate;
}

u32 DataObjDriver::getGuardRate(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 guardRate = get(isVirtual)->unknowna7;
  u32 blade = getBlade(isVirtual, -1);
  {
    DataObjBlade dataObjBlade(blade);
    if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
      return guardRate;
    }

    int slot = getBladeSet(isVirtual);
    if (slot >= 0 && unknown28[slot] != 0) {
      dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
    }

    guardRate += dataObjBlade.getGuardRate(isVirtual);
  }

  if (guardRate > RATE_MAX) {
    guardRate = RATE_MAX;
  }

  return guardRate;
}

u32 DataObjBlade::getGuardRate(bool isVirtual) const {
  u32 guardRate = 0;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    guardRate = bdatItem->getPcWpnGuardRate(weapon);
  }

  unknown002(guardRate, *get(isVirtual), ENHANCE_EFFECT_GUARD_RATE_PERCENT, ENHANCE_EFFECT_GUARD_RATE_ADD, isVirtualSetting() | unknown24);
  return guardRate;
}

u32 DataObjDriver::getAutoHate(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  return dataObjBlade.getAutoHate(isVirtual);
}

u32 DataObjBlade::getAutoHate(bool) const {
  if (!GfDataHana::isValid(getBdatId())) {
    return 0;
  }

  return GfDataHana::getAutoHate(getBdatId());
}

u32 DataObjDriver::getArtsHate(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  return dataObjBlade.getArtsHate(isVirtual);
}

u32 DataObjBlade::getArtsHate(bool) const {
  if (!GfDataHana::isValid(getBdatId())) {
    return 0;
  }

  return GfDataHana::getArtsHate(getBdatId());
}

u32 DataObjDriver::getWeaponDamage(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && unknown28[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
  }

  return dataObjBlade.getWeaponDamage(isVirtual);
}

u32 DataObjBlade::getWeaponDamage(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnDamage(weapon);
}

u32 DataObjDriver::getWeaponStability(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && unknown28[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(unknown28[slot], slot);
  }

  return dataObjBlade.getWeaponStability(isVirtual);
}

u32 DataObjBlade::getWeaponStability(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnStability(weapon);
}

u32 DataObjDriver::getNorAtkDmgMin(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  u32 strength = getStrength(isVirtual);
  return dataObjBlade.getNorAtkDmgMin(isVirtual) + strength;
}

u32 DataObjBlade::getNorAtkDmgMin(bool isVirtual) const {
  f32 damage = getWeaponDamage(isVirtual);
  u32 ratio = GfBdatBlade::get()->getFLD_IdeaTableWpnRatio(GfDataBlade::getTrustRank(getBdatId()));
  f32 baseDamage = damage * ratio * PERCENT;
  return baseDamage * (1.0f - getWeaponStability(isVirtual) * PERCENT);
}

u32 DataObjDriver::getNorAtkDmgMax(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  u32 strength = getStrength(isVirtual);
  return dataObjBlade.getNorAtkDmgMax(isVirtual) + strength;
}

u32 DataObjBlade::getNorAtkDmgMax(bool isVirtual) const {
  f32 damage = getWeaponDamage(isVirtual);
  u32 ratio = GfBdatBlade::get()->getFLD_IdeaTableWpnRatio(GfDataBlade::getTrustRank(getBdatId()));
  f32 baseDamage = damage * ratio * PERCENT;
  return baseDamage * (getWeaponStability(isVirtual) * PERCENT + 1.0f);
}

u32 DataObjDriver::getEquipAcce(u32 slot, bool isVirtual) const { return GfDataDriver::getEquipAcce(*get(isVirtual), slot); }

u32 DataObjDriver::getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) const { return GfEquipUtil::getEquipAcceResult(*get(isVirtual), slot, accessory); }

int DataObjDriver::getBladeSet(bool isVirtual) const { return GfDataDriver::getBladeSet(*get(isVirtual)); }

void DataObjDriver::setBladeSet(int slot) {
  if (slot < 0 || DataObjDriver::getBlade(true, slot) == 0) {
    return;
  }

  int oldSlot = unknown10->unknown24;
  if (oldSlot >= 0) {
    GfDataDriver::setEquipBlade(unknown10->unknown22, false, oldSlot);
  }

  GfDataDriver::setEquipBlade(unknown10->unknown22, true, slot);
  GfEvent::callBladeChange(unknown18, oldSlot, slot);
}

u32 DataObjDriver::getBlade(bool isVirtual, int slot) const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(unknown18);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    return setup->fixedBlade;
  }

  if (slot >= 0) {
    return unknown10->unknown26[slot];
  }

  slot = getBladeSet(isVirtual);
  if (slot < 0) {
    return 0;
  }

  return GfDataDriver::getBlade(*get(isVirtual), slot);
}

u32 DataObjDriver::getEquipWeapon(bool isVirtual, int slot) const {
  if (slot < 0) {
    slot = getBladeSet(isVirtual);
    if (slot < 0) {
      return 0;
    }
  }

  u32 blade = getBlade(isVirtual, slot);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  if (isVirtual && unknown28[slot] != 0) {
    return unknown28[slot];
  }

  return dataObjBlade.getEquipWeapon(isVirtual, slot);
}

u32 DataObjBlade::getEquipWeapon(bool isVirtual, int) const { return get(isVirtual)->unknown82c; }

u32 DataObjDriver::getWeaponType(bool isVirtual, int slot) const {
  u32 blade = getBlade(isVirtual, slot);
  GfObjSetup *setup = GfObjUtil::getObjSetup(unknown18);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    blade = setup->fixedBlade;
  }

  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->unknown06 == 0) {
    return 0;
  }

  return dataObjBlade.getWeaponType(isVirtual, slot);
}

u32 DataObjBlade::getWeaponType(bool isVirtual, int) const { return get(isVirtual)->unknown821; }

u32 DataObjDriver::getChestHeight() const { return GfBdatChrDr::get()->getChrDrChestHeight(getBdatId()); }

u32 DataObjDriver::getLandingHeight() const { return GfBdatChrDr::get()->getChrDrLandingHeight(getBdatId()); }

u32 DataObjDriver::getIconData() const { return GfBdatChrDr::get()->getChrDrStill(getBdatId()); }

u32 DataObjDriver::getRace() const { return GfBdatChrDr::get()->getChrDrRace(getBdatId()); }

u32 DataObjDriver::getFootStep() const { return GfBdatChrDr::get()->getChrDrFootStep(getBdatId()); }

u32 DataObjDriver::getFootStepEffect() const { return GfBdatChrDr::get()->getChrDrFootStepEffect(getBdatId()); }

u32 DataObjDriver::getGender() const { return GfBdatChrDr::get()->getChrDrGender(getBdatId()); }

u32 DataObjDriver::getAttribute(bool isVirtual, int slot) const {
  if (slot < 0) {
    slot = getBladeSet(isVirtual);
  }

  u32 blade = slot >= 0 ? unknown10->unknown26[slot] : 0;
  GfObjSetup *setup = GfObjUtil::getObjSetup(unknown18);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    blade = setup->fixedBlade;
  }

  DataObjBlade dataObjBlade(blade);
  return dataObjBlade.getAttribute(isVirtual, slot);
}

u32 DataObjBlade::getAttribute(bool, int) const { return GfDataBlade::getAttribute(getBdatId()); }

bool DataObjDriver::isScenarioMask() const { return GfDataDriver::isScenarioMask(getBdatId()); }

u32 DataObjDriver::getRole() const { return GfDataBlade::getRole(getBlade(false, -1)); }

const char *DataObjDriver::getVoiceStr() const { return GfDataDriver::getVoiceStr(*unknown10); }

u32 DataObjDriver::getFieldSkill(bool, u32 index) const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getFieldSkill(false, index);
}

u32 DataObjBlade::getFieldSkill(bool, u32 index) const { return get(false)->unknownae[index].unknown00; }

u32 DataObjDriver::getFieldSkillLevel(bool, u32 index) const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getFieldSkillLevel(false, index);
}

u32 DataObjBlade::getFieldSkillLevel(bool, u32 index) const { return get(false)->unknownae[index].unknown03; }

u32 DataObjDriver::getKeyLevel() const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getKeyLevel();
}

u32 DataObjBlade::getKeyLevel() const { return get(false)->unknown664; }

u32 DataObjDriver::getFavoriteCategory(FAVORITE favorite) const { return GfDataDriver::getFavorite(getBdatId(), favorite); }

u32 DataObjDriver::getFavoriteItem(FAVORITE favorite) const { return GfDataDriver::getFavorite(getBdatId(), favorite); }

DataObjBlade::DataObjBlade(u32 id) : unknown08(nullptr), unknown10(INVALID_HANDLE), unknown18(nullptr), unknown24(false) { setup(id); }

void DataObjBlade::setup(u32 id) {
  this->m_bdatId = id;
  if (id != 0) {
    unknown08 = GfDataBlade::getSDataBlade(id);
  }
}

DataObjBlade::DataObjBlade(GF_OBJ_HANDLE *handle) : unknown08(nullptr), unknown10(handle), unknown18(nullptr), m_bdatId(0), unknown24(false) {
  GfObjAcc objAcc(handle);
  setup(objAcc.getBladeId());
}

DataObjBlade::~DataObjBlade() {
  if (unknown18 != nullptr) {
    delete unknown18;
    unknown18 = nullptr;
  }
}

void DataObjBlade::setupVirtualParam() {
  if (unknown18 == nullptr) {
    unknown18 = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SDataBlade;
    *unknown18 = *unknown08;
    unknown08 = unknown18;
  }
}

const char *DataObjBlade::getModelResourceName() const { return get(false)->unknown70c.c_str(); }

const char *DataObjBlade::getMotionResourceName() const { return get(false)->unknown734.c_str(); }

const char *DataObjBlade::getEffectResourceName() const { return get(false)->unknown7ac; }

const char *DataObjBlade::getSeResourceName() const { return get(false)->unknown7fc; }

const char *DataObjBlade::getName() const { return GfDataBlade::getName(getBdatId(), 0); }

bool DataObjBlade::getName(u8 *&bdat, u32 &textId) const { return GfDataBlade::getName(bdat, textId, getBdatId()); }

u32 DataObjBlade::getBdatId() const { return m_bdatId; }

u32 DataObjBlade::getDataType() const { return get(false)->unknown00; }

u32 DataObjBlade::getHpMax(bool) const { return GfDataBlade::getHpMaxRev(getBdatId()); }

u32 DataObjBlade::getStrength(bool) const { return GfDataBlade::getStrengthRev(getBdatId()); }

u32 DataObjBlade::getPowerEther(bool) const { return GfDataBlade::getPowerEtherRev(getBdatId()); }

u32 DataObjBlade::getDex(bool) const { return GfDataBlade::getDexRev(getBdatId()); }

u32 DataObjBlade::getAgility(bool) const { return GfDataBlade::getAgilityRev(getBdatId()); }

u32 DataObjBlade::getLuck(bool) const { return GfDataBlade::getLuckRev(getBdatId()); }

bool DataObjBlade::getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool) const { return GfDataBlade::getEquipOrb(orbs, getBdatId()); }

u32 DataObjBlade::getChestHeight() const { return get(false)->unknown82e; }

u32 DataObjBlade::getLandingHeight() const { return get(false)->unknown830; }

u32 DataObjBlade::getIconData() const { return get(false)->unknown70a; }

u32 DataObjBlade::getRace() const { return get(false)->unknown708; }

u32 DataObjBlade::getQuestRace() const { return GfDataBlade::getQuestRace(get(false)->unknown06); }

u32 DataObjBlade::getFootStep() const { return GfDataBlade::getFootStep(getBdatId()); }

u32 DataObjBlade::getFootStepEffect() const { return GfDataBlade::getFootStepEffect(getBdatId()); }

u32 DataObjBlade::getGender() const { return get(false)->unknown709; }

bool DataObjBlade::isDispInitExtraParts(u32 part) const {
  if (part >= EXTRA_PARTS_COUNT) {
    return false;
  }

  return GfDataBlade::getExtraParts(*get(false), part);
}

u32 DataObjBlade::getRole() const { return GfDataBlade::getRole(getBdatId()); }

const char *DataObjBlade::getVoiceStr() const { return GfDataBlade::getVoiceStr(getBdatId()); }

int DataObjBlade::getBladeSet(bool) const {
  u32 creator = GfDataBlade::getCreator(getBdatId());
  if (GfDataParty::getDriverPartyID(creator) == -1) {
    return -1;
  }

  int maxSetBladeNum = GfDataDriver::getMaxSetBladeNum(creator);
  for (int slot = 0; slot < maxSetBladeNum; slot++) {
    if (GfDataDriver::getBlade(creator, slot) == getBdatId()) {
      return slot;
    }
  }

  return -1;
}

u32 DataObjBlade::getBlade(bool, int) const { return getBdatId(); }

u32 DataObjBlade::getBladePower(bool isVirtual) const { return GfDataBlade::getBladePower(*get(isVirtual)); }

u32 DataObjBlade::getBladeArts(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->unknown00; }

u32 DataObjBlade::getBladeArtsEnhance(bool, u32 index) const { return GfDataBlade::getArtsEnhance(getBdatId(), index); }

u32 DataObjBlade::getBladeArtsLevel(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->unknown07; }

u32 DataObjBlade::getBladeArtsH(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->unknown02; }

u32 DataObjBlade::getBladeArtsN(bool, u32 index) const { return GfDataBlade::getNArts(getBdatId(), index)->unknown00; }

u32 DataObjBlade::getBladeArtsNH(bool, u32 index) const { return GfDataBlade::getNArts(getBdatId(), index)->unknown02; }

u32 DataObjBlade::getBladeArtsEx(bool isVirtual) const { return get(isVirtual)->unknown84; }

u32 DataObjBlade::getBladeArtsExH(bool isVirtual) const { return get(isVirtual)->unknown86; }

u32 DataObjBlade::getBladeArtsEx2(bool isVirtual) const { return get(isVirtual)->unknown90; }

u32 DataObjBlade::getBladeArtsEx2H(bool isVirtual) const { return get(isVirtual)->unknown92; }

u32 DataObjBlade::getBladeSkill(bool isVirtual, u32 index) const { return get(isVirtual)->unknown9c[index].unknown00; }

u32 DataObjBlade::getBladeSkillLevel(bool isVirtual, u32 index) const { return get(isVirtual)->unknown9c[index].unknown03; }

u32 DataObjBlade::getPersonality() const { return get(false)->unknown824; }

u32 DataObjBlade::getCoolTime() const { return get(false)->unknown828; }

u32 DataObjBlade::getFavoriteCategory(FAVORITE favorite) const { return GfDataBlade::getFavorite(getBdatId(), favorite); }

u32 DataObjBlade::getFavoriteItem(FAVORITE favorite) const { return GfDataBlade::getFavorite(getBdatId(), favorite); }

u32 DataObjBlade::getArtsAchievement(u32 index) const { return get(false)->unknownc4[index].unknown00; }

u32 DataObjBlade::getSkillAchievement(u32 index) const { return get(false)->unknown274[index].unknown00; }

u32 DataObjBlade::getFieldSkillAchievement(u32 index) const { return get(false)->unknown424[index].unknown00; }

u32 DataObjBlade::getKeyAchievement() const { return get(false)->unknown5d4.unknown00; }

u32 DataObjBlade::getLinkNum() const {
  u32 kizunaLink = GfGameUtil::getKizunaLink(getBlade(false, -1));
  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkLinkNum(kizunaLink);
}

u32 DataObjBlade::getDeadNum() const {
  u32 kizunaLink = GfGameUtil::getKizunaLink(getBlade(false, -1));
  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkLinkNum(kizunaLink);
}

u32 DataObjBlade::getAppStNum() const {
  u32 kizunaLink = GfGameUtil::getKizunaLink(getBlade(false, -1));
  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkAppStNum(kizunaLink);
}

u32 DataObjBlade::getAppEndNum() const {
  u32 kizunaLink = GfGameUtil::getKizunaLink(getBlade(false, -1));
  return GfBdatBtl::get()->getBTL_Bl_KizunaLinkAppEndNum(kizunaLink);
}

void DataObjBlade::setVirtualEquipWpnChip(u32 chip) {
  if (chip == 0) {
    return;
  }

  setupVirtualParam();
  u32 weapon = GfDataBlade::getBladeWeaponByRank(getBdatId(), chip);
  if (weapon != 0) {
    unknown18->unknown82c = weapon;
  }
}

void DataObjBlade::setVirtualEquipOrb(u32 orb, u32 slot) {
  setupVirtualParam();
  unknown18->unknown678[slot] = orb;
}

bool DataObjBlade::isVirtualSetting() const { return unknown18 != nullptr; }

bool DataObjBlade::isEnbaleTarget() const { return false; }

u32 DataObjBlade::getMenuOffset() const { return GfDataBlade::getOffsetID(getBdatId()); }

const char *DataObjBlade::getCenterBone() const { return get(false)->unknown7d4; }

const char *DataObjBlade::getCamBone() const { return get(false)->unknown7e8; }

u32 DataObjBlade::getEyeRotControl() const { return get(false)->unknown826; }

DataObjPcWpn::DataObjPcWpn(u32 id) : unknown08(INVALID_HANDLE), m_bdatId(id) {}

DataObjPcWpn::DataObjPcWpn(GF_OBJ_HANDLE *handle) : unknown08(handle) {
  GfObjAcc objAcc(handle);
  m_bdatId = objAcc.getPcWeaponId();
}

DataObjPcWpn::~DataObjPcWpn() {}

bool DataObjPcWpn::isValid() const { return m_bdatId != 0; }

const char *DataObjPcWpn::getName() const { return GfDataItem::getName(getBdatId()); }

bool DataObjPcWpn::getName(u8 *&bdat, u32 &textId) const { return GfDataItem::getName(bdat, textId, getBdatId()); }

u32 DataObjPcWpn::getBdatId() const { return m_bdatId; }

u32 DataObjPcWpn::getAttribute(bool, int slot) const {
  if (unknown08 == INVALID_HANDLE) {
    return 0;
  }

  int member = GfObjUtil::getObjSetup(unknown08)->partyMember;
  if (member == -1) {
    return 0;
  }

  DataParamAcc paramAcc(GfGameParty::getHandleBlade(member, slot));
  return paramAcc.getAttribute(-1, false);
}

u32 DataObjPcWpn::getEquipWeapon(bool, int) const { return m_bdatId; }

u32 DataObjPcWpn::getWeaponType(bool, int) const { return GfBdatItem::get()->getPcWpnWpnType(getBdatId()); }

int DataObjPcWpn::getBladeSet(bool isVirtual) const {
  if (unknown08 == INVALID_HANDLE) {
    return -1;
  }

  int member = GfObjUtil::getObjSetup(unknown08)->partyMember;
  if (member == -1) {
    return -1;
  }

  u32 driver = GfDataParty::getDriver(member);
  if (driver == 0) {
    return -1;
  }

  int maxSetBladeNum = GfDataDriver::getMaxSetBladeNum(driver);
  for (int slot = 0; slot < maxSetBladeNum; slot++) {
    u32 blade = GfDataDriver::getBlade(driver, slot);
    if (blade == 0) {
      continue;
    }

    DataObjBlade dataObjBlade(blade);
    if (dataObjBlade.getEquipWeapon(isVirtual, -1) == getBdatId()) {
      return slot;
    }
  }

  return -1;
}

u32 DataObjPcWpn::getWeaponDamage(bool) const { return GfBdatItem::get()->getPcWpnDamage(getBdatId()); }

u32 DataObjPcWpn::getWeaponStability(bool) const { return GfBdatItem::get()->getPcWpnStability(getBdatId()); }

DataObjEnemy::~DataObjEnemy() {}

bool DataObjEnemy::isValid() const { return m_SDataEnemy != nullptr; }

const char *DataObjEnemy::getName() const { return GfDataEnemy::getName(getBdatId()); }

bool DataObjEnemy::getName(u8 *&bdat, u32 &textId) const { return GfDataEnemy::getName(bdat, textId, getBdatId()); }

const char *DataObjEnemy::getModelResourceName() const { return GfBdatRsc::get()->getRscEnModel(m_SDataEnemy->unknown44); }

const char *DataObjEnemy::getMotionResourceName() const { return GfBdatRsc::get()->getRscEnMotion(m_SDataEnemy->unknown44); }

const char *DataObjEnemy::getEffectResourceName() const { return GfBdatRsc::get()->getRscEnComp_Eff(m_SDataEnemy->unknown44); }

u32 DataObjEnemy::getBdatId() const { return m_SDataEnemy->unknown00; }

static bool unknown003(f32 &value, u32 arrange, u32 percentEffect,
                       u32 addEffect) { // Inferred role: applyEnemyEnhance; original function name unknown.
  if (GfDataEnemy::getEquipBlade(arrange) == 0) {
    return false;
  }

  mm::mtl::FixedVector<u16, 64> enhances;
  GfDataEnemy::getValidEnhance(enhances, arrange);
  GfBdatBtl *bdatBattle = GfBdatBtl::get();
  f32 base = value;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == addEffect) {
        base += bdatBattle->getBTL_EnhanceParam1(*enhance);
      }
    } while (++enhance != enhances.end());
  }

  f32 percent = 0.0f;
  if (enhances.size() != 0) {
    u16 *enhance = enhances.begin();
    do {
      if (bdatBattle->getBTL_EnhanceEnhanceEffect(*enhance) == percentEffect) {
        percent += bdatBattle->getBTL_EnhanceParam1(*enhance) * PERCENT;
      }
    } while (++enhance != enhances.end());
  }

  value = base + base * percent;
  return true;
}

u32 DataObjEnemy::getHpMax(bool) const {
  f32 hpMax = m_SDataEnemy->unknownac;
  if (unknown003(hpMax, getBdatIdEnArrange(), ENHANCE_EFFECT_HP_MAX_PERCENT, ENHANCE_EFFECT_HP_MAX_ADD)) {
    f32 rate = GfDataBlade::getHpMaxRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    hpMax += hpMax * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevHpMaxRev(param);
    if (rev != 0) {
      hpMax = rev * PERMILLE * hpMax;
    }
  }

  if (hpMax > ENEMY_HP_MAX) {
    hpMax = ENEMY_HP_MAX;
  }

  return hpMax;
}

u32 DataObjEnemy::getHp() const {
  if (unknown08 != INVALID_HANDLE) {
    return GfObjUtil::getHp(unknown08);
  }

  return getHpMax(false);
}

u32 DataObjEnemy::getStrength(bool) const {
  f32 strength = m_SDataEnemy->unknownb0;
  if (unknown003(strength, getBdatIdEnArrange(), ENHANCE_EFFECT_STRENGTH_PERCENT, ENHANCE_EFFECT_STRENGTH_ADD)) {
    f32 rate = GfDataBlade::getStrengthRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    strength += strength * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevStrengthRev(param);
    if (rev != 0) {
      strength = rev * PERMILLE * strength;
    }
  }

  if (strength > ENEMY_STATUS_MAX) {
    strength = ENEMY_STATUS_MAX;
  }

  return strength;
}

u32 DataObjEnemy::getPowerEther(bool) const {
  f32 powerEther = m_SDataEnemy->unknownb2;
  if (unknown003(powerEther, getBdatIdEnArrange(), ENHANCE_EFFECT_POWER_ETHER_PERCENT, ENHANCE_EFFECT_POWER_ETHER_ADD)) {
    f32 rate = GfDataBlade::getPowerEtherRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    powerEther += powerEther * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevPowEtherRev(param);
    if (rev != 0) {
      powerEther = rev * PERMILLE * powerEther;
    }
  }

  if (powerEther > ENEMY_STATUS_MAX) {
    powerEther = ENEMY_STATUS_MAX;
  }

  return powerEther;
}

u32 DataObjEnemy::getDex(bool) const {
  f32 dex = m_SDataEnemy->unknownb4;
  if (unknown003(dex, getBdatIdEnArrange(), ENHANCE_EFFECT_DEX_PERCENT, ENHANCE_EFFECT_DEX_ADD)) {
    f32 rate = GfDataBlade::getDexRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    dex += dex * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevDexRev(param);
    if (rev != 0) {
      dex = rev * PERMILLE * dex;
    }
  }

  if (dex > ENEMY_STATUS_MAX) {
    dex = ENEMY_STATUS_MAX;
  }

  return dex;
}

u32 DataObjEnemy::getAgility(bool) const {
  f32 agility = m_SDataEnemy->unknownb6;
  if (unknown003(agility, getBdatIdEnArrange(), ENHANCE_EFFECT_AGILITY_PERCENT, ENHANCE_EFFECT_AGILITY_ADD)) {
    f32 rate = GfDataBlade::getAgilityRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    agility += agility * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevAgilityRev(param);
    if (rev != 0) {
      agility = rev * PERMILLE * agility;
    }
  }

  if (agility > ENEMY_AGILITY_MAX) {
    agility = ENEMY_AGILITY_MAX;
  }

  return agility;
}

u32 DataObjEnemy::getLuck(bool) const {
  f32 luck = m_SDataEnemy->unknownb8;
  if (unknown003(luck, getBdatIdEnArrange(), ENHANCE_EFFECT_LUCK_PERCENT, ENHANCE_EFFECT_LUCK_ADD)) {
    f32 rate = GfDataBlade::getLuckRev(GfDataEnemy::getEquipBlade(getBdatIdEnArrange())) * PERCENT;
    luck += luck * rate;
  }

  u32 param = m_SDataEnemy->unknown34;
  if (param != 0) {
    u32 rev = GfBdatChrEnParam::get()->getChrEnParamRevLuckRev(param);
    if (rev != 0) {
      luck = rev * PERMILLE * luck;
    }
  }

  if (luck > ENEMY_LUCK_MAX) {
    luck = ENEMY_LUCK_MAX;
  }

  return luck;
}

u32 DataObjEnemy::getPArmor(bool) const {
  f32 pArmor = m_SDataEnemy->unknown5c;
  if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
    unknown003(pArmor, getBdatIdEnArrange(), ENHANCE_EFFECT_P_ARMOR_PERCENT, ENHANCE_EFFECT_P_ARMOR_ADD);
  }

  if (pArmor > ARMOR_MAX) {
    pArmor = ARMOR_MAX;
  }

  return pArmor;
}

u32 DataObjEnemy::getEArmor(bool) const {
  f32 eArmor = m_SDataEnemy->unknown5e;
  if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
    unknown003(eArmor, getBdatIdEnArrange(), ENHANCE_EFFECT_E_ARMOR_PERCENT, ENHANCE_EFFECT_E_ARMOR_ADD);
  }

  if (eArmor > ARMOR_MAX) {
    eArmor = ARMOR_MAX;
  }

  return eArmor;
}

u32 DataObjEnemy::getCriticalRate(bool) const {
  f32 criticalRate = m_SDataEnemy->unknown63;
  if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
    unknown003(criticalRate, getBdatIdEnArrange(), ENHANCE_EFFECT_CRITICAL_RATE_PERCENT, ENHANCE_EFFECT_CRITICAL_RATE_ADD);
  }

  if (criticalRate > RATE_MAX) {
    criticalRate = RATE_MAX;
  }

  return criticalRate;
}

u32 DataObjEnemy::getGuardRate(bool) const {
  f32 guardRate = m_SDataEnemy->unknown64;
  if (GfDataEnemy::getEquipBlade(getBdatIdEnArrange()) != 0) {
    unknown003(guardRate, getBdatIdEnArrange(), ENHANCE_EFFECT_GUARD_RATE_PERCENT, ENHANCE_EFFECT_GUARD_RATE_ADD);
  }

  if (guardRate > RATE_MAX) {
    guardRate = RATE_MAX;
  }

  return guardRate;
}

u32 DataObjEnemy::getFootStep() const { return GfBdatRsc::get()->getRscEnFootStep(getBdatId()); }

u32 DataObjEnemy::getFootStepEffect() const { return GfBdatRsc::get()->getRscEnFootStepEffect(getBdatId()); }

u32 DataObjEnemy::getBlade(bool, int) const { return GfDataEnemy::getEquipBlade(getBdatId()); }

u32 DataObjEnemy::getEquipWeapon(bool, int slot) const { return m_SDataEnemy->unknown9e[slot]; }

u32 DataObjEnemy::getWeaponType(bool, int) const {
  u32 blade = GfDataEnemy::getEquipBlade(getBdatIdEnArrange());
  if (blade == 0) {
    return 0;
  }

  return GfDataBlade::getBladeWpnType(blade);
}

u32 DataObjEnemy::getAttribute(bool, int) const {
  u32 blade = GfDataEnemy::getEquipBlade(getBdatIdEnArrange());
  if (blade != 0) {
    u32 bladeArrange = GfDataEnemy::getEquipBladeEnArrangeID(getBdatIdEnArrange());
    if (bladeArrange != 0) {
      GfBdatChrEnArrange *bdatChrEnArrange = GfBdatChrEnArrange::get();
      if (bdatChrEnArrange->getChrEnArrangeBladeAtr(bladeArrange) != 0) {
        return bdatChrEnArrange->getChrEnArrangeBladeAtr(bladeArrange);
      }
    }

    return GfDataBlade::getAttribute(blade);
  }

  GfBdatChrEnArrange *bdatChrEnArrange = GfBdatChrEnArrange::get();
  if (bdatChrEnArrange->getChrEnArrangeBladeAtr(getBdatIdEnArrange()) != 0) {
    return bdatChrEnArrange->getChrEnArrangeBladeAtr(getBdatIdEnArrange());
  }

  return m_SDataEnemy->unknown62;
}

bool DataObjEnemy::isEnbaleTarget() const {
  if (GfBdatChrEnArrange::get()->getChrEnArrangeBladeID(getBdatId()) != 0) {
    return false;
  }

  return !GfBdatChrEnArrange::get()->isChrEnArrangeFlagNoTarget(getBdatId());
}

u32 DataObjEnemy::getChestHeight() const { return GfBdatRsc::get()->getRscEnChestHeight(getBdatIdEnRsc()); }

const char *DataObjEnemy::getVoiceStr() const { return GfDataEnemy::getVoiceStr(getBdatIdEnArrange()); }

u32 DataObjEnemy::getMenuOffset() const { return GfBdatRsc::get()->getRscEnoffsetID(getBdatIdEnRsc()); }

u32 DataObjEnemy::getBdatIdEnRsc() const { return GfBdatChrEnParam::get()->getChrEnParamResourceID(getBdatIdEnParam()); }

u32 DataObjEnemy::getBdatIdEnParam() const { return GfBdatChrEnArrange::get()->getChrEnArrangeParamID(getBdatIdEnArrange()); }

bool DataObjEnemy::isGuardFront() const { return m_SDataEnemy->unknown04_5; }

bool DataObjEnemy::isGuardLeft() const { return m_SDataEnemy->unknown04_6; }

bool DataObjEnemy::isGuardRight() const { return m_SDataEnemy->unknown04_7; }

bool DataObjEnemy::isGuardBack() const { return m_SDataEnemy->unknown05_0; }

bool DataObjEnemy::isFieldDamage() const { return m_SDataEnemy->unknown05_1; }

u32 DataObjEnemy::getResistancePower() const { return m_SDataEnemy->unknown60; }

u32 DataObjEnemy::getResistanceEther() const { return m_SDataEnemy->unknown61; }

u32 DataObjEnemy::getResistanceCombo() const { return m_SDataEnemy->unknown66; }

u32 DataObjEnemy::getInvincibleCombo() const { return m_SDataEnemy->unknown68; }

u32 DataObjEnemy::getLevelGold() const {
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = getLevel(false);
  mm::clamp(level, bdatBtl->getGrowStart(), bdatBtl->getGrowEnd() - 1);
  f32 gold = bdatBtl->getGrowEnemyGold(level);
  return gold * m_SDataEnemy->unknown12 / PERCENT_SCALE;
}

u32 DataObjEnemy::getLevelExp() const {
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = getLevel(false);
  mm::clamp(level, bdatBtl->getGrowStart(), bdatBtl->getGrowEnd() - 1);
  f32 exp = bdatBtl->getGrowEnemyExp(level);
  return exp * GfBdatChrEnArrange::get()->getChrEnArrangeExpRev(getBdatId()) / PERCENT_SCALE;
}

u32 DataObjEnemy::getLevelWp() const {
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = getLevel(false);
  mm::clamp(level, bdatBtl->getGrowStart(), bdatBtl->getGrowEnd() - 1);
  f32 wp = bdatBtl->getGrowEnemyWP(level);
  return wp * GfBdatChrEnArrange::get()->getChrEnArrangeWPRev(getBdatId()) / PERCENT_SCALE;
}

u32 DataObjEnemy::getLevelSp() const {
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = getLevel(false);
  mm::clamp(level, bdatBtl->getGrowStart(), bdatBtl->getGrowEnd() - 1);
  f32 sp = bdatBtl->getGrowEnemySP(level);
  return sp * GfBdatChrEnArrange::get()->getChrEnArrangeSPRev(getBdatId()) / PERCENT_SCALE;
}

u32 DataObjEnemy::getGenus() const { return m_SDataEnemy->unknown99; }

bool DataObjEnemy::isLinkGenus() const { return m_SDataEnemy->unknown04_4; }

f32 DataObjEnemy::getLinkRadius() const { return m_SDataEnemy->unknown1f; }

u32 DataObjEnemy::getGoldDivide() const { return GfBdatBtl::get()->getGrowGoldDivide(getLevel(false)); }

u32 DataObjEnemy::getGoldDivideRev() const { return GfBdatRsc::get()->getRscEnGoldDivideRev(m_SDataEnemy->unknown44); }

const SDataEnemy *DataObjEnemy::getSDataEnemy() const { return m_SDataEnemy; }

bool DataObjEnemy::isDispInitExtraParts(u32 part) const {
  if (m_SDataEnemy == nullptr) {
    return true;
  }

  if (m_SDataEnemy->unknown42 != 0 && (m_SDataEnemy->unknown42 & 1 << part) != 0) {
    return true;
  }

  return GfDataEnemy::getExtraParts(m_SDataEnemy->unknown44, part);
}

bool DataObjEnemy::isNoCameraFade() const { return m_SDataEnemy->unknown05_3; }

bool DataObjEnemy::isWeaponDrawDisp() const { return m_SDataEnemy->unknown05_4; }

const char *DataObjEnemy::getCenterBone() const { return GfBdatRsc::get()->getRscEnCenterBone(getBdatIdEnRsc()); }

const char *DataObjEnemy::getCamBone() const { return GfBdatRsc::get()->getRscEnCamBone(getBdatIdEnRsc()); }

u32 DataObjEnemy::getEyeRotControl() const { return GfBdatRsc::get()->getRscEnEyeRot(getBdatIdEnRsc()); }

const char *DataObjEnemy::getRotateBone() const { return GfBdatRsc::get()->getRscEnRotateBone(getBdatIdEnRsc()); }

DataObjEnemyBlade::~DataObjEnemyBlade() {}

SDataBlade *DataObjEnemyBlade::get(bool) const { return unknowne0; }

const char *DataObjEnemyBlade::getName() const { return GfDataBlade::getName(unknownd8->blade, 0); }

bool DataObjEnemyBlade::getName(u8 *&bdat, u32 &textId) const { return GfDataBlade::getName(bdat, textId, unknownd8->blade); }

const char *DataObjEnemyBlade::getModelResourceName() const { return unknowne0->unknown70c.c_str(); }

const char *DataObjEnemyBlade::getMotionResourceName() const { return unknowne0->unknown734.c_str(); }

const char *DataObjEnemyBlade::getEffectResourceName() const { return unknowne0->unknown7ac; }

u32 DataObjEnemyBlade::getWeaponType(bool, int) const { return unknowne0->unknown821; }

u32 DataObjEnemyBlade::getPArmor(bool isVirtual) const {
  u32 pArmor = unknowne0->unknown83e;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    pArmor += bdatItem->getPcWpnPArmor(weapon);
  }

  return pArmor;
}

u32 DataObjEnemyBlade::getEArmor(bool isVirtual) const {
  u32 eArmor = unknowne0->unknown83f;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    eArmor += bdatItem->getPcWpnEArmor(weapon);
  }

  return eArmor;
}

u32 DataObjEnemyBlade::getCriticalRate(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnCriRate(weapon);
}

u32 DataObjEnemyBlade::getGuardRate(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnGuardRate(weapon);
}

u32 DataObjEnemyBlade::getWeaponDamage(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnDamage(weapon);
}

u32 DataObjEnemyBlade::getWeaponStability(bool isVirtual) const {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon == 0) {
    return 0;
  }

  return bdatItem->getPcWpnStability(weapon);
}

u32 DataObjEnemyBlade::getEquipWeapon(bool, int) const { return unknowne0->unknown82c; }

u32 DataObjEnemyBlade::getChestHeight() const { return unknowne0->unknown82e; }

u32 DataObjEnemyBlade::getLandingHeight() const { return unknowne0->unknown830; }

u32 DataObjEnemyBlade::getIconData() const { return unknowne0->unknown70a; }

u32 DataObjEnemyBlade::getRace() const { return unknowne0->unknown708; }

u32 DataObjEnemyBlade::getQuestRace() const { return GfDataBlade::getQuestRace(unknowne0->unknown06); }

u32 DataObjEnemyBlade::getGender() const { return unknowne0->unknown709; }

u32 DataObjEnemyBlade::getAttribute(bool, int) const {
  if (unknownd8->getEnArrangeID() != 0) {
    GfBdatChrEnArrange *bdatChrEnArrange = GfBdatChrEnArrange::get();
    if (bdatChrEnArrange->getChrEnArrangeBladeAtr(unknownd8->getEnArrangeID()) != 0) {
      return bdatChrEnArrange->getChrEnArrangeBladeAtr(unknownd8->getEnArrangeID());
    }
  }

  return unknowne0->unknown823;
}

bool DataObjEnemyBlade::isDispInitExtraParts(u32 part) const {
  if (unknownd8 != nullptr && unknownd8->dataEnemy->unknown42 != 0) {
    return (unknownd8->dataEnemy->unknown42 & 1 << part) != 0;
  }

  return unknowne0->unknownc0[part] != 0;
}

u32 DataObjEnemyBlade::getEyeRotControl() const { return unknowne0->unknown826; }

u32 DataObjEnemyBlade::getBladeArts(bool, u32 index) const { return unknowne0->unknown3c[index].unknown00; }

u32 DataObjEnemyBlade::getBladeArtsLevel(bool, u32 index) const { return unknowne0->unknown3c[index].unknown07; }

u32 DataObjEnemyBlade::getBladeArtsH(bool, u32 index) const { return unknowne0->unknown3c[index].unknown02; }

u32 DataObjEnemyBlade::getBladeArtsN(bool, u32 index) const { return unknowne0->unknown60[index].unknown00; }

u32 DataObjEnemyBlade::getBladeArtsNH(bool, u32 index) const { return unknowne0->unknown60[index].unknown02; }

u32 DataObjEnemyBlade::getBladeArtsEx(bool) const { return unknowne0->unknown84; }

u32 DataObjEnemyBlade::getBladeArtsExH(bool) const { return unknowne0->unknown86; }

u32 DataObjEnemyBlade::getBladeArtsEx2(bool) const { return unknowne0->unknown90; }

u32 DataObjEnemyBlade::getBladeArtsEx2H(bool) const { return unknowne0->unknown92; }

u32 DataObjEnemyBlade::getPersonality() const { return unknowne0->unknown824; }

u32 DataObjEnemyBlade::getCoolTime() const { return unknowne0->unknown828; }

DataObjNpc::DataObjNpc(GF_OBJ_HANDLE *handle) : unknown08(handle), m_bdatId(0) { m_bdatId = mm::mtl::dynamicCast<GfObjSetupNpc>(GfObjManager::getObjInfo(handle)->setup)->id; }

DataObjNpc::DataObjNpc(u32 id) : unknown08(INVALID_HANDLE), m_bdatId(id) {}

bool DataObjNpc::isValid() const { return m_bdatId != 0; }

const char *DataObjNpc::getName() const { return GfDataNpc::getName(getBdatId()); }

bool DataObjNpc::getName(u8 *&bdat, u32 &textId) const { return GfDataNpc::getName(bdat, textId, getBdatId()); }

const char *DataObjNpc::getModelResourceName() const { return GfDataNpc::getModelName(getBdatId()); }

const char *DataObjNpc::getMotionResourceName() const { return GfDataNpc::getMotionName(getBdatId()); }

u32 DataObjNpc::getBdatId() const { return m_bdatId; }

bool DataObjNpc::isDispInitExtraParts(u32 part) const { return GfDataNpc::getExtraParts(getBdatId(), part); }

u32 DataObjNpc::getMenuOffset() const { return GfDataNpc::getOffsetID(getBdatId()); }

u32 DataObjNpc::getFootStep() const { return GfDataNpc::getFootStep(getBdatId()); }

u32 DataObjNpc::getFootStepEffect() const { return GfDataNpc::getFootStepEffect(getBdatId()); }

u32 DataObjNpc::getEyeRotControl() const { return GfDataNpc::getEyeRotControl(getBdatId()); }

DataObjMap::DataObjMap(GF_OBJ_HANDLE *handle) : unknown08(handle), m_bdatId(0) { m_bdatId = mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->setup)->id; }

DataObjMap::DataObjMap(u32 id) : unknown08(INVALID_HANDLE), m_bdatId(id) {}

bool DataObjMap::isValid() const { return m_bdatId != 0; }

const char *DataObjMap::getName() const { return GfBdatMaplist::get()->getMaplistresource(getBdatId()); }

u32 DataObjMap::getBdatId() const { return m_bdatId; }

DataObjMob::DataObjMob(GF_OBJ_HANDLE *handle) : unknown08(handle), m_bdatId(0) { m_bdatId = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->setup)->id; }

DataObjMob::DataObjMob(u32 id) : unknown08(INVALID_HANDLE), m_bdatId(id) {}

bool DataObjMob::isValid() const { return m_bdatId != 0; }

const char *DataObjMob::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjMob::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjMob::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjMob::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjMob::getBdatId() const { return m_bdatId; }

bool DataObjMob::isDispInitExtraParts(u32 part) const { return GfBdatRsc::get()->getRscMobListExtraParts(getBdatId(), part) != 0; }

u32 DataObjMob::getMenuOffset() const { return GfBdatRsc::get()->getRscMobListOffsetID(getBdatId()); }

u32 DataObjMob::getFootStep() const { return GfDataMob::getFootStep(getBdatId()); }

u32 DataObjMob::getFootStepEffect() const { return GfDataMob::getFootStepEffect(getBdatId()); }

DataObjUiObj::DataObjUiObj(GF_OBJ_HANDLE *handle) : unknown08(handle), m_bdatId(0) { m_bdatId = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->setup)->id; }

DataObjUiObj::DataObjUiObj(u32 id) : unknown08(INVALID_HANDLE), m_bdatId(id) {}

bool DataObjUiObj::isValid() const { return m_bdatId != 0; }

const char *DataObjUiObj::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjUiObj::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjUiObj::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjUiObj::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjUiObj::getBdatId() const { return m_bdatId; }

bool DataObjUiObj::isDispInitExtraParts(u32) const { return false; }

DataObjGmk::DataObjGmk(GF_OBJ_HANDLE *handle) : unknown08(handle), m_bdatId(0) {
  GfObjSetupGimmick *setup = mm::mtl::dynamicCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(handle)->setup);
  m_bdatId = setup->id;
  m_gimmickType = setup->gimmickType;
}

DataObjGmk::DataObjGmk(u32 id, GimmickType gimmickType) : unknown08(INVALID_HANDLE), m_bdatId(id), m_gimmickType(gimmickType) {}

bool DataObjGmk::isValid() const { return m_bdatId != 0; }

const char *DataObjGmk::getName() const { return ""; }

bool DataObjGmk::getName(u8 *&, u32 &) const { return false; }

const char *DataObjGmk::getModelResourceName() const {
  if (m_gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListModel(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListModel(getBdatId());
}

const char *DataObjGmk::getMotionResourceName() const {
  if (m_gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListMotion(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListMotion(getBdatId());
}

u32 DataObjGmk::getBdatId() const { return m_bdatId; }

bool DataObjGmk::isDispInitExtraParts(u32) const {
  if (m_gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return false;
  }

  return GfBdatRsc::get()->getRSC_MapObjListExtraParts1(getBdatId()) != 0;
}

DataObjBelonging::DataObjBelonging(GF_OBJ_HANDLE *handle) : unknown08(handle) { GfObjUtil::getObjSetup<GfObjSetupBelonging>(handle); }

bool DataObjBelonging::isValid() const { return unknown08 != INVALID_HANDLE; }

const char *DataObjBelonging::getName() const { return ""; }

bool DataObjBelonging::getName(u8 *&, u32 &) const { return false; }

const char *DataObjBelonging::getModelResourceName() const { return ""; }

const char *DataObjBelonging::getMotionResourceName() const { return ""; }

u32 DataObjBelonging::getBdatId() const { return 0; }

} // namespace gf
