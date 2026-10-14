#include "gf/data/gf_data_weapon.h"
#include "bdat.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_bdat_msg.h"
#include "gf/data/gf_bdat_rsc.h"

namespace gf {

constexpr u32 WEAPON_TYPE_COUNT = 16;
constexpr u32 WEAPON_TYPE_SPECIAL = 0x11;

const char *GfDataWeapon::getName(u32 weapon) {
  u32 textId = GfBdatItem::get()->getPcWpnName(weapon);
  u8 *bdat = GfBdatMsg::getFpPcWpn();
  const char *name = textId == 0 || bdat == nullptr ? nullptr : Bdat::getMSText(bdat, textId);
  if (name == nullptr) {
    name = "";
  }

  return name;
}

bool GfDataWeapon::getName(u8 *&bdat, u32 &textId, u32 weapon) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  bdat = nullptr;
  textId = bdatItem->getPcWpnName(weapon);
  bdat = GfBdatMsg::getFpPcWpn();
  return textId != 0 && bdat != nullptr;
}

const char *GfDataWeapon::getModelName(u32 weapon) { return GfBdatRsc::get()->getRSC_PcWpnModel(weapon); }

const char *GfDataWeapon::getMotionName(u32 weapon) { return GfBdatRsc::get()->getRSC_PcWpnMotion(weapon); }

u32 GfDataWeapon::getNewWeapon(u32 weapon, u32 chip) {
  GfBdatItem *bdatItem = GfBdatItem::get();
  u32 weaponTypeIndex = bdatItem->getPcWpnWpnType(weapon) - 1;
  if (weaponTypeIndex < WEAPON_TYPE_COUNT) {
    return bdatItem->getPcWpnChipCreateWpn(chip, weaponTypeIndex);
  }

  return 0;
}

u32 GfDataWeapon::getDamage(u32 weapon) { return GfBdatItem::get()->getPcWpnDamage(weapon); }

u32 GfDataWeapon::getGuardRatio(u32 weapon) { return GfBdatItem::get()->getPcWpnGuardRate(weapon); }

u32 GfDataWeapon::getCriticalRatio(u32 weapon) { return GfBdatItem::get()->getPcWpnCriRate(weapon); }

u32 GfDataWeapon::getStability(u32 weapon) { return GfBdatItem::get()->getPcWpnStability(weapon); }

u32 GfDataWeapon::getEnhance(u32 weapon) { return GfBdatItem::get()->getPcWpnEnhance1(weapon); }

u32 GfDataWeapon::getRank(u32 weapon) {
  if (weapon == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcWpnRank(weapon);
}

bool GfDataWeapon::getWeaponTypeName(u8 *&bdat, u32 &textId, u32 weaponType) {
  textId = GfBdatItem::get()->getPcWpnTypeName(weaponType);
  bdat = GfBdatMsg::getFpPcWpnType();
  return textId != 0;
}

bool GfDataWeapon::getWeaponTypeNameByItem(u8 *&bdat, u32 &textId, u32 weapon) {
  u32 weaponType = GfBdatItem::get()->getPcWpnWpnType(weapon);
  if (weaponType == 0) {
    return false;
  }

  return getWeaponTypeName(bdat, textId, weaponType);
}

const char *GfDataWeapon::getWeaponTypeName(u32 weaponType) {
  const char *name = weaponType == 0 ? nullptr : Bdat::getMSText(GfBdatMsg::getFpPcWpnType(), weaponType);
  if (name == nullptr) {
    name = "";
  }

  return name;
}

u32 GfDataWeapon::getAsmWeaponType(u32 weaponType) {
  if (weaponType == 0) {
    return 0;
  }

  return GfBdatItem::get()->getPcWpnTypeMotion(weaponType);
}

u32 GfDataWeapon::getEffWeaponType(u32 weaponType) {
  if (weaponType == 0) {
    return 0;
  }

  if (weaponType == WEAPON_TYPE_SPECIAL) {
    return WEAPON_TYPE_SPECIAL;
  }

  return GfBdatItem::get()->getPcWpnTypeMotion(weaponType);
}

} // namespace gf
