#include "gf/object/component/pc/field/gf_pc_state_field_extra_control.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
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

void StateFieldExtraControl::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = MODE_UNKNOWN_FFFFFFFF;
  const char *stateName = behavior->unknown08->getComponent<GfComAsm>()->getStateName(ANIM_LAYER_UNKNOWN_0);
  if (stateName != nullptr) {
    if (__builtin_strcmp(stateName, "S_idle") == 0) {
      setMode(behavior, MODE_UNKNOWN_2);
    } else if (__builtin_strcmp(stateName, "S_move") == 0) {
      setMode(behavior, MODE_UNKNOWN_0);
    } else if (__builtin_strcmp(stateName, "S_walkendL") == 0 || __builtin_strcmp(stateName, "S_walkendR") == 0) {
      setMode(behavior, MODE_UNKNOWN_1);
    } else if (__builtin_strcmp(stateName, "S_talkA_02") == 0) {
      setMode(behavior, MODE_UNKNOWN_3);
    }
  }
  behavior->getProperty()->unknown94 = 0.0f;
}

void StateFieldExtraControl::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::setEnableDownIK(*behavior, false); }

void StateFieldExtraControl::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  if (unknown18 == MODE_UNKNOWN_FFFFFFFF) {
    reqState(STATE_ID_UNKNOWN_3);
    return;
  }

  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (!GfGameManager::isGmkTutorialSequenceOK()) {
    const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    if (stateName == nullptr || __builtin_strcmp(stateName, "S_talkA_02") != 0) {
      if (stateName == nullptr || __builtin_strcmp(stateName, "S_idle") != 0) {
        if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
          comAsm->setState("S_idle", ANIM_LAYER_UNKNOWN_0);
        }
      }
      reqState(STATE_ID_UNKNOWN_3);
      return;
    }
  }

  switch (unknown18) {
  case MODE_UNKNOWN_1: {
    MoveUtilField::updateBrake(info, *property);
    const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    if (stateName != nullptr && __builtin_strcmp(stateName, "S_idle") == 0) {
      setMode(behavior, MODE_UNKNOWN_2);
      return;
    }
    break;
  }
  case MODE_UNKNOWN_0: {
    const FieldParam *param = property->unknown310.unknown006();
    MoveUtilField::updateBrake(info, *property);
    f32 speed = sqrtf(property->unknown80.x * property->unknown80.x + property->unknown80.y * property->unknown80.y + property->unknown80.z * property->unknown80.z);
    if (speed <= 0.0f) {
      if (param->stopMotionThreshold != 0.0f && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
        setMode(behavior, MODE_UNKNOWN_2);
        return;
      }
    } else if (param->stopMotionThreshold != 0.0f && speed <= param->stopMotionThreshold && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WALKEND)) {
      StateUtil::setEnableDownIK(*behavior, true);
      property->unknown80 = mm::Vec3::zero;
      setMode(behavior, MODE_UNKNOWN_1);
      return;
    }
    StateUtilField::setAsmSpeedMove(*property);
    break;
  }
  default:
    break;
  }

  if (unknown18 == MODE_UNKNOWN_3) {
    const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
    if (stateName != nullptr && __builtin_strcmp(stateName, "S_idle") == 0) {
      setMode(behavior, MODE_UNKNOWN_2);
    }
  }
}

void StateFieldExtraControl::setMode(GfComBehaviorPc *behavior, Mode mode) {
  if (unknown18 == mode) {
    return;
  }
  if (mode == MODE_UNKNOWN_2) {
    GfGameManager::setGmkTutorialMoverOK(true);
    StateUtil::setEnableDownIK(*behavior, true);
    StateUtil::setEnableDownIK(*behavior, true);
  } else if (mode == MODE_UNKNOWN_3) {
    StateUtil::setEnableDownIK(*behavior, true);
  }
  unknown18 = mode;
}

} // namespace pc
} // namespace gf
