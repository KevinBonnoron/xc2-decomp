#include "gf/object/component/pc/field/gf_pc_state_field_water_warp_rise.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/scom/gf_scom_obj.h"

namespace gf {
namespace pc {

void StateFieldWaterWarpRise::enter(GfComBehaviorPc *behavior, ai::State *previous) { StateUtilField::setSpecialActStatus(*behavior, true); }

void StateFieldWaterWarpRise::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setSpecialActStatus(*behavior, false);
  StateUtilField::notifySkillAct(*behavior, false);
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  const MsgPcFieldNotifyWarp *info = property->unknown310.getWarpInfo();
  if (info != nullptr) {
    if (property->unknown111_2) {
      SCOM_QUEST_GIMMICK::createWarp(info->unknown34, 0.0f);
    }
    property->unknown310.setBigJumpInfo(nullptr);
  }
}

void StateFieldWaterWarpRise::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  property->setLocomotion(comAsm->getLocomotion());
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
    reqState(STATE_ID_UNKNOWN_20);
  }
}

} // namespace pc
} // namespace gf
