#include "gf/object/component/pc/field/gf_pc_state_field_water_dead_dive.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterDeadDive::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setWaterDiveMove(*behavior->unknown08->getComponent<GfComPropertyPc>(), false); }

void StateFieldWaterDeadDive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
