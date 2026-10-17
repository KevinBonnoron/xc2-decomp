#include "gf/object/component/pc/field/gf_pc_state_field_access.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace gf {
namespace pc {

void StateFieldAccess::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  if (__builtin_strcmp(comAsm->getStateName(ANIM_LAYER_BASE), "S_idle") == 0 && !GfGameManager::isPlayerPause()) {
    reqState(STATE_ID_FIELD_IDLE);
  }
}

} // namespace pc
} // namespace gf
