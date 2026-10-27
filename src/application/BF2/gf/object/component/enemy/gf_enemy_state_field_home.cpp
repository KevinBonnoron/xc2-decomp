#include "gf/object/component/enemy/gf_enemy_state_field_home.h"

#include "fw/fw_update_info.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/gf_obj.h"
#include "gf/scom/gf_scom_obj.h"
#include "gmk/gmk_manager.h"

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

} // namespace enemy
} // namespace gf
