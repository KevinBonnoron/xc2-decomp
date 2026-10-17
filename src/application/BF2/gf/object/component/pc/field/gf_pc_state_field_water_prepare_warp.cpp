#include "gf/object/component/pc/field/gf_pc_state_field_water_prepare_warp.h"

#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterPrepareWarp::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

} // namespace pc
} // namespace gf
