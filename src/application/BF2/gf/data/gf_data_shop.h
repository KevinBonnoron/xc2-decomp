#pragma once
#include "types.h"

namespace gf {

class GfDataShop {
public:
  static u32 getItemBit(u32 shop);
  static u32 getPrivilegeItem(u32 shop);
  static void setBuyItem(u32 shop, u32 item);
};

} // namespace gf
