#include "gf/object/component/enemy/gf_enemy_state_field_area_walk.h"

#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "ml/rand.h"

namespace gf {
namespace enemy {

bool StateFieldAreaWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  if (gmkInst == nullptr || gmkInst->getGmkType() != gmk::GmkEnemy::GMK_TYPE) {
    return false;
  }

  return !(static_cast<gmk::GmkEnemy *>(gmkInst)->getData()->unknown00 <= behavior.unknown140.unknown18);
}

void StateFieldAreaWalk::enter(GfComBehaviorEnemy *behavior, ai::State *previous) {
  if (behavior->unknown140.getGmkRouteNavi() != nullptr || behavior->getBindedGmkInst() == nullptr) {
    reqState(STATE_ID_UNKNOWN_1);
    return;
  }

  if (behavior->isFlyInsect()) {
    unknown18 = 2;
  } else if (behavior->isFlyCircle()) {
    unknown18 = 3;
    unknown1c = ml::mtRandf1() > 0.5f;
  } else if (behavior->isWater()) {
    unknown18 = 4;
  } else {
    unknown18 = 1;
  }

  behavior->unknown140.applyFieldMoveSpeed(static_cast<STATE_ID>(unknown08), *behavior);
  unknown58 = &StateFieldAreaWalk::seqInitGoalPos;
}

void StateFieldAreaWalk::leave(GfComBehaviorEnemy *behavior, ai::State *next) {}

void StateFieldAreaWalk::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  if (unknown58) {
    (this->*unknown58)(*behavior, info);
  }
}

void StateFieldAreaWalk::seqChangeState(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  enemy::STATE_ID next = behavior.getNextFieldStateId();
  if (behavior.isStateCondMatch(next)) {
    reqState(next);
  } else {
    reqState(STATE_ID_UNKNOWN_1);
  }
}

void StateFieldAreaWalk::seqWaitMoveEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown34) {
    unknown58 = &StateFieldAreaWalk::seqChangeState;
  }
}

void StateFieldAreaWalk::seqMoveToGoal(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown34) {
    bool isFly = behavior.isFly();
    if (!isFly && !canGetMoveVec(behavior.unknown140.unknown40)) {
      reqState(STATE_ID_UNKNOWN_1);
    } else {
      unknown68 = info.unknown04 + unknown68;
      if (behavior.unknown140.isArrivedToGoal() || unknown68 > 5.0f) {
        if (!isFly) {
          behavior.unknown140.applyFieldMoveSpeed(GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1, behavior);
          unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_walkend"));
          unknown58 = &StateFieldAreaWalk::seqWaitMoveEnd;
        } else {
          if (unknown18 == 3) {
            unknown58 = &StateFieldAreaWalk::seqInitGoalPos;
          } else {
            unknown58 = &StateFieldAreaWalk::seqChangeState;
          }
        }
      }

      behavior.unknown140.moveToGoal(info.unknown04);
    }
  }
}

void StateFieldAreaWalk::seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown53f0.unknown6c) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown68 = 0.0f;
    unknown58 = &StateFieldAreaWalk::seqMoveToGoal;
  }
}

} // namespace enemy
} // namespace gf
