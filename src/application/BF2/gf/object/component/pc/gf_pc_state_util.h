#pragma once

namespace gf {

class GfComBehaviorPc;
struct MsgObjectNotifyDead;

namespace pc {

class StateUtil {
public:
  static void setFallDamageDisable(GfComBehaviorPc &behavior, bool isDisable);
  static void notifyDead(GfComBehaviorPc &behavior, MsgObjectNotifyDead &message, bool isBroadcast);
};

} // namespace pc
} // namespace gf
