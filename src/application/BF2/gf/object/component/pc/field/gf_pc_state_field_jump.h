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

class StateFieldJump : public GfStateBase {
  GF_STATE_CLASS(StateFieldJump, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  f32 unknown18;  // Inferred role: elapsed time; original member name unknown.
  bool unknown1c; // Inferred role: entered from the slide move state; original member name unknown.
  f32 unknown20;  // Inferred role: last fall speed; original member name unknown.
  u8 _24[0x28 - 0x24];
};

static_assert(offsetof(StateFieldJump, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldJump, unknown1c) == 0x1c, "");
static_assert(offsetof(StateFieldJump, unknown20) == 0x20, "");
static_assert(sizeof(StateFieldJump) == 0x28, "");

} // namespace pc
} // namespace gf
