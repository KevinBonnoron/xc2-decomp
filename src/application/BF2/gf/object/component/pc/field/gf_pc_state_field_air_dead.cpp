#include "gf/object/component/pc/field/gf_pc_state_field_air_dead.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldAirDead::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  isDownMotion = __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_BASE), "S_down_00") == 0;
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->verticalSpeed = 4.3f;
  property->horizontalSpeed = 0.0f;
}

void StateFieldAirDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
