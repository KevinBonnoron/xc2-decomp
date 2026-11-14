#include "gf/object/component/pc/field/gf_pc_state_field_water_warp_dive.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/gf_com_dynamics.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterWarpDive::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

void StateFieldWaterWarpDive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  unknown18 = info.unknown04 + unknown18;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  property->setLocomotion(comAsm->getLocomotion());
  if (!unknown1c && unknown18 >= unknown20 && property->unknown38 == 0) {
    StateUtilField::startWaterWarpFade(*behavior);
    unknown1c = true;
  }
  const WaterCommonParam *param = property->unknown310.unknown002();
  if (unknown18 > param->waterHoleDiveTime && comAsm->setState("S_waterhole_01", ANIM_LAYER_UNKNOWN_0)) {
    const MsgPcFieldNotifyWarp *warp = property->unknown310.getWarpInfo();
    MsgPcFieldNotifyWaterWarpBuddy message(warp);
    StateUtil::sendMessageToBuddy(*behavior, message);
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
    if (property->unknown38 == 0) {
      GfGamePlayerCamera::requestResetCamera();
    }
    property->unknown310.unknown10_6 = false;
    reqState(STATE_ID_UNKNOWN_31);
  }
}

} // namespace pc
} // namespace gf
