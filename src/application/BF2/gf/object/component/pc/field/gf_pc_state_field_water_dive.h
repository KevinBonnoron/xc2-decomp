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

class GfComBehaviorPc;

namespace pc {

class StateFieldWaterDive : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterDive, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  void recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
};

static_assert(sizeof(StateFieldWaterDive) == 0x18, "");

} // namespace pc
} // namespace gf
