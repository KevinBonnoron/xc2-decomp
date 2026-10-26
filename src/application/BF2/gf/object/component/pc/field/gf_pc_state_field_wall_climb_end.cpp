#include "gf/object/component/pc/field/gf_pc_state_field_wall_climb_end.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

void StateFieldWallClimbEnd::enter(GfComBehaviorPc *behavior, ai::State *previous) { StateUtil::setEnvSensor(*behavior, 0x40, false); }

void StateFieldWallClimbEnd::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::setEnvSensor(*behavior, 0x40, true); }

} // namespace pc
} // namespace gf
