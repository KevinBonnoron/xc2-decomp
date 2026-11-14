#include "gf/object/component/pc/field/gf_pc_state_field_water_swim_sink.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldWaterSwimSink::enter(GfComBehaviorPc *behavior, ai::State *previous) { unknown18 = 0.0f; }

void StateFieldWaterSwimSink::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterSwimSink::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const WaterCommonParam *param = property->unknown310.unknown005();
  unknown18 += info.unknown04;
  if (unknown18 >= param->swimSinkTime) {
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
      reqState(STATE_ID_UNKNOWN_28);
      return;
    }
  }

  MoveUtilField::updateMoveSwim(info, *property);
  if (StateUtilField::getChildFrameHeight(*behavior) <= -param->sinkDepth) {
    property->unknown90 = 0.0f;
    return;
  }

  MoveUtilField::updateMoveWaterSink(info, *property);
}

} // namespace pc
} // namespace gf
