#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "gf/gf_state.h"
#include "types.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;
class GfComBehaviorNpc;

namespace npc {

class StateWalk : public ai::State {
  GF_STATE_CLASS(StateWalk, GfComBehaviorNpc)
  StateWalk() : unknown18(), unknown50(nullptr), unknown60(0.0f) {}
  void updateGoalPos(GfComBehaviorNpc &behavior);
  void enter(GfComBehaviorNpc *behavior, ai::State *previous);
  void leave(GfComBehaviorNpc *behavior, ai::State *next);
  void update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqWaitMoveEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqInterpPosRotToGoal(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                        // Inferred role: asm command; original member name unknown.
  void (StateWalk::*unknown50)(GfComBehaviorNpc &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  f32 unknown60;                                                            // Inferred role: interpolation time; original member name unknown.
};

static_assert(offsetof(StateWalk, unknown18) == 0x18, "");
static_assert(offsetof(StateWalk, unknown50) == 0x50, "");
static_assert(offsetof(StateWalk, unknown60) == 0x60, "");
static_assert(sizeof(StateWalk) == 0x68, "");

} // namespace npc
} // namespace gf
