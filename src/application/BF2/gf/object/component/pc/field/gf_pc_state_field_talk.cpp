#include "gf/object/component/pc/field/gf_pc_state_field_talk.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldTalk::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (!GfGameManager::isPlayerPause()) {
    GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
    const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
    bool isIdle = __builtin_strcmp(stateName, "S_idle") == 0;
    bool isTalkEnd = __builtin_strcmp(stateName, "S_talkA_02") == 0;
    if ((isIdle | isTalkEnd) || StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_FIELD_IDLE);
    }
  }
}

} // namespace pc
} // namespace gf
