#include "gf/object/component/pc/field/gf_pc_state_field_prepare_big_jump.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
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

void StateFieldPrepareBigJump::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_IDLE);
  StateUtilField::setAccessFlag(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateFieldPrepareBigJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setSpecialActStatus(*behavior, false);
  LipSyncPlugin *plugin = behavior->unknown001<LipSyncPlugin>(2);
  if (plugin != nullptr) {
    plugin->setWeight(1.0f);
  }
}

void StateFieldPrepareBigJump::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isPlayerPause()) {
    reqState(STATE_ID_UNKNOWN_3);
  }
}

bool StateFieldPrepareBigJump::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  if (message.unknown00 == MSG_PC_FIELD_NOTIFY_UNKNOWN_16777233) {
    procMsgPcFieldNotifyBigJump(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldNotifyBigJump &>(message));
    return true;
  }

  return false;
}

void StateFieldPrepareBigJump::procMsgPcFieldNotifyBigJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldNotifyBigJump &message) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown310.setBigJumpInfo(&message);
  MsgPcFieldNotifyHighJump notify(&message);
  StateUtil::broadcastPlayer(*behavior, notify);
  if (sender != nullptr) {
    GfObj *object = mm::mtl::dynamicCast<GfObj>(sender);
    if (object != nullptr) {
      property->unknown310.unknown78 = object->unknownf8;
    }
  }
  reqState(STATE_ID_UNKNOWN_17);
}

} // namespace pc
} // namespace gf
