#include "gf/object/component/pc/gf_pc_state_util_field.h"

#include "gf/camera/gf_camera_player.h"
#include "gf/game/gf_game_player_camera.h"
#include "gf/game/gf_game_ride.h"
#include "gf/object/component/animation/gf_com_asm.h"
#include "gf/object/component/pc/gf_com_behavior_pc.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "gf/object/gf_obj.h"

namespace gf {
namespace pc {

bool StateUtilField::execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id) { return comAsm.execCmd(getASMCmdNameField(id), ANIM_LAYER_BASE); }

bool StateUtilField::testVechile(GfComBehaviorPc &behavior) { return GfGameRide::isVehicle(static_cast<GfObj *>(behavior.owner)->handle); }

bool StateUtilField::isWalkMode(GfComPropertyPc &property) { return property.field.isWalkMode; }

bool StateUtilField::testAutoRun(GfComPropertyPc &property) { return property.field.isAutoRun; }

void StateUtilField::setIdleStatus(GfComPropertyPc &property, bool isIdle) {
  if (isIdle) {
    property.field.isIdle = true;
  } else {
    property.field.isIdle = false;
  }
}

bool StateUtilField::isWallUpMove(GfPropertyField::WALL_MOVE_MODE mode) {
  return (mode == GfPropertyField::WALL_MOVE_MODE_UP || mode == GfPropertyField::WALL_MOVE_MODE_UP_RIGHT) | (mode == GfPropertyField::WALL_MOVE_MODE_UP_LEFT);
}

ASM_CMD_ID_FIELD StateUtilField::getAsmID(GfPropertyField::WALL_MOVE_MODE mode) {
  switch (mode) {
  case GfPropertyField::WALL_MOVE_MODE_UP:
  case GfPropertyField::WALL_MOVE_MODE_UP_RIGHT:
  case GfPropertyField::WALL_MOVE_MODE_UP_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBUP;
  case GfPropertyField::WALL_MOVE_MODE_RIGHT:
    return ASM_CMD_ID_FIELD_CLIMBRIGHT;
  case GfPropertyField::WALL_MOVE_MODE_DOWN_RIGHT:
  case GfPropertyField::WALL_MOVE_MODE_DOWN:
  case GfPropertyField::WALL_MOVE_MODE_DOWN_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBDOWN;
  case GfPropertyField::WALL_MOVE_MODE_LEFT:
    return ASM_CMD_ID_FIELD_CLIMBLEFT;
  default:
    return ASM_CMD_ID_FIELD_CLIMBIDLE;
  }
}

void StateUtilField::resetCameraForWall(GfComBehaviorPc &behavior, Timing timing) {
  if (!behavior.getProperty()->isPadControl) {
    return;
  }
  static const ResetCameraWallTiming CAMERA_TIMINGS[] = {RESET_CAMERA_WALL_TIMING_UNDER_GROUND, RESET_CAMERA_WALL_TIMING_GROUND, RESET_CAMERA_WALL_TIMING_AIR};
  GfGamePlayerCamera::resetCameraClimb(CAMERA_TIMINGS[timing]);
}

} // namespace pc
} // namespace gf
