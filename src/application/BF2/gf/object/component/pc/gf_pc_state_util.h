#pragma once
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComBehaviorPc;
struct MsgObjectNotifyDead;

namespace pc {

class StateUtil {
public:
  static void setEnableGravity(GfComBehaviorPc &behavior, bool isEnable);
  static void setFallDamageDisable(GfComBehaviorPc &behavior, bool isDisable);
  static void setEnableDownIK(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableLookIK(GfComBehaviorPc &behavior, bool isEnable);
  static void resetPlacementDownDist(GfComBehaviorPc &behavior);
  static void changeGroundAnglesForMotion(GfComBehaviorPc &behavior, const mm::Vec3 &angles);
  static void setActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type, bool isActive);
  static void notifyDead(GfComBehaviorPc &behavior, MsgObjectNotifyDead &message, bool isBroadcast);
  static void setEnableFallDistChecker(GfComBehaviorPc &behavior, bool isEnable);
};

} // namespace pc
} // namespace gf
