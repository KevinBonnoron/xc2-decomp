#include "gf/object/component/behavior/npc/gf_npc_state_walk.h"

#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace npc {

void StateWalk::updateGoalPos(GfComBehaviorNpc &behavior) {
  gmk::GmkRouteNavi *navi = behavior.getGmkRouteNavi();
  if (navi == nullptr) {
    gmk::AGmkBase *gmk = behavior.getBindedGmkInst();
    if (gmk != nullptr) {
      behavior.setGoalPos(gmk->unknown08.unknown08->unknown00);
    }
  } else {
    const mm::Vec3 &position = behavior.getPos();
    validateGmkRouteNaviConsideringGfLocalSteer(*navi, behavior.unknown350, position);
    gmk::GmkRouteNavi::UpdateInfo info;
    info.position = position;
    navi->update(info);
    if (navi->unknown00.isValid() && navi->unknown28.isValid()) {
      behavior.setGoalPos(navi->unknown90);
    }
  }
}

void StateWalk::enter(GfComBehaviorNpc *behavior, ai::State *previous) {
  updateGoalPos(*behavior);
  behavior->execTurnCmdToGoal();
  unknown50 = &StateWalk::seqWaitTurnEnd;
}

void StateWalk::leave(GfComBehaviorNpc *behavior, ai::State *next) {}

void StateWalk::update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info) {
  updateGoalPos(*behavior);
  if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_4)) {
    reqState(STATE_ID_UNKNOWN_4);
  } else if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateWalk::seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c) {
    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown50 = &StateWalk::seqUpdateMove;
  }
}

} // namespace npc
} // namespace gf
