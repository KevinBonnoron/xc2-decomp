#include "gf/object/component/pc/field/gf_pc_state_field_idle_turn.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldIdleTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->horizontalSpeed = 0.0f;
}

} // namespace pc
} // namespace gf
