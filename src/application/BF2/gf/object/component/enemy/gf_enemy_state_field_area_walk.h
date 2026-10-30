#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd.h"
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "types.h"

namespace ai {
class State;
} // namespace ai

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComAsm;
class GfComBehaviorEnemy;

namespace enemy {

class StateFieldAreaWalk : public GfStateBase {
  GF_STATE_CLASS(StateFieldAreaWalk, GfComBehaviorEnemy)
  StateFieldAreaWalk() : unknown18(0), unknown1c(false), unknown20(), unknown58(nullptr), unknown68(0.0f) {}
  static bool isCondMatch(const GfComBehaviorEnemy &behavior);
  bool getGoalPosRandom(mm::Vec3 &position, const GfComBehaviorEnemy &behavior) const;
  bool getGoalPosWater(mm::Vec3 &position, const GfComBehaviorEnemy &behavior) const;
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  void seqChangeState(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqInitGoalPos(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqMoveToGoal(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitMoveEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);

  u32 unknown18;                                                                       // Inferred role: move mode; original member name unknown.
  bool unknown1c;                                                                      // Inferred role: circle direction; original member name unknown.
  TFieldExecCmd<GfComAsm> unknown20;                                                   // Inferred role: asm command; original member name unknown.
  void (StateFieldAreaWalk::*unknown58)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  f32 unknown68;                                                                       // Role and original member name unknown.
};

static_assert(offsetof(StateFieldAreaWalk, unknown20) == 0x20, "");
static_assert(offsetof(StateFieldAreaWalk, unknown58) == 0x58, "");
static_assert(offsetof(StateFieldAreaWalk, unknown68) == 0x68, "");
static_assert(sizeof(StateFieldAreaWalk) == 0x70, "");

} // namespace enemy
} // namespace gf
