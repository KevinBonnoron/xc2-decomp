#pragma once
#include <stddef.h>

#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
struct GfSetupParam;

class GfGameRide : public mm::mtl::PtrSingleton<GfGameRide> {
public:
  static void build(const GfSetupParam &param);
  static void destroy();
  static void setRideOn(bool isRide);
  static bool testRideOn();
  static bool isVehicle(GF_OBJ_HANDLE *handle);

  u8 _08[0x28 - 0x08];
  GF_OBJ_HANDLE *unknown28; // Inferred role: vehicle; original member name unknown.
  GF_OBJ_HANDLE *unknown30; // Inferred role: rider; original member name unknown.
};

static_assert(offsetof(GfGameRide, unknown28) == 0x28, "");
static_assert(offsetof(GfGameRide, unknown30) == 0x30, "");

} // namespace gf
