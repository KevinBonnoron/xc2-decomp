#pragma once
#include "types.h"

namespace gf {

enum {
  SHOP_RESULT_UNKNOWN_0 = 0, // Inferred role: shop result ok; original name unknown.
  SHOP_RESULT_UNKNOWN_1 = 1, // Inferred role: shop result item full; original name unknown.
  SHOP_RESULT_UNKNOWN_2 = 2, // Inferred role: shop result no item; original name unknown.
  SHOP_RESULT_UNKNOWN_3 = 3, // Inferred role: shop result no money; original name unknown.
  SHOP_RESULT_UNKNOWN_4 = 4, // Inferred role: shop result not sellable; original name unknown.
};

class GfShopUtil {
public:
  static u32 execBuy(u32 item, u32 count, u32 shop);
  static u32 execSell(u32 item, u32 count, u32 shop);
};

} // namespace gf
