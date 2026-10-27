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
class GfComBehaviorEnemy;

namespace enemy {

class StateFieldBlade : public GfStateBase {
  GF_STATE_CLASS(StateFieldBlade, GfComBehaviorEnemy)
  StateFieldBlade() : unknown18(), unknown50(nullptr) {}
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                                // Inferred role: asm command; original member name unknown.
  void (StateFieldBlade::*unknown50)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(StateFieldBlade, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldBlade, unknown50) == 0x50, "");
static_assert(sizeof(StateFieldBlade) == 0x60, "");

} // namespace enemy
} // namespace gf
