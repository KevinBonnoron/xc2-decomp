#pragma once

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfGameRide {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void setRideOn(bool isRide);
  static bool testRideOn();
  static bool isVehicle(GF_OBJ_HANDLE *handle);
};

} // namespace gf
