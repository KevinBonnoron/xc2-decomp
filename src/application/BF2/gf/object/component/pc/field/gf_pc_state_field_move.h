#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_math/mm_vec2.h"
#include "mm_mtl/fixed_queue.h"
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

  u8 _18[0x20 - 0x18];
  mm::mtl::FixedQueue<mm::Vec2, 2> unknown20; // Inferred role: direction queue; original member name unknown.
};

static_assert(offsetof(StateFieldMove, unknown20) == 0x20, "");
static_assert(sizeof(StateFieldMove) == 0x50, "");

} // namespace pc
} // namespace gf
