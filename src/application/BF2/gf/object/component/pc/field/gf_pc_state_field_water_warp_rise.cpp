#include "gf/object/component/pc/field/gf_pc_state_field_water_warp_rise.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterWarpRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { StateUtilField::setSpecialActStatus(*behavior, true); }

} // namespace pc
} // namespace gf
