#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorPc;

namespace pc {

class StateFieldIdleTurn : public GfStateBase {
  GF_STATE_CLASS(StateFieldIdleTurn, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  u8 _18[0x30 - 0x18];
};

static_assert(sizeof(StateFieldIdleTurn) == 0x30, "");

} // namespace pc
} // namespace gf
