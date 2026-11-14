#include "gf/object/component/pc/field/gf_pc_state_field_water_prepare_warp.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace pc {

void StateFieldWaterPrepareWarp::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_SWIM_01);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  unknown18 = false;
}

void StateFieldWaterPrepareWarp::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (!unknown18) {
    if (!GfGameManager::isPlayerPause()) {
      reqState(STATE_ID_UNKNOWN_20);
    }
  } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERHOLE_00)) {
    GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
    MsgPcFieldNotifyWaterWarp message(property->unknown310.getWarpInfo());
    StateUtil::broadcastMainChar(*behavior, message);
    reqState(STATE_ID_UNKNOWN_30);
  }
}

void StateFieldWaterPrepareWarp::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

bool StateFieldWaterPrepareWarp::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_PC_FIELD_NOTIFY_UNKNOWN_16777236) {
    procMsgPcFieldNotifyWarp(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldNotifyWarp &>(message));
    return true;
  }

  return false;
}

void StateFieldWaterPrepareWarp::procMsgPcFieldNotifyWarp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldNotifyWarp &message) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown310.setWarpInfo(&message);
  if (sender != nullptr) {
    GfObj *object = mm::mtl::dynamicCast<GfObj>(sender);
    if (object != nullptr) {
      property->unknown310.unknown78 = object->unknownf8;
    }
  }
  unknown18 = true;
}

} // namespace pc
} // namespace gf
