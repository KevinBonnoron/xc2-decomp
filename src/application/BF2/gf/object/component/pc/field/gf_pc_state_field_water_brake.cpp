#include "gf/object/component/pc/field/gf_pc_state_field_water_brake.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void StateFieldWaterBrake::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  behavior->getProperty()->horizontalSpeed = 0.0f;
  isStopped = false;
}

void StateFieldWaterBrake::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
