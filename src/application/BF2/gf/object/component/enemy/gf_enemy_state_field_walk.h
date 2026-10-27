#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd.h"
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_math/mm_vec3.h"
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

class StateFieldWalk : public GfStateBase {
  GF_STATE_CLASS(StateFieldWalk, GfComBehaviorEnemy)
  StateFieldWalk()
      : unknown18(0), unknown19(false), unknown1c(0), unknown20(), unknown58(nullptr), unknown68(0.0f), unknown70(mm::Vec3::zero), unknown80(-1), unknown84(-1), unknown88(false), unknown8c(0),
        unknown90(0), unknown94(0.0f), unknown98(5.0f), unknown9c(0.0f) {}
  static bool isCondMatch(const GfComBehaviorEnemy &behavior);
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  bool has_move_fly_ON() const;
  bool canLotteryMoveSpeed(GfComBehaviorEnemy &behavior) const;
  void updateRouteNavi(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqIdleInfinit(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitSpecialEndAtRoutePoint(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitSyncLoco(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);
  void seqWaitTurnEnd(GfComBehaviorEnemy &behavior, const fw::UpdateInfo &info);

  u8 unknown18;                                                                    // Inferred role: actMove_Atr of BDAT_FLD_ENACT_MOVE; original member name unknown.
  bool unknown19;                                                                  // Role and original member name unknown.
  u32 unknown1c;                                                                   // Role and original member name unknown.
  TFieldExecCmd<GfComAsm> unknown20;                                               // Inferred role: asm command; original member name unknown.
  void (StateFieldWalk::*unknown58)(GfComBehaviorEnemy &, const fw::UpdateInfo &); // Inferred role: sequence; original member name unknown.
  f32 unknown68;                                                                   // Role and original member name unknown.
  mm::Vec3 unknown70;                                                              // Inferred role: goal position; original member name unknown.
  int unknown80;                                                                   // Role and original member name unknown.
  int unknown84;                                                                   // Role and original member name unknown.
  bool unknown88;                                                                  // Role and original member name unknown.
  u32 unknown8c;                                                                   // Role and original member name unknown.
  u32 unknown90;                                                                   // Role and original member name unknown.
  f32 unknown94;                                                                   // Role and original member name unknown.
  f32 unknown98;                                                                   // Role and original member name unknown.
  f32 unknown9c;                                                                   // Role and original member name unknown.
};

static_assert(offsetof(StateFieldWalk, unknown20) == 0x20, "");
static_assert(offsetof(StateFieldWalk, unknown58) == 0x58, "");
static_assert(offsetof(StateFieldWalk, unknown70) == 0x70, "");
static_assert(offsetof(StateFieldWalk, unknown80) == 0x80, "");
static_assert(offsetof(StateFieldWalk, unknown9c) == 0x9c, "");
static_assert(sizeof(StateFieldWalk) == 0xa0, "");

} // namespace enemy
} // namespace gf
