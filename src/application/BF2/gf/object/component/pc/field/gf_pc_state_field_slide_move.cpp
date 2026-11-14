#include "gf/object/component/pc/field/gf_pc_state_field_slide_move.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_move_util_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateFieldSlideMove::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  mm::Vec3 velocity = mm::Vec3::unitY * property->unknown90 + property->unknown80 + property->unknownd0 * property->unknownc0;
  property->unknownc0 = property->unknownd0.x * velocity.x + property->unknownd0.y * velocity.y + property->unknownd0.z * velocity.z;
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3(0.7853982f, 0.0f, 0.0f));
}

void StateFieldSlideMove::leave(GfComBehaviorPc *behavior, ai::State *next) { StateUtil::changeGroundAnglesForMotion(*behavior, mm::Vec3::zero); }

void StateFieldSlideMove::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (StateUtilField::isEndSlipPosuture(*behavior) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
    if (!property->existInputXY()) {
      reqState(STATE_ID_UNKNOWN_55);
    } else {
      reqState(STATE_ID_UNKNOWN_7);
    }
  } else if (StateUtilField::isFallFromSlideState(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL)) {
    reqState(STATE_ID_UNKNOWN_15);
  } else if (property->unknown60.unknown08.test(INPUT_ID_UNKNOWN_2) && property->unknown310.unknown12_1 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP)) {
    reqState(STATE_ID_UNKNOWN_12);
  } else {
    MoveUtilField::updateMoveSlide(info, *property);
  }
}

} // namespace pc
} // namespace gf
