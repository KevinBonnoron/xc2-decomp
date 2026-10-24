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
  u32 unknown00_0 : 13; // Inferred role: index; original member name unknown.
  u32 m_type : 6;
  u32 unknown02_3 : 10; // Inferred role: count; original member name unknown.
  u32 _00_29 : 1;
  u32 unknown03_6 : 1; // Inferred role: is equip; original member name unknown.
  u32 _00_31 : 1;
  u32 unknown04;        // Inferred role: time; original member name unknown.
  u32 unknown08_0 : 26; // Inferred role: serial; original member name unknown.
  u32 _08_26 : 6;
};

static_assert(sizeof(SDataItemInfo) == 0x0c, "");

struct ItemBox {
  SDataItemInfo unknown00[200];         // Inferred role: pc wpn chips; original member name unknown.
  SDataItemInfo unknown960[900];        // Inferred role: pc equips; original member name unknown.
  SDataItemInfo unknown3390[500];       // Inferred role: equip orbs; original member name unknown.
  SDataItemInfo unknown4b00[200];       // Inferred role: salvages; original member name unknown.
  SDataItemInfo unknown5460[500];       // Inferred role: preciouses; original member name unknown.
  SDataItemInfo unknown6bd0[200];       // Inferred role: infos; original member name unknown.
  SDataItemInfo unknown7530[100];       // Inferred role: events; original member name unknown.
  SDataItemInfo unknown79e0[500];       // Inferred role: collection lists; original member name unknown.
  SDataItemInfo unknown9150[200];       // Inferred role: tresures; original member name unknown.
  SDataItemInfo unknown9ab0[500];       // Inferred role: empty orbs; original member name unknown.
  SDataItemInfo unknownb220[500];       // Inferred role: favorites; original member name unknown.
  SDataItemInfo unknownc990[200];       // Inferred role: crystal lists; original member name unknown.
  SDataItemInfo unknownd2f0[200];       // Inferred role: boosters; original member name unknown.
  SDataItemInfo unknowndc50[200];       // Inferred role: hana roles; original member name unknown.
  SDataItemInfo unknowne5b0[200];       // Inferred role: hana atrs; original member name unknown.
  SDataItemInfo unknownef10[200];       // Inferred role: hana arts enhs; original member name unknown.
  SDataItemInfo unknownf870[200];       // Inferred role: hana n arts sets; original member name unknown.
  SDataItemInfo unknown101d0[700];      // Inferred role: hana assists; original member name unknown.
  u32 unknown122a0[ITEM_BOX_INDEX_NUM]; // Inferred role: serials; original member name unknown.
};

static_assert(offsetof(ItemBox, unknown960) == 0x960, "");
static_assert(offsetof(ItemBox, unknown101d0) == 0x101d0, "");
static_assert(offsetof(ItemBox, unknown122a0) == 0x122a0, "");
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
  static bool isYuohCookItem(u32 item);
  static bool isMusubiCookItem(u32 item);
  static bool isMayItem(u32 item);
  static bool isTukiItem(u32 item);
};

} // namespace gf
