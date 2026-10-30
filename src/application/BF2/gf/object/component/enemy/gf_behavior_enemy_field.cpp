// Same order as in the game executable: the sensor is defined before the field behavior in the same unit.
// clang-format off
#include "gf/field/gf_field_enemy_sensor.cpp"
// clang-format on
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include <math.h>

#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/enemy/gf_beh_field_owner.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_com_property_enemy.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/param/enemy/gf_param_enemy.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

f32 GfBehaviorEnemyField::getWalkSpeed() const {
  DataParamAcc dataParam(unknown10);
  return dataParam.getSDataEnemy()->unknown49;
}

f32 GfBehaviorEnemyField::getRunSpeed() const {
  DataParamAcc dataParam(unknown10);
  return dataParam.getSDataEnemy()->unknown4a;
}

gmk::GmkRouteNavi *GfBehaviorEnemyField::getGmkRouteNavi() const {
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown10);
  if (gmkInst != nullptr && gmkInst->getGmkType() == gmk::GMK_TYPE_ROUTED_ENEMY) {
    return static_cast<gmk::GmkRoutedEnemy *>(gmkInst)->findRouteNavi(unknown10);
  }

  return nullptr;
}

bool GfBehaviorEnemyField::isChangeBattleCondMatch() const {
  if (!unknown52a8) {
    return false;
  }

  if (unknown52a4 < unknown52a0) {
    return false;
  }

  return unknownd0.isPlayerEnter() || unknownd0.unknown80;
}

bool GfBehaviorEnemyField::isArrivedToGoal() const {
  if (unknown200.isTimeOutCollide()) {
    return true;
  }

  const mm::Vec3 &position = unknown08->getTransform().unknown00;
  f32 dy = unknownc0.y - position.y;
  if (unknown1c < dy) {
    return false;
  }

  f32 dx = unknownc0.x - position.x;
  f32 dz = unknownc0.z - position.z;
  if (unknown20 != 3) {
    dy = 0.0f;
  }

  f32 distanceSq = dx * dx + dy * dy + dz * dz;
  return !(unknown18 * unknown18 < distanceSq);
}

void GfBehaviorEnemyField::getMoveDir(mm::Vec3 &direction) const {
  if (!getMoveVec(direction, unknown40)) {
    const mm::Vec3 &position = unknown08->getTransform().unknown00;
    direction = unknownc0 - position;
    if (unknown20 != 3) {
      direction.y = 0.0f;
    }
  }

  if (!(fabsf(direction.x) <= 0.000001f) || !(fabsf(direction.y) <= 0.000001f) || !(fabsf(direction.z) <= 0.000001f)) {
    f32 length = sqrtf(direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
    if (length <= 0.000001f) {
      direction = mm::Vec3::zero;
    } else {
      f32 inverse = 1.0f / length;
      direction.x = inverse * direction.x;
      direction.y = inverse * direction.y;
      direction.z = inverse * direction.z;
    }
  }
}

void GfBehaviorEnemyField::dispose() {
  unknown5268.dispose();
  unknown200.dispose();
  unknown1d0.dispose();
  unknownd0.dispose();
  unknown50.dispose();
  disposeNaviMeshObj();
  unknown08 = nullptr;
  unknown10 = INVALID_HANDLE;
  unknown18 = 1.0f;
  unknown1c = 2.0f;
  unknown20 = 0;
}

fw::ColiMoveObject *GfBehaviorEnemyField::getColiObject() const {
  GfObjAcc acc(unknown10);
  GfObj *obj = acc.getObj();
  if (obj != nullptr) {
    GfComCollider *collider = obj->getComponent<GfComCollider>();
    if (collider != nullptr) {
      fw::ColiObject *coli = collider->unknown18[0];
      if (coli != nullptr) {
        return mm::mtl::dynamicCast<fw::ColiMoveObject>(coli);
      }
    }
  }

  return nullptr;
}

void GfBehaviorEnemyField::createNaviMeshObj() {
  disposeNaviMeshObj();
  if (unknown20 != 3 && !unknown38) {
    unknown40 = fw::NaviManager::get()->createObject();
    if (unknown40 != nullptr) {
      unknown40->setMeshNum(0);
      unknown40->unknown10 |= 2;
    }
  }
}

void GfBehaviorEnemyField::createSquadNavi() {
  unknown50.dispose();
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown10);
  if (gmkInst != nullptr) {
    gmk::GmkSquadNavi::CreateInfo info;
    switch (gmkInst->getGmkType()) {
    case gmk::GMK_TYPE_ENEMY:
      info.unknown00 = static_cast<gmk::GmkEnemy *>(gmkInst)->unknown48.unknown150;
      break;
    case gmk::GMK_TYPE_ROUTED_ENEMY:
      info.unknown00 = static_cast<gmk::GmkRoutedEnemy *>(gmkInst)->unknown50.unknown150;
      break;
    default:
      break;
    }
    GF_OBJ_HANDLE *handle = unknown10;
    info.unknown08 = handle;
    GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
    if (info.unknown00 != nullptr && info.unknown08 != INVALID_HANDLE) {
      unknown50.create(info);
    }
  }
}

void GfBehaviorEnemyField::disposeSquadNavi() { unknown50.dispose(); }

void GfBehaviorEnemyField::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknown40);
  unknown40 = nullptr;
}

void GfBehaviorEnemyField::update(f32 deltaTime) {
  if (unknown08 == nullptr || unknown10 == INVALID_HANDLE) {
    return;
  }

  unknowna0.z = 0.0f;
  unknowna0.x = 0.0f;
  fw::ColiMoveObject *coli = getColiObject();
  if (coli == nullptr || coli->testAttribute(fw::COLI_ATRR_UNKNOWN_0) || coli->unknown30 == fw::COLI_TYPE_STATIC || !unknown90) {
    unknowna0.y = 0.0f;
  } else {
    unknowna0.y += deltaTime * -9.8f;
  }

  unknownb0 = 0;
  updateNaviMeshObj(deltaTime);
  updateSensor(deltaTime);
  unknown1d0.update(deltaTime);
  GfFieldLocalSteer::UpdateInfo steerInfo;
  steerInfo.unknown00 = unknownc0;
  steerInfo.unknown10 = deltaTime;
  unknown200.update(steerInfo);
  if (unknown52a4 < unknown52a0) {
    unknown52a4 += deltaTime;
  }

  GfObjAcc acc(unknown10);
  GfObj *obj = acc.getObj();
  if (obj == nullptr) {
    return;
  }

  GfComPropertyEnemy *property = obj->getComponent<GfComPropertyEnemy>();
  f32 waterHeight = 0.0f;
  bool isInWater = property->getWaterHeight(waterHeight);
  f32 chestHeight = property->getChestHeight();
  if (!GfGameManager::isControlFree() || acc.isEnemyBlade()) {
    unknown52a9 = false;
    return;
  }

  DataParamAcc dataParam(unknown10);
  switch (dataParam.getSDataEnemy()->unknown9a) {
  case 0:
    unknown52a9 = isInWater;
    break;
  case 1:
    unknown52a9 = !isInWater;
    if (waterHeight < chestHeight) {
      unknown90 = true;
    } else {
      unknown90 = false;
      unknowna0.y = (waterHeight - chestHeight) * 0.1f;
    }
    break;
  case 2:
    unknown52a9 = isInWater && chestHeight < waterHeight;
    break;
  }
}

void GfBehaviorEnemyField::updateNaviMeshObj(f32 deltaTime) {
  if (unknown40 != nullptr && (unknown40->unknown10 & 2) != 0 && unknown1d0.unknown00 != INVALID_HANDLE && !isArrivedToGoal()) {
    const mm::Vec3 &position = unknown08->getTransform().unknown00;
    unknown40->setBeginPos(position);
    unknown40->setEndPos(unknownc0);
    f32 speed = unknown1d0.unknown10 * 0.2777778f;
    unknown40->setMoveSpd(speed * deltaTime);
    mm::Vec3 direction;
    getMoveDir(direction);
  }
}

void GfBehaviorEnemyField::updateSensor(f32 deltaTime) { unknownd0.update(unknown10, *unknown08); }

void GfBehaviorEnemyField::updatePitchRollController() {
  gmk::GmkRouteNavi *navi = getGmkRouteNavi();
  if (navi != nullptr) {
    unknown5268.update(*navi);
  }
}

GfBehaviorEnemyField::MoveSpeed GfBehaviorEnemyField::getFieldMoveSpeedType(enemy::STATE_ID stateId) const {
  if (stateId >= enemy::STATE_ID_UNKNOWN_1 && stateId <= enemy::STATE_ID_UNKNOWN_7) {
    return MOVE_SPEED_UNKNOWN_0;
  }

  if (stateId >= enemy::STATE_ID_UNKNOWN_8 && stateId <= enemy::STATE_ID_UNKNOWN_9) {
    return MOVE_SPEED_UNKNOWN_1;
  }

  if (stateId >= enemy::STATE_ID_UNKNOWN_10 && stateId <= enemy::STATE_ID_UNKNOWN_11) {
    return MOVE_SPEED_UNKNOWN_2;
  }

  if (stateId >= enemy::STATE_ID_UNKNOWN_13 && stateId <= enemy::STATE_ID_UNKNOWN_15) {
    return MOVE_SPEED_UNKNOWN_1;
  }

  return MOVE_SPEED_UNKNOWN_0;
}

void GfBehaviorEnemyField::applyFieldMoveSpeed(enemy::STATE_ID stateId, GfComBehaviorEnemy &behavior) { applyFieldMoveSpeed(getFieldMoveSpeedType(stateId), behavior); }

void GfBehaviorEnemyField::applyFieldMoveSpeed(MoveSpeed moveSpeed, GfComBehaviorEnemy &behavior) {
  MoveSpeed currentMoveSpeed = MOVE_SPEED_UNKNOWN_0;
  if (behavior.unknown53f0.unknown6c) {
    currentMoveSpeed = getFieldMoveSpeedType(static_cast<enemy::STATE_ID>(behavior.getStateId()));
  }

  applyFieldMoveSpeed(currentMoveSpeed, moveSpeed, behavior);
}

void GfBehaviorEnemyField::applyFieldMoveSpeed(MoveSpeed currentMoveSpeed, MoveSpeed targetMoveSpeed, GfComBehaviorEnemy &behavior) {
  f32 speed = getWalkSpeed();
  switch (targetMoveSpeed) {
  case MOVE_SPEED_UNKNOWN_0:
    speed = unknown1d0.unknown08;
    break;
  case MOVE_SPEED_UNKNOWN_1:
    speed = getWalkSpeed();
    break;
  case MOVE_SPEED_UNKNOWN_2:
    speed = getRunSpeed();
    break;
  default:
    break;
  }

  f32 delta = unknown001(currentMoveSpeed, targetMoveSpeed, *getEnemeyMoveParam(unknown36));
  unknown1d0.setSpeedKmph(speed, delta);
}

} // namespace gf
