#include "gf/object/component/pc/field/gf_pc_state_field_start.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj_handle.h"

namespace gf {
namespace pc {

void StateFieldStart::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setSpecialActStatus(*behavior, true);
  if (!behavior->getProperty()->unknown111_2) {
    StateUtil::setTarget(*behavior, INVALID_HANDLE);
  }
}

void StateFieldStart::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setSpecialActStatus(*behavior, false); }

void StateFieldStart::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (property->unknown114 == 3) {
    if (!property->unknown111_3) {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        return;
      }

      reqState(STATE_ID_FIELD_WATER_SINK);
    } else {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERDEAD)) {
        return;
      }

      reqState(STATE_ID_FIELD_WATER_DEAD_SINK);
    }
  } else if (!property->unknown110_4) {
    if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL)) {
      return;
    }

    reqState(STATE_ID_FIELD_FALL);
  } else {
    const char *name = comAsm->getStateName(ANIM_LAYER_BASE);
    if (name == nullptr || __builtin_strcmp(name, "S_idle") != 0) {
      return;
    }

    reqState(STATE_ID_FIELD_IDLE);
  }
}

} // namespace pc
} // namespace gf
