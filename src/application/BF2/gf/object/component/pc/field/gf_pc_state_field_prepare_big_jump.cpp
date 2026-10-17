#include "gf/object/component/pc/field/gf_pc_state_field_prepare_big_jump.h"

#include "gf/game/gf_game_manager.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

void StateFieldPrepareBigJump::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isPlayerPause()) {
    reqState(STATE_ID_FIELD_IDLE);
  }
}

} // namespace pc
} // namespace gf
