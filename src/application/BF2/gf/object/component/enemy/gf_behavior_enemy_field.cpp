// Same order as in the game executable: the sensor is defined before the field behavior in the same unit.
// clang-format off
#include "gf/field/gf_field_enemy_sensor.cpp"
// clang-format on
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "framework/coli/coli_object.h"
#include "framework/navi/navi_manager.h"
#include "fw/fw_transform.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/enemy/gf_beh_field_owner.h"
#include "gf/object/component/gf_com_collider.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_acc.h"
#include "gf/object/gf_obj_handle.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/object/gf_obj_util.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_manager.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/vector.h"

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

void GfBehaviorEnemyField::createSquadNavi() {
  unknown50.dispose();
  gmk::AGmkBase *gmkInst = gmk::getBindedGmkInst(unknown10);
  if (gmkInst != nullptr) {
    gmk::GmkSquadNavi::CreateInfo info;
    gmk::GmkSquad *squad = nullptr;
    switch (gmkInst->getGmkType()) {
    case gmk::GMK_TYPE_ENEMY:
      squad = static_cast<gmk::GmkEnemy *>(gmkInst)->unknown48.unknown150;
      break;
    case gmk::GMK_TYPE_ROUTED_ENEMY:
      squad = static_cast<gmk::GmkRoutedEnemy *>(gmkInst)->unknown50.unknown150;
      break;
    default:
      break;
    }
    info.unknown00 = squad;
    GF_OBJ_HANDLE *handle = unknown10;
    info.unknown08 = handle;
    GfObjUtil::getObjSetup<GfObjSetupEnemy>(handle);
    if (squad != nullptr && handle != INVALID_HANDLE) {
      unknown50.create(info);
    }
  }
}

void GfBehaviorEnemyField::disposeSquadNavi() { unknown50.dispose(); }

void GfBehaviorEnemyField::disposeNaviMeshObj() {
  fw::NaviManager::get()->releaseObject(unknown40);
  unknown40 = nullptr;
}

void GfBehaviorEnemyField::updateSensor(f32 deltaTime) { unknownd0.update(unknown10, *unknown08); }

void GfBehaviorEnemyField::updatePitchRollController() {
  gmk::GmkRouteNavi *navi = getGmkRouteNavi();
  if (navi != nullptr) {
    unknown5268.update(*navi);
  }
}

} // namespace gf
