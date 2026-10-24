#pragma once
#include <stddef.h>

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuItemInfo {
  MenuItemInfo() : unknown00(ItemType::NONE), unknown04(0), unknown08(0), unknown0c(0) {}

  ItemType::Type unknown00; // Inferred role: type; original member name unknown.
  u32 unknown04;            // Inferred role: item; original member name unknown.
  s16 unknown08;            // Inferred role: count; original member name unknown.
  u16 unknown0a;            // Inferred role: index; original member name unknown.
  GfItemHandle unknown0c;   // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(MenuItemInfo, unknown08) == 0x8, "");
static_assert(offsetof(MenuItemInfo, unknown0a) == 0xa, "");
static_assert(offsetof(MenuItemInfo, unknown0c) == 0xc, "");
static_assert(sizeof(MenuItemInfo) == 0x10, "");

class GfMenuItemList : public ui::UIListInfo<MenuItemInfo> {
public:
  GfMenuItemList();
  ~GfMenuItemList() override;
  static GfMenuItemList *create();
  void sort(u32 type, bool ascending);
  static bool sortNameDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortNameAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortRareAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortRareDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortSellPriceAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortSellPriceDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeBoosterAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeBoosterDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeCollectionAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeCollectionDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeFavoriteAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeFavoriteDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeAsCoreAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeAsCoreDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeAsCoreEquipAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeAsCoreEquipDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeTreasureAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortTypeTreasureDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortWpnRankAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortWpnRankDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortFavoriteTimeAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortFavoriteTimeDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortGetAreaAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortGetAreaDescending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortIdAscending(const MenuItemInfo &info, const MenuItemInfo &other);
  static bool sortIdDescending(const MenuItemInfo &info, const MenuItemInfo &other);
};

static_assert(sizeof(GfMenuItemList) == 0x78, "");

} // namespace gf
