#pragma once
#include "framework/message/message_object.h"
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "gf/object/component/pc/gf_pc_property_field.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComAsm;
class GfComBehaviorPc;
class GfComPropertyPc;
class GfComponent;
struct GF_OBJ_HANDLE;

namespace pc {

enum VehicleEvent {};

struct MsgPcFieldNotifyRiderEvent : fw::Message {
  MsgPcFieldNotifyRiderEvent(VehicleEvent event) : fw::Message(0x1000024, 0x40), unknown08(event) {}

  VehicleEvent unknown08; // Inferred role: vehicle event; original member name unknown.
};

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
  static void setLookAtFlag(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableLure(GfComBehaviorPc &behavior, bool isEnable);
  static GF_OBJ_HANDLE *getLureTargetHandle(GfComBehaviorPc &behavior);
  static bool isStop(GfComPropertyPc &property, u32 noInputFrameCount);
  static void flipAutoRun(GfComPropertyPc &property);
  static void setAutoRun(GfComPropertyPc &property, bool isAutoRun);
  static bool testAutoRun(GfComPropertyPc &property);
  static void setAutoRunInput(GfComPropertyPc &property);
  static void setAsmSpeedMove(GfComPropertyPc &property);
  static bool isTurnEndRangeCacheInput(GfComPropertyPc &property, const mm::Vec3 &direction);
  static bool isInputInverseDir(GfComPropertyPc &property);
  static bool isInputInverseDirAutoRun(GfComPropertyPc &property);
  static void setIdleStatus(GfComPropertyPc &property, bool isIdle);
  static void setAirStatus(GfComBehaviorPc &behavior, bool isAir);
  static void setSpecialActStatus(GfComBehaviorPc &behavior, bool isSpecialAct);
  static void notifyJumpEnd(GfComBehaviorPc &behavior);
  static void setEnableWaterIn(GfComBehaviorPc &behavior, bool isEnable);
  static void setWaterMode(GfComBehaviorPc &behavior, bool isWater);
  static void setWaterDiveMove(GfComPropertyPc &property, bool isDive);
  static f32 getChildFrameHeight(GfComponent &component);
  static bool isWallUpMove(GfPropertyField::WALL_MOVE_MODE mode);
  static ASM_CMD_ID_FIELD getAsmID(GfPropertyField::WALL_MOVE_MODE mode);
  static void resetCameraForWall(GfComBehaviorPc &behavior, Timing timing);
  static void setAsmSpeedSlideBrake(GfComPropertyPc &property);
  static void notifyRiderEvent(GfComBehaviorPc &behavior, VehicleEvent event);
  static bool isBackMove(GfComPropertyPc &property);
  static bool isInterruptionWater(GfComPropertyPc &property);
};

} // namespace pc
} // namespace gf
