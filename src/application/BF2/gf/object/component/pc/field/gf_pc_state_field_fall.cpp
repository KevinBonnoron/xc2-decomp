#include "gf/object/component/pc/field/gf_pc_state_field_fall.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

namespace gf {
namespace pc {

void StateFieldFall::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  for (ai::State *state = previous; state != nullptr; state = state->unknown10) {
    if (state->unknown08 == STATE_ID_UNKNOWN_38) {
      StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE_UNKNOWN_0, true);
      return;
    }
  }
}

void StateFieldFall::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtil::setActivateTimer(*behavior, TimerPlugin::TYPE_UNKNOWN_0, false);
  if (next == nullptr || next->unknown08 == STATE_ID_UNKNOWN_13) {
    return;
  }
  StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldFall::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (!property->unknown110_4) {
    if (StateUtilField::isSlideSlope(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SLOPE)) {
      reqState(STATE_ID_UNKNOWN_54);
      return;
    }

    if (StateUtilField::isBackRangeAir(*property)) {
      MoveUtilField::updateMoveJumpBack(info, *property);
    } else {
      MoveUtilField::updateMoveJump(info, *property);
    }
    MoveUtilField::updateFallDown(info, *property);
  } else if (StateUtilField::isSlideGroundLanding(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SLOPE)) {
    reqState(STATE_ID_UNKNOWN_54);
  } else if (property->unknownc0 > 0.0f && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    StateUtilField::onLandSliding(*behavior);
    reqState(STATE_ID_UNKNOWN_55);
  } else if (StateUtilField::isBigLandDistance(*behavior)) {
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMPDMG);
    reqState(STATE_ID_UNKNOWN_14);
  } else {
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP_END);
    reqState(STATE_ID_UNKNOWN_13);
  }
}
} // namespace pc
} // namespace gf
