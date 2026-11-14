#include "gf/object/component/pc/field/gf_pc_state_field_water_brake.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/field/gf_pc_param_field.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldWaterBrake::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  behavior->getProperty()->unknown94 = 0.0f;
  unknown18 = false;
}

void StateFieldWaterBrake::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldWaterBrake::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (property->existInputXY()) {
    if (!StateUtilField::isInputInverseDir(*property)) {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00);
      reqState(STATE_ID_UNKNOWN_22);
    } else {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_01);
      reqState(STATE_ID_UNKNOWN_21);
    }
    return;
  }

  const FieldParam *param = property->unknown310.unknown006();
  MoveUtilField::updateBrake(info, *property);
  f32 speed = sqrtf(property->unknown80.x * property->unknown80.x + property->unknown80.y * property->unknown80.y + property->unknown80.z * property->unknown80.z);
  if (speed <= 0.0f) {
    if (__builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_wateridle") == 0) {
      reqState(STATE_ID_UNKNOWN_20);
    }
  }

  if (!unknown18 && speed <= param->stopMotionThresholdWater && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_01)) {
    unknown18 = true;
  }
}

} // namespace pc
} // namespace gf
