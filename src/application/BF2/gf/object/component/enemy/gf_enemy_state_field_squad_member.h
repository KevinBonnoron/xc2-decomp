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

class StateFieldSquadMember : public GfStateBase {
  GF_STATE_CLASS(StateFieldSquadMember, GfComBehaviorEnemy)
  StateFieldSquadMember();
  static bool isCondMatch(const GfComBehaviorEnemy &behavior);
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);

  void seqUpdateIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                                      // Inferred role: asm command; original member name unknown.
  void (StateFieldSquadMember::*unknown50)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  bool unknown60;                                                                         // Inferred role: the enemy is at its position in the squad; original member name unknown.
  f32 unknown64;                                                                          // Inferred role: distance to the position in the squad; original member name unknown.
};

static_assert(offsetof(StateFieldSquadMember, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldSquadMember, unknown50) == 0x50, "");
static_assert(offsetof(StateFieldSquadMember, unknown60) == 0x60, "");
static_assert(offsetof(StateFieldSquadMember, unknown64) == 0x64, "");
static_assert(sizeof(StateFieldSquadMember) == 0x68, "");

} // namespace enemy
} // namespace gf
