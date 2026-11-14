#include "gf/object/component/pc/field/gf_pc_state_field_water_warp_rise_buddy.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

void StateFieldWaterWarpRiseBuddy::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyWarp *warp = property->unknown310.getWarpInfo();
  mm::Vec3 position = warp->unknown10;
  position.y -= property->unknown2f0;
  property->unknown160.unknown00 = position;
  f32 angle = warp->unknown20 * 0.5f;
  f32 sine = sinf(angle);
  f32 cosine = cosf(angle);
  property->unknown160.unknown10.x = 0.0f;
  property->unknown160.unknown10.y = sine;
  property->unknown160.unknown10.z = 0.0f;
  property->unknown160.unknown10.w = cosine;
  property->syncDirection();
  StateUtilField::setChildFrameHeight(*behavior, -property->unknown310.unknown50);
  GfComDynamics *dynamics = behavior->unknown08->getComponent<GfComDynamics>();
  if (dynamics != nullptr) {
    dynamics->resetMovement();
  }
}

void StateFieldWaterWarpRiseBuddy::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterWarpRiseBuddy::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  MoveUtilField::updateMoveWaterHoleRise(info, *property);
  f32 distance = info.unknown04 * property->unknown90;
  if (StateUtilField::getChildFrameHeight(*behavior) + distance >= 0.0f) {
    reqState(STATE_ID_UNKNOWN_20);
  }
}

} // namespace pc
} // namespace gf
