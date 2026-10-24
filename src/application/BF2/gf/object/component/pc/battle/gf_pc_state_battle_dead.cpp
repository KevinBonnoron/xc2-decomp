#include "gf/object/component/pc/battle/gf_pc_state_battle_dead.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

bool StateBattleDead::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  unknown22 = false;
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleDead::Leave(GfComBehaviorPc *behavior, ai::State *next) { unknown22 = false; }

} // namespace pc
} // namespace gf
