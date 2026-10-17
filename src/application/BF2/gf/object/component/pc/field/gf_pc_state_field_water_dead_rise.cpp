#include "gf/object/component/pc/field/gf_pc_state_field_water_dead_rise.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void StateFieldWaterDeadRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->verticalSpeed = 0.0f; }

void StateFieldWaterDeadRise::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
