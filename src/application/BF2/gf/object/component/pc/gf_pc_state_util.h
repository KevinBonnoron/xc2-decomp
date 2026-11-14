#pragma once
#include <stddef.h>

#include "types.h"

#include "framework/message/message_object.h"
#include "gf/object/component/env_sensor/gf_com_env_sensor.h"
#include "gf/object/component/pc/plugin/gf_pc_timer_plugin.h"

namespace fw {
enum VibrationID : int;
} // namespace fw

namespace mm {
struct Vec3;
} // namespace mm

namespace gf {

class GfComBehaviorPc;
struct GF_OBJ_HANDLE;
struct MsgObjectNotifyDead;
struct MsgObjectNotifyHealHp;

enum {
  MSG_PC_FIELD_UNKNOWN_16777235 = 0x1000013, // Inferred role: msg pc field wall jump; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777238 = 0x1000016, // Inferred role: msg pc field high jump; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777240 = 0x1000018, // Inferred role: msg pc field water warp; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777246 = 0x100001e, // Inferred role: msg pc field relay survive; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777248 = 0x1000020, // Inferred role: msg pc field water warp buddy; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777252 = 0x1000024, // Inferred role: msg pc field notify rider event; original name unknown.
  MSG_PC_FIELD_UNKNOWN_16777253 = 0x1000025, // Inferred role: msg pc field req fall dead motion; original name unknown.
};

// Layout evidence: TaskFieldWallJumpWait::update (0x7100545800) builds it on the stack and tests the member at 0x8 that
// StateFieldOnWall::procMsgPcFieldWallJump sets.
struct MsgPcFieldWallJump : fw::Message {
  MsgPcFieldWallJump() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777235, 0x40), unknown08(false) {}

  bool unknown08; // Inferred role: wall jump accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldWallJump, unknown08) == 0x08, "");

// Layout evidence: TaskFieldSensor::update (0x7100544988) builds it on the stack and tests the member at 0x8 that
// StateFieldIdle::procMsgPcFieldHighJump sets.
struct MsgPcFieldHighJump : fw::Message {
  MsgPcFieldHighJump() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777238, 0x40), unknown08(false) {}

  bool unknown08; // Inferred role: high jump accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldHighJump, unknown08) == 0x08, "");

// Layout evidence: TaskFieldSensor::update (0x7100544988) builds it on the stack and tests the member at 0x8 that
// StateFieldWaterNormal::procMsgPcFieldWaterWarp sets.
struct MsgPcFieldWaterWarp : fw::Message {
  MsgPcFieldWaterWarp() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777240, 0x40), unknown08(false) {}

  bool unknown08; // Inferred role: warp accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldWaterWarp, unknown08) == 0x08, "");

// Layout evidence: TaskFieldSensor::update (0x7100544988) builds it on the stack and tests the member at 0x8 that
// StateFieldWaterNormal::procMsgPcFieldWaterWarpBuddy sets.
struct MsgPcFieldWaterWarpBuddy : fw::Message {
  MsgPcFieldWaterWarpBuddy() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777248, 0x40), unknown08(false) {}

  bool unknown08; // Inferred role: warp accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldWaterWarpBuddy, unknown08) == 0x08, "");

// Layout evidence: the pc states build it on the stack (0x710053cbcc) with a MsgObjectNotifyHealHp or a MsgObjectNotifyDead,
// and StateFieldDead::procMsgPcFieldRelaySurvive reads the member at 0x8.
struct MsgPcFieldRelaySurvive : fw::Message {
  explicit MsgPcFieldRelaySurvive(fw::Message *message) : fw::Message(MSG_PC_FIELD_UNKNOWN_16777246, 0x40), unknown08(message) {}

  fw::Message *unknown08; // Inferred role: heal or dead notification relayed to the buddy; original member name unknown.
};

struct MsgPcFieldReqFallDeadMotion : fw::Message {
  MsgPcFieldReqFallDeadMotion() : fw::Message(MSG_PC_FIELD_UNKNOWN_16777253, 0x40) {}
};

namespace pc {

class StateUtil {
public:
  static u32 getFwPadKey(const char *name);
  static void resetCamera();
  static bool isManualCamera();
  static GF_OBJ_HANDLE *getTarget(const GfComBehaviorPc &behavior);
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
  static void setEnableSpineIK(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableSpineRotate(GfComBehaviorPc &behavior, bool isEnable, f32 time);
  static void setSpineRotateAngles(GfComBehaviorPc &behavior, f32 yaw, f32 pitch);
  static void changePlacementDownDist(GfComBehaviorPc &behavior, f32 distance);
  static void resetPlacementDownDist(GfComBehaviorPc &behavior);
  static void changeGroundAnglesForMotion(GfComBehaviorPc &behavior, const mm::Vec3 &angles);
  static void setEnvSensor(GfComBehaviorPc &behavior, u32 flags, bool isEnable);
  static bool testEnvSensor(GfComBehaviorPc &behavior, EnviromentSensor::Flag flag);
  static void setEnableAttach(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableTimer(GfComBehaviorPc &behavior, bool isEnable);
  static void setEnableHeadDetectForSwitcher(GfComBehaviorPc &behavior, bool isEnable);
  static void setActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type, bool isActive);
  static const f32 *getActivateTimer(GfComBehaviorPc &behavior, TimerPlugin::TYPE type);
  static void switchPlacementIK(GfComBehaviorPc &behavior, bool isOn);
  static void setLipSpeed(GfComBehaviorPc &behavior, f32 speed);
  static void setEnableFootStep(GfComBehaviorPc &behavior, bool isEnable);
  static void notifyDead(GfComBehaviorPc &behavior, MsgObjectNotifyDead &message, bool isBroadcast);
  static void setEnableFallDistChecker(GfComBehaviorPc &behavior, bool isEnable);
  static EnviromentSensor::GroundInfo *getGroundInfo(GfComBehaviorPc &behavior);
  static void applyDamage(GfComBehaviorPc &behavior, u32 rate, bool isTerrain);
  static EnviromentSensor::unknown003 *getClimbWallInfo(GfComBehaviorPc &behavior);
  static EnviromentSensor::GroundInfo *getClimbEndGroundInfo(GfComBehaviorPc &behavior);
  static EnviromentSensor::unknown003 *getDescendWallInfo(GfComBehaviorPc &behavior);
  static EnviromentSensor::unknown001 *getWaterInfo(GfComBehaviorPc &behavior);
  static EnviromentSensor::unknown002 *getDeadPlaneInfo(GfComBehaviorPc &behavior);
  static bool isOnSlideGround(GfComBehaviorPc &behavior);
  static GF_OBJ_HANDLE *getBuddyHandle(GfComBehaviorPc &behavior);
  static void sendMessageToBuddy(GfComBehaviorPc &behavior, fw::Message &message);
  static void notifyRevival(GfComBehaviorPc &behavior, MsgObjectNotifyHealHp &message);
  static bool sendMessageToRider(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastDriver(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastBlade(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastPlayer(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastMainChar(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastDriverAll(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastBladeAll(GfComBehaviorPc &behavior, fw::Message &message);
  static void broadcastPlayerAll(GfComBehaviorPc &behavior, fw::Message &message);
  static void sendMessageGfObj(GfComBehaviorPc &behavior, GF_OBJ_HANDLE *handle, fw::Message &message);
  static void playVibration(GfComBehaviorPc &behavior, fw::VibrationID id);
  static void reflectionAdsorption(GfComBehaviorPc &behavior);
};

} // namespace pc
} // namespace gf
