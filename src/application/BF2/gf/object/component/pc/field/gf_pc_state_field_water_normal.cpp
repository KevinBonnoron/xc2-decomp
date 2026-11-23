#include "gf/object/component/pc/field/gf_pc_state_field_water_normal.h"

#include "ai/ai_state.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_access_plugin.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateFieldWaterNormal::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setAccessFlag(*behavior, true);
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 16;
  }
}

void StateFieldWaterNormal::leave(GfComBehaviorPc *behavior, ai::State *next) {
  if (next != nullptr && next->m_state != STATE_ID_UNKNOWN_29) {
    StateUtilField::setAccessFlag(*behavior, false);
  }
  AccessPlugin *plugin = behavior->unknown001<AccessPlugin>(4);
  if (plugin != nullptr) {
    plugin->unknown28 = 0;
  }
}

void StateFieldWaterNormal::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfObj *target = StateUtilField::getAccessTarget(*behavior);
  if (target != nullptr && property->unknown60.unknown08.test(INPUT_ID_UNKNOWN_0)) {
    MsgPcFieldGetAccessType message;
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(target, message);
    if (message.unknown08 == 4) {
      reqState(STATE_ID_UNKNOWN_29);
    }
  }
}

void StateFieldWaterNormal::onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message) {
  StateUtil::notifyDead(*behavior, message, true);
  behavior->unknown08->getComponent<GfComAsm>()->execCmd("C_waterdead", ANIM_LAYER_UNKNOWN_0);
  reqState(STATE_ID_UNKNOWN_35);
}

bool StateFieldWaterNormal::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_PC_FIELD_UNKNOWN_16777240:
    procMsgPcFieldWaterWarp(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldWaterWarp &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777248:
    procMsgPcFieldWaterWarpBuddy(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldWaterWarpBuddy &>(message));
    break;
  case MSG_OBJECT_UNKNOWN_16777272:
    procMsgObjectNotifyDead(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyDead &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777246:
    procMsgPcFieldRelaySurvive(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldRelaySurvive &>(message));
    break;
  default:
    return false;
  }

  return true;
}

void StateFieldWaterNormal::procMsgPcFieldWaterWarp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWaterWarp &message) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  MsgPcGetState getState;
  behavior->recieveMessage(static_cast<GfObj *>(behavior->unknown08), getState);
  if (getState.unknown08 == STATE_ID_UNKNOWN_20 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERHOLE_00)) {
    message.unknown08 = true;
    reqState(STATE_ID_UNKNOWN_30);
  }
}

void StateFieldWaterNormal::procMsgPcFieldWaterWarpBuddy(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldWaterWarpBuddy &message) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  message.unknown08 = true;
  reqState(STATE_ID_UNKNOWN_32);
}

void StateFieldWaterNormal::procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message) {
  onDead(behavior, message);
  if (message.unknown08 != DEAD_TYPE_UNKNOWN_3) {
    MsgPcFieldRelaySurvive relay(&message);
    StateUtil::sendMessageToBuddy(*behavior, relay);
  }
}

void StateFieldWaterNormal::procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message) {
  fw::Message *relayed = message.unknown08;
  if (relayed != nullptr && relayed->unknown00 == MSG_OBJECT_UNKNOWN_16777272) {
    onDead(behavior, static_cast<MsgObjectNotifyDead &>(*relayed));
  }
}

} // namespace pc
} // namespace gf

// The other swimming and drowning states (0x7100561fc8 to 0x7100564068, 0x7100564194 to 0x71005642a4) sit between the normal water state functions
// (0x71005617a0 to 0x7100561f0c) and the normal, dive, prepare warp and dead virtual wrappers (0x71005642a8 to 0x7100564504), which a unit emits after
// everything it defines.
// clang-format off
#include "gf_pc_state_field_water_idle.cpp"
#include "gf_pc_state_field_water_swim.cpp"
#include "gf_pc_state_field_water_brake.cpp"
#include "gf_pc_state_field_water_idle_turn.cpp"
#include "gf_pc_state_field_water_dive.cpp"
#include "gf_pc_state_field_water_sink.cpp"
#include "gf_pc_state_field_water_rise.cpp"
#include "gf_pc_state_field_water_swim_sink.cpp"
#include "gf_pc_state_field_water_swim_rise.cpp"
#include "gf_pc_state_field_water_prepare_warp.cpp"
#include "gf_pc_state_field_water_warp_dive.cpp"
#include "gf_pc_state_field_water_warp_rise.cpp"
#include "gf_pc_state_field_water_warp_rise_buddy.cpp"
#include "gf_pc_state_field_water_dead.cpp"
#include "gf_pc_state_field_water_dead_dive.cpp"
#include "gf_pc_state_field_water_dead_sink.cpp"
#include "gf_pc_state_field_water_dead_rise.cpp"
#include "gf_pc_state_field_water_dead_idle.cpp"
// clang-format on
