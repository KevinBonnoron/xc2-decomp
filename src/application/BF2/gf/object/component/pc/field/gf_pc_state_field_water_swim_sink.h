#pragma once
#include <stddef.h>

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

class GfComBehaviorPc;

namespace pc {

class StateFieldWaterSwimSink : public GfStateBase {
  GF_STATE_CLASS(StateFieldWaterSwimSink, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  f32 elapsedTime;
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(StateFieldWaterSwimSink, elapsedTime) == 0x18, "");
static_assert(sizeof(StateFieldWaterSwimSink) == 0x20, "");

} // namespace pc
} // namespace gf
