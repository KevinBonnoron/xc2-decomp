#include "gf/object/component/pc/field/gf_pc_state_field_ride_on.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"

namespace gf {
namespace pc {

void StateFieldRideOn::enter(GfComBehaviorPc *behavior, ai::State *previous) { behavior->getProperty()->isFieldControl = true; }

void StateFieldRideOn::leave(GfComBehaviorPc *behavior, ai::State *next) { behavior->getProperty()->isFieldControl = false; }

} // namespace pc
} // namespace gf
