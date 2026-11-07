#include "gf/object/component/pc/field/gf_pc_state_field_air.h"

#include "ai/ai_state.h"
#include "framework/object/updatable_object.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_state_id.h"
#include "gf/object/component/pc/gf_pc_state_util.h"
#include "gf/object/component/pc/gf_pc_state_util_field.h"

namespace gf {
namespace pc {

void StateFieldAir::enter(GfComBehaviorPc *behavior, ai::State *previous) {
  StateUtil::setEnableGravity(*behavior, false);
  StateUtilField::setEnableFallIntoColi(*behavior, true);
  StateUtilField::setAirStatus(*behavior, true);
  StateUtilField::setEnableWaterIn(*behavior, true);
  StateUtil::setEnableFallDistChecker(*behavior, true);
}

void StateFieldAir::leave(GfComBehaviorPc *behavior, ai::State *next) {
  StateUtilField::setEnableWaterIn(*behavior, false);
  StateUtil::setEnableGravity(*behavior, true);
  StateUtilField::setEnableFallIntoColi(*behavior, false);
  StateUtilField::setAirStatus(*behavior, false);
  StateUtil::setEnableFallDistChecker(*behavior, false);
  if (next != nullptr && next->unknown08 == STATE_ID_FIELD_SLIDE_MOVE) {
    StateUtilField::setSlideDirForce(*behavior->unknown08->getComponent<GfComPropertyPc>());
  }
}

void StateFieldAir::update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {
  GfComPropertyPc *property = behavior->unknown08->getComponent<GfComPropertyPc>();
  GfComAsm *comAsm = behavior->unknown08->getComponent<GfComAsm>();
  if (StateUtilField::isWallAdsorptionAir(*property) && StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_CLIMBIDLE)) {
    reqState(STATE_ID_FIELD_WALL_ADSORPTION_AIR);
    return;
  }

  if (property->unknown114 != 3) {
    return;
  }

  if (!property->unknown111_3) {
    if (!StateUtilField::isSwimFromAir(*property)) {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        return;
      }

      if (!StateUtilField::isSwimMoveFromAir(*property)) {
        reqState(STATE_ID_FIELD_WATER_SINK);
      } else {
        reqState(STATE_ID_FIELD_WATER_SWIM_SINK);
      }
    } else if (!StateUtilField::isSwimMoveFromAir(*property)) {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERIDLE)) {
        return;
      }

      reqState(STATE_ID_FIELD_WATER_IDLE);
    } else {
      if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_SWIM_00)) {
        return;
      }

      reqState(STATE_ID_FIELD_WATER_SWIM);
    }
  } else {
    if (!StateUtilField::execAsmCmd(*comAsm, ASM_CMD_ID_FIELD_WATERDEAD)) {
      return;
    }

    reqState(STATE_ID_FIELD_WATER_DEAD_SINK);
  }
}

} // namespace pc
} // namespace gf
