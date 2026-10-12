#pragma once

namespace gf {
class GfDataBlade {
public:
  static bool isHikariCurrent();
  static void setHikariCurrent(bool hikariCurrent);
  static bool isHomuriNameHikari();
  static void setHomuriNameHikari(bool homuriNameHikari);
};
} // namespace gf
