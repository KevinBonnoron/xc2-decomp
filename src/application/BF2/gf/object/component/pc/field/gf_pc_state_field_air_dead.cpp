#include "gf/object/component/pc/field/gf_pc_state_field_air_dead.h"

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

void StateFieldAirDead::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  unknown18 = __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_down_00") == 0;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 4.3f;
  property->unknown94 = 0.0f;
}

void StateFieldAirDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldAirDead::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (property->unknown110_4) {
    if (unknown18) {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWN_01);
    }
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DEAD);
    reqState(STATE_ID_UNKNOWN_58);
    return;
  }
  if (unknown18 && comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWN_01)) {
    unknown18 = false;
  }
  MoveUtilField::updateFallDown(info, *property);
}

} // namespace pc
} // namespace gf
