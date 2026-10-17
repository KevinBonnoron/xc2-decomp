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

class StateFieldWallAdsorptionUnderGround : public GfStateBase {
  GF_STATE_CLASS(StateFieldWallAdsorptionUnderGround, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  u8 _18[0x40 - 0x18];
};

static_assert(sizeof(StateFieldWallAdsorptionUnderGround) == 0x40, "");

} // namespace pc
} // namespace gf
