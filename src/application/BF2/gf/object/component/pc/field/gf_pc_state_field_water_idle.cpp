#include "gf/object/component/pc/field/gf_pc_state_field_water_idle.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterIdle::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setIdleStatus(*behavior->owner->getComponent<GfComPropertyPc>(), false);
}

} // namespace pc
} // namespace gf
