#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd.h"
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

class GfComAsm;
class GfComBehaviorEnemy;

namespace enemy {

class StateFieldIdle : public GfStateBase {
  GF_STATE_CLASS(StateFieldIdle, GfComBehaviorEnemy)
  StateFieldIdle() : unknown18(0), unknown20(), unknown58(0.0f), unknown5c(0.0f), unknown60(nullptr) {}
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  void seqFlyInsectIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqOthersIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);

  u32 unknown18;                                                                   // Inferred role: move mode; original member name unknown.
  TFieldExecCmd<GfComAsm> unknown20;                                               // Inferred role: asm command; original member name unknown.
  f32 unknown58;                                                                   // Inferred role: idle time left; original member name unknown.
  f32 unknown5c;                                                                   // Inferred role: idle time; original member name unknown.
  void (StateFieldIdle::*unknown60)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(StateFieldIdle, unknown20) == 0x20, "");
static_assert(offsetof(StateFieldIdle, unknown58) == 0x58, "");
static_assert(offsetof(StateFieldIdle, unknown60) == 0x60, "");
static_assert(sizeof(StateFieldIdle) == 0x70, "");

} // namespace enemy
} // namespace gf
