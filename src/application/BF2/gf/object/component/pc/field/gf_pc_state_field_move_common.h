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

class StateFieldMoveCommon : public GfStateBase {
  GF_STATE_CLASS(StateFieldMoveCommon, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);

  u32 noInputFrameCount;
  u8 _1c[0x20 - 0x1c];
};

static_assert(offsetof(StateFieldMoveCommon, noInputFrameCount) == 0x18, "");
static_assert(sizeof(StateFieldMoveCommon) == 0x20, "");

} // namespace pc
} // namespace gf
