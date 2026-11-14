#pragma once
#include "types.h"
#include <stddef.h>

namespace gf {

struct ItemType {
  enum Type {
    ITEM_TYPE_UNKNOWN_0,  // Inferred role: none; original name unknown.
    ITEM_TYPE_UNKNOWN_1,  // Inferred role: pc wpn chip; original name unknown.
    ITEM_TYPE_UNKNOWN_2,  // Inferred role: pc equip; original name unknown.
    ITEM_TYPE_UNKNOWN_3,  // Inferred role: equip orb; original name unknown.
    ITEM_TYPE_UNKNOWN_4,  // Inferred role: pc wpn; original name unknown.
    ITEM_TYPE_UNKNOWN_5,  // Inferred role: salvage; original name unknown.
    ITEM_TYPE_UNKNOWN_6,  // Inferred role: precious; original name unknown.
    ITEM_TYPE_UNKNOWN_7,  // Inferred role: collection list; original name unknown.
    ITEM_TYPE_UNKNOWN_8,  // Inferred role: tresure; original name unknown.
    ITEM_TYPE_UNKNOWN_9,  // Inferred role: empty orb; original name unknown.
    ITEM_TYPE_UNKNOWN_10, // Inferred role: favorite; original name unknown.
    ITEM_TYPE_UNKNOWN_11, // Inferred role: crystal list; original name unknown.
    ITEM_TYPE_UNKNOWN_12, // Inferred role: booster; original name unknown.
    ITEM_TYPE_UNKNOWN_13, // Inferred role: heal pot; original name unknown.
    ITEM_TYPE_UNKNOWN_14, // Inferred role: info; original name unknown.
    ITEM_TYPE_UNKNOWN_15, // Inferred role: event; original name unknown.
    ITEM_TYPE_UNKNOWN_16, // Inferred role: hana role; original name unknown.
    ITEM_TYPE_UNKNOWN_17, // Inferred role: hana atr; original name unknown.
    ITEM_TYPE_UNKNOWN_18, // Inferred role: hana arts enh; original name unknown.
    ITEM_TYPE_UNKNOWN_19, // Inferred role: hana n arts set; original name unknown.
    ITEM_TYPE_UNKNOWN_20, // Inferred role: hana assist; original name unknown.
  };
};

enum {
  FAVORITE_CATEGORY_FOOD_UNKNOWN_12 = 12, // Inferred role: favorite category food first; original name unknown.
  FAVORITE_CATEGORY_FOOD_UNKNOWN_17 = 17, // Inferred role: favorite category food last; original name unknown.
  FAVORITE_CATEGORY_UNKNOWN_20 = 20,      // Inferred role: favorite category of a blade without one, not a food; original name unknown.
};

enum ITEM_BOX_INDEX {
  ITEM_BOX_INDEX_UNKNOWN_0,  // Inferred role: item box index none; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_1,  // Inferred role: item box index pc wpn chip; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_2,  // Inferred role: item box index pc equip; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_3,  // Inferred role: item box index equip orb; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_4,  // Inferred role: item box index salvage; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_5,  // Inferred role: item box index precious; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_6,  // Inferred role: item box index info; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_7,  // Inferred role: item box index event; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_8,  // Inferred role: item box index collection list; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_9,  // Inferred role: item box index tresure; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_10, // Inferred role: item box index empty orb; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_11, // Inferred role: item box index favorite; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_12, // Inferred role: item box index crystal list; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_13, // Inferred role: item box index booster; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_14, // Inferred role: item box index hana role; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_15, // Inferred role: item box index hana atr; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_16, // Inferred role: item box index hana arts enh; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_17, // Inferred role: item box index hana n arts set; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_18, // Inferred role: item box index hana assist; original name unknown.
  ITEM_BOX_INDEX_UNKNOWN_19, // Inferred role: item box index num; original name unknown.
};

// Inferred role: save data item info; original type name unknown.
struct unknown117 {
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

static_assert(sizeof(unknown117) == 0x0c, "");

struct ItemBox {
  unknown117 unknown00[200];                   // Inferred role: pc wpn chips; original member name unknown.
  unknown117 unknown960[900];                  // Inferred role: pc equips; original member name unknown.
  unknown117 unknown3390[500];                 // Inferred role: equip orbs; original member name unknown.
  unknown117 unknown4b00[200];                 // Inferred role: salvages; original member name unknown.
  unknown117 unknown5460[500];                 // Inferred role: preciouses; original member name unknown.
  unknown117 unknown6bd0[200];                 // Inferred role: infos; original member name unknown.
  unknown117 unknown7530[100];                 // Inferred role: events; original member name unknown.
  unknown117 unknown79e0[500];                 // Inferred role: collection lists; original member name unknown.
  unknown117 unknown9150[200];                 // Inferred role: tresures; original member name unknown.
  unknown117 unknown9ab0[500];                 // Inferred role: empty orbs; original member name unknown.
  unknown117 unknownb220[500];                 // Inferred role: favorites; original member name unknown.
  unknown117 unknownc990[200];                 // Inferred role: crystal lists; original member name unknown.
  unknown117 unknownd2f0[200];                 // Inferred role: boosters; original member name unknown.
  unknown117 unknowndc50[200];                 // Inferred role: hana roles; original member name unknown.
  unknown117 unknowne5b0[200];                 // Inferred role: hana atrs; original member name unknown.
  unknown117 unknownef10[200];                 // Inferred role: hana arts enhs; original member name unknown.
  unknown117 unknownf870[200];                 // Inferred role: hana n arts sets; original member name unknown.
  unknown117 unknown101d0[700];                // Inferred role: hana assists; original member name unknown.
  u32 unknown122a0[ITEM_BOX_INDEX_UNKNOWN_19]; // Inferred role: serials; original member name unknown.
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
