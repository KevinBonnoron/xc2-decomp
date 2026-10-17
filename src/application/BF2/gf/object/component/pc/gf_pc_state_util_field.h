#pragma once
#include "gf/object/component/pc/gf_pc_asm_cmd_id_field.h"
#include "types.h"

namespace gf {

class GfComAsm;
class GfComBehaviorPc;
class GfComPropertyPc;
class GfComponent;

namespace pc {

class StateUtilField {
public:
  enum Timing {
    TIMING_UNDER_GROUND,
    TIMING_GROUND,
    TIMING_AIR,
  };

  static bool execAsmCmd(GfComAsm &comAsm, ASM_CMD_ID_FIELD id);
  static void setEnableFallIntoColi(GfComBehaviorPc &behavior, bool isEnable);
  static void setAccessFlag(GfComBehaviorPc &behavior, bool isEnable);
  static void setLookAtFlag(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableLure(GfComBehaviorPc &behavior, bool isEnable);
  static bool isStop(GfComPropertyPc &property, u32 noInputFrameCount);
  static void flipAutoRun(GfComPropertyPc &property);
  static void setAutoRun(GfComPropertyPc &property, bool isAutoRun);
  static bool testAutoRun(GfComPropertyPc &property);
  static void setAutoRunInput(GfComPropertyPc &property);
  static bool isInputInverseDirAutoRun(GfComPropertyPc &property);
  static void setIdleStatus(GfComPropertyPc &property, bool isIdle);
  static void setAirStatus(GfComBehaviorPc &behavior, bool isAir);
  static void setSpecialActStatus(GfComBehaviorPc &behavior, bool isSpecialAct);
  static void notifyJumpEnd(GfComBehaviorPc &behavior);
  static void setEnableWaterIn(GfComBehaviorPc &behavior, bool isEnable);
  static void setWaterMode(GfComBehaviorPc &behavior, bool isWater);
  static void setWaterDiveMove(GfComPropertyPc &property, bool isDive);
  static f32 getChildFrameHeight(GfComponent &component);
  static void resetCameraForWall(GfComBehaviorPc &behavior, Timing timing);
  static void setAsmSpeedSlideBrake(GfComPropertyPc &property);
};

} // namespace pc
} // namespace gf
