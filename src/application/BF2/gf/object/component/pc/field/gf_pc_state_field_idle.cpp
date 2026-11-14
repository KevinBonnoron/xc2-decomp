#include "gf/object/component/pc/field/gf_pc_state_field_idle.h"

#include <float.h>
#include <math.h>

#include "framework/object/updatable_object.h"
#include "fw/fw_coli_check.h"
#include "fw/fw_transform.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace gf {
namespace pc {

void StateFieldIdle::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableDownIK(*behavior, true);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  StateUtilField::setIdleStatus(*property, true);
}

void StateFieldIdle::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setIdleStatus(*behavior->unknown08->getComponent<GfComPropertyPc>(), false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setEnableLookIK(*behavior, true);
}

void StateFieldIdle::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  const char *stateName = comAsm->getStateName(ANIM_LAYER_UNKNOWN_0);
  StateUtil::setEnableLookIK(*behavior, stateName != nullptr && __builtin_strcmp(stateName, "S_idle") == 0);
  if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    if (StateUtilField::isInputInverseDir(*property)) {
      reqState(STATE_ID_UNKNOWN_4);
    } else {
      reqState(STATE_ID_UNKNOWN_7);
    }
  }
}

bool StateFieldIdle::checkSpace(GfComBehaviorPc *behavior) const {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  f32 space = property->unknown310.unknown54;
  if (space > FLT_EPSILON) {
    fw::ColiCheckConfig config;
    config.unknown08 = 0.0f;
    config.unknown0c = 0.0f;
    config.unknown14 = false;
    config.unknown15 = false;
    config.unknown00 = 9;
    config.unknown10 = 0;
    config.unknown04 = 0x80000076;
    f32 length = space - 0.5f;
    mm::Vec3 base = property->unknown160.unknown00 + property->unknown1c0 * 0.6f;
    length = fmaxf(length, 0.01f);
    mm::Vec3 start = base + property->unknown1e0 * 0.5f;
    mm::Vec3 end = base + property->unknown1e0 * length;
    fw::TColiCheckResult<256> result;
    return !fw::ColiCheck::testCapsule(result, start, end, 0.5f, config);
  }

  return true;
}

void StateFieldIdle::procMsgPcFieldHighJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldHighJump &message) {
  message.unknown08 = true;
  reqState(STATE_ID_UNKNOWN_17);
}

} // namespace pc
} // namespace gf
