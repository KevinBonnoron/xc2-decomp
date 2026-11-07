#include "gf/object/component/pc/field/gf_pc_state_field_land_big.h"

#include "framework/object/updatable_object.h"
#include "fw/fw_pad.h"
#include "gf/data/gf_data_param_acc.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/request/gf_req_scom.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldLandBig::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  StateUtilField::setAirStatus(*behavior, true);
  StateUtil::setEnableDownIK(*behavior, true);
  ParamObj object = {static_cast<GfObj *>(behavior->unknown08)->unknownf8, 0, 0};
  SCOM_FIELD_VOICE::createHighLanding(object);
  StateUtil::playVibration(*behavior, fw::VIBRATION_ID_UNKNOWN_2);
}

void StateFieldLandBig::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldLandBig::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm->isEnd(ANIM_LAYER_BASE) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
    reqState(STATE_ID_FIELD_IDLE);
  }
}

} // namespace pc
} // namespace gf
