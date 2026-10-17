#include "gf/menu/list/gf_menu_item_list.h"

#include <functional>

#include "gf/gf_allocator.h"
#include "gf/menu/list/gf_menu_sort_type.h"
#include "gf/util/gf_item_util.h"

namespace gf {

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
      times[i] = GfItemUtil::getItemTime(getContents(i).item, getContents(i).handle);
      getContents(i).index = i;
    }
    if (ascending) {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.index];
        u32 otherTime = times[other.index];
        if (time == otherTime) {
          return info.item < other.item;
        }
        return time < otherTime;
      });
    } else {
      UIListInfo<MenuItemInfo>::sort([times](const MenuItemInfo &info, const MenuItemInfo &other) {
        u32 time = times[info.index];
        u32 otherTime = times[other.index];
        if (time == otherTime) {
          return info.item < other.item;
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
    switch (GfItemUtil::getType(getContents(0).item)) {
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

} // namespace gf
