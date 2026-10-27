#include "gf/object/component/enemy/gf_enemy_state_field_area_walk.h"

#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_enemy/gmk_enemy.h"

namespace gf {
namespace enemy {

bool StateFieldAreaWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  if (gmkInst == nullptr || gmkInst->getGmkType() != gmk::GmkEnemy::GMK_TYPE) {
    return false;
  }

  return !(static_cast<gmk::GmkEnemy *>(gmkInst)->getData()->unknown00 <= behavior.unknown140.unknown18);
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

} // namespace enemy
} // namespace gf
