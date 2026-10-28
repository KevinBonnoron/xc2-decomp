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

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComAsm;
class GfComBehaviorEnemy;
struct GF_OBJ_HANDLE;

namespace enemy {

class StateFieldBlade : public GfStateBase {
  GF_STATE_CLASS(StateFieldBlade, GfComBehaviorEnemy)
  StateFieldBlade() : unknown18(), unknown50(nullptr) {}
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  void seqWaitIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqIdle(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqMoveToDriver(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  bool getOwnerDriverPos(mm::Vec3 &position, GF_OBJ_HANDLE *handle) const;
  f32 getEnRadius(const GfComBehaviorEnemy &behavior) const;

  TFieldExecCmd<GfComAsm> unknown18;                                                // Inferred role: asm command; original member name unknown.
  void (StateFieldBlade::*unknown50)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
};

static_assert(offsetof(StateFieldBlade, unknown18) == 0x18, "");
static_assert(offsetof(StateFieldBlade, unknown50) == 0x50, "");
static_assert(sizeof(StateFieldBlade) == 0x60, "");

} // namespace enemy
} // namespace gf
