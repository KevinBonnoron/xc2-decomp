#include "gf/object/component/pc/field/gf_pc_state_field_wall.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWall::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  flushWallType(behavior);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  if (!property->unknown310.unknown10_6) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_UNKNOWN_3);
    }
  }
}

} // namespace pc
} // namespace gf
