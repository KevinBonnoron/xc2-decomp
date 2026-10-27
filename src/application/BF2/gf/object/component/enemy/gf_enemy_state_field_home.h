#pragma once
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

class GfComBehaviorEnemy;

namespace enemy {

class StateFieldHome : public GfStateBase {
  GF_STATE_CLASS(StateFieldHome, GfComBehaviorEnemy)
  StateFieldHome();
  static bool isCondMatch(const GfComBehaviorEnemy &behavior);
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);

  u8 unknown18[0x68 - 0x18]; // Inferred role: members not reconstructed yet; the size comes from Hfsm::registerState<StateFieldHome>.
};

static_assert(sizeof(StateFieldHome) == 0x68, "");

} // namespace enemy
} // namespace gf
