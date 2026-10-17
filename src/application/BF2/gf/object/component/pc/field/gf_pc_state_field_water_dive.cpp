#include "gf/object/component/pc/field/gf_pc_state_field_water_dive.h"

#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterDive::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->getProperty();
  property->horizontalSpeed = 0.0f;
  StateUtilField::setWaterDiveMove(*property, true);
  StateUtil::setFallDamageDisable(*behavior, true);
}

void StateFieldWaterDive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
