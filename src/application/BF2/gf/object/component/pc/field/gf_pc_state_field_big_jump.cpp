#include "gf/object/component/pc/field/gf_pc_state_field_big_jump.h"

#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_param_manager.h"
#include "fw/fw_transform.h"
#include "fw/fw_update_info.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/behavior/movement/gf_move_fall.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/scom/gf_scom_obj.h"
#include "mm_math/mm_math.h"
#include "mm_math/mm_quat.h"
#include "mm_mtl/intrusive_ptr.h"

namespace gf {
namespace pc {

void StateFieldBigJump::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  unknown18 = 0.0f;
  StateUtil::setEnableGravity(*behavior, false);
  StateUtilField::setSpecialActStatus(*behavior, true);
  StateUtilField::notifySkillAct(*behavior, true);
  StateUtil::setFallDamageDisable(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyBigJump *info = property->unknown310.getBigJumpInfo();
  f32 gravity = static_cast<const GfMoveFallControler::Param *>(property->unknown310.unknown08->unknown10[8].param)->accel;
  unknown30 = property->unknown160.unknown00;
  f32 height = info->unknown10.y >= unknown30.y ? (info->unknown10.y - unknown30.y) + info->unknown24 : info->unknown24;
  f32 speed = __builtin_fmaxf(info->unknown28, 0.03f);
  unknown1c = speed;
  unknown28 = (height + speed * (gravity * 0.5f * speed)) / speed;
  f32 diff = info->unknown10.y - unknown30.y;
  f32 speedSquared = unknown28 * unknown28;
  f32 rise = (gravity + gravity) * diff;
  unknown20 = __builtin_fmaxf((unknown28 - sqrtf(speedSquared - rise)) / gravity, 0.0f);
  unknown24 = __builtin_fmaxf((unknown28 + sqrtf(unknown28 * unknown28 - rise)) / gravity, 0.0f);
  unknown40 = property->unknown160.unknown10;
  f32 scale = 1.0f / sqrtf(unknown40.x * unknown40.x + unknown40.y * unknown40.y + unknown40.z * unknown40.z + unknown40.w * unknown40.w);
  unknown40.x = unknown40.x * scale;
  unknown40.y = scale * unknown40.y;
  unknown40.z = scale * unknown40.z;
  unknown40.w = scale * unknown40.w;
  f32 angle = info->unknown20 * 0.5f;
  unknown50.y = sinf(angle);
  unknown50.w = cosf(angle);
  unknown50.x = 0.0f;
  unknown50.z = 0.0f;
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (!comAsm->existState("S_highjump_00")) {
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL);
    unknown60 = false;
  } else {
    StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_HIGHJUMP);
    f32 time = 0.0f;
    comAsm->getPlaybackTime(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), &time);
    time = time <= 0.01f ? 0.01f : time;
    comAsm->setSpeed(time / unknown1c, ANIM_LAYER_UNKNOWN_0);
    unknown60 = true;
  }
}

void StateFieldBigJump::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::notifySkillAct(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyBigJump *info = property->unknown310.getBigJumpInfo();
  if (info != nullptr) {
    if (property->unknown111_2) {
      SCOM_QUEST_GIMMICK::createJump(info->unknown3c, 0.0f);
    }
    property->unknown310.setBigJumpInfo(nullptr);
  }
  StateUtil::setEnableGravity(*behavior, true);
  StateUtilField::setSpecialActStatus(*behavior, false);
}

void StateFieldBigJump::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  unknown18 = info.unknown04 + unknown18;
  GfComPropertyPc *property = behavior->getProperty();
  f32 gravity = static_cast<const GfMoveFallControler::Param *>(property->unknown310.unknown004(8).unknown00->param)->accel;
  const MsgPcFieldNotifyBigJump *jump = property->unknown310.getBigJumpInfo();
  if (unknown18 >= unknown24) {
    property->unknown160.unknown00 = jump->unknown10;
    f32 angle = jump->unknown20 * 0.5f;
    f32 sine = sinf(angle);
    f32 cosine = cosf(angle);
    property->unknown160.unknown10.x = 0.0f;
    property->unknown160.unknown10.y = sine;
    property->unknown160.unknown10.z = 0.0f;
    property->unknown160.unknown10.w = cosine;
    property->syncDirection();
    GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
    if (!StateUtilField::isBigLandDistance(*behavior)) {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP_END);
      reqState(STATE_ID_UNKNOWN_13);
    } else {
      StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMPDMG);
      reqState(STATE_ID_UNKNOWN_14);
    }
  } else {
    if (unknown60) {
      GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
      if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0)) {
        StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_HIGHJUMP_01);
        f32 time = 0.0f;
        comAsm->getPlaybackTime(comAsm->getStateName(ANIM_LAYER_UNKNOWN_0), &time);
        f32 duration = __builtin_fmaxf(unknown24 - unknown1c, 0.01f);
        comAsm->setSpeed(time / duration, ANIM_LAYER_UNKNOWN_0);
        unknown60 = false;
      }
    }
    f32 y = unknown30.y + unknown28 * unknown18 + unknown18 * (gravity * -0.5f * unknown18);
    mm::Vec3 position = unknown30;
    if (unknown18 >= unknown20) {
      f32 weight = mm::clamp((unknown18 - unknown20) / (unknown24 - unknown20), 0.0f, 1.0f);
      f32 angle = jump->unknown20 * 0.5f;
      mm::Quat target;
      target.y = sinf(angle);
      target.w = cosf(angle);
      target.x = 0.0f;
      target.z = 0.0f;
      property->unknown160.unknown10 = mm::slerp(unknown40, target, weight);
      property->syncDirection();
      position = unknown30 * (1.0f - weight) + jump->unknown10 * weight;
    }
    position.y = y;
    property->unknown160.unknown00 = position;
  }
}

} // namespace pc
} // namespace gf
