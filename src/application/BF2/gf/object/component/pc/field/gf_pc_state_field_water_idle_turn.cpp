#include "gf/object/component/pc/field/gf_pc_state_field_water_idle_turn.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterIdleTurn::leave(GfComBehaviorPc *behavior, ai::State *next) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->horizontalSpeed = 0.0f;
}

void StateFieldWaterIdleTurn::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  if (StateUtilField::isTurnEndRangeCacheInput(*property, inputDirection)) {
    GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
    if (!property->existInputXY()) {
      reqState(STATE_ID_FIELD_WATER_IDLE);
      return;
    }
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
      reqState(STATE_ID_FIELD_WATER_SWIM);
      return;
    }
  }
  MoveUtilField::updateMoveWaterTurn(info, *property, inputDirection);
}

} // namespace pc
} // namespace gf
