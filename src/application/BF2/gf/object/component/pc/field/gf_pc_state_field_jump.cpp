#include "gf/object/component/pc/field/gf_pc_state_field_jump.h"

#include <float.h>
#include <math.h>

#include "ai/ai_state.h"
#include "anm/anm_qs_transform.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/component/pc/param/gf_pc_param.h"
#include "gf/object/gf_obj.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_vec3.h"
#include "mm_math/mm_vec4.h"

namespace gf {
namespace pc {

void StateFieldJump::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  unknown18 = 0.0f;
  unknown20 = 0.0f;
  unknown1c = false;
  if (previous != nullptr && previous->unknown08 == STATE_ID_FIELD_SLIDE_MOVE) {
    unknown1c = true;
  }

  ParamObj object = {static_cast<GfObj *>(behavior->unknown08)->unknownf8, 0, 0};
  SCOM_FIELD_VOICE::createJump(object);
}

void StateFieldJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  if (next == nullptr || next->unknown08 == STATE_ID_FIELD_LAND || next->unknown08 == STATE_ID_FIELD_FALL) {
    return;
  }
  StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldJump::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const MoveParam *param = property->unknown005();
  anm::QsTransform locomotion = comAsm->getLocomotion();
  locomotion.unknown00.x = param->jumpRatio * locomotion.unknown00.x;
  locomotion.unknown00.y = param->jumpRatio * locomotion.unknown00.y;
  locomotion.unknown00.z = param->jumpRatio * locomotion.unknown00.z;
  locomotion.unknown00.w = param->jumpRatio * locomotion.unknown00.w;
  property->setLocomotion(locomotion);
  unknown18 += info.unknown04;
  if (!StateUtilField::ignoreOnGroundJump(*property, unknown18)) {
    if (!property->unknown110_4) {
      if (StateUtilField::isSlideSlope(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SLOPE)) {
        reqState(STATE_ID_FIELD_SLIDE_MOVE);
        return;
      }
    } else if (StateUtilField::isSlideGroundLanding(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SLOPE)) {
      reqState(STATE_ID_FIELD_SLIDE_MOVE);
      return;
    } else if (property->unknownc0 > 0.0f && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
      StateUtilField::onLandSliding(*behavior);
      reqState(STATE_ID_FIELD_SLIDE_LAND_BRAKE);
      return;
    } else if (StateUtilField::isBigLandDistance(*behavior)) {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMPDMG);
      reqState(STATE_ID_FIELD_LAND_BIG);
      return;
    } else {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP_END);
      reqState(STATE_ID_FIELD_LAND);
      return;
    }
  }

  if (comAsm->isEnd(ANIM_LAYER_BASE) && __builtin_strcmp(comAsm->getStateName(ANIM_LAYER_BASE), "S_jump_01") == 0) {
    property->unknown90 = unknown20;
    property->unknown110_2 = false;
    if (StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL)) {
      reqState(STATE_ID_FIELD_FALL);
      return;
    }
  }

  const fw::Transform &current = property->getLocomotion();
  if (fabsf(current.unknown00.y) > FLT_EPSILON) {
    unknown20 = current.unknown00.y / info.unknown04;
  }

  if (unknown1c) {
    return;
  }

  if (StateUtilField::isBackRangeAir(*property)) {
    MoveUtilField::updateMoveJumpBack(info, *property);
  } else {
    MoveUtilField::updateMoveJump(info, *property);
  }
}

} // namespace pc
} // namespace gf
