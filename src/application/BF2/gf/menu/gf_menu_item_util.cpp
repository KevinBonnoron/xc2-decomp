#include "gf/menu/gf_menu_item_util.h"

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_bdat_item.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_blade.h"
#include "gf/data/gf_data_driver.h"
#include "gf/data/gf_data_hana.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_party.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/util/gf_equip_util.h"
#include "gf/util/gf_item_util.h"
#include "gf/util/gf_recipe_orb_util.h"
#include "mm_mtl/fixed_array.h"
#include "mm_mtl/fixed_vector.h"
#include "ui/ui_str.h"

namespace gf {

namespace {

const u32 unknown001[] = {0, 0x16, 2, 1, 0xa}; // Inferred role: common window id of each equip error; original name unknown.

// Inferred role: shop icon to item type conversion entry; original name unknown.
struct unknown002 {
  u32 unknown00;            // Inferred role: shop icon id; original member name unknown.
  ItemType::Type unknown04; // Inferred role: item type; original member name unknown.
  u32 unknown08;            // Inferred role: item type parameter; original member name unknown.
};

const unknown002 unknown003[] = {
    // Inferred role: shop icon conversion table; original name unknown.
    {428, ItemType::ITEM_TYPE_UNKNOWN_5, 0},
    {429, ItemType::ITEM_TYPE_UNKNOWN_14, 0},
    {430, ItemType::ITEM_TYPE_UNKNOWN_1, 0},
    {432, ItemType::ITEM_TYPE_UNKNOWN_3, 0},
    {434, ItemType::ITEM_TYPE_UNKNOWN_10, 12},
    {435, ItemType::ITEM_TYPE_UNKNOWN_10, 13},
    {436, ItemType::ITEM_TYPE_UNKNOWN_10, 14},
    {437, ItemType::ITEM_TYPE_UNKNOWN_10, 15},
    {438, ItemType::ITEM_TYPE_UNKNOWN_10, 16},
    {439, ItemType::ITEM_TYPE_UNKNOWN_10, 17},
    {440, ItemType::ITEM_TYPE_UNKNOWN_10, 18},
    {441, ItemType::ITEM_TYPE_UNKNOWN_10, 19},
    {442, ItemType::ITEM_TYPE_UNKNOWN_10, 20},
    {443, ItemType::ITEM_TYPE_UNKNOWN_10, 21},
    {444, ItemType::ITEM_TYPE_UNKNOWN_10, 22},
    {445, ItemType::ITEM_TYPE_UNKNOWN_10, 23},
    {446, ItemType::ITEM_TYPE_UNKNOWN_2, 0},
};

} // namespace

void GfMenuItemUtil::getItemName(u8 itemType, u32 item, ui::UIStr &name) {
  u8 *bdat = GfMenuBdat::getItemDataFP(itemType, item);
  u8 *textBdat = GfMenuBdat::getItemTextFP(itemType, item);
  if (bdat != nullptr && textBdat != nullptr && Bdat::getMember(bdat, "Name") != nullptr && GfMenuBdat::isValidBdatID(bdat, item)) {
    u16 nameId = Bdat::getVal(bdat, "Name", item).valueU16;
    if (nameId != 0 && GfMenuBdat::isValidBdatID(textBdat, nameId)) {
      name.copy(ui::UIStr(textBdat, nameId));
    }
  }
}

void GfMenuItemUtil::getItemTypeName(u8 itemType, ui::UIStr &name) {
  u8 *bdat = GfDataBdat::getFP(BDAT_MNU_MSG_ITEM_TYPE);
  if (GfMenuBdat::isValidBdatID(bdat, itemType + 1)) {
    u16 nameId = Bdat::getVal(bdat, "name", itemType + 1).valueU16;
    name.copy(ui::UIStr(GfDataBdat::getFP(BDAT_MENU_MS), nameId));
  }
}

bool GfMenuItemUtil::canCountStack(u32 itemType) {
  switch (itemType) {
  case ItemType::ITEM_TYPE_UNKNOWN_2:
  case ItemType::ITEM_TYPE_UNKNOWN_3:
  case ItemType::ITEM_TYPE_UNKNOWN_16:
  case ItemType::ITEM_TYPE_UNKNOWN_17:
  case ItemType::ITEM_TYPE_UNKNOWN_18:
  case ItemType::ITEM_TYPE_UNKNOWN_19:
  case ItemType::ITEM_TYPE_UNKNOWN_20:
    return false;
  default:
    return true;
  }
}

bool GfMenuItemUtil::canBuyItem(u32 item, u32 shop) {
  ItemPrice price;
  price.clear();
  GfItemUtil::getPrice(price, item, shop);
  if (GfDataUtil::getMoney() < price.unknown04) {
    return false;
  }

  if (GfDataItem::getItemType(item) == ItemType::ITEM_TYPE_UNKNOWN_2) {
    u32 count = GfItemUtil::getCountByType(ItemType::ITEM_TYPE_UNKNOWN_2);
    u32 stock = GfItemUtil::getEnableStock(item);
    if (count >= stock) {
      return false;
    }
  } else {
    u32 stock = GfItemUtil::getEnableStock(item);
    u32 count = GfItemUtil::getItemBoxCount(item);
    if (stock == count) {
      return false;
    }
  }

  return true;
}

bool GfMenuItemUtil::canSellItem(u32 item, u32 shop) {
  if (GfDataUtil::getMoney() >= MONEY_UNKNOWN_999999999) {
    return false;
  }

  return GfDataItem::isEnableSell(item);
}

bool GfMenuItemUtil::canSellItemType(u32 itemType) {
  switch (itemType) {
  case ItemType::ITEM_TYPE_UNKNOWN_1:
  case ItemType::ITEM_TYPE_UNKNOWN_2:
  case ItemType::ITEM_TYPE_UNKNOWN_3:
  case ItemType::ITEM_TYPE_UNKNOWN_5:
  case ItemType::ITEM_TYPE_UNKNOWN_7:
  case ItemType::ITEM_TYPE_UNKNOWN_8:
  case ItemType::ITEM_TYPE_UNKNOWN_9:
  case ItemType::ITEM_TYPE_UNKNOWN_10:
  case ItemType::ITEM_TYPE_UNKNOWN_11:
  case ItemType::ITEM_TYPE_UNKNOWN_12:
    return true;
  default:
    return false;
  }
}

u32 GfMenuItemUtil::canEquipAcc(u32 accessory, u32 driver, u32 slot) {
  if (driver == 0) {
    return 0;
  }
  if (GfEquipUtil::getEquipDriverAcce(driver, slot) == accessory) {
    return 1;
  }

  switch (GfEquipUtil::getEquipAcceResult(driver, slot, accessory)) {
  case EQUIP_RESULT_UNKNOWN_0:
    return 0;
  case EQUIP_RESULT_UNKNOWN_5:
    return 3;
  case EQUIP_RESULT_UNKNOWN_6:
    return 2;
  default:
    return 4;
  }
}

u32 GfMenuItemUtil::canEquipAcc(u32 accessory, GfItemHandle handle, u32 driver, u32 slot) {
  if (driver == 0) {
    return 0;
  }
  u32 result = GfEquipUtil::getEquipAcceResult(driver, slot, accessory);
  switch (result) {
  case EQUIP_RESULT_UNKNOWN_6: {
    for (u32 i = 0; i < 2; i++) {
      u32 equip = GfEquipUtil::getEquipDriverAcce(driver, i);
      if (equip != 0 && equip == accessory && GfDataDriver::getEquipAcceHandle(driver, i).value == handle.value) {
        return 1;
      }
    }
    return 2;
  }
  case EQUIP_RESULT_UNKNOWN_5:
    return 3;
  case EQUIP_RESULT_UNKNOWN_0:
    break;
  default:
    if (result == EQUIP_RESULT_UNKNOWN_3 || result == EQUIP_RESULT_UNKNOWN_4) {
      u32 equipDriver = searchEquipAcc(accessory, handle, nullptr);
      if (equipDriver == 0) {
        return 4;
      }
      return equipDriver == driver ? 1 : 4;
    }
    return 0;
  }
  u32 equipDriver = searchEquipAcc(accessory, handle, nullptr);
  if (equipDriver == 0) {
    return 0;
  }
  return equipDriver == driver ? 1 : 2;
}

u32 GfMenuItemUtil::searchEquipAcc(u32 accessory, GfItemHandle handle, u32 *slot) {
  mm::mtl::FixedVector<u16, 16> drivers;
  GfPartySelect::getDriverList(drivers, GfPartySelect::LIST_TYPE_UNKNOWN_6, 0);
  for (u32 i = 0; i < drivers.size(); i++) {
    u32 driver = drivers[i];
    if (driver == 0) {
      continue;
    }
    for (u32 j = 0; j < 2; j++) {
      u32 equip = GfEquipUtil::getEquipDriverAcce(driver, j);
      if (equip != 0 && equip == accessory && GfDataDriver::getEquipAcceHandle(driver, j).value == handle.value) {
        if (slot != nullptr) {
          *slot = j;
        }
        return driver;
      }
    }
  }
  return 0;
}

u32 GfMenuItemUtil::canEquipOrb(u32 orb, u32 blade, u32 slot) {
  if (blade == 0) {
    return 0;
  }
  if (GfEquipUtil::getEquipBladeOrb(blade, slot) == orb) {
    return 1;
  }
  if (GfEquipUtil::getEquipOrbResult(blade, orb, slot) == EQUIP_RESULT_UNKNOWN_3) {
    return 4;
  }
  return 0;
}

u32 GfMenuItemUtil::canEquipOrb(u32 orb, GfItemHandle handle, u32 blade, u32 slot) {
  if (blade == 0) {
    return 0;
  }
  u32 result = GfEquipUtil::getEquipOrbResult(blade, orb, slot);
  switch (result) {
  case EQUIP_RESULT_UNKNOWN_6: {
    u32 equipOrbMax = GfEquipUtil::getEquipOrbMax(blade);
    for (u32 i = 0; i < equipOrbMax; i++) {
      u32 equip = GfEquipUtil::getEquipBladeOrb(blade, i);
      if (equip != 0 && equip == orb && GfDataBlade::getEquipOrbHandle(blade, i).value == handle.value) {
        return 1;
      }
    }
    return 2;
  }
  case EQUIP_RESULT_UNKNOWN_5:
    return 3;
  case EQUIP_RESULT_UNKNOWN_0:
    break;
  default:
    if (result == EQUIP_RESULT_UNKNOWN_3 || result == EQUIP_RESULT_UNKNOWN_4) {
      u32 equipBlade = searchEquipOrb(orb, handle, nullptr);
      if (equipBlade == 0) {
        return 4;
      }
      return equipBlade == blade ? 1 : 4;
    }
    return 0;
  }
  u32 equipBlade = searchEquipOrb(orb, handle, nullptr);
  if (equipBlade == 0) {
    return 0;
  }
  return equipBlade == blade ? 1 : 2;
}

u32 GfMenuItemUtil::searchEquipOrb(u32 orb, GfItemHandle handle, u32 *slot) {
  mm::mtl::FixedVector<u16, 422> blades;
  GfDataBlade::getListRegular(blades);
  GfDataBlade::getListRare(blades);
  GfDataBlade::getlistCommon(blades);
  for (u32 i = 0; i < blades.size(); i++) {
    u16 blade = blades[i];
    if (blade == 0) {
      continue;
    }
    u32 equipOrbMax = GfEquipUtil::getEquipOrbMax(blade);
    for (u32 j = 0; j < equipOrbMax; j++) {
      u32 equip = GfEquipUtil::getEquipBladeOrb(blade, j);
      if (equip != 0 && equip == orb && GfDataBlade::getEquipOrbHandle(blade, j).value == handle.value) {
        if (slot != nullptr) {
          *slot = j;
        }
        return blade;
      }
    }
  }
  return 0;
}

u32 GfMenuItemUtil::searchEquipHanaParts(u32 type, u32 parts, GfItemHandle handle) {
  if (parts == 0) {
    return 0;
  }
  mm::mtl::FixedVector<u16, 422> blades;
  if (!GfDataBlade::getListUse(blades)) {
    return 0;
  }
  for (u32 i = 0; i < blades.size(); i++) {
    u32 blade = blades[i];
    if (blade == 0 || !GfDataHana::isValid(blade)) {
      continue;
    }
    EquipHana *equip = GfDataHana::getEquipParts(blade);
    switch (type) {
    case 1:
      if (equip->unknown00 == parts && equip->unknown58 == handle.value) {
        return blade;
      }
      break;
    case 2:
      if (equip->unknown02 == parts && equip->unknown5c == handle.value) {
        return blade;
      }
      break;
    case 3:
    case 4:
    case 5:
      for (u32 j = 0; j < 3; j++) {
        if (equip->unknown28[j].unknown04 == parts && equip->unknown28[j].unknown0a == handle.value) {
          return blade;
        }
      }
      break;
    case 6:
    case 7:
    case 8:
    case 12:
    case 13:
    case 14:
      for (u32 j = 0; j < 3; j++) {
        if (equip->unknown4c[j] == parts && equip->unknown60[j] == handle.value) {
          return blade;
        }
      }
      for (u32 j = 0; j < 3; j++) {
        if (equip->unknown52[j] == parts && equip->unknown6c[j] == handle.value) {
          return blade;
        }
      }
      break;
    case 9:
    case 10:
    case 11:
      for (u32 j = 0; j < 3; j++) {
        if (equip->unknown04[j].unknown04 == parts && equip->unknown04[j].unknown0a == handle.value) {
          return blade;
        }
      }
      break;
    }
  }
  return 0;
}

u32 GfMenuItemUtil::canCreateOrb(u32 item) {
  u32 recipe = GfRecipeOrbUtil::getRecipeID(item);
  if (recipe == 0) {
    return 3;
  }
  if (!GfRecipeOrbUtil::isEnableRecipe(recipe)) {
    return 2;
  }

  u64 count;
  {
    mm::mtl::FixedVector<GfItem, 1024> items;
    GfItemUtil::getInfo(items, ItemType::ITEM_TYPE_UNKNOWN_3, false);
    count = items.size() + 1;
  }
  return count > 500;
}

u32 GfMenuItemUtil::getEquipErrorCmnWindowID(u32 error) {
  if (error > 4) {
    return 0;
  }

  return unknown001[error];
}

bool GfMenuItemUtil::getItemCrystal(u32 item, CrystalInfo &info) {
  if (item >= GfBdatItem::get()->getCrystalListStart() && item < GfBdatItem::get()->getCrystalListEnd()) {
    info.unknown00 = 3;
    info.unknown01 = 1;
  }
  return false;
}

u32 GfMenuItemUtil::getItemNum(u8 itemType, u32 itemId) { return GfItemUtil::getItemBoxCount(itemId); }

int GfMenuItemUtil::getItemIconID(u8 itemType, u32 itemId) { return itemType - 1; }

bool GfMenuItemUtil::convShopIcon(u32 icon, ItemType::Type &type, u32 &param) {
  for (u32 i = 0; i < sizeof(unknown003) / sizeof(unknown003[0]); i++) {
    if (unknown003[i].unknown00 == icon) {
      type = unknown003[i].unknown04;
      param = unknown003[i].unknown08;
      return true;
    }
  }
  return false;
}

} // namespace gf
