#include "gf/object/component/behavior/npc/gf_npc_state_walk.h"

#include "framework/object/updatable_object.h"
#include "framework/reference_frame.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior_npc.h"
#include "gf/object/component/gf_com_transform.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"

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

void StateWalk::seqUpdateMove(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (!unknown18.unknown34) {
    return;
  }

  if (unknown18.unknown35) {
    behavior.init(true);
  }

  behavior.execTurnCmdToGoal();
  if (!behavior.unknown2e0.unknown6c) {
    unknown50 = &StateWalk::seqWaitTurnEnd;
    return;
  }

  if (behavior.getGmkRouteNavi() == nullptr) {
    const mm::Vec3 &position = behavior.getPos();
    mm::Vec3 difference = behavior.unknown005() - position;
    if (difference.x * difference.x + difference.y * difference.y + difference.z * difference.z < 0.010000001f) {
      gmk::AGmkBase *gmk = behavior.getBindedGmkInst();
      if (gmk == nullptr || gmk->getGmkType() != gmk::GMK_TYPE_NPC) {
        reqState(STATE_ID_UNKNOWN_0);
        return;
      }

      unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_walkend"));
      unknown50 = &StateWalk::seqWaitMoveEnd;
    }
  }

  behavior.moveToGoal(info.unknown04);
}

void StateWalk::seqInterpPosRotToGoal(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown2e0.unknown6c && behavior.getBindedGmkInst() != nullptr) {
    GfComTransform *transform = behavior.unknown08->getComponent<GfComTransform>();
    fw::Transform &world = transform->unknown001()->unknown003();
    mm::Vec3 &goal = behavior.unknown005();
    world.unknown00 += (goal - world.unknown00) * (info.unknown04 + info.unknown04);
    unknown60 = info.unknown04 + unknown60;
    if (unknown60 >= 0.5f) {
      world.unknown00 = goal;
      reqState(STATE_ID_UNKNOWN_0);
    }
  }
}

} // namespace npc
} // namespace gf
