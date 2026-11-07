#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "mm_math/mm_plane.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComAsm;
class GfComBehaviorPc;
class GfComPropertyPc;
class GfComponent;
class GfObj;
struct GF_OBJ_HANDLE;

struct MsgPcFieldNotifyWall : fw::Message {
  MsgPcFieldNotifyWall() : fw::Message(0x100000f, 0x40) {}

  mm::Plane unknown10;     // Inferred role: wall plane; original member name unknown.
  fw::Transform unknown30; // Inferred role: transform, pushed as a whole by AIAgentField::procMsgPcFieldNotifyWall; original member name unknown.
  u32 unknown50;           // Inferred role: notify type (0 enter, 1 leave, 2 jump, 3 move); original member name unknown.
};

static_assert(offsetof(MsgPcFieldNotifyWall, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldNotifyWall, unknown30) == 0x30, "");
static_assert(offsetof(MsgPcFieldNotifyWall, unknown50) == 0x50, "");

namespace pc {

enum VehicleEvent {};

struct MsgPcFieldNotifyRiderEvent : fw::Message {
  MsgPcFieldNotifyRiderEvent(VehicleEvent event) : fw::Message(0x1000024, 0x40), unknown08(event) {}

  VehicleEvent unknown08; // Inferred role: vehicle event; original member name unknown.
};

f32 calcInputDiffAngle(GfComPropertyPc &property);
f32 calcInputDiffAngleVel(GfComPropertyPc &property);

class StateUtilField {
public:
  enum Timing {
    TIMING_UNDER_GROUND,
    TIMING_GROUND,
    TIMING_AIR,
  };

  static bool execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id);
  static bool testVechile(GfComBehaviorPc &behavior);
  static void setEnableFallIntoColi(GfComBehaviorPc &behavior, bool isEnable);
  static bool isWalkMode(GfComPropertyPc &property);
  static void setAccessFlag(GfComBehaviorPc &behavior, bool isEnable);
  static GfObj *getAccessTarget(GfComBehaviorPc &behavior);
  static void setLookAtFlag(GfComBehaviorPc &behavior, bool isEnable);
  static void setSlideDirForce(GfComPropertyPc &property);
  static void setEnableLure(GfComBehaviorPc &behavior, bool isEnable);
  static GF_OBJ_HANDLE *getLureTargetHandle(GfComBehaviorPc &behavior);
  static GfObj *getLureTarget(GfComBehaviorPc &behavior);
  static void startWaterWarpFade(GfComBehaviorPc &behavior);
  static void onLandSliding(GfComBehaviorPc &behavior);
  static bool isStop(GfComPropertyPc &property, u32 noInputFrameCount);
  static void flipAutoRun(GfComPropertyPc &property);
  static void setAutoRun(GfComPropertyPc &property, bool isAutoRun);
  static bool testAutoRun(GfComPropertyPc &property);
  static void setAutoRunInput(GfComPropertyPc &property);
  static f32 setAsmSpeedMove(GfComPropertyPc &property);
  static void setAsmSpeedSwim(GfComPropertyPc &property);
  static bool isTurnEndRangeCacheInput(GfComPropertyPc &property, const mm::Vec3 &direction);
  static bool isInputInverseDir(GfComPropertyPc &property);
  static bool isInputInverseDirAutoRun(GfComPropertyPc &property);
  static bool isSlideSlope(GfComPropertyPc &property);
  static bool isSlideGroundLanding(GfComPropertyPc &property);
  static bool isEndSlipPosuture(GfComBehaviorPc &behavior);
  static bool isStartSlidePosuture(GfComBehaviorPc &behavior);
  static bool isTurnEndRange(GfComPropertyPc &property);
  static bool isBackRange(GfComPropertyPc &property);
  static bool isBackRangeAir(GfComPropertyPc &property);
  static bool ignoreOnGroundJump(GfComPropertyPc &property, f32 time);
  static bool isSwimFromAir(GfComPropertyPc &property);
  static bool isSwimMoveFromAir(GfComPropertyPc &property);
  static bool isWallFall(GfComPropertyPc &property);
  static bool ignoreSlideJump(GfComPropertyPc &property, f32 time);
  static bool isFallFromSlideState(GfComPropertyPc &property);
  static bool isSlideStop(GfComPropertyPc &property);
  static void setChildFrameHeight(GfComponent &component, f32 height);
  static bool isWallIdleMotion(GfComAsm &comAsm);
  static void notifyTurn(GfComBehaviorPc &behavior);
  static bool isEnableWallPrepare(GfComPropertyPc &property);
  static mm::Vec3 calcWallPreparePosition(GfComPropertyPc &property, const mm::Vec3 &position, const mm::Plane &plane);
  static bool isWallPreparePosition(GfComPropertyPc &property, const mm::Vec3 &position);
  static bool isEnableWallAdsorptionStart(GfComPropertyPc &property, const mm::Vec3 &position, const mm::Vec3 &preparePosition);
  static bool isNearPlayerWall(GfComPropertyPc &property, const mm::Vec3 &position, f32 range);
  static bool isNearPlayer(GfComPropertyPc &property, const mm::Vec3 &position, f32 range);
  static bool isWallDetach(GfComPropertyPc &property);
  static void setEnableDeadColCheck(GfComBehaviorPc &behavior, bool isEnable);
  static void setIdleStatus(GfComPropertyPc &property, bool isIdle);
  static void setAirStatus(GfComBehaviorPc &behavior, bool isAir);
  static void setSpecialActStatus(GfComBehaviorPc &behavior, bool isSpecialAct);
  static void notifySkillAct(GfComBehaviorPc &behavior, bool isSkillAct);
  static void notifyJumpEnd(GfComBehaviorPc &behavior);
  static void setEnableWaterIn(GfComBehaviorPc &behavior, bool isEnable);
  static void setWaterMode(GfComBehaviorPc &behavior, bool isWater);
  static void setWaterDiveMove(GfComPropertyPc &property, bool isDive);
  static f32 getChildFrameHeight(GfComponent &component);
  static GfPropertyField::WALL_MOVE_MODE decideWallMoveMode(GfComPropertyPc &property);
  static bool isWallUpMove(GfPropertyField::WALL_MOVE_MODE mode);
  static bool isMovableWall(GfComPropertyPc &property, GfPropertyField::WALL_MOVE_MODE mode);
  static ASM_CMD_ID_FIELD getAsmID(GfPropertyField::WALL_MOVE_MODE mode);
  static void sendMessageWallChilds(GfComPropertyPc &property, fw::Message &message);
  static bool isWallClimbEnd(GfComPropertyPc &property);
  static bool isWallAdsorption(GfComPropertyPc &property);
  static bool isWallAdsorptionAir(GfComPropertyPc &property);
  static bool isWallAdsorptionUnderWall(GfComPropertyPc &property);
  static void resetCameraForWall(GfComBehaviorPc &behavior, Timing timing);
  static void setAsmSpeedSlideBrake(GfComPropertyPc &property);
  static f32 calcFallSpeed(GfComPropertyPc &property);
  static bool isBigSplashFallSpeed(GfComBehaviorPc &behavior);
  static bool isBigLandDistance(GfComBehaviorPc &behavior);
  static void notifyRiderEvent(GfComBehaviorPc &behavior, VehicleEvent event);
  static void requestGetOffRider(GfComBehaviorPc &behavior);
  static bool isBackMove(GfComPropertyPc &property);
  static bool isInterruptionWater(GfComPropertyPc &property);
};

} // namespace pc
} // namespace gf
