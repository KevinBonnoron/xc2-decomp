#include "gf/util/gf_shop_util.h"
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_data_shop.h"
#include "gf/data/gf_data_util.h"
#include "gf/event/gf_event.h"
#include "gf/game/achiev/gf_achiev_manager.h"
#include "gf/game/gf_game_manager.h"
#include "gf/request/gf_req_scom.h"
#include "gf/util/gf_item_util.h"

namespace gf {

u32 GfShopUtil::execBuy(u32 item, u32 count, u32 shop) {
  if (!GfItemUtil::isEnableAddItemBox(item, count)) {
    return SHOP_RESULT_ITEM_FULL;
  }

  ItemPrice price;
  GfItemUtil::getPrice(price, item, shop);
  u32 money = price.buyPrice * count;
  if (GfDataUtil::getMoney() < money) {
    return SHOP_RESULT_NO_MONEY;
  }

  GfItemUtil::addItemBox(item, count);
  SCOM_ADD_MONEY::create(-money);
  SCOM_ADD_DEVELOP::create(GfGameManager::getMapZoneID(), price.buyDevelop * count);
  GfDataShop::setBuyItem(shop, item);
  GfAchievStats::checkBuyItemFromShop(item, count, shop, money);
  GfEvent::callExecBuy(item, count, shop);
  return SHOP_RESULT_OK;
}

u32 GfShopUtil::execSell(u32 item, u32 count, u32 shop) {
  if (!GfDataItem::isEnableSell(item)) {
    return SHOP_RESULT_NOT_SELLABLE;
  }
  if (GfItemUtil::getItemBoxCount(item) < count) {
    return SHOP_RESULT_NO_ITEM;
  }

  ItemPrice price;
  GfItemUtil::getPrice(price, item, shop);
  GfItemUtil::addItemBox(item, -static_cast<int>(count));
  u32 money = price.sellPrice * count;
  SCOM_ADD_MONEY::create(money);
  SCOM_ADD_DEVELOP::create(GfGameManager::getMapZoneID(), price.sellDevelop * count);
  GfAchievStats::checkSellItemFromShop(item, count, shop, money);
  return SHOP_RESULT_OK;
}

} // namespace gf
