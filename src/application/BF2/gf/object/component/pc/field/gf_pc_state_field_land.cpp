#include "gf/object/component/pc/field/gf_pc_state_field_land.h"

#include "framework/object/updatable_object.h"
#include "gf/game/gf_game_manager.h"
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

void StateFieldLand::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  property->unknown80 = mm::Vec3::zero;
  property->unknown90 = 0.0f;
  property->unknown94 = 0.0f;
  StateUtilField::setAirStatus(*behavior, true);
  StateUtil::setEnableDownIK(*behavior, true);
}

void StateFieldLand::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableDownIK(*behavior, false);
  StateUtil::setFallDamageDisable(*behavior, false);
  StateUtilField::notifyJumpEnd(*behavior);
}

void StateFieldLand::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (!property->unknown111_2 || !GfGameManager::isGmkTutorialSequenceOK()) {
    if (property->existInputXY() && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_MOVE)) {
      if (!StateUtilField::isInputInverseDir(*property)) {
        reqState(STATE_ID_UNKNOWN_7);
      } else {
        reqState(STATE_ID_UNKNOWN_4);
      }
      return;
    }

    if (!property->unknown110_4 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_FALL)) {
      reqState(STATE_ID_UNKNOWN_15);
      return;
    }

    if (property->unknown60.unknown08.test(INPUT_ID_UNKNOWN_2) && property->unknown310.unknown12_1 && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_JUMP)) {
      property->unknownc0 = 0.0f;
      reqState(STATE_ID_UNKNOWN_12);
      return;
    }
  }

  MoveUtilField::updateLandBrake(info, *property);
  if (comAsm->isEnd(ANIM_LAYER_UNKNOWN_0) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_IDLE)) {
    reqState(STATE_ID_UNKNOWN_3);
  }
}

} // namespace pc
} // namespace gf
