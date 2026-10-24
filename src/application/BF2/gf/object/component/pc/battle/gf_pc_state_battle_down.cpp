#include "gf/object/component/pc/battle/gf_pc_state_battle_down.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

bool StateBattleDown::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleDown::Leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateBattleDown::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) { StateBattleActionBase::Update(character, behavior, info); }

} // namespace pc
} // namespace gf
