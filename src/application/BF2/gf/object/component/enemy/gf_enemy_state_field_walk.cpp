#include "gf/object/component/enemy/gf_enemy_state_field_walk.h"

#include <string.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/field/gf_field_pitch_roll_controller.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_math.h"

namespace gf {
namespace enemy {

// Inferred role: commands played at a route point, indexed by the type of the route point; original name unknown.
static const struct {
  const char *name[7];
} unknown002 = {{nullptr, nullptr, "C_uniqueA", "C_uniqueB", "C_specialA_00", "C_specialB_00", nullptr}};

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  return gmkInst != nullptr && static_cast<u32>(gmkInst->getGmkType()) <= gmk::GMK_TYPE_ROUTED_ENEMY;
}

void StateFieldWalk::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_14)) {
    reqState(STATE_ID_UNKNOWN_14);
    return;
  }

  gmk::GmkRouteNavi *navi = behavior->unknown140.getGmkRouteNavi();
  if (navi != nullptr) {
    unknown84 = navi->unknowna0;
  }

  if (unknown58) {
    (this->*unknown58)(*behavior, info);
  }

  validateMoveSpeed(*behavior);
  if (canLotteryMoveSpeed(*behavior)) {
    unknown9c = info.unknown04 + unknown9c;
    if (unknown98 <= unknown9c) {
      unknown9c = 0.0f;
      u32 stateId = behavior->getNextFieldStateId();
      behavior->unknown140.applyFieldMoveSpeed((stateId & ~1) == STATE_ID_UNKNOWN_10 ? GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_2 : GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1, *behavior);
    }
  }
}

void StateFieldWalk::leave(GfComBehaviorEnemy *behavior, ai::State *next) { behavior->unknown54e1 = false; }

bool StateFieldWalk::has_move_fly_ON() const { return (unknown18 >> 5) & 1; }

bool StateFieldWalk::canLotteryMoveSpeed(GfComBehaviorEnemy &behavior) const {
  gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
  bool result = false;
  if (navi != nullptr) {
    if (navi->unknown28.unknown38 == nullptr) {
      result = false;
    } else {
      result = unknown18 == 0;
    }
  }

  return result;
}

void StateFieldWalk::updateRouteNavi(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
  if (navi != nullptr) {
    const mm::Vec3 &position = behavior.getTransform().unknown00;
    validateGmkRouteNaviConsideringGfLocalSteer(*navi, behavior.unknown140.unknown200, position);
    gmk::GmkRouteNavi::UpdateInfo updateInfo;
    updateInfo.position = position;
    navi->update(updateInfo);
    behavior.unknown140.unknownc0 = navi->unknown90;
  }
}

void StateFieldWalk::seqIdleInfinit(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) { unknown20.update(info.unknown04); }

void StateFieldWalk::seqWaitSpecialEndAtRoutePoint(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if ((unknown90 | 1) == 5) {
    behavior.extractLoco();
  }

  unknown20.update(info.unknown04);
  if (unknown20.unknown34) {
    if ((unknown90 | 1) == 5) {
      unknown58 = &StateFieldWalk::seqWaitSyncLoco;
    } else {
      behavior.execTurnCmdToGoal();
      unknown58 = &StateFieldWalk::seqWaitTurnEnd;
    }
  }
}

void StateFieldWalk::validateMoveSpeed(GfComBehaviorEnemy &behavior) {
  u32 moveSpeed = 1;
  if (has_move_fly_ON()) {
    f32 pitch = behavior.unknown140.unknown5268.unknown28;
    if (pitch > 5.0f * mm::DEG_TO_RAD) {
      moveSpeed = 3;
    }

    if (pitch < -10.0f * mm::DEG_TO_RAD) {
      moveSpeed = 2;
    }
  }

  if (unknown1c != moveSpeed) {
    unknown1c = moveSpeed;
    switch (moveSpeed) {
    case 1: {
      GfBehaviorEnemyField::MoveSpeed speed = GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1;
      if ((unknown08 & ~1) == STATE_ID_UNKNOWN_10) {
        speed = GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_2;
      }

      behavior.unknown140.applyFieldMoveSpeed(speed, behavior);
      break;
    }
    case 2:
      behavior.unknown140.applyFieldMoveSpeed(STATE_ID_UNKNOWN_9, behavior);
      break;
    case 3:
      behavior.unknown140.applyFieldMoveSpeed(STATE_ID_UNKNOWN_11, behavior);
      break;
    }
  }
}

void StateFieldWalk::seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown53f0.unknown6c) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown58 = &StateFieldWalk::seqUpdateMove;
    behavior.unknown140.applyFieldMoveSpeed(
        GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_0, (unknown08 & ~1) == STATE_ID_UNKNOWN_10 ? GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_2 : GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1, behavior);
  }
}

void StateFieldWalk::seqInitGoalPos(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  updateRouteNavi(behavior, info);
  if (behavior.unknown140.isArrivedToGoal()) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_move"));
    unknown58 = &StateFieldWalk::seqUpdateMove;
  } else {
    behavior.execTurnCmdToGoal();
    unknown58 = &StateFieldWalk::seqWaitTurnEnd;
  }
}

void StateFieldWalk::pollToShiftLandingSeq(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior.unknown08->getComponent<GfComAsm>();
  if (comAsm != nullptr && behavior.isFly()) {
    gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
    if (navi != nullptr && unknown90 == 6 && navi->unknown28.unknown38 != nullptr) {
      mm::Vec3 position;
      if (navi->getRoute()->getRoutePointPos(position, unknown84)) {
        behavior.unknown140.unknownc0 = position;
        if (navi->isArrived(position, behavior.getTransform().unknown00)) {
          unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_idle"));
          unknown58 = &StateFieldWalk::seqWaitToIdle;
          behavior.unknown54e1 = true;
        }
      }
    }
  }
}

void StateFieldWalk::seqUpdateMove(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (!unknown20.unknown34) {
    return;
  }

  behavior.execTurnCmdToGoal();
  if (!behavior.unknown53f0.unknown6c) {
    unknown58 = &StateFieldWalk::seqWaitTurnEnd;
    return;
  }

  updateRouteNavi(behavior, info);
  gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
  if (navi != nullptr && unknown84 != navi->unknowna0) {
    const gmk::GmkRoute *route = navi->getRoute();
    if (!unknown19) {
      if (route != nullptr) {
        const gmk::GmkRoutePoint *point = route->getRoutePoint(unknown84);
        if (point != nullptr && (point->getData()->unknown1c & gmk::GmkRoutePoint::FLAG_UNKNOWN_1)) {
          const gmk::GmkRoutePoint::Data *data = point->getData();
          unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_walkend"));
          unknown88 = (data->unknown1c & gmk::GmkRoutePoint::FLAG_UNKNOWN_2) != 0;
          unknown8c = data->unknown20;
          unknown90 = data->unknown28;
          unknown94 = data->unknown24;
          unknown58 = &StateFieldWalk::seqWaitToIdleAtRoutePoint;
        }
      }
    } else {
      if (route != nullptr) {
        int pointNum = route->getRoutePointNum();
        if (unknown84 == 0 || unknown84 == pointNum - 1) {
          unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_walkend"));
          unknown58 = &StateFieldWalk::seqIdleInfinit;
        }
      }
    }
  }

  pollToShiftLandingSeq(behavior, info);
  behavior.unknown140.moveToGoal(info.unknown04);
}

void StateFieldWalk::seqWaitTurnEndAtRoutePoint(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown53f0.unknown6c) {
    if (unknown90 != 1 && unknown002.name[unknown90] != nullptr) {
      unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, unknown002.name[unknown90]));
    }

    unknown68 = 0.0f;
    unknown58 = &StateFieldWalk::seqPlayMotAtRoutePoint;
  }
}

void StateFieldWalk::seqLandingIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown68 = info.unknown04 + unknown68;
  if (!behavior.unknown54e2 && unknown68 < unknown94) {
    return;
  }

  unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_specialA_02"));
  unknown58 = &StateFieldWalk::seqWaitTakeOffEnd;
}

void StateFieldWalk::seqWaitSyncLoco(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  behavior.extractLoco();
  GfObjAcc acc(static_cast<GfObj *>(behavior.unknown08)->unknownf8);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComAsm *comAsm = obj->getComponent<GfComAsm>();
    if (comAsm != nullptr) {
      const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
      if (stateName == nullptr) {
        return;
      }

      if (strcmp(stateName, "S_idle") != 0) {
        return;
      }

      gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
      if (navi != nullptr) {
        navi->updateNextPos();
      }
    }
  }

  behavior.execTurnCmdToGoal();
  unknown58 = &StateFieldWalk::seqWaitTurnEnd;
}

void StateFieldWalk::seqWaitToIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown34) {
    unknown20.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, "C_specialA_00"));
    unknown58 = &StateFieldWalk::seqMoveToBeginLanding;
    behavior.unknown140.unknown5268.unknown30 = true;
    behavior.unknown140.unknown1d0.setSpeedKmph(behavior.unknown140.unknown1d0.unknown08, 0.0f);
  }
}

void StateFieldWalk::seqWaitToIdleAtRoutePoint(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown20.update(info.unknown04);
  if (unknown20.unknown34) {
    if (unknown88) {
      behavior.execTurnCmdAccurately(unknown8c);
    }

    unknown58 = &StateFieldWalk::seqWaitTurnEndAtRoutePoint;
  }
}

} // namespace enemy
} // namespace gf
