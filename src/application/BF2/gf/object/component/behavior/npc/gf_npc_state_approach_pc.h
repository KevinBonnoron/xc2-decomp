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
class GfComBehaviorNpc;

namespace npc {

class StateApproachPc : public GfStateBase {
  GF_STATE_CLASS(StateApproachPc, GfComBehaviorNpc)
  StateApproachPc() : unknown18(), unknown50(nullptr) {}
  void enter(GfComBehaviorNpc *behavior, ai::State *previous);
  void leave(GfComBehaviorNpc *behavior, ai::State *next);
  void update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info);
  void seqTurnPc(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqApproachPc(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                              // Inferred role: asm command; original member name unknown.
  void (StateApproachPc::*unknown50)(GfComBehaviorNpc &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(StateApproachPc, unknown18) == 0x18, "");
static_assert(offsetof(StateApproachPc, unknown50) == 0x50, "");
static_assert(sizeof(StateApproachPc) == 0x60, "");

} // namespace npc
} // namespace gf
