#include "gf/object/component/pc/field/gf_pc_state_field_wall_performance.h"

#include "anm/anm_qs_transform.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec4.h"

namespace gf {
namespace pc {

void StateFieldWallPerformance::enter(GfComBehaviorPc *behavior, ai::State *previous) {}

void StateFieldWallPerformance::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::notifyRiderEvent(*behavior, VEHICLE_EVENT_UNKNOWN_0);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  anm::QsTransform locomotion;
  locomotion.unknown00 = mm::Vec4::zero;
  locomotion.unknown10 = mm::Quat::identity;
  locomotion.unknown20 = mm::Vec4::unit;
  property->setLocomotion(locomotion);
}

void StateFieldWallPerformance::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

} // namespace pc
} // namespace gf
