#include "gf/util/gf_equip_util.h"
#include "gf/data/gf_bdat_btl.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_driver_arts.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_id.h"
#include "gf/request/gf_req_command.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"

namespace gf {

bool GfEquipUtil::isEquipBladeChip(u32 blade, u32 chip) {
  if (GfItemUtil::getItemBoxCount(chip) == 0) {
    return false;
  }
  return GfDataBlade::getBladeWeaponByRank(blade, chip) != 0;
}

void GfEquipUtil::equipBladeChip(u32 blade, u32 chip) {
  GfDataBlade::getBladeWeapon(blade);
  if (GfItemUtil::getItemBoxCount(chip) != 0) {
    GfItemUtil::addItemBox(chip, -1);
  }
  GfDataBlade::setBladeWeapon(blade, GfDataBlade::getBladeWeaponByRank(blade, chip));
  GfReqCommand::reqRebuildPartyWeapon(blade);
}

u32 GfEquipUtil::getEquipDriverAcce(u32 driver, u32 slot) { return GfDataDriver::getEquipAcce(driver, slot); }

bool GfEquipUtil::equipDriverAcce(u32 driver, u32 slot, u32 accessory, GfItemHandle handle) {
  GfDataItem::getItemType(accessory);
  u32 oldAccessory = GfDataDriver::getEquipAcce(driver, slot);
  if (oldAccessory != 0) {
    GfItemHandle oldHandle = GfDataDriver::getEquipAcceHandle(driver, slot);
    GfDataDriver::setEquipAcce(driver, slot, 0);
    GfDataDriver::setEquipAcceHandle(driver, slot, GfItemHandle(0));
    if (oldHandle.value != 0) {
      GfItemUtil::setEquipFlag(oldAccessory, oldHandle, false);
    } else if (GfItemUtil::isEnableAddItemBox(oldAccessory, 1)) {
      GfItemUtil::addItemBox(oldAccessory, 1);
    } else if (GfDataItem::isEnableSell(oldAccessory)) {
      SCOM_ADD_MONEY::create(GfDataItem::getPrice(oldAccessory));
    }
  }

  if (handle.value == 0) {
    handle = GfItemUtil::getNoEquipItemHandle(accessory);
  }
  GfItemUtil::setEquipFlag(accessory, handle, true);
  GfDataDriver::setEquipAcce(driver, slot, accessory);
  GfDataDriver::setEquipAcceHandle(driver, slot, handle);
  return true;
}

u32 GfEquipUtil::getEquipAcceResult(u32 driver, u32 slot, u32 accessory) { return getEquipAcceResult(*GfDataDriver::getSDataDriver(driver), slot, accessory); }

u32 GfEquipUtil::getEquipOrbMax(u32 blade) { return GfDataBlade::getEquipOrbMax(blade); }

u32 GfEquipUtil::getEquipBladeOrb(u32 blade, u32 slot) { return GfDataBlade::getEquipOrb(blade, slot); }

bool GfEquipUtil::equipBladeOrb(u32 blade, u32 orb, u32 slot, GfItemHandle handle) {
  u32 oldOrb = GfDataBlade::getEquipOrb(blade, slot);
  if (oldOrb != 0) {
    GfItemHandle oldHandle = GfDataBlade::getEquipOrbHandle(blade, slot);
    if (oldHandle.value != 0) {
      GfItemUtil::setEquipFlag(oldOrb, oldHandle, false);
    } else {
      GfDataBlade::setEquipOrb(blade, 0, slot);
      if (GfItemUtil::isEnableAddItemBox(oldOrb, 1)) {
        GfItemUtil::addItemBox(oldOrb, 1);
      } else if (GfDataItem::isEnableSell(oldOrb)) {
        SCOM_ADD_MONEY::create(GfDataItem::getPrice(oldOrb));
      }
    }
  }

  if (handle.value == 0) {
    handle = GfItemUtil::getNoEquipItemHandle(orb);
  }
  GfItemUtil::setEquipFlag(orb, handle, true);
  GfDataBlade::setEquipOrb(blade, orb, slot);
  GfDataBlade::setEquipOrbHandle(blade, handle, slot);
  return true;
}

u32 GfEquipUtil::getEquipOrbResult(u32 blade, u32 orb, u32 slot) {
  if (GfDataItem::getItemType(orb) != ItemType::EQUIP_ORB) {
    return EQUIP_RESULT_INVALID_TYPE;
  }
  if (GfItemUtil::getItemBoxCount(orb) == 0) {
    return EQUIP_RESULT_NO_ITEM;
  }

  GfBdatItem *bdatItem = GfBdatItem::get();
  GfBdatBtl *bdatBtl = GfBdatBtl::get();
  u32 enhanceCategory = bdatItem->getEquipOrbEnhanceCategory(orb);
  u32 equipOrbMax = GfDataBlade::getEquipOrbMax(blade);
  for (u32 i = 0; i < equipOrbMax; i++) {
    u32 equipOrb = GfDataBlade::getEquipOrb(blade, i);
    if (slot != i && equipOrb != 0 && bdatItem->getEquipOrbEnhanceCategory(equipOrb) == enhanceCategory) {
      return EQUIP_RESULT_SAME_CATEGORY;
    }
  }

  u32 effect = bdatBtl->getBTL_EnhanceEnhanceEffect(bdatItem->getEquipOrbEnhance(orb));
  equipOrbMax = GfDataBlade::getEquipOrbMax(blade);
  for (u32 i = 0; i < equipOrbMax; i++) {
    u32 equipOrb = GfDataBlade::getEquipOrb(blade, i);
    if (slot != i && equipOrb != 0 && effect == bdatBtl->getBTL_EnhanceEnhanceEffect(bdatItem->getEquipOrbEnhance(equipOrb))) {
      return EQUIP_RESULT_SAME_EFFECT;
    }
  }

  if (slot == static_cast<u32>(-1) && GfDataBlade::isEquipOrbFull(blade)) {
    return EQUIP_RESULT_FULL;
  }
  return EQUIP_RESULT_OK;
}

u32 GfEquipUtil::execWpUpItem(u32 driver, u32 item, u32 weaponType) {
  if (item >= ITEM_WP_UP_FIRST && item <= ITEM_WP_UP_LAST) {
    if (GfItemUtil::getItemBoxCount(item) == 0) {
      return EQUIP_RESULT_NO_ITEM;
    }
    GfDataDriverArts::addWp(driver, weaponType, GfBdatItem::get()->getPreciousType(item));
    GfItemUtil::addItemBox(item, -1);
    return EQUIP_RESULT_OK;
  }
  return EQUIP_RESULT_INVALID_TYPE;
}

} // namespace gf
