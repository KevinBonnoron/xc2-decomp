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
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/util/gf_equip_util.h"
#include "mm_math/mm_math.h"

namespace gf {

static GF_OBJ_HANDLE *const INVALID_HANDLE = reinterpret_cast<GF_OBJ_HANDLE *>(-1);

constexpr u32 DRIVER_LEVEL_MAX = 99;
constexpr u32 DRIVER_ARTS_LEVEL_MAX = 5;
constexpr int SLOT_ARTS_COUNT = 3;
constexpr u32 EXTRA_PARTS_COUNT = 4;
constexpr u32 ARMOR_MAX = 100;
constexpr f32 PERCENT = 0.01f;
constexpr f32 PERCENT_SCALE = 100.0f;

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

DataObjDriver::DataObjDriver(u32 id) : data(nullptr), handle(INVALID_HANDLE), virtualData(nullptr), virtualEquipWeapons(), menuParam(false) {
  setup(id);
}

void DataObjDriver::setup(u32 id) {
  this->id = id;
  if (id != 0) {
    data = GfDataDriver::getSDataDriver(id);
  }
}

DataObjDriver::DataObjDriver(GF_OBJ_HANDLE *handle)
    : id(0), data(nullptr), handle(handle), virtualData(nullptr), virtualEquipWeapons(), menuParam(false) {
  GfObjAcc objAcc(handle);
  setup(objAcc.getDriverId());
}

DataObjDriver::~DataObjDriver() {
  if (virtualData != nullptr) {
    delete virtualData;
    virtualData = nullptr;
  }
}

void DataObjDriver::setVirtualLevel(u32 level) {
  setupVirtualParam();
  SDataDriver &dataDriver = *data;
  GfDataDriver::setLevel(dataDriver, level);
  GfDataDriver::calcDriverBaseParamByLevel(dataDriver);
}

void DataObjDriver::setVirtualEquipWpn(u32 weapon, int slot) {
  setupVirtualParam();
  if (slot < 0) {
    slot = getBladeSet(false);
  }

  if (slot >= 0) {
    virtualEquipWeapons[slot] = weapon;
  }
}

void DataObjDriver::setVirtualEquipAcc(u32 slot, u32 accessory) {
  setupVirtualParam();
  if (GfDataItem::getItemType(accessory) == ItemType::PC_EQUIP) {
    GfDataDriver::setEquipAcce(*data, slot, accessory);
  }
}

void DataObjDriver::setVirtualSetBlade(u32 blade, int slot) {
  setupVirtualParam();
  SDataDriver *dataDriver = data;
  int ruleSlot = GfDataDriver::getRuleSetBlade(getBdatId(), blade, slot);
  int maxSetBladeNum = GfDataDriver::getMaxSetBladeNum(*dataDriver);
  for (int i = 0; i < maxSetBladeNum; i++) {
    if (getBlade(true, i) == blade) {
      dataDriver->blades[ruleSlot] = 0;
      break;
    }
  }

  dataDriver->blades[ruleSlot] = blade;
  if (dataDriver->bladeSet < 0) {
    dataDriver->bladeSet = ruleSlot;
  }
}

bool DataObjDriver::isVirtualSetting() const { return virtualData != nullptr; }

u32 DataObjDriver::getMenuOffset() const { return GfBdatChrDr::get()->getChrDrOffsetID(getBdatId()); }

const char *DataObjDriver::getCenterBone() const { return GfBdatChrDr::get()->getChrDrCenterBone(getBdatId()); }

const char *DataObjDriver::getCamBone() const { return GfBdatChrDr::get()->getChrDrCamBone(getBdatId()); }

u32 DataObjDriver::getEyeRotControl() const { return GfDataDriver::getEyeRotControl(getBdatId()); }

bool DataObjDriver::isValid() const { return data != nullptr && data->id != 0; }

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

u32 DataObjDriver::getBdatId() const { return id; }

u32 DataObjDriver::getDataType() const { return data->activate; }

u32 DataObjDriver::getHp() const { return GfObjUtil::getHp(handle); }

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

    weaponType = GfDataBlade::getSDataBlade(blade)->weaponType;
  }

  return get(false)->weapons[weaponType].wp;
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

u32 DataObjDriver::getDriverArts(u32 weaponType, u32 index) const { return get(false)->weapons[weaponType].slotArts[index]; }

u32 DataObjDriver::getDriverArtsLevel(u32 arts) const { return get(false)->artsLevel[arts]; }

void DataObjDriver::setDriverArtsLevel(u32 arts, u32 level) {
  if (level > DRIVER_ARTS_LEVEL_MAX) {
    level = DRIVER_ARTS_LEVEL_MAX;
  }

  get(false)->artsLevel[arts] = level;
}

u32 DataObjDriver::getClass(bool isVirtual) const { return GfDataDriver::getClass(*get(isVirtual)); }

u32 DataObjDriver::getPArmor(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->id == 0) {
    return dataDriver->pArmor;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && virtualEquipWeapons[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(virtualEquipWeapons[slot], slot);
  }

  u32 bladePArmor = dataObjBlade.getPArmor(isVirtual);
  u32 pArmor = get(isVirtual)->pArmor + bladePArmor;
  return pArmor > ARMOR_MAX ? ARMOR_MAX : pArmor;
}

bool DataObjBlade::isValid() const { return data != nullptr && data->id != 0; }

void DataObjBlade::setVirtualEquipWpn(u32 weapon, int) {
  if (weapon != 0) {
    setupVirtualParam();
    virtualData->weapon = weapon;
  }
}

static void applyBladeEnhance(u32 &value, SDataBlade &dataBlade, u32 percentEffect, u32 addEffect, bool isVirtual) {
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

  applyBladeEnhance(pArmor, *get(isVirtual), ENHANCE_EFFECT_P_ARMOR_PERCENT, ENHANCE_EFFECT_P_ARMOR_ADD, isVirtualSetting() | menuParam);
  applyBladeEnhance(pArmor, *get(isVirtual), ENHANCE_EFFECT_NONE, ENHANCE_EFFECT_ARMOR_ADD, isVirtualSetting() | menuParam);
  return pArmor;
}

u32 DataObjDriver::getEArmor(bool isVirtual) const {
  SDataDriver *dataDriver = get(isVirtual);
  u32 blade = getBlade(isVirtual, -1);
  DataObjBlade dataObjBlade(blade);
  if (blade == 0 || dataObjBlade.get(true)->id == 0) {
    return dataDriver->eArmor;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && virtualEquipWeapons[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(virtualEquipWeapons[slot], slot);
  }

  u32 bladeEArmor = dataObjBlade.getEArmor(isVirtual);
  u32 eArmor = dataDriver->eArmor + bladeEArmor;
  return eArmor > ARMOR_MAX ? ARMOR_MAX : eArmor;
}

u32 DataObjBlade::getEArmor(bool isVirtual) const {
  u32 eArmor = GfDataBlade::getEarmor(getBdatId());
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    eArmor += bdatItem->getPcWpnEArmor(weapon);
  }

  applyBladeEnhance(eArmor, *get(isVirtual), ENHANCE_EFFECT_E_ARMOR_PERCENT, ENHANCE_EFFECT_E_ARMOR_ADD, isVirtualSetting() | menuParam);
  applyBladeEnhance(eArmor, *get(isVirtual), ENHANCE_EFFECT_NONE, ENHANCE_EFFECT_ARMOR_ADD, isVirtualSetting() | menuParam);
  return eArmor;
}

u32 DataObjBlade::getCriticalRate(bool isVirtual) const {
  u32 criticalRate = 0;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    criticalRate = bdatItem->getPcWpnCriRate(weapon);
  }

  applyBladeEnhance(
      criticalRate, *get(isVirtual), ENHANCE_EFFECT_CRITICAL_RATE_PERCENT, ENHANCE_EFFECT_CRITICAL_RATE_ADD, isVirtualSetting() | menuParam);
  return criticalRate;
}

u32 DataObjBlade::getGuardRate(bool isVirtual) const {
  u32 guardRate = 0;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    guardRate = bdatItem->getPcWpnGuardRate(weapon);
  }

  applyBladeEnhance(guardRate, *get(isVirtual), ENHANCE_EFFECT_GUARD_RATE_PERCENT, ENHANCE_EFFECT_GUARD_RATE_ADD, isVirtualSetting() | menuParam);
  return guardRate;
}

u32 DataObjDriver::getAutoHate(bool isVirtual) const {
  u32 blade = getBlade(isVirtual, -1);
  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->id == 0) {
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
  if (dataObjBlade.get(true)->id == 0) {
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
  if (dataObjBlade.get(true)->id == 0) {
    return 0;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && virtualEquipWeapons[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(virtualEquipWeapons[slot], slot);
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
  if (dataObjBlade.get(true)->id == 0) {
    return 0;
  }

  int slot = getBladeSet(isVirtual);
  if (slot >= 0 && virtualEquipWeapons[slot] != 0) {
    dataObjBlade.setVirtualEquipWpn(virtualEquipWeapons[slot], slot);
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
  if (blade == 0 || dataObjBlade.get(true)->id == 0) {
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
  if (blade == 0 || dataObjBlade.get(true)->id == 0) {
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

u32 DataObjDriver::getEquipAcceResult(u32 slot, u32 accessory, bool isVirtual) const {
  return GfEquipUtil::getEquipAcceResult(*get(isVirtual), slot, accessory);
}

int DataObjDriver::getBladeSet(bool isVirtual) const { return GfDataDriver::getBladeSet(*get(isVirtual)); }

void DataObjDriver::setBladeSet(int slot) {
  if (slot < 0 || DataObjDriver::getBlade(true, slot) == 0) {
    return;
  }

  int oldSlot = data->bladeSet;
  if (oldSlot >= 0) {
    GfDataDriver::setEquipBlade(data->id, false, oldSlot);
  }

  GfDataDriver::setEquipBlade(data->id, true, slot);
  GfEvent::callBladeChange(handle, oldSlot, slot);
}

u32 DataObjDriver::getBlade(bool isVirtual, int slot) const {
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    return setup->fixedBlade;
  }

  if (slot >= 0) {
    return data->blades[slot];
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
  if (dataObjBlade.get(true)->id == 0) {
    return 0;
  }

  if (isVirtual && virtualEquipWeapons[slot] != 0) {
    return virtualEquipWeapons[slot];
  }

  return dataObjBlade.getEquipWeapon(isVirtual, slot);
}

u32 DataObjBlade::getEquipWeapon(bool isVirtual, int) const { return get(isVirtual)->weapon; }

u32 DataObjDriver::getWeaponType(bool isVirtual, int slot) const {
  u32 blade = getBlade(isVirtual, slot);
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    blade = setup->fixedBlade;
  }

  if (blade == 0) {
    return 0;
  }

  DataObjBlade dataObjBlade(blade);
  if (dataObjBlade.get(true)->id == 0) {
    return 0;
  }

  return dataObjBlade.getWeaponType(isVirtual, slot);
}

u32 DataObjBlade::getWeaponType(bool isVirtual, int) const { return get(isVirtual)->weaponType; }

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

  u32 blade = slot >= 0 ? data->blades[slot] : 0;
  GfObjSetup *setup = GfObjUtil::getObjSetup(handle);
  if (setup != nullptr && setup->hasFixedBlade && setup->fixedBlade != 0) {
    blade = setup->fixedBlade;
  }

  DataObjBlade dataObjBlade(blade);
  return dataObjBlade.getAttribute(isVirtual, slot);
}

u32 DataObjBlade::getAttribute(bool, int) const { return GfDataBlade::getAttribute(getBdatId()); }

bool DataObjDriver::isScenarioMask() const { return GfDataDriver::isScenarioMask(getBdatId()); }

u32 DataObjDriver::getRole() const { return GfDataBlade::getRole(getBlade(false, -1)); }

const char *DataObjDriver::getVoiceStr() const { return GfDataDriver::getVoiceStr(*data); }

u32 DataObjDriver::getFieldSkill(bool, u32 index) const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getFieldSkill(false, index);
}

u32 DataObjBlade::getFieldSkill(bool, u32 index) const { return get(false)->fieldSkills[index].id; }

u32 DataObjDriver::getFieldSkillLevel(bool, u32 index) const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getFieldSkillLevel(false, index);
}

u32 DataObjBlade::getFieldSkillLevel(bool, u32 index) const { return get(false)->fieldSkills[index].level; }

u32 DataObjDriver::getKeyLevel() const {
  DataObjBlade dataObjBlade(getBlade(false, -1));
  return dataObjBlade.getKeyLevel();
}

u32 DataObjBlade::getKeyLevel() const { return get(false)->keyReleaseLevel; }

u32 DataObjDriver::getFavoriteCategory(FAVORITE favorite) const { return GfDataDriver::getFavorite(getBdatId(), favorite); }

u32 DataObjDriver::getFavoriteItem(FAVORITE favorite) const { return GfDataDriver::getFavorite(getBdatId(), favorite); }

DataObjBlade::DataObjBlade(u32 id) : data(nullptr), handle(INVALID_HANDLE), virtualData(nullptr), menuParam(false) { setup(id); }

void DataObjBlade::setup(u32 id) {
  this->id = id;
  if (id != 0) {
    data = GfDataBlade::getSDataBlade(id);
  }
}

DataObjBlade::DataObjBlade(GF_OBJ_HANDLE *handle) : data(nullptr), handle(handle), virtualData(nullptr), id(0), menuParam(false) {
  GfObjAcc objAcc(handle);
  setup(objAcc.getBladeId());
}

DataObjBlade::~DataObjBlade() {
  if (virtualData != nullptr) {
    delete virtualData;
    virtualData = nullptr;
  }
}

void DataObjBlade::setupVirtualParam() {
  if (virtualData == nullptr) {
    virtualData = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) SDataBlade;
    *virtualData = *data;
    data = virtualData;
  }
}

const char *DataObjBlade::getModelResourceName() const { return get(false)->resourceNameModel.c_str(); }

const char *DataObjBlade::getMotionResourceName() const { return get(false)->resourceNameMotion.c_str(); }

const char *DataObjBlade::getEffectResourceName() const { return get(false)->resourceNameEffect; }

const char *DataObjBlade::getSeResourceName() const { return get(false)->sePack; }

const char *DataObjBlade::getName() const { return GfDataBlade::getName(getBdatId(), 0); }

bool DataObjBlade::getName(u8 *&bdat, u32 &textId) const { return GfDataBlade::getName(bdat, textId, getBdatId()); }

u32 DataObjBlade::getBdatId() const { return id; }

u32 DataObjBlade::getDataType() const { return get(false)->activate; }

u32 DataObjBlade::getHpMax(bool) const { return GfDataBlade::getHpMaxRev(getBdatId()); }

u32 DataObjBlade::getStrength(bool) const { return GfDataBlade::getStrengthRev(getBdatId()); }

u32 DataObjBlade::getPowerEther(bool) const { return GfDataBlade::getPowerEtherRev(getBdatId()); }

u32 DataObjBlade::getDex(bool) const { return GfDataBlade::getDexRev(getBdatId()); }

u32 DataObjBlade::getAgility(bool) const { return GfDataBlade::getAgilityRev(getBdatId()); }

u32 DataObjBlade::getLuck(bool) const { return GfDataBlade::getLuckRev(getBdatId()); }

bool DataObjBlade::getEquipOrb(mm::mtl::FixedArray<u16, 3> &orbs, bool) const { return GfDataBlade::getEquipOrb(orbs, getBdatId()); }

u32 DataObjBlade::getChestHeight() const { return get(false)->chestHeight; }

u32 DataObjBlade::getLandingHeight() const { return get(false)->landingHeight; }

u32 DataObjBlade::getIconData() const { return get(false)->iconData; }

u32 DataObjBlade::getRace() const { return get(false)->race; }

u32 DataObjBlade::getQuestRace() const { return GfDataBlade::getQuestRace(get(false)->id); }

u32 DataObjBlade::getFootStep() const { return GfDataBlade::getFootStep(getBdatId()); }

u32 DataObjBlade::getFootStepEffect() const { return GfDataBlade::getFootStepEffect(getBdatId()); }

u32 DataObjBlade::getGender() const { return get(false)->gender; }

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

u32 DataObjBlade::getBladeArts(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->id; }

u32 DataObjBlade::getBladeArtsEnhance(bool, u32 index) const { return GfDataBlade::getArtsEnhance(getBdatId(), index); }

u32 DataObjBlade::getBladeArtsLevel(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->level; }

u32 DataObjBlade::getBladeArtsH(bool, u32 index) const { return GfDataBlade::getArts(getBdatId(), index)->artsH; }

u32 DataObjBlade::getBladeArtsN(bool, u32 index) const { return GfDataBlade::getNArts(getBdatId(), index)->id; }

u32 DataObjBlade::getBladeArtsNH(bool, u32 index) const { return GfDataBlade::getNArts(getBdatId(), index)->artsH; }

u32 DataObjBlade::getBladeArtsEx(bool isVirtual) const { return get(isVirtual)->artsEx; }

u32 DataObjBlade::getBladeArtsExH(bool isVirtual) const { return get(isVirtual)->artsExH; }

u32 DataObjBlade::getBladeArtsEx2(bool isVirtual) const { return get(isVirtual)->artsEx2; }

u32 DataObjBlade::getBladeArtsEx2H(bool isVirtual) const { return get(isVirtual)->artsEx2H; }

u32 DataObjBlade::getBladeSkill(bool isVirtual, u32 index) const { return get(isVirtual)->skills[index].id; }

u32 DataObjBlade::getBladeSkillLevel(bool isVirtual, u32 index) const { return get(isVirtual)->skills[index].level; }

u32 DataObjBlade::getPersonality() const { return get(false)->personality; }

u32 DataObjBlade::getCoolTime() const { return get(false)->coolTime; }

u32 DataObjBlade::getFavoriteCategory(FAVORITE favorite) const { return GfDataBlade::getFavorite(getBdatId(), favorite); }

u32 DataObjBlade::getFavoriteItem(FAVORITE favorite) const { return GfDataBlade::getFavorite(getBdatId(), favorite); }

u32 DataObjBlade::getArtsAchievement(u32 index) const { return get(false)->artsAchievements[index].achievement; }

u32 DataObjBlade::getSkillAchievement(u32 index) const { return get(false)->skillAchievements[index].achievement; }

u32 DataObjBlade::getFieldSkillAchievement(u32 index) const { return get(false)->fieldSkillAchievements[index].achievement; }

u32 DataObjBlade::getKeyAchievement() const { return get(false)->keyAchievement.achievement; }

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
    virtualData->weapon = weapon;
  }
}

void DataObjBlade::setVirtualEquipOrb(u32 orb, u32 slot) {
  setupVirtualParam();
  virtualData->equipOrbs[slot] = orb;
}

bool DataObjBlade::isVirtualSetting() const { return virtualData != nullptr; }

bool DataObjBlade::isEnbaleTarget() const { return false; }

u32 DataObjBlade::getMenuOffset() const { return GfDataBlade::getOffsetID(getBdatId()); }

const char *DataObjBlade::getCenterBone() const { return get(false)->centerBone; }

const char *DataObjBlade::getCamBone() const { return get(false)->camBone; }

u32 DataObjBlade::getEyeRotControl() const { return get(false)->eyeRotControl; }

DataObjPcWpn::DataObjPcWpn(u32 id) : handle(INVALID_HANDLE), id(id) {}

DataObjPcWpn::DataObjPcWpn(GF_OBJ_HANDLE *handle) : handle(handle) {
  GfObjAcc objAcc(handle);
  id = objAcc.getPcWeaponId();
}

DataObjPcWpn::~DataObjPcWpn() {}

bool DataObjPcWpn::isValid() const { return id != 0; }

const char *DataObjPcWpn::getName() const { return GfDataItem::getName(getBdatId()); }

bool DataObjPcWpn::getName(u8 *&bdat, u32 &textId) const { return GfDataItem::getName(bdat, textId, getBdatId()); }

u32 DataObjPcWpn::getBdatId() const { return id; }

u32 DataObjPcWpn::getAttribute(bool, int slot) const {
  if (handle == INVALID_HANDLE) {
    return 0;
  }

  int member = GfObjUtil::getObjSetup(handle)->partyMember;
  if (member == -1) {
    return 0;
  }

  DataParamAcc paramAcc(GfGameParty::getHandleBlade(member, slot));
  return paramAcc.getAttribute(-1, false);
}

u32 DataObjPcWpn::getEquipWeapon(bool, int) const { return id; }

u32 DataObjPcWpn::getWeaponType(bool, int) const { return GfBdatItem::get()->getPcWpnWpnType(getBdatId()); }

int DataObjPcWpn::getBladeSet(bool isVirtual) const {
  if (handle == INVALID_HANDLE) {
    return -1;
  }

  int member = GfObjUtil::getObjSetup(handle)->partyMember;
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

bool DataObjEnemy::isValid() const { return data != nullptr; }

const char *DataObjEnemy::getName() const { return GfDataEnemy::getName(getBdatId()); }

bool DataObjEnemy::getName(u8 *&bdat, u32 &textId) const { return GfDataEnemy::getName(bdat, textId, getBdatId()); }

const char *DataObjEnemy::getModelResourceName() const { return GfBdatRsc::get()->getRscEnModel(data->resource); }

const char *DataObjEnemy::getMotionResourceName() const { return GfBdatRsc::get()->getRscEnMotion(data->resource); }

const char *DataObjEnemy::getEffectResourceName() const { return GfBdatRsc::get()->getRscEnComp_Eff(data->resource); }

u32 DataObjEnemy::getBdatId() const { return data->arrange; }

u32 DataObjEnemy::getHp() const {
  if (handle != INVALID_HANDLE) {
    return GfObjUtil::getHp(handle);
  }

  return getHpMax(false);
}

u32 DataObjEnemy::getFootStep() const { return GfBdatRsc::get()->getRscEnFootStep(getBdatId()); }

u32 DataObjEnemy::getFootStepEffect() const { return GfBdatRsc::get()->getRscEnFootStepEffect(getBdatId()); }

u32 DataObjEnemy::getBlade(bool, int) const { return GfDataEnemy::getEquipBlade(getBdatId()); }

u32 DataObjEnemy::getEquipWeapon(bool, int slot) const { return data->equipWeapons[slot]; }

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

  return data->bladeAttribute;
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

bool DataObjEnemy::isGuardFront() const { return data->guardFront; }

bool DataObjEnemy::isGuardLeft() const { return data->guardLeft; }

bool DataObjEnemy::isGuardRight() const { return data->guardRight; }

bool DataObjEnemy::isGuardBack() const { return data->guardBack; }

bool DataObjEnemy::isFieldDamage() const { return data->fieldDamage; }

u32 DataObjEnemy::getResistancePower() const { return data->resistancePower; }

u32 DataObjEnemy::getResistanceEther() const { return data->resistanceEther; }

u32 DataObjEnemy::getResistanceCombo() const { return data->resistanceCombo; }

u32 DataObjEnemy::getInvincibleCombo() const { return data->invincibleCombo; }

u32 DataObjEnemy::getLevelGold() const {
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 level = getLevel(false);
  mm::clamp(level, bdatBtl->getGrowStart(), bdatBtl->getGrowEnd() - 1);
  f32 gold = bdatBtl->getGrowEnemyGold(level);
  return gold * data->goldRev / PERCENT_SCALE;
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

u32 DataObjEnemy::getGenus() const { return data->genus; }

bool DataObjEnemy::isLinkGenus() const { return data->linkGenus; }

f32 DataObjEnemy::getLinkRadius() const { return data->linkRadius; }

u32 DataObjEnemy::getGoldDivide() const { return GfBdatBtl::get()->getGrowGoldDivide(getLevel(false)); }

u32 DataObjEnemy::getGoldDivideRev() const { return GfBdatRsc::get()->getRscEnGoldDivideRev(data->resource); }

const SDataEnemy *DataObjEnemy::getSDataEnemy() const { return data; }

bool DataObjEnemy::isDispInitExtraParts(u32 part) const {
  if (data == nullptr) {
    return true;
  }

  if (data->extraParts != 0 && (data->extraParts & 1 << part) != 0) {
    return true;
  }

  return GfDataEnemy::getExtraParts(data->resource, part);
}

bool DataObjEnemy::isNoCameraFade() const { return data->noCameraFade; }

bool DataObjEnemy::isWeaponDrawDisp() const { return data->weaponDrawDisp; }

const char *DataObjEnemy::getCenterBone() const { return GfBdatRsc::get()->getRscEnCenterBone(getBdatIdEnRsc()); }

const char *DataObjEnemy::getCamBone() const { return GfBdatRsc::get()->getRscEnCamBone(getBdatIdEnRsc()); }

u32 DataObjEnemy::getEyeRotControl() const { return GfBdatRsc::get()->getRscEnEyeRot(getBdatIdEnRsc()); }

const char *DataObjEnemy::getRotateBone() const { return GfBdatRsc::get()->getRscEnRotateBone(getBdatIdEnRsc()); }

DataObjEnemyBlade::~DataObjEnemyBlade() {}

SDataBlade *DataObjEnemyBlade::get(bool) const { return dataBlade; }

const char *DataObjEnemyBlade::getName() const { return GfDataBlade::getName(setupEnemy->blade, 0); }

bool DataObjEnemyBlade::getName(u8 *&bdat, u32 &textId) const { return GfDataBlade::getName(bdat, textId, setupEnemy->blade); }

const char *DataObjEnemyBlade::getModelResourceName() const { return dataBlade->resourceNameModel.c_str(); }

const char *DataObjEnemyBlade::getMotionResourceName() const { return dataBlade->resourceNameMotion.c_str(); }

const char *DataObjEnemyBlade::getEffectResourceName() const { return dataBlade->resourceNameEffect; }

u32 DataObjEnemyBlade::getWeaponType(bool, int) const { return dataBlade->weaponType; }

u32 DataObjEnemyBlade::getPArmor(bool isVirtual) const {
  u32 pArmor = dataBlade->pArmor;
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weapon = getEquipWeapon(isVirtual, -1);
  if (weapon != 0) {
    pArmor += bdatItem->getPcWpnPArmor(weapon);
  }

  return pArmor;
}

u32 DataObjEnemyBlade::getEArmor(bool isVirtual) const {
  u32 eArmor = dataBlade->eArmor;
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

u32 DataObjEnemyBlade::getEquipWeapon(bool, int) const { return dataBlade->weapon; }

u32 DataObjEnemyBlade::getChestHeight() const { return dataBlade->chestHeight; }

u32 DataObjEnemyBlade::getLandingHeight() const { return dataBlade->landingHeight; }

u32 DataObjEnemyBlade::getIconData() const { return dataBlade->iconData; }

u32 DataObjEnemyBlade::getRace() const { return dataBlade->race; }

u32 DataObjEnemyBlade::getQuestRace() const { return GfDataBlade::getQuestRace(dataBlade->id); }

u32 DataObjEnemyBlade::getGender() const { return dataBlade->gender; }

u32 DataObjEnemyBlade::getAttribute(bool, int) const {
  if (setupEnemy->getEnArrangeID() != 0) {
    GfBdatChrEnArrange *bdatChrEnArrange = GfBdatChrEnArrange::get();
    if (bdatChrEnArrange->getChrEnArrangeBladeAtr(setupEnemy->getEnArrangeID()) != 0) {
      return bdatChrEnArrange->getChrEnArrangeBladeAtr(setupEnemy->getEnArrangeID());
    }
  }

  return dataBlade->attribute;
}

bool DataObjEnemyBlade::isDispInitExtraParts(u32 part) const {
  if (setupEnemy != nullptr && setupEnemy->dataEnemy->extraParts != 0) {
    return (setupEnemy->dataEnemy->extraParts & 1 << part) != 0;
  }

  return dataBlade->extraParts[part] != 0;
}

u32 DataObjEnemyBlade::getEyeRotControl() const { return dataBlade->eyeRotControl; }

u32 DataObjEnemyBlade::getBladeArts(bool, u32 index) const { return dataBlade->arts[index].id; }

u32 DataObjEnemyBlade::getBladeArtsLevel(bool, u32 index) const { return dataBlade->arts[index].level; }

u32 DataObjEnemyBlade::getBladeArtsH(bool, u32 index) const { return dataBlade->arts[index].artsH; }

u32 DataObjEnemyBlade::getBladeArtsN(bool, u32 index) const { return dataBlade->nArts[index].id; }

u32 DataObjEnemyBlade::getBladeArtsNH(bool, u32 index) const { return dataBlade->nArts[index].artsH; }

u32 DataObjEnemyBlade::getBladeArtsEx(bool) const { return dataBlade->artsEx; }

u32 DataObjEnemyBlade::getBladeArtsExH(bool) const { return dataBlade->artsExH; }

u32 DataObjEnemyBlade::getBladeArtsEx2(bool) const { return dataBlade->artsEx2; }

u32 DataObjEnemyBlade::getBladeArtsEx2H(bool) const { return dataBlade->artsEx2H; }

u32 DataObjEnemyBlade::getPersonality() const { return dataBlade->personality; }

u32 DataObjEnemyBlade::getCoolTime() const { return dataBlade->coolTime; }

DataObjNpc::DataObjNpc(GF_OBJ_HANDLE *handle) : handle(handle), id(0) {
  id = mm::mtl::dynamicCast<GfObjSetupNpc>(GfObjManager::getObjInfo(handle)->setup)->id;
}

DataObjNpc::DataObjNpc(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjNpc::isValid() const { return id != 0; }

const char *DataObjNpc::getName() const { return GfDataNpc::getName(getBdatId()); }

bool DataObjNpc::getName(u8 *&bdat, u32 &textId) const { return GfDataNpc::getName(bdat, textId, getBdatId()); }

const char *DataObjNpc::getModelResourceName() const { return GfDataNpc::getModelName(getBdatId()); }

const char *DataObjNpc::getMotionResourceName() const { return GfDataNpc::getMotionName(getBdatId()); }

u32 DataObjNpc::getBdatId() const { return id; }

bool DataObjNpc::isDispInitExtraParts(u32 part) const { return GfDataNpc::getExtraParts(getBdatId(), part); }

u32 DataObjNpc::getMenuOffset() const { return GfDataNpc::getOffsetID(getBdatId()); }

u32 DataObjNpc::getFootStep() const { return GfDataNpc::getFootStep(getBdatId()); }

u32 DataObjNpc::getFootStepEffect() const { return GfDataNpc::getFootStepEffect(getBdatId()); }

u32 DataObjNpc::getEyeRotControl() const { return GfDataNpc::getEyeRotControl(getBdatId()); }

DataObjMap::DataObjMap(GF_OBJ_HANDLE *handle) : handle(handle), id(0) {
  id = mm::mtl::dynamicCast<GfObjSetupMap>(GfObjManager::getObjInfo(handle)->setup)->id;
}

DataObjMap::DataObjMap(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjMap::isValid() const { return id != 0; }

const char *DataObjMap::getName() const { return GfBdatMaplist::get()->getMaplistresource(getBdatId()); }

u32 DataObjMap::getBdatId() const { return id; }

DataObjMob::DataObjMob(GF_OBJ_HANDLE *handle) : handle(handle), id(0) {
  id = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->setup)->id;
}

DataObjMob::DataObjMob(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjMob::isValid() const { return id != 0; }

const char *DataObjMob::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjMob::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjMob::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjMob::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjMob::getBdatId() const { return id; }

bool DataObjMob::isDispInitExtraParts(u32 part) const { return GfBdatRsc::get()->getRscMobListExtraParts(getBdatId(), part) != 0; }

u32 DataObjMob::getMenuOffset() const { return GfBdatRsc::get()->getRscMobListOffsetID(getBdatId()); }

u32 DataObjMob::getFootStep() const { return GfDataMob::getFootStep(getBdatId()); }

u32 DataObjMob::getFootStepEffect() const { return GfDataMob::getFootStepEffect(getBdatId()); }

DataObjUiObj::DataObjUiObj(GF_OBJ_HANDLE *handle) : handle(handle), id(0) {
  id = mm::mtl::dynamicCast<GfObjSetupMob>(GfObjManager::getObjInfo(handle)->setup)->id;
}

DataObjUiObj::DataObjUiObj(u32 id) : handle(INVALID_HANDLE), id(id) {}

bool DataObjUiObj::isValid() const { return id != 0; }

const char *DataObjUiObj::getName() const { return GfDataMob::getName(getBdatId()); }

bool DataObjUiObj::getName(u8 *&bdat, u32 &textId) const { return GfDataMob::getName(bdat, textId, getBdatId()); }

const char *DataObjUiObj::getModelResourceName() const { return GfBdatRsc::get()->getRscMobListModel(getBdatId()); }

const char *DataObjUiObj::getMotionResourceName() const { return GfBdatRsc::get()->getRscMobListMotion(getBdatId()); }

u32 DataObjUiObj::getBdatId() const { return id; }

bool DataObjUiObj::isDispInitExtraParts(u32) const { return false; }

DataObjGmk::DataObjGmk(GF_OBJ_HANDLE *handle) : handle(handle), id(0) {
  GfObjSetupGimmick *setup = mm::mtl::dynamicCast<GfObjSetupGimmick>(GfObjManager::getObjInfo(handle)->setup);
  id = setup->id;
  gimmickType = setup->gimmickType;
}

DataObjGmk::DataObjGmk(u32 id, GimmickType gimmickType) : handle(INVALID_HANDLE), id(id), gimmickType(gimmickType) {}

bool DataObjGmk::isValid() const { return id != 0; }

const char *DataObjGmk::getName() const { return ""; }

bool DataObjGmk::getName(u8 *&, u32 &) const { return false; }

const char *DataObjGmk::getModelResourceName() const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListModel(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListModel(getBdatId());
}

const char *DataObjGmk::getMotionResourceName() const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return GfBdatRsc::get()->getRSC_TboxListMotion(getBdatId());
  }

  return GfBdatRsc::get()->getRSC_MapObjListMotion(getBdatId());
}

u32 DataObjGmk::getBdatId() const { return id; }

bool DataObjGmk::isDispInitExtraParts(u32) const {
  if (gimmickType == GIMMICK_TYPE_TREASURE_BOX) {
    return false;
  }

  return GfBdatRsc::get()->getRSC_MapObjListExtraParts1(getBdatId()) != 0;
}

DataObjBelonging::DataObjBelonging(GF_OBJ_HANDLE *handle) : handle(handle) { GfObjUtil::getObjSetup<GfObjSetupBelonging>(handle); }

bool DataObjBelonging::isValid() const { return handle != INVALID_HANDLE; }

const char *DataObjBelonging::getName() const { return ""; }

bool DataObjBelonging::getName(u8 *&, u32 &) const { return false; }

const char *DataObjBelonging::getModelResourceName() const { return ""; }

const char *DataObjBelonging::getMotionResourceName() const { return ""; }

u32 DataObjBelonging::getBdatId() const { return 0; }

} // namespace gf
