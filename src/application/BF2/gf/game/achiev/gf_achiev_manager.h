#pragma once
#include "types.h"

namespace gf {

class GfAchievStats {
public:
  static void checkBuyItemFromShop(u32 item, u32 count, u32 shop, u32 money);
  static void checkSellItemFromShop(u32 item, u32 count, u32 shop, u32 money);
};

} // namespace gf
