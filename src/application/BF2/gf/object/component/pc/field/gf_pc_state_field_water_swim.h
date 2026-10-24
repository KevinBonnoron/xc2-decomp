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

class StateFieldWaterSwim : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterSwim, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  StateFieldWaterSwim() : unknown40(0), unknown48(0) {}

  u8 _18[0x20 - 0x18];
  // FixedQueue<mm::Vec2, 2> of the game, whose mm::Vec2 is 16 bytes wide.
  u8 unknown20[0x40 - 0x20]; // Inferred role: direction queue; original member name unknown.
  size_t unknown40;          // Inferred role: direction queue size; original member name unknown.
  size_t unknown48;          // Inferred role: direction queue front; original member name unknown.
};

static_assert(offsetof(StateFieldWaterSwim, unknown20) == 0x20, "");
static_assert(offsetof(StateFieldWaterSwim, unknown40) == 0x40, "");
static_assert(sizeof(StateFieldWaterSwim) == 0x50, "");

} // namespace pc
} // namespace gf
