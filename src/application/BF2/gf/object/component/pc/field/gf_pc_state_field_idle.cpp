#include "gf/object/component/pc/field/gf_pc_state_field_idle.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldIdle::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableDownIK(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  StateUtilField::setIdleStatus(*property, true);
}

void StateFieldIdle::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setIdleStatus(*behavior->unknown08->getComponent<GfComPropertyPc>(), false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setEnableLookIK(*behavior, true);
}

void StateFieldIdle::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const char *stateName = comAsm->getStateName(ANIM_LAYER_BASE);
  StateUtil::setEnableLookIK(*behavior, stateName != nullptr && __builtin_strcmp(stateName, "S_idle") == 0);
  if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    if (StateUtilField::isInputInverseDir(*property)) {
      reqState(STATE_ID_FIELD_IDLE_TURN);
    } else {
      reqState(STATE_ID_FIELD_MOVE);
    }
  }
}

} // namespace pc
} // namespace gf
