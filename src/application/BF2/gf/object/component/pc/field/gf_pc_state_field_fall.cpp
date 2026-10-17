#include "gf/object/component/pc/field/gf_pc_state_field_fall.h"

#include "ai/ai_state.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

namespace gf {
namespace pc {

void StateFieldFall::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  for (ai::State *state = previous; state != nullptr; state = state->childState) {
    if (state->stateID == STATE_ID_FIELD_WALL) {
      StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE_FALL, true);
      return;
    }
  }
}

void StateFieldFall::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE_FALL, false);
  if (next == nullptr || next->stateID == STATE_ID_FIELD_LAND) {
    return;
  }
  StateUtilField::notifyJumpEnd(*behavior);
}

} // namespace pc
} // namespace gf
