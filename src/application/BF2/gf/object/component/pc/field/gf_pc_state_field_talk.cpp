#include "gf/object/component/pc/field/gf_pc_state_field_talk.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/game/gf_game_message.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/behavior/plugin/gf_lip_sync_plugin.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

// Inferred role: talk state of each MsgGameTalkAction action; original name unknown.
static const char *const unknown002[] = {"S_talkA_00", "S_talkA_01", "S_talkA_02", "S_idle"};
// Inferred role: talk command of each MsgGameTalkAction action, none for the actions that only set the state; original name unknown.
static const char *const unknown003[] = {"C_talkA_00", nullptr, "C_talkA_02", nullptr};

void StateFieldTalk::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = unknown020;
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr) {
    unknown18 = target->unknownf8;
    MsgPcFieldNotifyAction message(0);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setAccessFlag(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_IDLE);
  StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldTalk::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfObj *target = GfObjUtil::getObj(unknown18);
  if (target != nullptr) {
    MsgPcFieldNotifyAction message(1);
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
  }
  StateUtilField::setSpecialActStatus(*behavior, false);
  fw::Message message(0x100001a, 0x20);
  StateUtil::broadcastPlayer(*behavior, message);
  StateUtil::setEnableDownIK(*behavior, false);
}

void StateFieldTalk::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isPlayerPause()) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    bool isIdle = __builtin_strcmp(stateName, "S_idle") == 0;
    bool isTalkEnd = __builtin_strcmp(stateName, "S_talkA_02") == 0;
    if ((isIdle | isTalkEnd) || StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_UNKNOWN_3);
    }
  }
}

bool StateFieldTalk::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_GAME_UNKNOWN_16777261:
    procMsgGameTalkAction(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgGameTalkAction &>(message));
    break;
  case MSG_GAME_UNKNOWN_16777262:
    procMsgGameLipAction(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgGameLipAction &>(message));
    break;
  case MSG_GAME_UNKNOWN_16777263:
    procMsgGameSetLipWeight(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgGameSetLipWeight &>(message));
    break;
  default:
    return false;
  }

  return true;
}

void StateFieldTalk::procMsgGameTalkAction(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgGameTalkAction &message) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (message.isDirect) {
    message.isSuccess = comAsm->setState(unknown002[message.action], ANIM_LAYER_UNKNOWN_0);
  } else {
    if (unknown003[message.action] != nullptr) {
      message.isSuccess = comAsm->execCmd(unknown003[message.action], ANIM_LAYER_UNKNOWN_0);
    }
    if (!message.isSuccess && unknown003[message.action] != nullptr) {
      message.isSuccess = comAsm->setState(unknown002[message.action], ANIM_LAYER_UNKNOWN_0);
    }
  }
}

void StateFieldTalk::procMsgGameLipAction(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgGameLipAction &message) {
  switch (message.action) {
  case 0: {
    LipSyncPlugin *plugin = behavior->unknown001<LipSyncPlugin>(2);
    if (plugin != nullptr) {
      plugin->unknown21 = true;
    }
    break;
  }
  case 1: {
    LipSyncPlugin *plugin = behavior->unknown001<LipSyncPlugin>(2);
    if (plugin != nullptr) {
      plugin->unknown21 = false;
    }
    break;
  }
  }
}

void StateFieldTalk::procMsgGameSetLipWeight(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgGameSetLipWeight &message) {
  LipSyncPlugin *plugin = behavior->unknown001<LipSyncPlugin>(2);
  if (plugin != nullptr) {
    plugin->setWeight(message.unknown08);
  }
}

} // namespace pc
} // namespace gf
