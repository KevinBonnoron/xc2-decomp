#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_math/mm_vec3.h"
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

class StateFieldWaterIdleTurn : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterIdleTurn, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  u8 _18[0x20 - 0x18];
  mm::Vec3 inputDirection;
};

static_assert(offsetof(StateFieldWaterIdleTurn, inputDirection) == 0x20, "");
static_assert(sizeof(StateFieldWaterIdleTurn) == 0x30, "");

} // namespace pc
} // namespace gf
