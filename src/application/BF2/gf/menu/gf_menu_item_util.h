#pragma once
#include "gf/data/gf_data_item.h"
#include "types.h"

namespace gf {

class GfMenuItemUtil {
public:
  static bool canCountStack(u32 itemType);
  static bool canBuyItem(u32 item, u32 shop);
  static bool canSellItem(u32 item, u32 shop);
  static bool canSellItemType(u32 itemType);
  static u32 getEquipErrorCmnWindowID(u32 error);
  static u32 getItemNum(u8 itemType, u32 itemId);
  static int getItemIconID(u8 itemType, u32 itemId);
  static bool convShopIcon(u32 icon, ItemType::Type &type, u32 &param);
};

} // namespace gf
