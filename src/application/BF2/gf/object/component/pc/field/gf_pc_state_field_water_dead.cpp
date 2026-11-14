#include "gf/object/component/pc/field/gf_pc_state_field_water_dead.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/property/gf_com_property.h"
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

void StateFieldWaterDead::onAlive(GfComBehaviorPc *behavior, MsgObjectNotifyHealHp &message) {
  StateUtil::notifyRevival(*behavior, message);
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
    reqState(STATE_ID_UNKNOWN_20);
  }
}

bool StateFieldWaterDead::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_OBJECT_UNKNOWN_16777273:
    procMsgObjectNotifyHealHp(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyHealHp &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777246:
    procMsgPcFieldRelaySurvive(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldRelaySurvive &>(message));
    break;
  default:
    return false;
  }

  return true;
}

void StateFieldWaterDead::procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message) {
  if (message.unknown10 == 0) {
    onAlive(behavior, message);
    MsgPcFieldRelaySurvive relay(&message);
    StateUtil::sendMessageToBuddy(*behavior, relay);
  }
}

void StateFieldWaterDead::procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message) {
  fw::Message *relayed = message.unknown08;
  if (relayed != nullptr && relayed->unknown00 == MSG_OBJECT_UNKNOWN_16777273 && static_cast<MsgObjectNotifyHealHp *>(relayed)->unknown10 == 0) {
    onAlive(behavior, *static_cast<MsgObjectNotifyHealHp *>(relayed));
  }
}

} // namespace pc
} // namespace gf
