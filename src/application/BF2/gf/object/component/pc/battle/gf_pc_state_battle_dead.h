#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/pc/battle/gf_pc_state_battle_base.h"

namespace gf {

class GfComBehaviorPc;

namespace pc {

class StateBattleDead : public StateBattleActionBase {
  GF_STATE_CLASS(StateBattleDead, GfComBehaviorPc)
  bool Enter(GfComBehaviorPc *behavior, ai::State *previous) override;
  void Leave(GfComBehaviorPc *behavior, ai::State *next) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) override;

  bool isDeadNotified;
};

static_assert(offsetof(StateBattleDead, isDeadNotified) == 0x22, "");
static_assert(sizeof(StateBattleDead) == 0x28, "");

} // namespace pc
} // namespace gf
