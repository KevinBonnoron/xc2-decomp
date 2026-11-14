#pragma once
#include <stddef.h>

#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "types.h"
#include "ui/list/ui_list_info.h"

namespace gf {

struct MenuItemInfo {
  MenuItemInfo() : unknown00(ItemType::ITEM_TYPE_UNKNOWN_0), unknown04(0), unknown08(0), unknown0c(0) {}

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
  struct FiltertInfo {
    u32 unknown00; // Inferred role: filter flags (rarity, rarity more, collection type, favorite type); original member name unknown.
    u8 unknown04;  // Inferred role: rarity; original member name unknown.
    u8 unknown05;  // Inferred role: collection category; original member name unknown.
    u8 unknown06;  // Inferred role: favorite category; original member name unknown.
  };

  struct HanaPartsSetup {
    SetupParam unknown00;     // Inferred role: param; original member name unknown.
    ItemType::Type unknown14; // Inferred role: item type of the parts; original member name unknown.
  };

  struct ItemBoxSetup {
    ItemBoxSetup() : unknown14(ItemType::ITEM_TYPE_UNKNOWN_0), unknown18(nullptr), unknown20(0), unknown28(true), unknown29(true), unknown2a(false), unknown2b(false) {}

    SetupParam unknown00;     // Inferred role: param; original member name unknown.
    ItemType::Type unknown14; // Inferred role: item type of the item box; original member name unknown.
    FiltertInfo *unknown18;   // Inferred role: filter; original member name unknown.
    u64 unknown20;            // Role and original member name unknown.
    bool unknown28;           // Role and original member name unknown.
    bool unknown29;           // Inferred role: keep items whose count is zero; original member name unknown.
    bool unknown2a;           // Inferred role: skip items that cannot be sold; original member name unknown.
    bool unknown2b;           // Inferred role: skip items equipped by a character; original member name unknown.
  };

  struct ItemShopSetup {
    SetupParam unknown00; // Inferred role: param; original member name unknown.
    u32 unknown14;        // Inferred role: shop; original member name unknown.
  };

  struct ItemShopExcSetup {
    ItemShopExcSetup() : unknown14(0) {}

    SetupParam unknown00; // Inferred role: param; original member name unknown.
    u32 unknown14;        // Inferred role: exchange task; original member name unknown.
  };

  struct QuestRewardSetup {
    // Evidence: GfMenuObjQuestReward::RewardListener::reciveEvent clears unknown14 of its two setup locals (str wzr, [sp, #0x14] at 0x71004c6cf8 and 0x71004c6e80).
    QuestRewardSetup() : unknown14(0) {}

    SetupParam unknown00; // Inferred role: param; original member name unknown.
    u32 unknown14;        // Inferred role: reward set; original member name unknown.
  };

  struct MissionRewardSetup {
    // Evidence: GfMenuObjQuestReward::RewardListener::reciveEvent clears unknown14 of its two setup locals (str wzr, [sp, #0x14] at 0x71004c6cf8 and 0x71004c6e80).
    MissionRewardSetup() : unknown14(0) {}

    SetupParam unknown00; // Inferred role: param; original member name unknown.
    u32 unknown14;        // Inferred role: mission; original member name unknown.
  };

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
  static bool isValidItem(const MenuItemInfo &info);
  static u32 getSortRarity(const MenuItemInfo &info);
  void updateCount();
  int findItem(ItemType::Type type, u32 item);
  void addItem(u32 index, u32 count, bool isAddItemBox);
  void decItem(const MenuItemInfo &info, bool isAddItemBox);
  void decItem(u32 index, u32 count, bool isAddItemBox);
  void filterRarity(const FiltertInfo &filter);
  void filterRarityMore(const FiltertInfo &filter);
  void filterCollectionType(const FiltertInfo &filter);
  void filterFavoriteType(const FiltertInfo &filter);
  void addItem(const MenuItemInfo &info, bool isAddItemBox);
  void setupFromHanaParts(const HanaPartsSetup &setup);
  void setupFromBox(const ItemBoxSetup &setup);
  void addListFromBox(const ItemBoxSetup &setup);
  void setupFromShop(const ItemShopSetup &setup);
  void setupFromShopExcTask(const ItemShopExcSetup &setup);
  void setupFromQuestReward(const QuestRewardSetup &setup);
  void setupFromMissionReward(const MissionRewardSetup &setup);
};

static_assert(offsetof(GfMenuItemList::HanaPartsSetup, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown14) == 0x14, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown18) == 0x18, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown20) == 0x20, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown28) == 0x28, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown29) == 0x29, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown2a) == 0x2a, "");
static_assert(offsetof(GfMenuItemList::ItemBoxSetup, unknown2b) == 0x2b, "");
static_assert(sizeof(GfMenuItemList::ItemBoxSetup) == 0x30, "");
static_assert(offsetof(GfMenuItemList::ItemShopSetup, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuItemList::ItemShopSetup) == 0x18, "");
static_assert(offsetof(GfMenuItemList::ItemShopExcSetup, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuItemList::ItemShopExcSetup) == 0x18, "");
static_assert(offsetof(GfMenuItemList::QuestRewardSetup, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuItemList::QuestRewardSetup) == 0x18, "");
static_assert(offsetof(GfMenuItemList::MissionRewardSetup, unknown14) == 0x14, "");
static_assert(sizeof(GfMenuItemList::MissionRewardSetup) == 0x18, "");

static_assert(offsetof(GfMenuItemList::FiltertInfo, unknown04) == 0x4, "");
static_assert(offsetof(GfMenuItemList::FiltertInfo, unknown05) == 0x5, "");
static_assert(offsetof(GfMenuItemList::FiltertInfo, unknown06) == 0x6, "");

static_assert(sizeof(GfMenuItemList) == 0x78, "");

} // namespace gf
