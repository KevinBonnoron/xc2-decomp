#include "gf/object/component/pc/field/gf_pc_state_field_wall_adsorption_ground.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallAdsorptionGround::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::resetCameraForWall(*behavior, StateUtilField::TIMING_GROUND);
}

void StateFieldWallAdsorptionGround::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
