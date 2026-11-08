#include "gf/game/gf_game_util_shop.h"

#include "gf/data/gf_bdat_quest.h"
#include "gf/data/gf_bdat_shop.h"
#include "gf/data/gf_data_develop.h"
#include "gf/game/gf_game_cond.h"
#include "gf/game/gf_game_manager.h"
#include "gf/request/gf_req_scom.h"

namespace gf {

enum {
  SHOP_TYPE_UNKNOWN_1 = 1, // Inferred role: change shop; original enumerator name unknown.
  SHOP_TYPE_UNKNOWN_2 = 2, // Inferred role: inn; original enumerator name unknown.
};

void GfGameUtilShop::execPayInn(u32 shop, u32 money, bool isDouble) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  u32 price = money;
  if (bdatShop->getShopListShopType(shop) == SHOP_TYPE_UNKNOWN_2) {
    price = bdatShop->getShopInnPrice(bdatShop->getShopListTableID(shop)) << isDouble;
  }
  SCOM_ADD_MONEY::create(-money);
  u32 zone = GfGameManager::getMapZoneID();
  f32 rate = static_cast<f32>(QuestListAcc::get()->getFLD_DevelopmentLevelValue(1)) / 10000.0f;
  SCOM_ADD_DEVELOP::create(zone, static_cast<u32>(static_cast<f32>(price) * rate));
}

u32 GfGameUtilShop::getNeedMoneyForInn(u32 shop) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  if (bdatShop->getShopListShopType(shop) != SHOP_TYPE_UNKNOWN_2) {
    return 0;
  }
  u32 price = bdatShop->getShopInnPrice(bdatShop->getShopListTableID(shop));
  int level = GfDataDevelop::getLevel(GfGameManager::getMapZoneID());
  if (level != 0) {
    price -= static_cast<u32>(static_cast<f32>(price) * static_cast<f32>(bdatShop->getShopListDiscount(shop, level - 1)) * 0.01f);
  }
  return price == 0 ? 1 : price;
}

bool GfGameUtilShop::getChangeTask(ShopTaskInfo &info, u32 shop) {
  GfBdatShop *bdatShop = GfBdatShop::get();
  if (bdatShop->getShopListShopType(shop) != SHOP_TYPE_UNKNOWN_1) {
    return false;
  }
  info.unknown48 = bdatShop->getShopListTableID(shop);
  for (u32 i = 0; i < 8; i++) {
    u32 taskSet = bdatShop->getShopChangeDefTaskSet(info.unknown48, i);
    if (taskSet != 0) {
      info.unknown00.push_back(taskSet);
    }
  }
  for (u32 i = 0; i < 8; i++) {
    u32 taskSet = bdatShop->getShopChangeAddTaskSet(info.unknown48, i);
    if (taskSet != 0) {
      u32 condition = bdatShop->getShopChangeAddCondition(info.unknown48, i);
      if (condition == 0 || GfGameCond::isGameCond(condition)) {
        info.unknown00.push_back(taskSet);
      }
    }
  }
  return info.unknown00.size() != 0;
}

} // namespace gf
