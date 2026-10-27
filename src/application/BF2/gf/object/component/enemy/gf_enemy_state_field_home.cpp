#include "gf/object/component/enemy/gf_enemy_state_field_home.h"

#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_manager.h"
#include "gf/object/gf_obj_setup.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_acc.h"
#include "gmk/gmk_manager.h"
#include "gmk/gmk_route_navi.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/rtti.h"

namespace gf {
namespace enemy {

StateFieldHome::StateFieldHome() : unknown18(), unknown50(nullptr), unknown60(false), unknown64(0.0f) {}

bool StateFieldHome::isCondMatch(const GfComBehaviorEnemy &behavior) { return gmk::isPlayerExist(); }

void StateFieldHome::leave(GfComBehaviorEnemy *behavior, ai::State *next) {}

void StateFieldHome::update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {
  if (!unknown60) {
    unknown64 = info.unknown04 + unknown64;
    if (unknown64 > 10.0f) {
      unknown60 = true;
      SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj *>(behavior->unknown08)->unknownf8, 1.0f, 0);
    }
  }

  if (behavior->isStateCondMatch(STATE_ID_UNKNOWN_1) && behavior->unknown140.isArrivedToGoal() && !unknown60) {
    unknown60 = true;
    SCOM_DESTROY_GAME_OBJ::create(static_cast<GfObj *>(behavior->unknown08)->unknownf8, 1.0f, 0);
  }

  if (unknown50) {
    (this->*unknown50)(*behavior, info);
  }
}

void StateFieldHome::seqWaitIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  unknown18.update(info.unknown04);
  if (unknown18.unknown34 && unknown18.unknown35) {
    unknown50 = &StateFieldHome::seqInitHomePos;
  }
}

void StateFieldHome::seqInitHomePos(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info) {
  gmk::GmkRouteNavi *navi = behavior.unknown140.getGmkRouteNavi();
  mm::Vec3 position;
  if (navi == nullptr) {
    GfObjSetupEnemy *setup = mm::mtl::dynamicCast<GfObjSetupEnemy>(GfObjManager::getObjInfo(static_cast<GfObj *>(behavior.unknown08)->unknownf8)->unknown30);
    position = setup->unknown20;
  } else {
    if (!navi->unknown00.isValid()) {
      return;
    }

    if (!navi->unknown28.isValid()) {
      return;
    }

    const mm::Vec3 &current = behavior.getTransform().unknown00;
    gmk::GmkRouteNavi::UpdateInfo updateInfo;
    updateInfo.position = current;
    navi->update(updateInfo);
    if (!navi->unknown80) {
      return;
    }

    position = navi->unknown90;
  }

  behavior.unknown140.unknownc0 = position;
  behavior.execTurnCmdToGoal();
  unknown50 = &StateFieldHome::seqWaitTurnEnd;
}

} // namespace enemy
} // namespace gf
