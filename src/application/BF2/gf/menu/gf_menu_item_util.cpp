#include "gf/menu/gf_menu_item_util.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_util.h"
#include "gf/util/gf_item_util.h"

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
    {428, ItemType::SALVAGE, 0},
    {429, ItemType::INFO, 0},
    {430, ItemType::PC_WPN_CHIP, 0},
    {432, ItemType::EQUIP_ORB, 0},
    {434, ItemType::FAVORITE, 12},
    {435, ItemType::FAVORITE, 13},
    {436, ItemType::FAVORITE, 14},
    {437, ItemType::FAVORITE, 15},
    {438, ItemType::FAVORITE, 16},
    {439, ItemType::FAVORITE, 17},
    {440, ItemType::FAVORITE, 18},
    {441, ItemType::FAVORITE, 19},
    {442, ItemType::FAVORITE, 20},
    {443, ItemType::FAVORITE, 21},
    {444, ItemType::FAVORITE, 22},
    {445, ItemType::FAVORITE, 23},
    {446, ItemType::PC_EQUIP, 0},
};

} // namespace

bool GfMenuItemUtil::canCountStack(u32 itemType) {
  switch (itemType) {
  case ItemType::PC_EQUIP:
  case ItemType::EQUIP_ORB:
  case ItemType::HANA_ROLE:
  case ItemType::HANA_ATR:
  case ItemType::HANA_ARTS_ENH:
  case ItemType::HANA_N_ARTS_SET:
  case ItemType::HANA_ASSIST:
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

  if (GfDataItem::getItemType(item) == ItemType::PC_EQUIP) {
    u32 count = GfItemUtil::getCountByType(ItemType::PC_EQUIP);
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
  if (GfDataUtil::getMoney() >= MONEY_MAX) {
    return false;
  }

  return GfDataItem::isEnableSell(item);
}

bool GfMenuItemUtil::canSellItemType(u32 itemType) {
  switch (itemType) {
  case ItemType::PC_WPN_CHIP:
  case ItemType::PC_EQUIP:
  case ItemType::EQUIP_ORB:
  case ItemType::SALVAGE:
  case ItemType::COLLECTION_LIST:
  case ItemType::TRESURE:
  case ItemType::EMPTY_ORB:
  case ItemType::FAVORITE:
  case ItemType::CRYSTAL_LIST:
  case ItemType::BOOSTER:
    return true;
  default:
    return false;
  }
}

u32 GfMenuItemUtil::getEquipErrorCmnWindowID(u32 error) {
  if (error > 4) {
    return 0;
  }

  return unknown001[error];
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
