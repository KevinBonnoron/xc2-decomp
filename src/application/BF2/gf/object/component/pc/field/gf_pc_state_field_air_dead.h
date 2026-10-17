#pragma once
#include <stddef.h>

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

class StateFieldAirDead : public GfStateBase {
  GF_STATE_CLASS(StateFieldAirDead, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  bool isDownMotion;
  u8 _19[0x20 - 0x19];
};

static_assert(offsetof(StateFieldAirDead, isDownMotion) == 0x18, "");
static_assert(sizeof(StateFieldAirDead) == 0x20, "");

} // namespace pc
} // namespace gf
