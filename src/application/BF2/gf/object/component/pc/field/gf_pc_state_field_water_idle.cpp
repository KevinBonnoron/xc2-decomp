#include "gf/object/component/pc/field/gf_pc_state_field_water_idle.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterIdle::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->horizontalSpeed = 0.0f;
  StateUtilField::setIdleStatus(*property, true);
}

void StateFieldWaterIdle::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setIdleStatus(*behavior->owner->getComponent<GfComPropertyPc>(), false); }

void StateFieldWaterIdle::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  if (property->existInputXY()) {
    GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
    if (StateUtilField::isInputInverseDir(*property)) {
      reqState(STATE_ID_FIELD_WATER_IDLE_TURN);
    } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
      reqState(STATE_ID_FIELD_WATER_SWIM);
    }
  }
}

} // namespace pc
} // namespace gf
