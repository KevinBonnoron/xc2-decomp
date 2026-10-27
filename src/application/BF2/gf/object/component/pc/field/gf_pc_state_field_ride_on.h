#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorPc;

namespace pc {

class StateFieldRideOn : public GfStateBase {
  GF_STATE_CLASS(StateFieldRideOn, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;

  mm::mtl::FixedQueue<mm::mtl::FixStr<32>, 8> unknown18; // Inferred role: commands; original member name unknown.
};

static_assert(offsetof(StateFieldRideOn, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldRideOn) == 0x148, "");

} // namespace pc
} // namespace gf
