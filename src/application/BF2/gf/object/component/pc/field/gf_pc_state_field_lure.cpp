#include "gf/object/component/pc/field/gf_pc_state_field_lure.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldLure::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  unknown18 = StateUtilField::getLureTargetHandle(*behavior);
}

void StateFieldLure::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setEnableLure(*behavior, false); }

} // namespace pc
} // namespace gf
