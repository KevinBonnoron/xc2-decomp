#include "gf/game/gf_game_ride.h"

#include "gf/object/gf_obj_handle.h"

namespace gf {

bool GfGameRide::testRideOn() {
  GfGameRide *ride = get();
  if (ride->unknown28 != INVALID_HANDLE) {
    return ride->unknown30 != INVALID_HANDLE;
  }

  return false;
}

bool GfGameRide::isVehicle(GF_OBJ_HANDLE *handle) {
  if (handle != INVALID_HANDLE) {
    return get()->unknown28 == handle;
  }

  return false;
}

} // namespace gf
