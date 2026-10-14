#pragma once
#include "types.h"

namespace gf {

class GfDataBlade {
public:
  static bool isHikariCurrent();
  static void setHikariCurrent(bool hikariCurrent);
  static bool isHomuriNameHikari();
  static void setHomuriNameHikari(bool homuriNameHikari);
  static void setActivateDriver(u32 bladeId, int slot, u32 driverId, u32 option);
};

} // namespace gf
