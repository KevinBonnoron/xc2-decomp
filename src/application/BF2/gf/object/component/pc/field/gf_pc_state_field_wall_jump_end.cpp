#include "gf/object/component/pc/field/gf_pc_state_field_wall_jump_end.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWallJumpEnd::enter(GfComBehaviorPc *behavior, ai::State *previous) {}

void StateFieldWallJumpEnd::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWallJumpEnd::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->owner->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->owner->getComponent<GfComAsm>();
  property->setLocomotion(comAsm->getLocomotion());
  if (comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBIDLE)) {
    reqState(STATE_ID_FIELD_WALL_IDLE);
  }
}

} // namespace pc
} // namespace gf
