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
class GfComBehaviorNpc;

namespace npc {

class StateIdle : public ai::State {
  GF_STATE_CLASS(StateIdle, GfComBehaviorNpc)
  StateIdle() : unknown18() {}
  void enter(GfComBehaviorNpc *behavior, ai::State *previous);
  void leave(GfComBehaviorNpc *behavior, ai::State *next);
  void update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18; // Inferred role: asm command; original member name unknown.
};

static_assert(offsetof(StateIdle, unknown18) == 0x18, "");
static_assert(sizeof(StateIdle) == 0x50, "");

} // namespace npc
} // namespace gf
