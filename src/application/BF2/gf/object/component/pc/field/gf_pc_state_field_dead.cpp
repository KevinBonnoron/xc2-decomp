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
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  isDownPosePending = __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_BASE), "S_downpose") != 0;
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  property->velocity = mm::Vec3::zero;
  property->verticalSpeed = 0.0f;
  property->horizontalSpeed = 0.0f;
}

void StateFieldDead::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldDead::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (isDownPosePending) {
    GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
    if (comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_DOWNPOSE)) {
      isDownPosePending = false;
    }
  }
}

} // namespace pc
} // namespace gf
