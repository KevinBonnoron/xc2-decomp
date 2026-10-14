#pragma once

namespace gf {

struct GfSetupParam;

class GfGameRide {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static bool testRideOn();
};

} // namespace gf
