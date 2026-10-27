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

class StateFieldHome : public GfStateBase {
  GF_STATE_CLASS(StateFieldHome, GfComBehaviorEnemy)
  StateFieldHome();
  static bool isCondMatch(const GfComBehaviorEnemy &behavior);
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                               // Inferred role: asm command; original member name unknown.
  void (StateFieldHome::*unknown50)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  bool unknown60;                                                                  // Inferred role: destroy requested; original member name unknown.
  f32 unknown64;                                                                   // Inferred role: time since the enemy started to go home; original member name unknown.
};

static_assert(offsetof(StateFieldHome, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldHome, unknown50) == 0x50, "");
static_assert(offsetof(StateFieldHome, unknown60) == 0x60, "");
static_assert(offsetof(StateFieldHome, unknown64) == 0x64, "");
static_assert(sizeof(StateFieldHome) == 0x68, "");

} // namespace enemy
} // namespace gf
