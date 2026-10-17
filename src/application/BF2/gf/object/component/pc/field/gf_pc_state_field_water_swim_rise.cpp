#include "gf/object/component/pc/field/gf_pc_state_field_water_swim_rise.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void StateFieldWaterSwimRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->verticalSpeed = 0.0f; }

void StateFieldWaterSwimRise::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
