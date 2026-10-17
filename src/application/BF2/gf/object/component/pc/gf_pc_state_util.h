#pragma once
#include "types.h"

#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComBehaviorPc;
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDead;

namespace pc {

class StateUtil {
public:
  static void resetCamera();
  static bool isManualCamera();
  static void setTarget(GfComBehaviorPc &behavior, GF_OBJ_HANDLE *target);
  static void setTargetLock(bool isLock);
  static bool isBattle(GfComBehaviorPc &behavior);
  static void setEnableAgentField(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableAgentBattle(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableGravity(GfComBehaviorPc &behavior, bool isEnable);
  static bool testEnableGravity(GfComBehaviorPc &behavior);
  static void setFallDamageDisable(GfComBehaviorPc &behavior, bool isDisable);
  static void setEnableDownIK(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableLookIK(GfComBehaviorPc &behavior, bool isEnable);
  static void changePlacementDownDist(GfComBehaviorPc &behavior, f32 distance);
  static void resetPlacementDownDist(GfComBehaviorPc &behavior);
  static void changeGroundAnglesForMotion(GfComBehaviorPc &behavior, const mm::Vec3 &angles);
  static void setEnvSensor(GfComBehaviorPc &behavior, u32 flags, bool isEnable);
  static void setActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type, bool isActive);
  static void notifyDead(GfComBehaviorPc &behavior, MsgObjectNotifyDead &message, bool isBroadcast);
  static void setEnableFallDistChecker(GfComBehaviorPc &behavior, bool isEnable);
};

} // namespace pc
} // namespace gf
