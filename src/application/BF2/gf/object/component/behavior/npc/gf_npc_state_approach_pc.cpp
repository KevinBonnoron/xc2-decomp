#include "gf/object/component/behavior/npc/gf_npc_state_approach_pc.h"

#include "ai/ai_state.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace npc {

void StateApproachPc::enter(GfComBehaviorNpc *behavior, ai::State *previous) {
  behavior->validateLocalSteer(static_cast<STATE_ID>(m_state));
  unknown50 = &StateApproachPc::seqTurnPc;
}

void StateApproachPc::leave(GfComBehaviorNpc *behavior, ai::State *next) {
  if (next != nullptr) {
    behavior->validateLocalSteer(static_cast<STATE_ID>(next->m_state));
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

void StateApproachPc::seqApproachPc(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (!unknown18.unknown34) {
    return;
  }
  if (unknown18.unknown35) {
    behavior.init(true);
  }
  if (!gmk::isPlayerExist()) {
    return;
  }
  gmk::AGmkBase *binded = behavior.getBindedGmkInst();
  if (binded == nullptr) {
    return;
  }
  behavior.setGoalPos(gmk::getPlayerPos());
  if (!isCondMatch(behavior)) {
    reqState(STATE_ID_UNKNOWN_1);
    return;
  }
  // The block ends the first `acc` before the second one is built, as the game's stack frame shows (0x90 bytes, `add sp, sp, #0x90` at 0x71005386b8): with both
  // declared in the function the frame is 0xa0.
  bool isNear = false;
  {
    GfObjAcc acc(static_cast<GfObj *>(behavior.unknown08));
    const mm::Vec3 &position = acc.getWorldTransform().unknown00;
    mm::Vec3 delta = gmk::getPlayerPos() - position;
    if (delta.y < 1.0f) {
      delta.y = 0.0f;
      isNear = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z < 1.0f;
    }
  }
  if (!isNear) {
    // The goal copy loads the goal and then the position before the call to getDistYThreshold, as the game does (0x7100538740-0x710053874c, call at 0x7100538754);
    // without it the position is loaded first. The distance local places the sum before the load of m_bdatInfo.unknown04 (0x710053877c); without it the
    // squares are scheduled in another order. The negated `<` tests are the game's (fcmp operand order and b.mi/b.pl): `>=` and `<=` change them.
    GfObjAcc acc(static_cast<GfObj *>(behavior.unknown08));
    const mm::Vec3 &position = acc.getWorldTransform().unknown00;
    mm::Vec3 goal = binded->m_createBaseInfo.m_xform->unknown00;
    mm::Vec3 delta = position - goal;
    if (!(GfComBehaviorNpc::BdatInfo::getDistYThreshold() < delta.y)) {
      delta.y = 0.0f;
      f32 distanceSq = delta.x * delta.x + delta.y * delta.y + delta.z * delta.z;
      if (!(behavior.m_bdatInfo.unknown04 < distanceSq)) {
        behavior.moveToGoal(info.unknown04);
        return;
      }
    }
  }
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_idle"));
  unknown50 = &StateApproachPc::seqApproachPcIdle;
}

// The result local keeps the game's two return blocks after the last test (b.pl at 0x710053884c to the `orr w0, wzr, #1` block at 0x7100538858, the failed test
// falling to its own `mov w0, wzr` at 0x7100538850): early returns and a combined return expression fold the last test into a cset (27 instructions against the
// game's 30), nested ifs with `return true` give 28. The negated `<` tests are the game's (b.pl): `>=` gives b.ge.
bool StateApproachPc::isCondMatch(const GfComBehaviorNpc &behavior) {
  bool match = false;
  if (gmk::isPlayerExist() && 0.0f < behavior.m_bdatInfo.unknown04) {
    if (!(GfComBehaviorNpc::BdatInfo::getDistYThreshold() * GfComBehaviorNpc::BdatInfo::getDistYThreshold() < behavior.unknowne4)) {
      if (!(behavior.m_bdatInfo.unknown04 < behavior.unknowne0)) {
        match = true;
      }
    }
  }
  return match;
}

void StateApproachPc::seqApproachPcIdle(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (unknown18.unknown35) {
    behavior.init(false);
  }
  if (!isCondMatch(behavior)) {
    reqState(STATE_ID_UNKNOWN_1);
  }
}

} // namespace npc
} // namespace gf
