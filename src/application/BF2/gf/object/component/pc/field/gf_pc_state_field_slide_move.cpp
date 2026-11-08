#include "gf/object/component/pc/field/gf_pc_state_field_slide_move.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldSlideMove::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  mm::Vec3 velocity = mm::Vec3::unitY * property->unknown90 + property->unknown80 + property->unknownd0 * property->unknownc0;
  property->unknownc0 = property->unknownd0.x * velocity.x + property->unknownd0.y * velocity.y + property->unknownd0.z * velocity.z;
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3(0.7853982f, 0.0f, 0.0f));
}

void StateFieldSlideMove::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3::zero); }

} // namespace pc
} // namespace gf
