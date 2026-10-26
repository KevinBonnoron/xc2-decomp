#pragma once
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/bitflag.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct ItemPrice {
  void clear() {
    unknown00 = 0;
    unknown04 = 0;
    unknown08 = 0;
    unknown0c = 0;
    unknown10 = 0;
  }

  u32 unknown00; // Inferred role: price; original member name unknown.
  u32 unknown04; // Inferred role: buy price; original member name unknown.
  u32 unknown08; // Inferred role: sell price; original member name unknown.
  u32 unknown0c; // Inferred role: buy develop; original member name unknown.
  u32 unknown10; // Inferred role: sell develop; original member name unknown.
};

static_assert(sizeof(ItemPrice) == 0x14, "");

struct ItemProperty {
  ItemProperty() : unknown30() {}

  enum {
    FLAG_VALID = 0,
    FLAG_NO_SELL = 2,
    FLAG_NO_MULTIPLE = 3,
    FLAG_QUEST = 4,
    FLAG_EQUIP_DRIVER = 16,
  };

  void clear() {
    static const char *szNull = "";
    unknown00.clear();
    unknown04 = 0;
    unknown06 = 0;
    unknown08 = ItemType::NONE;
    unknown0c = 0;
    _0e = 0;
    unknown10 = 0;
    unknown12 = 0;
    unknown18 = szNull;
    unknown20 = nullptr;
    unknown28 = 0;
    unknown2c = 0;
    unknown30.clear();
    unknown44 = 0;
    unknown45 = 0;
    unknown46 = 0;
    _48 = 0;
    unknown4a = 0;
    unknown4c = 0;
    unknown4d = 0;
    unknown4e = 0;
    unknown50 = 0;
    unknown52 = 0;
    unknown54 = 0;
    unknown56 = 0;
    unknown58 = 0;
    unknown5a = 0;
    _5c = 0;
    unknown5d = 0;
    unknown5e = 0;
    unknown60 = 0;
    _62 = 0;
    unknown64 = 0;
    unknown65 = 0;
    unknown68 = 0;
    unknown6c = 0;
    unknown70 = 0;
    unknown72 = 0;
    unknown74 = 0;
    unknown75 = 0;
    unknown76 = 0;
    unknown77 = 0;
    unknown78 = 0;
    unknown79 = 0;
    unknown7a = 0;
    unknown7b = 0;
    unknown7c = 0;
    unknown7d = 0;
    _7e = 0;
  }

  mm::mtl::BitFlag<32> unknown00; // Inferred role: flags; original member name unknown.
  u16 unknown04;                  // Inferred role: id; original member name unknown.
  u16 unknown06;                  // Inferred role: index; original member name unknown.
  ItemType::Type unknown08;       // Inferred role: type; original member name unknown.
  u16 unknown0c;                  // Inferred role: count; original member name unknown.
  u16 _0e;
  u16 unknown10;         // Inferred role: enable stock; original member name unknown.
  u16 unknown12;         // Inferred role: zone; original member name unknown.
  u32 unknown14;         // Inferred role: time; original member name unknown.
  const char *unknown18; // Inferred role: debug name; original member name unknown.
  u8 *unknown20;         // Inferred role: bdat; original member name unknown.
  u32 unknown28;         // Inferred role: name text id; original member name unknown.
  u32 unknown2c;         // Inferred role: caption text id; original member name unknown.
  ItemPrice unknown30;   // Inferred role: price; original member name unknown.
  u8 unknown44;          // Inferred role: rarity; original member name unknown.
  u8 unknown45;          // Inferred role: booster category; original member name unknown.
  s8 unknown46;          // Inferred role: booster idea; original member name unknown.
  u8 _47[0x48 - 0x47];
  u16 _48;
  u16 unknown4a; // Inferred role: enhance; original member name unknown.
  u8 unknown4c;  // Inferred role: enhance category; original member name unknown.
  u8 unknown4d;  // Inferred role: collection category; original member name unknown.
  u8 unknown4e;  // Inferred role: favorite category; original member name unknown.
  u8 _4f[0x50 - 0x4f];
  u16 unknown50; // Inferred role: favorite type; original member name unknown.
  u16 unknown52; // Inferred role: favorite time; original member name unknown.
  u16 unknown54; // Inferred role: recipe; original member name unknown.
  u16 unknown56; // Inferred role: equip item; original member name unknown.
  u16 unknown58; // Inferred role: precious category; original member name unknown.
  u16 unknown5a; // Inferred role: precious type; original member name unknown.
  u8 _5c;
  u8 unknown5d;  // Inferred role: tresure category; original member name unknown.
  u16 unknown5e; // Inferred role: tresure graphic; original member name unknown.
  u16 unknown60; // Inferred role: tresure flag; original member name unknown.
  u16 _62;
  u8 unknown64; // Inferred role: chip rank; original member name unknown.
  u8 unknown65; // Inferred role: icon; original member name unknown.
  u8 _66[0x68 - 0x66];
  u32 unknown68; // Inferred role: need ether; original member name unknown.
  u32 unknown6c; // Inferred role: dust ether; original member name unknown.
  u16 unknown70; // Inferred role: condition; original member name unknown.
  u16 unknown72; // Inferred role: n arts; original member name unknown.
  u8 unknown74;  // Inferred role: hana attribute; original member name unknown.
  u8 unknown75;  // Inferred role: hana role; original member name unknown.
  u8 unknown76;  // Inferred role: p armor; original member name unknown.
  u8 unknown77;  // Inferred role: e armor; original member name unknown.
  u8 unknown78;  // Inferred role: hp max rev; original member name unknown.
  u8 unknown79;  // Inferred role: strength rev; original member name unknown.
  u8 unknown7a;  // Inferred role: pow ether rev; original member name unknown.
  u8 unknown7b;  // Inferred role: dex rev; original member name unknown.
  u8 unknown7c;  // Inferred role: agility rev; original member name unknown.
  u8 unknown7d;  // Inferred role: luck rev; original member name unknown.
  u16 _7e;
};

static_assert(offsetof(ItemProperty, unknown04) == 0x04, "");
static_assert(offsetof(ItemProperty, unknown08) == 0x08, "");
static_assert(offsetof(ItemProperty, unknown10) == 0x10, "");
static_assert(offsetof(ItemProperty, unknown14) == 0x14, "");
static_assert(offsetof(ItemProperty, unknown18) == 0x18, "");
static_assert(offsetof(ItemProperty, unknown30) == 0x30, "");
static_assert(offsetof(ItemProperty, unknown44) == 0x44, "");
static_assert(offsetof(ItemProperty, unknown4a) == 0x4a, "");
static_assert(offsetof(ItemProperty, unknown50) == 0x50, "");
static_assert(offsetof(ItemProperty, unknown5d) == 0x5d, "");
static_assert(offsetof(ItemProperty, unknown64) == 0x64, "");
static_assert(offsetof(ItemProperty, unknown68) == 0x68, "");
static_assert(offsetof(ItemProperty, unknown74) == 0x74, "");
static_assert(offsetof(ItemProperty, unknown7d) == 0x7d, "");
static_assert(sizeof(ItemProperty) == 0x80, "");

struct GfItem {
  GfItem() : unknown00(0), unknown02(0), unknown04(0), unknown08(0) {}

  u16 unknown00;          // Inferred role: id; original member name unknown.
  u16 unknown02;          // Inferred role: count; original member name unknown.
  u16 unknown04;          // Inferred role: character; original member name unknown.
  GfItemHandle unknown08; // Inferred role: handle; original member name unknown.
};

static_assert(offsetof(GfItem, unknown04) == 0x04, "");
static_assert(offsetof(GfItem, unknown08) == 0x08, "");
static_assert(sizeof(GfItem) == 0x0c, "");

class GfItemUtil {
public:
  static u32 getCountByType(ItemType::Type type);
  static u32 getItemBoxCount(u32 item);
  static u32 getCountByItemCategory(u32 category);
  static bool addItemBox(u32 item, int count);
  static bool addItemBoxWithSilent(u32 item, int count);
  static bool addItemBoxForDebug(u32 item, int count);
  static u32 getItemBoxCountWithoutEquip(u32 item);
  static bool isEnableAddItemBox(u32 item, int count);
  static ItemType::Type getType(u32 item);
  static u32 getEnableStock(u32 item);
  static void getPrice(ItemPrice &price, u32 item, u32 shop);
  static GfItem getInfo(u32 item);
  static bool isPrecious(u32 item);
  static void getPropertyChip(ItemProperty &property);
  static void getPropertyAcce(ItemProperty &property);
  static void getPropertyOrb(ItemProperty &property);
  static void getPropertyOrbEquip(ItemProperty &property);
  static void getPropertySalvage(ItemProperty &property);
  static void getPropertyPrecious(ItemProperty &property);
  static void getPropertyInfo(ItemProperty &property);
  static void getPropertyEvent(ItemProperty &property);
  static void getPropertyCollect(ItemProperty &property);
  static void getPropertyTresure(ItemProperty &property);
  static void getPropertyFavorite(ItemProperty &property);
  static void getPropertyCrystal(ItemProperty &property);
  static void getPropertyBooster(ItemProperty &property);
  static void getPropertyHanaArts(ItemProperty &property);
  static void getPropertyHanaAssist(ItemProperty &property);
  static void getPropertyHanaAttribute(ItemProperty &property);
  static void getPropertyHanaNArts(ItemProperty &property);
  static void getPropertyHanaRole(ItemProperty &property);
  static bool getProperty(ItemProperty &property, u32 item, u32 shop);
  static u32 getItemTime(u32 item);
  static u32 getItemTime(u32 item, GfItemHandle handle);
  static bool isFavoriteFood(u32 item);
  static ItemType::Type getItemCategory(u32 item);
  static u32 getCrystalNum();
  static bool isValidCrystal(u32 item);
  static void setEquipFlag(u32 item, GfItemHandle handle, bool isEquip);
  static GfItemHandle getNoEquipItemHandle(u32 item);
  static u32 getEquipChar(GfItemHandle handle);
  static void setupNewGameParam();
};

} // namespace gf
