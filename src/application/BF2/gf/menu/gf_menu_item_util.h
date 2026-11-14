#pragma once
#include "gf/data/gf_data_item.h"
#include "gf/data/gf_item_handle.h"
#include "types.h"
#include <stddef.h>

namespace ui {
class UIStr;
} // namespace ui

namespace gf {

class GfMenuItemUtil {
public:
  // Inferred role: crystal item display info; original layout unknown.
  struct CrystalInfo {
    u8 unknown00; // Inferred role: display type; original member name unknown.
    u8 unknown01; // Inferred role: display flag; original member name unknown.
  };

  static void getItemName(u8 itemType, u32 item, ui::UIStr &name);
  static void getItemTypeName(u8 itemType, ui::UIStr &name);
  static bool canCountStack(u32 itemType);
  static bool canBuyItem(u32 item, u32 shop);
  static bool canSellItem(u32 item, u32 shop);
  static bool canSellItemType(u32 itemType);
  static u32 canEquipAcc(u32 accessory, u32 driver, u32 slot);
  static u32 canEquipAcc(u32 accessory, GfItemHandle handle, u32 driver, u32 slot);
  static u32 searchEquipAcc(u32 accessory, GfItemHandle handle, u32 *slot);
  static u32 canEquipOrb(u32 orb, u32 blade, u32 slot);
  static u32 canEquipOrb(u32 orb, GfItemHandle handle, u32 blade, u32 slot);
  static u32 searchEquipOrb(u32 orb, GfItemHandle handle, u32 *slot);
  static u32 searchEquipHanaParts(u32 type, u32 parts, GfItemHandle handle);
  static u32 canCreateOrb(u32 item);
  static u32 getEquipErrorCmnWindowID(u32 error);
  static bool getItemCrystal(u32 item, CrystalInfo &info);
  static u32 getItemNum(u8 itemType, u32 itemId);
  static int getItemIconID(u8 itemType, u32 itemId);
  static bool convShopIcon(u32 icon, ItemType::Type &type, u32 &param);
  static bool getIconNumber(ItemType::Type type, u32 param, u32 &number, bool unknown);
};

static_assert(offsetof(GfMenuItemUtil::CrystalInfo, unknown01) == 0x01, "");
static_assert(sizeof(GfMenuItemUtil::CrystalInfo) == 0x02, "");

} // namespace gf
