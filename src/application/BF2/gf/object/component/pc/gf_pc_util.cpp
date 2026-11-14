#include "gf/object/component/pc/gf_pc_util.h"

#include "ai/ai_state.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

bool isWallState(ai::State *state) {
  while (state != nullptr) {
    if (state->unknown08 == STATE_ID_UNKNOWN_38) {
      return true;
    }

    state = state->unknown10;
  }

  return false;
}

} // namespace pc
} // namespace gf
