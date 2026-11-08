#include "gf/object/component/behavior/npc/gf_npc_state_approach_pc.h"

#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_manager.h"

namespace gf {
namespace npc {

void StateApproachPc::enter(GfComBehaviorNpc *behavior, ai::State *previous) {
  behavior->validateLocalSteer(static_cast<STATE_ID>(unknown08));
  unknown50 = &StateApproachPc::seqTurnPc;
}

void StateApproachPc::leave(GfComBehaviorNpc *behavior, ai::State *next) {
  if (next != nullptr) {
    behavior->validateLocalSteer(static_cast<STATE_ID>(next->unknown08));
  }
  unknown50 = nullptr;
}

void StateApproachPc::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateApproachPc::seqTurnPc(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (gmk::isPlayerExist()) {
    behavior.execTurnCmdToPos(gmk::getPlayerPos());
    unknown50 = &StateApproachPc::seqWaitTurnEnd;
  }
}

void StateApproachPc::seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c) {
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown50 = &StateApproachPc::seqApproachPc;
  }
}

} // namespace npc
} // namespace gf
