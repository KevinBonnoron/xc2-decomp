#include "gf/object/component/pc/field/gf_pc_state_field_land_big.h"

#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldLandBig::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtilField::notifyJumpEnd(*behavior);
}

} // namespace pc
} // namespace gf
