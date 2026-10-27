#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorEnemy;

namespace enemy {

class StateFieldSpawn : public GfStateBase {
  GF_STATE_CLASS(StateFieldSpawn, GfComBehaviorEnemy)
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
};

static_assert(sizeof(StateFieldSpawn) == 0x18, "");

} // namespace enemy
} // namespace gf
