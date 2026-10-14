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

struct SDataItemBox {
  u8 _00000[0x122ec - 0x00000];
};

static_assert(sizeof(SDataItemBox) == 0x122ec, "");

class GfDataItem {
public:
  static bool getName(u8 *&bdat, u32 &textId, u32 item);
  static ItemType::Type getItemType(u32 item);
  static bool getCaption(u8 *&bdat, u32 &textId, u32 item);
  static f32 getFavoriteItemTime(u32 item);
  static u32 getFavoriteItemType(u32 item);
  static SDataItemBox *getItemBox();
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
