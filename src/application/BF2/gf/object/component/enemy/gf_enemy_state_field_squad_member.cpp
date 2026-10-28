#include "gf/object/component/enemy/gf_enemy_state_field_squad_member.h"
#include "gf/field/gf_field_exec_cmd_turn.h"

#include <math.h>

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gmk/gmk_squad.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace enemy {

StateFieldSquadMember::StateFieldSquadMember() : unknown18(), unknown50(nullptr), unknown60(false), unknown64(0.0f) {}

void StateFieldSquadMember::enter(GfComBehaviorEnemy *behavior, ai::State *previous) {
  unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior->unknown08)->unknownf8, "C_idle"));
  unknown50 = &StateFieldSquadMember::seqUpdateIdle;
}

void StateFieldSquadMember::leave(GfComBehaviorEnemy *behavior, ai::State *next) {}

void StateFieldSquadMember::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  unknown60 = unknown64 < 0.1f;
  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }

  gmk::GmkSquadNavi &navi = behavior->unknown140.unknown50;
  if (navi.unknown001()) {
    if (navi.unknown28 == 0) {
      reqState(STATE_ID_UNKNOWN_1);
    } else {
      gmk::GmkSquadNavi::UpdateInfo updateInfo;
      updateInfo.position = behavior->getTransform().unknown00;
      navi.update(updateInfo);
      mm::Vec3 position;
      f32 rotY;
      if (navi.getPosRotY(position, rotY)) {
        behavior->unknown140.unknownc0 = position;
        const mm::Vec3 &current = behavior->getTransform().unknown00;
        f32 dx = position.x - current.x;
        f32 dz = position.z - current.z;
        unknown64 = sqrtf(dx * dx + dz * dz);
        if (!unknown60) {
          GfBehaviorEnemyField::MoveSpeed moveSpeed;
          if (unknown64 < 0.5f) {
            moveSpeed = GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_0;
          } else {
            moveSpeed = unknown64 < 1.0f ? GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_1 : GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_2;
          }
          behavior->unknown140.applyFieldMoveSpeed(moveSpeed, *behavior);
        }
      }
    }
  }
}

void StateFieldSquadMember::seqUpdateIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (unknown18.unknown34) {
    mm::Vec3 position;
    f32 rotY;
    if (behavior.unknown140.unknown50.getPosRotY(position, rotY)) {
      behavior.execTurnCmd(rotY);
      unknown50 = &StateFieldSquadMember::seqWaitTurnEnd;
    }
  }
}

void StateFieldSquadMember::seqUpdateMove(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (unknown18.unknown34) {
    mm::Vec3 position;
    f32 rotY;
    if (!unknown60 || !behavior.unknown140.unknown50.getPosRotY(position, rotY)) {
      behavior.execTurnCmdToGoal();
      if (behavior.unknown53f0.unknown6c) {
        behavior.unknown140.moveToGoal(info.unknown04);
        return;
      }
    } else {
      behavior.execTurnCmd(rotY);
    }

    unknown50 = &StateFieldSquadMember::seqWaitTurnEnd;
  }
}

void StateFieldSquadMember::seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  if (behavior.unknown53f0.unknown6c) {
    if (unknown60) {
      behavior.unknown140.applyFieldMoveSpeed(GfBehaviorEnemyField::MOVE_SPEED_UNKNOWN_0, behavior);
    }

    unknown18.create(TFieldExecCmd<GfComAsm>::CreateInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8, unknown60 ? "C_idle" : "C_move"));
    unknown50 = unknown60 ? &StateFieldSquadMember::seqUpdateIdle : &StateFieldSquadMember::seqUpdateMove;
  }
}

} // namespace enemy
} // namespace gf
