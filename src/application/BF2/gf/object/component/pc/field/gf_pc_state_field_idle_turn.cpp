#include "gf/object/component/pc/field/gf_pc_state_field_idle_turn.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldIdleTurn::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  comAsm->setVariable("V_speed", 8.0f);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown007();
  unknown008(*property, unknown20);
  StateUtilField::notifyTurn(*behavior);
}

void StateFieldIdleTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown007();
}

void StateFieldIdleTurn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (StateUtilField::isTurnEndRangeCacheInput(*property, unknown20)) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (!property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_UNKNOWN_3);
      return;
    }

    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE);
    const char *name = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    if (name != nullptr && __builtin_strcmp(name, "S_move") == 0) {
      reqState(STATE_ID_UNKNOWN_7);
      return;
    }
  }

  MoveUtilField::updateMoveTurn(info, *property, unknown20);
}

} // namespace pc
} // namespace gf
