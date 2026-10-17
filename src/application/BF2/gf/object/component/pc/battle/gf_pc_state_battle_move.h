#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_base.h"

namespace gf {

class GfComBehaviorPc;

namespace pc {

class StateBattleMove : public StateBattleActionBase {
  GF_STATE_CLASS(StateBattleMove, GfComBehaviorPc)
  bool Enter(GfComBehaviorPc *behavior, ai::State *previous) override;
  void Leave(GfComBehaviorPc *behavior, ai::State *next) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) override;
};

} // namespace pc
} // namespace gf
