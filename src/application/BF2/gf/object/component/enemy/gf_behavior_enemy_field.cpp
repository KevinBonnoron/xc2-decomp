// Same order as in the game executable: the sensor is defined before the field behavior in the same unit.
// clang-format off
#include "gf/field/gf_field_enemy_sensor.cpp"
// clang-format on
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include <math.h>

#include "bdat.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
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
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_property.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gf/param/enemy/gf_param_enemy.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_math.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"
#include "navi/nvmsh_ac_obj.h"

namespace gf {

GfBehaviorEnemyField::GfBehaviorEnemyField(const CreateInfo *info)
    : unknown28(50), unknown2c(10.0f), unknown30(0.7853982f), unknown34(50), unknown35(100), unknown36(0), unknown37(0), unknown38(false), unknown40(nullptr), unknown90(true),
      unknowna0(mm::Vec3::zero), unknownb0(0), unknownc0(mm::Vec3::zero), unknown52a0(0.0f), unknown52a4(0.0f), unknown52a8(true), unknown52a9(false) {
  if (info != nullptr) {
    create(*info);
  }
}

void GfBehaviorEnemyField::create(const CreateInfo &info) {
  dispose();
  unknown08 = info;
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown08.unknown08);
  GfObjSetupEnemy *setup = GfObjUtil::getObjSetup<GfObjSetupEnemy>(unknown08.unknown08);
  unknownc0 = setup->unknown20;
  if (setup->unknowna8 > 0) {
    u8 *bdat = GfDataBdat::getFP(BDAT_FLD_ENACT_MOVE);
    unknown28 = Bdat::getValCheck(bdat, "Dir_Per", setup->unknowna8, 1);
    unknown2c = static_cast<f32>(static_cast<u16>(Bdat::getValCheck(bdat, "Dir_Line", setup->unknowna8, 2))) * mm::DEG_TO_RAD;
    unknown30 = static_cast<f32>(static_cast<u16>(Bdat::getValCheck(bdat, "Dir_Curve", setup->unknowna8, 2))) * mm::DEG_TO_RAD;
    unknown34 = Bdat::getValCheck(bdat, "Dis_Min", setup->unknowna8, 1);
    unknown35 = Bdat::getValCheck(bdat, "Dis_Max", setup->unknowna8, 1);
    unknown36 = Bdat::getValCheck(bdat, "fldEne_Param", setup->unknowna8, 1);
  }

  if (gmkInst != nullptr) {
    u8 *bdat = gmkInst->getBindedBdatFp();
    if (bdat != nullptr) {
      int index = gmkInst->unknown20.unknown18;
      unknown37 = Bdat::getValCheck(bdat, "party_flag", index, 1);
      if (Bdat::getMember(bdat, "noNaviMesh") != nullptr) {
        unknown38 = Bdat::getFlagVal(bdat, "flag", index, "noNaviMesh") != 0;
      }
    }
  }

  if (!unknown38) {
    u8 *bdat = GfDataBdat::getFP(BDAT_CHR_EN_ARRANGE);
    unknown38 = Bdat::getFlagVal(bdat, "Flag", setup->getEnArrangeID(), "NoNaviMesh") != 0;
  }

  if (gmkInst != nullptr && unknown37 != 0) {
    GfObjProperty *property = GfObjUtil::getProperty(unknown08.unknown08);
    if (property != nullptr) {
      GfObjPropertyEnemy *enemy = property->getEnemy();
      if (enemy != nullptr) {
        enemy->unknown150 = gmkInst->unknown20.unknown18;
      }
    }
  }

  createNaviMeshObj();
  createSquadNavi();
  createSensor();
  {
    GfEnemyFieldMoveSpeed::CreateInfo moveSpeedInfo;
    moveSpeedInfo.unknown00 = info.unknown08;
    unknown1d0.create(moveSpeedInfo);
  }
  {
    GfFieldLocalSteer::CreateInfo steerInfo;
    steerInfo.unknown10 = 0.5f;
    steerInfo.unknown00 = info.unknown08;
    steerInfo.unknown08 = info.unknown10 * 1.5f;
    steerInfo.unknown0c = info.unknown14 * 0.5f;
    steerInfo.unknown14 = false;
    steerInfo.unknown18 = &unknown5260;
    unknown200.create(steerInfo);
  }
  gmk::GmkRouteNavi *navi = getGmkRouteNavi();
  if (navi != nullptr) {
    navi->unknown68 = info.unknown10;
    navi->unknown6c = info.unknown14;
    {
      gmk::GmkRouteNavi::UpdateInfo updateInfo;
      updateInfo.position = unknown08.unknown00->getTransform().unknown00;
      navi->update(updateInfo);
    }
    unknownc0 = navi->unknown90;
    GfObjSetupEnemy *setupEnemy = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(info.unknown08)->unknown30);
    if (setupEnemy->unknown68 == 3 && setupEnemy->unknowna8 > 0) {
      GfFieldPitchRollController::CreateInfo pitchRollInfo;
      pitchRollInfo.unknown00 = info.unknown08;
      u8 *bdat = GfDataBdat::getFP(BDAT_FLD_ENACT_MOVE);
      u32 attribute = Bdat::getValCheck(bdat, "actMove_Atr", setupEnemy->unknowna8, 1);
      pitchRollInfo.unknown08.unknown00 = (attribute >> 2) & 1;
      pitchRollInfo.unknown08.unknown01 = (attribute >> 3) & 1;
      pitchRollInfo.unknown0a = (attribute >> 4) & 1;
      unknown5268.create(pitchRollInfo);
    }
  }

  switch (unknown08.unknown18) {
  case 0:
  case 2:
    unknown90 = true;
    break;
  case 1:
  case 3:
    unknown90 = false;
    break;
  }
}

f32 GfBehaviorEnemyField::getWalkSpeed() const {
  DataParamAcc dataParam(unknown08.unknown08);
  return dataParam.getSDataEnemy()->unknown49;
}

f32 GfBehaviorEnemyField::getRunSpeed() const {
  DataParamAcc dataParam(unknown08.unknown08);
  return dataParam.getSDataEnemy()->unknown4a;
}

gmk::GmkRouteNavi *GfBehaviorEnemyField::getGmkRouteNavi() const {
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown08.unknown08);
  if (gmkInst != nullptr && gmkInst->getGmkType() == gmk::GMK_TYPE_ROUTED_ENEMY) {
    return static_cast<gmk::GmkRoutedEnemy *>(gmkInst)->findRouteNavi(unknown08.unknown08);
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

  const mm::Vec3 &position = unknown08.unknown00->getTransform().unknown00;
  f32 dy = unknownc0.y - position.y;
  if (unknown08.unknown14 < dy) {
    return false;
  }

  f32 dx = unknownc0.x - position.x;
  f32 dz = unknownc0.z - position.z;
  if (unknown08.unknown18 != 3) {
    dy = 0.0f;
  }

  f32 distanceSq = dx * dx + dy * dy + dz * dz;
  return !(unknown08.unknown10 * unknown08.unknown10 < distanceSq);
}

void GfBehaviorEnemyField::getMoveDir(mm::Vec3 &direction) const {
  if (!getMoveVec(direction, unknown40)) {
    const mm::Vec3 &position = unknown08.unknown00->getTransform().unknown00;
    direction = unknownc0 - position;
    if (unknown08.unknown18 != 3) {
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
  unknown002();
  unknown50.dispose();
  disposeNaviMeshObj();
  unknown08 = CreateInfo();
}

fw::ColiMoveObject *GfBehaviorEnemyField::getColiObject() const {
  GfObjAcc acc(unknown08.unknown08);
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
  if (unknown08.unknown18 != 3 && !unknown38) {
    unknown40 = fw::NaviManager::get()->createObject();
    if (unknown40 != nullptr) {
      unknown40->setMeshNum(0);
      unknown40->unknown10 |= 2;
    }
  }
}

void GfBehaviorEnemyField::createSquadNavi() {
  unknown50.dispose();
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown08.unknown08);
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
    GF_OBJ_HANDLE *handle = unknown08.unknown08;
    info.unknown08 = handle;
    GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
    if (info.unknown00 != nullptr && info.unknown08 != INVALID_HANDLE) {
      unknown50.create(info);
    }
  }
}

void GfBehaviorEnemyField::createSensor() {
  unknown002();
  GfFieldEnemySensor::CreateInfo info;
  unknown08.unknown00->getTransform().unknown001(info.unknown00);
  GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(unknown08.unknown08)->unknown30);
  info.unknown40 = setup->unknown10;
  info.unknown44 = setup->m_enArrangeID;
  unknown08.unknown00->getGmkBattleLockInfo(info.unknown48, info.unknown4c);
  unknownd0.create(info);
}

void GfBehaviorEnemyField::disposeSquadNavi() { unknown50.dispose(); }

void GfBehaviorEnemyField::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknown40);
  unknown40 = nullptr;
}

void GfBehaviorEnemyField::update(f32 deltaTime) {
  if (unknown08.unknown00 == nullptr || unknown08.unknown08 == INVALID_HANDLE) {
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

  GfObjAcc acc(unknown08.unknown08);
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

  DataParamAcc dataParam(unknown08.unknown08);
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
    const mm::Vec3 &position = unknown08.unknown00->getTransform().unknown00;
    unknown40->setBeginPos(position);
    unknown40->setEndPos(unknownc0);
    f32 speed = unknown1d0.unknown10 * 0.2777778f;
    unknown40->setMoveSpd(speed * deltaTime);
    mm::Vec3 direction;
    getMoveDir(direction);
  }
}

void GfBehaviorEnemyField::updateSensor(f32 deltaTime) { unknownd0.update(unknown08.unknown08, *unknown08.unknown00); }

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
