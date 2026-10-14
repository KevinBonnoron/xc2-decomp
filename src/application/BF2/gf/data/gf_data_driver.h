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
  u8 _000[0x0c0 - 0x000];
  SDataDriverWeapon weapons[28];
  u8 artsLevel[0x570 - 0x2f0];
  u8 _570[0x5a0 - 0x570];
};

static_assert(sizeof(SDataDriverWeapon) == 0x14, "");
static_assert(offsetof(SDataDriver, weapons) == 0x0c0, "");
static_assert(offsetof(SDataDriver, artsLevel) == 0x2f0, "");
static_assert(sizeof(SDataDriver) == 0x5a0, "");

class GfDataDriver {
public:
  static SDataDriver *getSDataDriver(u32 driver);
};

} // namespace gf
