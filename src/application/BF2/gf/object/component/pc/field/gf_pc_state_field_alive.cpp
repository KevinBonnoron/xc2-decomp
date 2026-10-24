#include "gf/object/component/pc/field/gf_pc_state_field_alive.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldAlive::enter(GfComBehaviorPc *behavior, ai::State *previous) {}

void StateFieldAlive::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldAlive::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
    reqState(STATE_ID_FIELD_IDLE);
  }
}

} // namespace pc
} // namespace gf
