#include "gf/object/component/pc/field/gf_pc_state_field_lure.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/enemy/gf_com_behavior_enemy.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "gf/object/gf_obj.h"
#include "gf/object/gf_obj_util.h"
#include "mm_math/mm_vec3.h"

namespace gf {
namespace pc {

void StateFieldLure::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown94 = 0.0f;
  unknown18 = StateUtilField::getLureTargetHandle(*behavior);
}

void StateFieldLure::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtilField::setEnableLure(*behavior, false); }

void StateFieldLure::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
    notifyLure(behavior);
    reqState(STATE_ID_UNKNOWN_3);
  }
}

void StateFieldLure::notifyLure(GfComBehaviorPc *behavior) {
  GfObj *obj = GfObjUtil::getObj(unknown18);
  if (obj != nullptr) {
    MsgObjectLure message;
    static_cast<GfObj *>(behavior->unknown08)->sendMessage(obj, message);
  }
}

} // namespace pc
} // namespace gf
