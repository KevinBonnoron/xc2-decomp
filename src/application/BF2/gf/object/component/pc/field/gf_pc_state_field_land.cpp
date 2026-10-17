#include "gf/object/component/pc/field/gf_pc_state_field_land.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldLand::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->verticalSpeed = 0.0f;
  property->horizontalSpeed = 0.0f;
  StateUtilField::setAirStatus(*behavior, true);
  StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldLand::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtilField::notifyJumpEnd(*behavior);
}

} // namespace pc
} // namespace gf
