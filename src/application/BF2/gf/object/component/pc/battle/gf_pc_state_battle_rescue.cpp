#include "gf/object/component/pc/battle/gf_pc_state_battle_rescue.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

bool StateBattleRescue::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleRescue::Leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateBattleRescue::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) { StateBattleActionBase::Update(character, behavior, info); }

} // namespace pc
} // namespace gf
