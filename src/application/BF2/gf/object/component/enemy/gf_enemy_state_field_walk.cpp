#include "gf/object/component/enemy/gf_enemy_state_field_walk.h"

#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gmk/gmk_base.h"
#include "gmk/gmk_manager.h"

namespace gf {
namespace enemy {

bool StateFieldWalk::isCondMatch(const GfComBehaviorEnemy &behavior) {
  gmk::AGmkBase *gmkInst = behavior.getBindedGmkInst();
  return gmkInst != nullptr && static_cast<u32>(gmkInst->getGmkType()) <= gmk::GMK_TYPE_ROUTED_ENEMY;
}

void StateFieldWalk::leave(GfComBehaviorEnemy *behavior, ai::State *next) { behavior->unknown54e1 = false; }

bool StateFieldWalk::has_move_fly_ON() const { return (unknown18 >> 5) & 1; }

} // namespace enemy
} // namespace gf
