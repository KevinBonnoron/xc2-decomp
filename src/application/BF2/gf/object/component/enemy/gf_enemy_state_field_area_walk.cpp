#include "gf/object/component/enemy/gf_enemy_state_field_area_walk.h"

#include <math.h>

#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "ml/rand.h"
#include "mm_math/mm_mat44.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace enemy {

bool StateFieldAreaWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  if (gmkInst == nullptr || gmkInst->getGmkType() != gmk::GmkEnemy::GMK_TYPE) {
    return false;
  }

  return !(static_cast<gmk::GmkEnemy *>(gmkInst)->getData()->unknown00 <= behavior.unknown140.unknown08.unknown10);
}

bool StateFieldAreaWalk::getGoalPosRandom(mm::Vec3 &position, const GfComBehaviorEnemy &behavior) const {
  gmk::GmkEnemy *gmkInst = static_cast<gmk::GmkEnemy *>(behavior.getBindedGmkInst());
  if (gmkInst == nullptr) {
    return false;
  }

  GfObjAcc acc(static_cast<GfObj *>(behavior.unknown08)->unknownf8);
  if (!acc.isValidTransform()) {
    return false;
  }

  mm::Vec3 current = mm::Vec3::zero;
  const fw::Transform &transform = acc.getWorldTransformNoSync();
  current = transform.unknown00;
  mm::Vec3 front = transform.unknown10.rotate(mm::Vec3::unitZ);
  f32 rotY = atan2f(front.x, front.z);

  bool isFront = ml::mtRandf1(0.0f, 100.0f) <= behavior.unknown140.unknown28;
  f32 angleMin = rotY + (isFront ? -1.5707964f : 1.5707964f);
  f32 angleMax = rotY + (isFront ? 1.5707964f : 4.712389f);
  f32 distanceMin = behavior.unknown140.unknown34 * 0.01f;
  f32 distanceMax = behavior.unknown140.unknown35 * 0.01f;

  if (gmkInst->isPointInsideRandomWalk(current)) {
    mm::Mat44 rotation;
    rotation.setRotY(ml::mtRandf1(angleMin, angleMax));
    f32 distance = gmkInst->getData()->unknown00 * ml::mtRandf1(distanceMin, distanceMax);
    mm::Vec3 offset(0.0f, 0.0f, distance);
    mm::Vec3 rotated;
    rotated.x = offset.x * rotation.rows[0][0] + offset.y * rotation.rows[1][0] + offset.z * rotation.rows[2][0];
    rotated.y = offset.x * rotation.rows[0][1] + offset.y * rotation.rows[1][1] + offset.z * rotation.rows[2][1];
    rotated.z = offset.x * rotation.rows[0][2] + offset.y * rotation.rows[1][2] + offset.z * rotation.rows[2][2];
    position = rotated;
    position += current;
    if (!gmkInst->isPointInsideRandomWalk(position)) {
      return false;
    }
  } else {
    gmkInst->getPositionInRandomWalk(position, angleMin, angleMax, distanceMin, distanceMax);
  }

  return true;
}

bool StateFieldAreaWalk::getGoalPosWater(mm::Vec3 &position, const GfComBehaviorEnemy &behavior) const {
  if (!getGoalPosRandom(position, behavior)) {
    return false;
  }

  fw::TColiCheckResult<256> result;
  result.clear();
  mm::Vec3 start = position;
  start.y += 5.0f;
  mm::Vec3 end = position;
  end.y -= 5.0f;
  fw::ColiCheckConfig config;
  config.unknown04 = 0xffffffff;
  config.unknown00 = 9;
  config.unknown08 = 0.0f;
  config.unknown0c = 0.0f;
  config.unknown14 = false;
  config.unknown15 = false;
  config.unknown10 = 1;
  if (!fw::ColiCheck::testLineChara(result, start, end, config)) {
    return false;
  }

  if (result.getMaterial(0).unknown00 != 1) {
    return false;
  }

  position = result.getPosition(0);
  return true;
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
