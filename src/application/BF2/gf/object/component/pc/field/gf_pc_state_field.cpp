#include "gf/object/component/pc/field/gf_pc_state_field.h"

#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_battle.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/property/gf_com_property.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateField::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(behavior->unknown08)->unknownf8, true);
  StateUtilField::setLookAtFlag(*behavior, true);
  StateUtil::setEnableLookIK(*behavior, true);
  StateUtil::setEnableAgentField(*behavior, true);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::switchPlacementIK(*behavior, true);
  StateUtil::setEnableHeadDetectForSwitcher(*behavior, true);
  behavior->getProperty()->unknown110_0 = true;
  StateUtil::setEnvSensor(*behavior, 0xd0, true);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtil::setEnableSpineIK(*behavior, true);
  StateUtil::setEnableAttach(*behavior, true);
  StateUtil::setEnableTimer(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateField::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfObjUtil::setEnableEyeBlink(static_cast<GfObj *>(behavior->unknown08)->unknownf8, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  StateUtilField::setAutoRun(*property, false);
  StateUtilField::setLookAtFlag(*behavior, false);
  StateUtil::setEnableAgentField(*behavior, false);
  property->unknown110_0 = false;
  StateUtil::setEnvSensor(*behavior, 0xd0, false);
  StateUtil::setEnableHeadDetectForSwitcher(*behavior, false);
  StateUtil::setEnableSpineIK(*behavior, false);
  StateUtil::switchPlacementIK(*behavior, false);
  StateUtil::setEnableAttach(*behavior, false);
  StateUtil::setEnableTimer(*behavior, false);
}

void StateField::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->getProperty();
  if (property->unknown60.unknown08.test(INPUT_ID_UNKNOWN_1)) {
    StateUtilField::flipAutoRun(*property);
  }
  if (StateUtilField::isInputInverseDirAutoRun(*property)) {
    StateUtilField::setAutoRun(*property, false);
  }
  if (StateUtilField::testAutoRun(*property)) {
    StateUtilField::setAutoRunInput(*property);
  }
}

void StateField::onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message) {
  StateUtil::notifyDead(*behavior, message, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (message.unknown08 == DEAD_TYPE_UNKNOWN_4) {
    if (__builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_fall") != 0) {
      comAsm->setState("S_fall", ANIM_LAYER_UNKNOWN_0);
    }
    comAsm->execCmd("C_falldead", ANIM_LAYER_UNKNOWN_0);
    StateUtil::setFallDamageDisable(*behavior, true);
    MsgPcFieldReqFallDeadMotion request;
    StateUtil::sendMessageToBuddy(*behavior, request);
  } else {
    bool isSlide = property->unknown110_4;
    comAsm->setState("S_idle", ANIM_LAYER_UNKNOWN_0);
    if (!isSlide) {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWN_00)) {
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DEAD);
      }
      reqState(STATE_ID_UNKNOWN_60);
    } else {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DEAD);
      reqState(STATE_ID_UNKNOWN_58);
    }
  }
}

bool StateField::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
  case MSG_PC_BATTLE_UNKNOWN_16777226:
    procMsgPcBattleStart(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcBattleStart &>(message));
    break;
  case MSG_PC_FIELD_UNKNOWN_16777246:
    procMsgPcFieldRelaySurvive(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgPcFieldRelaySurvive &>(message));
    break;
  case MSG_OBJECT_UNKNOWN_16777271:
    procMsgObjectNotifyDamage(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyDamage &>(message));
    break;
  case MSG_OBJECT_UNKNOWN_16777272:
    procMsgObjectNotifyDead(static_cast<GfComBehaviorPc *>(owner), sender, static_cast<MsgObjectNotifyDead &>(message));
    break;
  default:
    return false;
  }

  return true;
}

void StateField::procMsgPcBattleStart(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcBattleStart &message) {
  behavior->unknown08->getComponent<GfComPropertyPc>()->unknown470.SetStartCondition(message);
  reqState(STATE_ID_UNKNOWN_63);
}

void StateField::procMsgObjectNotifyDamage(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDamage &message) {
  const MsgObjectDamage *damage = message.unknown08;
  if (damage != nullptr && damage->unknown10 == 0 && damage->unknown2a) {
    MsgPcBattleStart start(3);
    start.unknown0c = damage->unknown2a;
    start.unknown10 = damage->unknown2b;
    procMsgPcBattleStart(behavior, sender, start);
  }
}

void StateField::procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message) {
  const MsgObjectDamage *damage = message.unknown10;
  if (damage != nullptr && damage->unknown00 == MSG_OBJECT_UNKNOWN_16777266 && damage->unknown10 == 0) {
    GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
    property->unknown80 = mm::Vec3::zero;
    property->unknown90 = 0.0f;
    property->unknown94 = 0.0f;
    MsgPcBattleStart start(2);
    property->unknown470.SetStartCondition(start);
    reqState(STATE_ID_UNKNOWN_63);
  } else {
    onDead(behavior, message);
    if (message.unknown08 != DEAD_TYPE_UNKNOWN_4) {
      MsgPcFieldRelaySurvive relay(&message);
      StateUtil::sendMessageToBuddy(*behavior, relay);
    }
  }
}

void StateField::procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message) {
  fw::Message *relayed = message.unknown08;
  if (relayed != nullptr && relayed->unknown00 == MSG_OBJECT_UNKNOWN_16777272) {
    onDead(behavior, static_cast<MsgObjectNotifyDead &>(*relayed));
  }
}

} // namespace pc
} // namespace gf
