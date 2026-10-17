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

class StateFieldMove : public GfStateBase {
  GF_STATE_CLASS(StateFieldMove, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  StateFieldMove() : directionQueueSize(0), directionQueueFront(0) {}

  u8 _18[0x20 - 0x18];
  // FixedQueue<mm::Vec2, 2> of the game, whose mm::Vec2 is 16 bytes wide.
  u8 directionQueue[0x40 - 0x20];
  size_t directionQueueSize;
  size_t directionQueueFront;
};

static_assert(offsetof(StateFieldMove, directionQueue) == 0x20, "");
static_assert(offsetof(StateFieldMove, directionQueueSize) == 0x40, "");
static_assert(sizeof(StateFieldMove) == 0x50, "");

} // namespace pc
} // namespace gf
