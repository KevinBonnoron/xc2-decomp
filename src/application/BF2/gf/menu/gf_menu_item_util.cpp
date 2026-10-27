#include "gf/menu/gf_menu_item_util.h"

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_util.h"
#include "gf/util/gf_item_util.h"

namespace gf {

namespace {

const u32 unknown001[] = {0, 0x16, 2, 1, 0xa}; // Inferred role: common window id of each equip error; original name unknown.

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

} // namespace gf
