#include "gf/object/component/pc/field/gf_pc_state_field_water_sink.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterSink::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  elapsedTime = 0.0f;
}

void StateFieldWaterSink::leave(GfComBehaviorPc *behavior, ai::State *next) {}

} // namespace pc
} // namespace gf
