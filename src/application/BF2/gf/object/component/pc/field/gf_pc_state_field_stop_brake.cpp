#include "gf/object/component/pc/field/gf_pc_state_field_stop_brake.h"

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
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldStopBrake::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  behavior->getProperty()->unknown94 = 0.0f;
  unknown18 = false;
}

void StateFieldStopBrake::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldStopBrake::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    if (!StateUtilField::isInputInverseDir(*property)) {
      reqState(STATE_ID_UNKNOWN_7);
    } else {
      reqState(STATE_ID_UNKNOWN_4);
    }
    return;
  }

  const FieldParam *param = property->unknown310.unknown006();
  MoveUtilField::updateBrake(info, *property);
  f32 speed = sqrtf(property->unknown80.x * property->unknown80.x + property->unknown80.y * property->unknown80.y + property->unknown80.z * property->unknown80.z);
  if (speed <= 0.0f) {
    if (param->stopMotionThreshold != 0.0f) {
      if (__builtin_strcmp(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), "S_idle") == 0) {
        reqState(STATE_ID_UNKNOWN_3);
        return;
      }
    } else if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_UNKNOWN_3);
      return;
    }
  }

  if (param->stopMotionThreshold != 0.0f && !unknown18 && speed <= param->stopMotionThreshold && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WALKEND)) {
    unknown18 = true;
    StateUtil::setEnableDownIK(*behavior, true);
    property->unknown80 = mm::Vec3::zero;
  }
  StateUtilField::setAsmSpeedMove(*property);
}

} // namespace pc
} // namespace gf
