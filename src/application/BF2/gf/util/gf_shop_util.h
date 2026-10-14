#pragma once
#include "types.h"

namespace gf {

enum {
  SHOP_RESULT_OK = 0,
  SHOP_RESULT_ITEM_FULL = 1,
  SHOP_RESULT_NO_ITEM = 2,
  SHOP_RESULT_NO_MONEY = 3,
  SHOP_RESULT_NOT_SELLABLE = 4,
};

class GfShopUtil {
public:
  static u32 execBuy(u32 item, u32 count, u32 shop);
  static u32 execSell(u32 item, u32 count, u32 shop);
};

} // namespace gf
