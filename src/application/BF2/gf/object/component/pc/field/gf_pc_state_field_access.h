#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorPc;
struct GF_OBJ_HANDLE;

namespace pc {

class StateFieldAccess : public GfStateBase {
  GF_STATE_CLASS(StateFieldAccess, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  GF_OBJ_HANDLE *unknown18; // Inferred role: accessed object; original member name unknown.
};

static_assert(offsetof(StateFieldAccess, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldAccess) == 0x20, "");

} // namespace pc
} // namespace gf
