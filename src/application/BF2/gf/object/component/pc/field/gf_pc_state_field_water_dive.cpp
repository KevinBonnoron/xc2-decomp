#include "gf/object/component/pc/field/gf_pc_state_field_water_dive.h"

#include "ai/ai_state.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/property/gf_com_property.h"

namespace gf {
namespace pc {

void StateFieldWaterDive::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->getProperty();
  property->unknown94 = 0.0f;
  StateUtilField::setWaterDiveMove(*property, true);
  StateUtil::setFallDamageDisable(*behavior, true);
}

void StateFieldWaterDive::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (next == nullptr || next->unknown08 != STATE_ID_UNKNOWN_35) {
    StateUtilField::setWaterDiveMove(*property, false);
    property->unknown90 = 0.0f;
  }
  StateUtil::setFallDamageDisable(*behavior, false);
}

void StateFieldWaterDive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}

void StateFieldWaterDive::onDead(GfComBehaviorPc *behavior, MsgObjectNotifyDead &message) {
  StateUtil::notifyDead(*behavior, message, true);
  behavior->unknown08->getComponent<GfComAsm>()->execCmd("C_waterdead", ANIM_LAYER_UNKNOWN_0);
  reqState(STATE_ID_UNKNOWN_35);
}

bool StateFieldWaterDive::recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) {
  switch (message.unknown00) {
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

void StateFieldWaterDive::procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message) {
  onDead(behavior, message);
  if (message.unknown08 != DEAD_TYPE_UNKNOWN_3) {
    MsgPcFieldRelaySurvive relay(&message);
    StateUtil::sendMessageToBuddy(*behavior, relay);
  }
}

void StateFieldWaterDive::procMsgPcFieldRelaySurvive(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldRelaySurvive &message) {
  fw::Message *relayed = message.unknown08;
  if (relayed != nullptr && relayed->unknown00 == MSG_OBJECT_UNKNOWN_16777272) {
    onDead(behavior, static_cast<MsgObjectNotifyDead &>(*relayed));
  }
}

} // namespace pc
} // namespace gf
