#include "gf/object/component/pc/field/gf_pc_state_field_water_dive.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
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

void StateFieldWaterDive::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  if (next == nullptr || next->stateID != STATE_ID_FIELD_WATER_DEAD_SINK) {
    StateUtilField::setWaterDiveMove(*property, false);
    property->verticalSpeed = 0.0f;
  }
  StateUtil::setFallDamageDisable(*behavior, false);
}

void StateFieldWaterDive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
