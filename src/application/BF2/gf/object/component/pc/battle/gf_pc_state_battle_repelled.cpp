#include "gf/object/component/pc/battle/gf_pc_state_battle_repelled.h"

#include "gf/object/component/pc/gf_pc_state_util.h"

namespace gf {
namespace pc {

bool StateBattleRepelled::Enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setFallDamageDisable(*behavior, false);
  return StateBattleActionBase::Enter(behavior, previous);
}

void StateBattleRepelled::Leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateBattleRepelled::Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  StateBattleActionBase::Update(character, behavior, info);
}

} // namespace pc
} // namespace gf
