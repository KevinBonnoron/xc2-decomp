#include "gf/object/component/pc/field/gf_pc_state_field_slide_land_brake.h"

#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"
#include "mm_mtl/bitflag.h"

namespace gf {
namespace pc {

void StateFieldSlideLandBrake::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  StateUtilField::setAsmSpeedSlideBrake(*property);
  property->unknown90 = 0.0f;
}

void StateFieldSlideLandBrake::leave(GfComBehaviorPc *behavior, ai::State *next) {}

void StateFieldSlideLandBrake::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (StateUtilField::isFallFromSlideState(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL)) {
    reqState(STATE_ID_FIELD_FALL);
  } else if (property->unknown60.unknown08.test(INPUT_ID_JUMP) && property->unknown310.unknown12_1 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP)) {
    reqState(STATE_ID_FIELD_JUMP);
  } else if (StateUtilField::isStartSlidePosuture(*behavior) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SLOPE)) {
    reqState(STATE_ID_FIELD_SLIDE_MOVE);
  } else if (!property->existInputXY()) {
    if (StateUtilField::isSlideStop(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
      reqState(STATE_ID_FIELD_IDLE);
    } else {
      StateUtilField::setAsmSpeedSlideBrake(*property);
    }
  } else {
    property->unknownc0 = 0.0f;
    reqState(STATE_ID_FIELD_MOVE);
  }
}

} // namespace pc
} // namespace gf
