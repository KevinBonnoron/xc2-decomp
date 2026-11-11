#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd.h"
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;
class GfComBehaviorMob;

namespace mob {

class StateIdle : public GfStateBase {
  GF_STATE_CLASS(StateIdle, GfComBehaviorMob)
  StateIdle() : unknown18() {}
  void enter(GfComBehaviorMob *behavior, ai::State *previous);
  void leave(GfComBehaviorMob *behavior, ai::State *next);
  void update(GfComBehaviorMob *behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18; // Inferred role: asm command; original member name unknown.
};

static_assert(offsetof(StateIdle, unknown18) == 0x18, "");
static_assert(sizeof(StateIdle) == 0x50, "");

} // namespace mob
} // namespace gf
