#pragma once
#include "gf/data/gf_item_handle.h"
#include "types.h"

namespace gf {

struct SDataDriver;

enum {
  EQUIP_RESULT_UNKNOWN_0 = 0, // Inferred role: equip result ok; original name unknown.
  EQUIP_RESULT_UNKNOWN_1 = 1, // Inferred role: equip result invalid type; original name unknown.
  EQUIP_RESULT_UNKNOWN_2 = 2, // Inferred role: equip result full; original name unknown.
  EQUIP_RESULT_UNKNOWN_3 = 3, // Inferred role: equip result same category; original name unknown.
  EQUIP_RESULT_UNKNOWN_4 = 4, // Inferred role: equip result same effect; original name unknown.
  EQUIP_RESULT_UNKNOWN_5 = 5, // Inferred role: equip result invalid driver; original name unknown.
  EQUIP_RESULT_UNKNOWN_6 = 6, // Inferred role: equip result no item; original name unknown.
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
