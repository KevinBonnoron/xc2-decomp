#include "gf/object/component/pc/field/gf_pc_state_field_water_idle_turn.h"

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

void StateFieldWaterIdleTurn::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown007();
  unknown008(*property, unknown20);
  StateUtilField::notifyTurn(*behavior);
}

void StateFieldWaterIdleTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown007();
}

void StateFieldWaterIdleTurn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (StateUtilField::isTurnEndRangeCacheInput(*property, unknown20)) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (!property->existInputXY()) {
      reqState(STATE_ID_UNKNOWN_20);
      return;
    }
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
      reqState(STATE_ID_UNKNOWN_22);
      return;
    }
  }
  MoveUtilField::updateMoveWaterTurn(info, *property, unknown20);
}

} // namespace pc
} // namespace gf
