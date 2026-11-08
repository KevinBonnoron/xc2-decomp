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

class StateTalk : public ai::State {
  GF_STATE_CLASS(StateTalk, GfComBehaviorNpc)
  StateTalk();
  void enter(GfComBehaviorNpc *behavior, ai::State *previous);
  void leave(GfComBehaviorNpc *behavior, ai::State *next);
  void update(GfComBehaviorNpc *behavior, const fw::UpdateInfo &info);
  void setCollideNpcMob(bool isCollide);
  void seqWaitTalkEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorNpc &behavior, const fw::UpdateInfo &info);

  TFieldExecCmd<GfComAsm> unknown18;                                        // Inferred role: asm command; original member name unknown.
  void (StateTalk::*unknown50)(GfComBehaviorNpc &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  bool unknown60;                                                           // Inferred role: entered from the idle state; original member name unknown.
};

static_assert(offsetof(StateTalk, unknown18) == 0x18, "");
static_assert(offsetof(StateTalk, unknown50) == 0x50, "");
static_assert(offsetof(StateTalk, unknown60) == 0x60, "");
static_assert(sizeof(StateTalk) == 0x68, "");

} // namespace npc
} // namespace gf
