#include "gf/object/component/enemy/gf_behavior_enemy_field.h"

#include "fw/fw_transform.h"
#include "gf/data/gf_data_enemy.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/enemy/gf_beh_field_owner.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_routed_enemy.h"
#include "gmk/gmk_manager.h"

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

} // namespace gf
