#include "gf/object/component/pc/field/gf_pc_state_field_water_dead.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterDead::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
}

void StateFieldWaterDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterDead::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
