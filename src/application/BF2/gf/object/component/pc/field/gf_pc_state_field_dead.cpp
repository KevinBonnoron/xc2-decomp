#include "gf/object/component/pc/field/gf_pc_state_field_dead.h"

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

void StateFieldDead::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  unknown18 = __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_downpose") != 0;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateFieldDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldDead::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (unknown18) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWNPOSE)) {
      unknown18 = false;
    }
  }
}

void StateFieldDead::onAlive(GfComBehaviorPc *behavior, MsgObjectNotifyHealHp &message) {
  StateUtil::notifyRevival(*behavior, message);
  StateUtilField::execAsmCmd(*behavior->unknown08->getComponent<GfComAsm>(), ASM_CMD_ID_FIELD_RISE);
  reqState(STATE_ID_UNKNOWN_59);
}

bool StateFieldDead::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
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

void StateFieldDead::procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message) {
  if (message.unknown10 == 0) {
    onAlive(behavior, message);
    MsgPcFieldRelaySurvive relay(&message);
    StateUtil::sendMessageToBuddy(*behavior, relay);
  }
}

void StateFieldDead::procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message) {
  fw::Message *relayed = message.unknown08;
  if (relayed != nullptr && relayed->unknown00 == MSG_OBJECT_UNKNOWN_16777273 && static_cast<MsgObjectNotifyHealHp *>(relayed)->unknown10 == 0) {
    onAlive(behavior, *static_cast<MsgObjectNotifyHealHp *>(relayed));
  }
}

} // namespace pc
} // namespace gf
