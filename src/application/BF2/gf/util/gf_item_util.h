#pragma once
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "mm_mtl/bitflag.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct ItemPrice {
  void clear() {
    price = 0;
    buyPrice = 0;
    sellPrice = 0;
    buyDevelop = 0;
    sellDevelop = 0;
  }

  u32 price;
  u32 buyPrice;
  u32 sellPrice;
  u32 buyDevelop;
  u32 sellDevelop;
};

static_assert(sizeof(ItemPrice) == 0x14, "");

struct ItemProperty {
  enum {
    FLAG_VALID = 0,
    FLAG_NO_SELL = 2,
    FLAG_NO_MULTIPLE = 3,
    FLAG_QUEST = 4,
    FLAG_EQUIP_DRIVER = 16,
  };

  void clear() {
    static const char *szNull = "";
    flags.clear();
    id = 0;
    index = 0;
    type = ItemType::NONE;
    count = 0;
    _0e = 0;
    enableStock = 0;
    zone = 0;
    debugName = szNull;
    bdat = nullptr;
    nameTextId = 0;
    captionTextId = 0;
    price.clear();
    rarity = 0;
    boosterCategory = 0;
    boosterIdea = 0;
    _48 = 0;
    enhance = 0;
    enhanceCategory = 0;
    collectionCategory = 0;
    favoriteCategory = 0;
    favoriteType = 0;
    favoriteTime = 0;
    recipe = 0;
    equipItem = 0;
    preciousCategory = 0;
    preciousType = 0;
    _5c = 0;
    tresureCategory = 0;
    tresureGraphic = 0;
    tresureFlag = 0;
    _62 = 0;
    chipRank = 0;
    icon = 0;
    needEther = 0;
    dustEther = 0;
    condition = 0;
    nArts = 0;
    hanaAttribute = 0;
    hanaRole = 0;
    pArmor = 0;
    eArmor = 0;
    hpMaxRev = 0;
    strengthRev = 0;
    powEtherRev = 0;
    dexRev = 0;
    agilityRev = 0;
    luckRev = 0;
    _7e = 0;
  }

  mm::mtl::BitFlag<32> flags;
  u16 id;
  u16 index;
  ItemType::Type type;
  u16 count;
  u16 _0e;
  u16 enableStock;
  u16 zone;
  u32 time;
  const char *debugName;
  u8 *bdat;
  u32 nameTextId;
  u32 captionTextId;
  ItemPrice price;
  u8 rarity;
  u8 boosterCategory;
  s8 boosterIdea;
  u8 _47[0x48 - 0x47];
  u16 _48;
  u16 enhance;
  u8 enhanceCategory;
  u8 collectionCategory;
  u8 favoriteCategory;
  u8 _4f[0x50 - 0x4f];
  u16 favoriteType;
  u16 favoriteTime;
  u16 recipe;
  u16 equipItem;
  u16 preciousCategory;
  u16 preciousType;
  u8 _5c;
  u8 tresureCategory;
  u16 tresureGraphic;
  u16 tresureFlag;
  u16 _62;
  u8 chipRank;
  u8 icon;
  u8 _66[0x68 - 0x66];
  u32 needEther;
  u32 dustEther;
  u16 condition;
  u16 nArts;
  u8 hanaAttribute;
  u8 hanaRole;
  u8 pArmor;
  u8 eArmor;
  u8 hpMaxRev;
  u8 strengthRev;
  u8 powEtherRev;
  u8 dexRev;
  u8 agilityRev;
  u8 luckRev;
  u16 _7e;
};

static_assert(offsetof(ItemProperty, id) == 0x04, "");
static_assert(offsetof(ItemProperty, type) == 0x08, "");
static_assert(offsetof(ItemProperty, enableStock) == 0x10, "");
static_assert(offsetof(ItemProperty, time) == 0x14, "");
static_assert(offsetof(ItemProperty, debugName) == 0x18, "");
static_assert(offsetof(ItemProperty, price) == 0x30, "");
static_assert(offsetof(ItemProperty, rarity) == 0x44, "");
static_assert(offsetof(ItemProperty, enhance) == 0x4a, "");
static_assert(offsetof(ItemProperty, favoriteType) == 0x50, "");
static_assert(offsetof(ItemProperty, tresureCategory) == 0x5d, "");
static_assert(offsetof(ItemProperty, chipRank) == 0x64, "");
static_assert(offsetof(ItemProperty, needEther) == 0x68, "");
static_assert(offsetof(ItemProperty, hanaAttribute) == 0x74, "");
static_assert(offsetof(ItemProperty, luckRev) == 0x7d, "");
static_assert(sizeof(ItemProperty) == 0x80, "");

struct GfItem {
  GfItem() : id(0), count(0), character(0), handle(0) {}

  u16 id;
  u16 count;
  u16 character;
  GfItemHandle handle;
};

static_assert(offsetof(GfItem, character) == 0x04, "");
static_assert(offsetof(GfItem, handle) == 0x08, "");
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
