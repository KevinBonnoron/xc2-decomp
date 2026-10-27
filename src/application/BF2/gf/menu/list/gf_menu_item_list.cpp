#include "gf/menu/list/gf_menu_item_list.h"

#include <functional>

#include "bdat.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/data/gf_data_item.h"
#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/util/gf_item_util.h"

namespace gf {

namespace {

// Inferred role: compares the key of two items of one type, ties broken by item id; original name unknown.
template <typename T> bool unknown001(const MenuItemInfo &info, const MenuItemInfo &other, ItemType::Type type, T ItemProperty::*key, bool ascending) {
  ItemProperty property;
  ItemProperty otherProperty;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  GfItemUtil::getProperty(otherProperty, other.unknown04, 0);
  if (property.unknown08 == type) {
    if (otherProperty.unknown08 == type) {
      if (property.*key == otherProperty.*key) {
        return info.unknown04 < other.unknown04;
      }
      if (ascending) {
        return property.*key < otherProperty.*key;
      }
      return property.*key > otherProperty.*key;
    }
    return true;
  }
  return false;
}

// Inferred role: compares the enhance category of the equipped items of two empty orbs, ties broken by item id; original name unknown.
template <bool Ascending> bool unknown002(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemProperty property;
  ItemProperty otherProperty;
  GfItemUtil::getProperty(property, info.unknown04, 0);
  GfItemUtil::getProperty(otherProperty, other.unknown04, 0);
  if (property.unknown08 == ItemType::EMPTY_ORB) {
    if (otherProperty.unknown08 == ItemType::EMPTY_ORB) {
      GfItemUtil::getProperty(property, property.unknown56, 0);
      GfItemUtil::getProperty(otherProperty, otherProperty.unknown56, 0);
      if (property.unknown4c == otherProperty.unknown4c) {
        return info.unknown04 < other.unknown04;
      }
      if (Ascending) {
        return property.unknown4c < otherProperty.unknown4c;
      }
      return property.unknown4c > otherProperty.unknown4c;
    }
    return true;
  }
  return false;
}

} // namespace

GfMenuItemList::GfMenuItemList() {}

GfMenuItemList::~GfMenuItemList() { ; }

GfMenuItemList *GfMenuItemList::create() {
  // __LINE__ must be 55 as in the original source: it is the line argument of operator new.
#line 55
  GfMenuItemList *list = new (getAllocator(ALLOCATOR_DEFAULT), __FILE__, __LINE__, 8) GfMenuItemList();
  list->addRef();
  return list;
}

void GfMenuItemList::sort(u32 type, bool ascending) {
  if (getSize() == 0) {
    return;
  }
  std::function<bool(const MenuItemInfo &, const MenuItemInfo &)> compare;
  switch (type) {
  case SORT_TIME: {
    u32 *times = new (getAllocator(ALLOCATOR_DEFAULT), nullptr, 0, 8) u32[getSize()];
    for (u32 i = 0; i < getSize(); i++) {
      times[i] = GfItemUtil::getItemTime(getContents(i).unknown04, getContents(i).unknown0c);
      getContents(i).unknown0a = i;
    }
    if (ascending) {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.unknown0a];
        u32 otherTime = times[other.unknown0a];
        if (time == otherTime) {
          return info.unknown04 < other.unknown04;
        }
        return time < otherTime;
      });
    } else {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.unknown0a];
        u32 otherTime = times[other.unknown0a];
        if (time == otherTime) {
          return info.unknown04 < other.unknown04;
        }
        return time > otherTime;
      });
    }
    delete[] times;
    return;
  }
  case SORT_NAME:
    compare = ascending ? sortNameDescending : sortNameAscending;
    break;
  case SORT_RARITY:
    compare = ascending ? sortRareAscending : sortRareDescending;
    break;
  case SORT_SELL_PRICE:
    compare = ascending ? sortSellPriceAscending : sortSellPriceDescending;
    break;
  case SORT_FAVORITE_TIME:
    compare = ascending ? sortFavoriteTimeAscending : sortFavoriteTimeDescending;
    break;
  case SORT_TYPE:
    switch (GfItemUtil::getType(getContents(0).unknown04)) {
    case ItemType::EQUIP_ORB:
      compare = ascending ? sortTypeAsCoreEquipAscending : sortTypeAsCoreEquipDescending;
      break;
    case ItemType::COLLECTION_LIST:
      compare = ascending ? sortTypeCollectionAscending : sortTypeCollectionDescending;
      break;
    case ItemType::TRESURE:
      compare = ascending ? sortTypeTreasureAscending : sortTypeTreasureDescending;
      break;
    case ItemType::EMPTY_ORB:
      compare = ascending ? sortTypeAsCoreAscending : sortTypeAsCoreDescending;
      break;
    case ItemType::FAVORITE:
      compare = ascending ? sortTypeFavoriteAscending : sortTypeFavoriteDescending;
      break;
    case ItemType::BOOSTER:
      compare = ascending ? sortTypeBoosterAscending : sortTypeBoosterDescending;
      break;
    default:
      break;
    }
    break;
  case SORT_WPN_RANK:
    compare = ascending ? sortWpnRankAscending : sortWpnRankDescending;
    break;
  case SORT_GET_AREA:
    compare = ascending ? sortGetAreaAscending : sortGetAreaDescending;
    break;
  case SORT_ID:
    compare = ascending ? sortIdAscending : sortIdDescending;
    break;
  default:
    return;
  }
  UIListInfo<MenuItemInfo>::sort(compare);
}

bool GfMenuItemList::sortRareAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 rarity = getSortRarity(info);
  u32 otherRarity = getSortRarity(other);
  if (rarity == otherRarity) {
    return info.unknown04 < other.unknown04;
  }
  return rarity < otherRarity;
}

bool GfMenuItemList::sortRareDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 rarity = getSortRarity(info);
  u32 otherRarity = getSortRarity(other);
  if (rarity == otherRarity) {
    return info.unknown04 < other.unknown04;
  }
  return rarity > otherRarity;
}

bool GfMenuItemList::sortSellPriceAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemPrice price;
  ItemPrice otherPrice;
  price.clear();
  otherPrice.clear();
  GfItemUtil::getPrice(price, info.unknown04, 0);
  GfItemUtil::getPrice(otherPrice, other.unknown04, 0);
  if (price.unknown08 == otherPrice.unknown08) {
    return info.unknown04 < other.unknown04;
  }
  return price.unknown08 < otherPrice.unknown08;
}

bool GfMenuItemList::sortSellPriceDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  ItemPrice price;
  ItemPrice otherPrice;
  price.clear();
  otherPrice.clear();
  GfItemUtil::getPrice(price, info.unknown04, 0);
  GfItemUtil::getPrice(otherPrice, other.unknown04, 0);
  if (price.unknown08 == otherPrice.unknown08) {
    return info.unknown04 < other.unknown04;
  }
  return price.unknown08 > otherPrice.unknown08;
}

bool GfMenuItemList::sortGetAreaAscending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 area;
  u32 otherArea;
  if (info.unknown00 == ItemType::TRESURE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
    area = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    otherArea = Bdat::getVal(bdat, "Zone", other.unknown04).valueU16;
  } else {
    area = info.unknown04;
    otherArea = other.unknown04;
  }
  if (area == otherArea) {
    return info.unknown04 < other.unknown04;
  }
  return area < otherArea;
}

bool GfMenuItemList::sortGetAreaDescending(const MenuItemInfo &info, const MenuItemInfo &other) {
  u32 area;
  u32 otherArea;
  if (info.unknown00 == ItemType::TRESURE) {
    u8 *bdat = GfDataBdat::getFP(BDAT_ITM_TRESURE_LIST);
    area = Bdat::getVal(bdat, "Zone", info.unknown04).valueU16;
    otherArea = Bdat::getVal(bdat, "Zone", other.unknown04).valueU16;
  } else {
    area = info.unknown04;
    otherArea = other.unknown04;
  }
  if (area == otherArea) {
    return info.unknown04 < other.unknown04;
  }
  return area > otherArea;
}

bool GfMenuItemList::sortTypeBoosterAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::BOOSTER, &ItemProperty::unknown45, true); }

bool GfMenuItemList::sortTypeBoosterDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::BOOSTER, &ItemProperty::unknown45, false); }

bool GfMenuItemList::sortWpnRankAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::PC_WPN_CHIP, &ItemProperty::unknown64, true); }

bool GfMenuItemList::sortWpnRankDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::PC_WPN_CHIP, &ItemProperty::unknown64, false); }

bool GfMenuItemList::sortTypeAsCoreAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown002<true>(info, other); }

bool GfMenuItemList::sortTypeAsCoreDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown002<false>(info, other); }

bool GfMenuItemList::sortTypeCollectionAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::COLLECTION_LIST, &ItemProperty::unknown4d, true); }

bool GfMenuItemList::sortTypeCollectionDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::COLLECTION_LIST, &ItemProperty::unknown4d, false); }

bool GfMenuItemList::sortTypeFavoriteAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::FAVORITE, &ItemProperty::unknown4e, true); }

bool GfMenuItemList::sortTypeFavoriteDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::FAVORITE, &ItemProperty::unknown4e, false); }

bool GfMenuItemList::sortTypeTreasureAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::TRESURE, &ItemProperty::unknown5d, true); }

bool GfMenuItemList::sortTypeTreasureDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::TRESURE, &ItemProperty::unknown5d, false); }

bool GfMenuItemList::sortFavoriteTimeAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::FAVORITE, &ItemProperty::unknown52, true); }

bool GfMenuItemList::sortFavoriteTimeDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return unknown001(info, other, ItemType::FAVORITE, &ItemProperty::unknown52, false); }

bool GfMenuItemList::sortIdAscending(const MenuItemInfo &info, const MenuItemInfo &other) { return info.unknown04 < other.unknown04; }

bool GfMenuItemList::sortIdDescending(const MenuItemInfo &info, const MenuItemInfo &other) { return info.unknown04 > other.unknown04; }

bool GfMenuItemList::isValidItem(const MenuItemInfo &info) { return info.unknown04 != 0 && info.unknown08 > 0; }

u32 GfMenuItemList::getSortRarity(const MenuItemInfo &info) {
  if (info.unknown00 == ItemType::PRECIOUS || info.unknown00 == ItemType::INFO || info.unknown00 == ItemType::EVENT) {
    return 0;
  }
  return GfDataItem::getRarity(info.unknown04);
}

} // namespace gf
