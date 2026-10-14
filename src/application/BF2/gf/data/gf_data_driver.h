#pragma once
#include "mm_mtl/fixed_array.h"
#include "types.h"
#include <stddef.h>

namespace gf {

struct SDataDriverWeapon {
  mm::mtl::FixedArray<u32, 3> slotArts;
  u32 wp;
  u32 totalWp;
};

struct SDataDriver {
  u8 _000[0x022 - 0x000];
  u16 setBladeType;
  s16 bladeSet;
  u16 blades[5];
  u8 _030[0x0c0 - 0x030];
  SDataDriverWeapon weapons[28];
  u8 artsLevel[0x570 - 0x2f0];
  u8 _570[0x5a0 - 0x570];
};

static_assert(sizeof(SDataDriverWeapon) == 0x14, "");
static_assert(offsetof(SDataDriver, setBladeType) == 0x022, "");
static_assert(offsetof(SDataDriver, bladeSet) == 0x024, "");
static_assert(offsetof(SDataDriver, blades) == 0x026, "");
static_assert(offsetof(SDataDriver, weapons) == 0x0c0, "");
static_assert(offsetof(SDataDriver, artsLevel) == 0x2f0, "");
static_assert(sizeof(SDataDriver) == 0x5a0, "");

class GfDataDriver {
public:
  static SDataDriver *getSDataDriver(u32 driver);
  static int getMaxSetBladeNum(u32 driver);
  static u32 getBlade(u32 driver, int slot);
  static int getBladeSet(u32 driver);
  static u32 getBlade(const SDataDriver &dataDriver, int slot);
  static int getBladeSet(const SDataDriver &dataDriver);
  static int getMaxSetBladeNum(const SDataDriver &dataDriver);
};

} // namespace gf
