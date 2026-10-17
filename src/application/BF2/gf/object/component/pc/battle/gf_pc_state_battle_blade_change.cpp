#include "gf/object/component/pc/battle/gf_pc_state_battle_blade_change.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

bool StateBattleBladeChange::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleBladeChange::Leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateBattleBladeChange::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  StateBattleActionBase::Update(character, behavior, info);
}

} // namespace pc
} // namespace gf
