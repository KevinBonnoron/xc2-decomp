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
class GfComBehaviorMob;

namespace mob {

class StateSquadMember : public GfStateBase {
  GF_STATE_CLASS(StateSquadMember, GfComBehaviorMob)
  StateSquadMember() : unknown18(0.5f), unknown20(), unknown58(nullptr), unknown68(false) {}
  static bool isCondMatch(const GfComBehaviorMob &behavior);
  void enter(GfComBehaviorMob *behavior, ai::State *previous);
  void leave(GfComBehaviorMob *behavior, ai::State *next);
  void update(GfComBehaviorMob *behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(GfComBehaviorMob &behavior, const fw::UpdateInfo &info);
  void seqUpdateIdle(GfComBehaviorMob &behavior, const fw::UpdateInfo &info);

  f32 unknown18;                                                                   // Inferred role: arrival distance; original member name unknown.
  TFieldExecCmd<GfComAsm> unknown20;                                               // Inferred role: asm command; original member name unknown.
  void (StateSquadMember::*unknown58)(GfComBehaviorMob &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  bool unknown68;                                                                  // Inferred role: the squad position moved; original member name unknown.
};

static_assert(offsetof(StateSquadMember, unknown18) == 0x18, "");
static_assert(offsetof(StateSquadMember, unknown20) == 0x20, "");
static_assert(offsetof(StateSquadMember, unknown58) == 0x58, "");
static_assert(offsetof(StateSquadMember, unknown68) == 0x68, "");
static_assert(sizeof(StateSquadMember) == 0x70, "");

} // namespace mob
} // namespace gf
