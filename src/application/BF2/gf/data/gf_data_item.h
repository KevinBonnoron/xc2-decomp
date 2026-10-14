#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct ItemType {
  enum Type {
    NONE,
    PC_WPN_CHIP,
    PC_EQUIP,
    EQUIP_ORB,
    PC_WPN,
    SALVAGE,
    PRECIOUS,
    COLLECTION_LIST,
    TRESURE,
    EMPTY_ORB,
    FAVORITE,
    CRYSTAL_LIST,
    BOOSTER,
    HEAL_POT,
    INFO,
    EVENT,
    HANA_ROLE,
    HANA_ATR,
    HANA_ARTS_ENH,
    HANA_N_ARTS_SET,
    HANA_ASSIST,
  };
};

enum {
  FAVORITE_CATEGORY_FOOD_FIRST = 12,
  FAVORITE_CATEGORY_FOOD_LAST = 17,
};

enum ITEM_BOX_INDEX {
  ITEM_BOX_INDEX_NONE,
  ITEM_BOX_INDEX_PC_WPN_CHIP,
  ITEM_BOX_INDEX_PC_EQUIP,
  ITEM_BOX_INDEX_EQUIP_ORB,
  ITEM_BOX_INDEX_SALVAGE,
  ITEM_BOX_INDEX_PRECIOUS,
  ITEM_BOX_INDEX_INFO,
  ITEM_BOX_INDEX_EVENT,
  ITEM_BOX_INDEX_COLLECTION_LIST,
  ITEM_BOX_INDEX_TRESURE,
  ITEM_BOX_INDEX_EMPTY_ORB,
  ITEM_BOX_INDEX_FAVORITE,
  ITEM_BOX_INDEX_CRYSTAL_LIST,
  ITEM_BOX_INDEX_BOOSTER,
  ITEM_BOX_INDEX_HANA_ROLE,
  ITEM_BOX_INDEX_HANA_ATR,
  ITEM_BOX_INDEX_HANA_ARTS_ENH,
  ITEM_BOX_INDEX_HANA_N_ARTS_SET,
  ITEM_BOX_INDEX_HANA_ASSIST,
  ITEM_BOX_INDEX_NUM,
};

struct SDataItemInfo {
  u32 index : 13;
  u32 type : 6;
  u32 count : 10;
  u32 _00_29 : 1;
  u32 isEquip : 1;
  u32 _00_31 : 1;
  u32 time;
  u32 serial : 26;
  u32 _08_26 : 6;
};

static_assert(sizeof(SDataItemInfo) == 0x0c, "");

struct ItemBox {
  SDataItemInfo pcWpnChips[200];
  SDataItemInfo pcEquips[900];
  SDataItemInfo equipOrbs[500];
  SDataItemInfo salvages[200];
  SDataItemInfo preciouses[500];
  SDataItemInfo infos[200];
  SDataItemInfo events[100];
  SDataItemInfo collectionLists[500];
  SDataItemInfo tresures[200];
  SDataItemInfo emptyOrbs[500];
  SDataItemInfo favorites[500];
  SDataItemInfo crystalLists[200];
  SDataItemInfo boosters[200];
  SDataItemInfo hanaRoles[200];
  SDataItemInfo hanaAtrs[200];
  SDataItemInfo hanaArtsEnhs[200];
  SDataItemInfo hanaNArtsSets[200];
  SDataItemInfo hanaAssists[700];
  u32 serials[ITEM_BOX_INDEX_NUM];
};

static_assert(offsetof(ItemBox, pcEquips) == 0x960, "");
static_assert(offsetof(ItemBox, hanaAssists) == 0x101d0, "");
static_assert(offsetof(ItemBox, serials) == 0x122a0, "");
static_assert(sizeof(ItemBox) == 0x122ec, "");

class GfDataItem {
public:
  static bool getName(u8 *&bdat, u32 &textId, u32 item);
  static ItemType::Type getItemType(u32 item);
  static bool getCaption(u8 *&bdat, u32 &textId, u32 item);
  static f32 getFavoriteItemTime(u32 item);
  static u32 getFavoriteItemType(u32 item);
  static ItemBox *getItemBox();
  static bool getItemType(ItemType::Type &type, u32 &index, u32 item);
  static bool isEnableSell(u32 item);
  static const char *getName(u32 item);
  static const char *getCaption(u32 item);
  static u32 getItemStartID(ItemType::Type type);
  static bool getItemBdatCount(u32 &start, u32 &end, ItemType::Type type);
  static u32 getItemBdatCount(ItemType::Type type);
  static u32 getPrice(u32 item);
  static u32 getRarity(u32 item);
  static u32 getCategory(u32 item);
  static ItemType::Type getTypeByItemCategory(u32 category);
  static bool isNoMultiple(u32 item);
  static void setNoMultiple(u32 item, bool noMultiple);
  static bool isFavoriteCategoryFood(u32 category);
  static bool isHomuraCookItem(u32 item);
  static bool isMusubiCookItem(u32 item);
  static bool isMayItem(u32 item);
  static bool isTukiItem(u32 item);
};

} // namespace gf
