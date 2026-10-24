#include "gf/object/component/pc/field/gf_pc_state_field_jump.h"

#include "ai/ai_state.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  if (next == nullptr || next->unknown08 == STATE_ID_FIELD_LAND || next->unknown08 == STATE_ID_FIELD_FALL) {
    return;
  }
  StateUtilField::notifyJumpEnd(*behavior);
}

} // namespace pc
} // namespace gf
