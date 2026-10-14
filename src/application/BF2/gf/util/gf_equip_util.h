#pragma once
#include "gf/data/gf_item_handle.h"
#include "types.h"

namespace gf {

struct SDataDriver;

enum {
  EQUIP_RESULT_OK = 0,
  EQUIP_RESULT_INVALID_TYPE = 1,
  EQUIP_RESULT_FULL = 2,
  EQUIP_RESULT_SAME_CATEGORY = 3,
  EQUIP_RESULT_SAME_EFFECT = 4,
  EQUIP_RESULT_INVALID_DRIVER = 5,
  EQUIP_RESULT_NO_ITEM = 6,
};

class GfEquipUtil {
public:
  static bool isEquipBladeChip(u32 blade, u32 chip);
  static void equipBladeChip(u32 blade, u32 chip);
  static u32 getEquipDriverAcce(u32 driver, u32 slot);
  static bool equipDriverAcce(u32 driver, u32 slot, u32 accessory, GfItemHandle handle);
  static u32 getEquipAcceResult(const SDataDriver &dataDriver, u32 slot, u32 accessory);
  static u32 getEquipAcceResult(u32 driver, u32 slot, u32 accessory);
  static u32 getEquipOrbMax(u32 blade);
  static u32 getEquipBladeOrb(u32 blade, u32 slot);
  static bool equipBladeOrb(u32 blade, u32 orb, u32 slot, GfItemHandle handle);
  static u32 getEquipOrbResult(u32 blade, u32 orb, u32 slot);
  static u32 execWpUpItem(u32 driver, u32 item, u32 weaponType);
};

} // namespace gf
