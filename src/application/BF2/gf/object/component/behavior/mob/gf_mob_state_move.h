#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/field/gf_field_exec_cmd.h"
#include "gf/gf_state.h"

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;
class GfComBehaviorMob;

namespace mob {

class StateMove : public ai::State {
  GF_STATE_CLASS(StateMove, GfComBehaviorMob)
  StateMove() : unknown18(), unknown50(nullptr) {}
  static bool isCondMatch(const GfComBehaviorMob &behavior);
  void enter(GfComBehaviorMob *behavior, ai::State *previous);
  void leave(GfComBehaviorMob *behavior, ai::State *next);
  void update(GfComBehaviorMob *behavior, const fw::UpdateInfo &info);
  void seqUpdateMove(GfComBehaviorMob &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorMob &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                        // Inferred role: asm command; original member name unknown.
  void (StateMove::*unknown50)(GfComBehaviorMob &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(StateMove, unknown18) == 0x18, "");
static_assert(offsetof(StateMove, unknown50) == 0x50, "");
static_assert(sizeof(StateMove) == 0x60, "");

} // namespace mob
} // namespace gf
