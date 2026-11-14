#include "gf/object/component/pc/field/gf_pc_state_field_water.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWater::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtilField::setWaterMode(*behavior, true);
  StateUtil::setEnableLookIK(*behavior, false);
  StateUtilField::setLookAtFlag(*behavior, false);
  behavior->getProperty()->unknownc0 = 0.0f;
}

void StateFieldWater::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setWaterMode(*behavior, false);
  StateUtil::setEnableLookIK(*behavior, true);
  StateUtilField::setLookAtFlag(*behavior, true);
}

void StateFieldWater::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->getProperty();
  if (property->unknown11c <= property->unknown2f8 || StateUtilField::isInterruptionWater(*property)) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (!property->existInputXY()) {
      if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
        reqState(STATE_ID_UNKNOWN_3);
      }
    } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
      reqState(STATE_ID_UNKNOWN_7);
    }
  }
}

} // namespace pc
} // namespace gf
