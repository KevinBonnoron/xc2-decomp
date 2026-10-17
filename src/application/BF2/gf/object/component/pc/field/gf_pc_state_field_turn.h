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

class StateFieldTurn : public GfStateBase {
  GF_STATE_CLASS(StateFieldTurn, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  bool isWalkTurn;
  u8 _19[0x20 - 0x19];
  mm::Vec3 inputDirection;
};

static_assert(offsetof(StateFieldTurn, isWalkTurn) == 0x18, "");
static_assert(offsetof(StateFieldTurn, inputDirection) == 0x20, "");
static_assert(sizeof(StateFieldTurn) == 0x30, "");

} // namespace pc
} // namespace gf
