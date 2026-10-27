#include "gf/object/component/enemy/gf_enemy_state_field_walk.h"

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route_navi.h"

namespace gf {
namespace enemy {

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  return gmkInst != nullptr && static_cast<u32>(gmkInst->getGmkType()) <= gmk::GMK_TYPE_ROUTED_ENEMY;
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

} // namespace enemy
} // namespace gf
