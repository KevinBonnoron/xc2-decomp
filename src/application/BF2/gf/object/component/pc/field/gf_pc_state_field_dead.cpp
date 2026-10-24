#include "gf/object/component/pc/field/gf_pc_state_field_dead.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldDead::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  unknown18 = __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_BASE), "S_downpose") != 0;
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
}

void StateFieldDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldDead::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (unknown18) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWNPOSE)) {
      unknown18 = false;
    }
  }
}

} // namespace pc
} // namespace gf
