#include "gf/data/gf_data_shop.h"
#include "gf/data/gf_bdat_shop.h"
#include "gf/data/gf_game_flag.h"

namespace gf {

enum {
  SHOP_TYPE_NORMAL = 0,
};

constexpr u32 DEFAULT_ITEM_COUNT = 10;
constexpr u32 ADD_ITEM_COUNT = 5;

static u32 getBuyItemBit(const GfBdatShop &bdatShop, u32 table, u32 item) {
  if (bdatShop.getShopNormalDefItem(table, 0) == item) {
    return 1 << 0;
  }

  if (bdatShop.getShopNormalDefItem(table, 1) == item) {
    return 1 << 1;
  }

  if (bdatShop.getShopNormalDefItem(table, 2) == item) {
    return 1 << 2;
  }

  if (bdatShop.getShopNormalDefItem(table, 3) == item) {
    return 1 << 3;
  }

  if (bdatShop.getShopNormalDefItem(table, 4) == item) {
    return 1 << 4;
  }

  if (bdatShop.getShopNormalDefItem(table, 5) == item) {
    return 1 << 5;
  }

  if (bdatShop.getShopNormalDefItem(table, 6) == item) {
    return 1 << 6;
  }

  if (bdatShop.getShopNormalDefItem(table, 7) == item) {
    return 1 << 7;
  }

  if (bdatShop.getShopNormalDefItem(table, 8) == item) {
    return 1 << 8;
  }

  if (bdatShop.getShopNormalDefItem(table, 9) == item) {
    return 1 << 9;
  }

  if (bdatShop.getShopNormalAddItem(table, 0) == item && bdatShop.getShopNormalPrivilegeCheck(table, 0) == 0) {
    return 1 << 10;
  }

  if (bdatShop.getShopNormalAddItem(table, 1) == item && bdatShop.getShopNormalPrivilegeCheck(table, 1) == 0) {
    return 1 << 11;
  }

  if (bdatShop.getShopNormalAddItem(table, 2) == item && bdatShop.getShopNormalPrivilegeCheck(table, 2) == 0) {
    return 1 << 12;
  }

  if (bdatShop.getShopNormalAddItem(table, 3) == item && bdatShop.getShopNormalPrivilegeCheck(table, 3) == 0) {
    return 1 << 13;
  }

  if (bdatShop.getShopNormalAddItem(table, 4) == item && bdatShop.getShopNormalPrivilegeCheck(table, 4) == 0) {
    return 1 << 14;
  }

  return 0;
}

u32 GfDataShop::getItemBit(u32 shop) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  if (bdatShop->getShopListShopType(shop) != SHOP_TYPE_NORMAL) {
    return 0;
  }

  u32 table = bdatShop->getShopListTableID(shop);
  u32 itemBit = 0;
  for (u32 index = 0; index < DEFAULT_ITEM_COUNT; index++) {
    if (bdatShop->getShopNormalDefItem(table, index) != 0) {
      itemBit |= 1 << index;
    }
  }

  for (u32 index = 0; index < ADD_ITEM_COUNT; index++) {
    if (bdatShop->getShopNormalAddItem(table, index) != 0) {
      itemBit |= (bdatShop->getShopNormalPrivilegeCheck(table, index) == 0) << (DEFAULT_ITEM_COUNT + index);
    }
  }

  return itemBit;
}

u32 GfDataShop::getPrivilegeItem(u32 shop) {
  u32 itemBit = getItemBit(shop);
  if (itemBit != 0) {
    GfBdatShop *bdatShop = GfBdatShop::get();
    u32 table = bdatShop->getShopListTableID(shop);
    if (itemBit == GfGameFlag::getLocal(32, GfBdatShop::get()->getShopNormalPrivilegeFlag(table))) {
      return bdatShop->getShopNormalPrivilegeItem(table);
    }
  }

  return 0;
}

void GfDataShop::setBuyItem(u32 shop, u32 item) {
  if (shop == 0) {
    return;
  }

  GfBdatShop *bdatShop = GfBdatShop::get();
  if (bdatShop->getShopListShopType(shop) != SHOP_TYPE_NORMAL) {
    return;
  }

  u32 table = bdatShop->getShopListTableID(shop);
  u32 boughtBit = GfGameFlag::getLocal(32, GfBdatShop::get()->getShopNormalPrivilegeFlag(table));
  u32 itemBit = getBuyItemBit(*bdatShop, table, item);
  if (itemBit == 0) {
    return;
  }

  boughtBit |= itemBit;
  GfGameFlag::setLocal(32, GfBdatShop::get()->getShopNormalPrivilegeFlag(table), boughtBit);
}

} // namespace gf
