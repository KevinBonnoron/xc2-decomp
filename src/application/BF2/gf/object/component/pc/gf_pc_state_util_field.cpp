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

void StateUtilField::resetCameraForWall(GfComBehaviorPc &behavior, Timing timing) {
  if (!behavior.getProperty()->isPadControl) {
    return;
  }
  static const ResetCameraWallTiming CAMERA_TIMINGS[] = {
      RESET_CAMERA_WALL_TIMING_UNDER_GROUND, RESET_CAMERA_WALL_TIMING_GROUND, RESET_CAMERA_WALL_TIMING_AIR};
  GfGamePlayerCamera::resetCameraClimb(CAMERA_TIMINGS[timing]);
}

} // namespace pc
} // namespace gf
