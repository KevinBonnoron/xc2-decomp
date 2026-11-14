#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_air.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallAdsorptionAir::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = 0.0f;
  unknown1c = behavior->getProperty()->unknown310.unknown18;
  StateUtilField::resetCameraForWall(*behavior, StateUtilField::TIMING_UNKNOWN_2);
}

void StateFieldWallAdsorptionAir::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
