#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_hfsm.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "framework/sound/sound_res_source_manager.h"
#include "fw/fw_transform.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace mm {
struct Vec3;
} // namespace mm

namespace fw {
class ReferenceFrame;
class ColiObject;
struct UpdateInfo;
} // namespace fw

namespace gf {

struct GF_OBJ_HANDLE;
struct MsgDebugActivateComponentWindow;
struct MsgDebugNotifyReloadLookAtBdat;
struct MsgGameChangeTarget;
struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;
struct MsgPcFieldDrawDebug;
struct MsgPcFieldElvWarp;
struct MsgPcFieldGetFallMaxHeight;
struct MsgPcFieldNotifyHighJump;
struct MsgPcFieldNotifyWall;
struct MsgPcFieldNotifyWallJumpStart;
struct MsgPcFieldNotifyWaterWarp;
struct MsgPcFieldNotifyWaterWarpBuddy;
struct MsgPcFieldReqFallDeadMotion;
struct MsgPcFieldSetFallMaxHeight;
struct MsgPcResetState;
class GfComAsm;

namespace pc {
class Agent;
} // namespace pc
struct CallBackCache;

enum {
  MSG_PC_UNKNOWN_16777221 = 0x1000005, // Inferred role: msg pc get state; original name unknown.
  MSG_PC_UNKNOWN_16777225 = 0x1000009, // Inferred role: msg pc apply field damage; original name unknown.
  MSG_PC_UNKNOWN_16777241 = 0x1000019, // Inferred role: msg pc field warp; original name unknown.
  MSG_PC_UNKNOWN_16777243 = 0x100001b, // Inferred role: msg pc field change control mode; original name unknown.
};

// Layout evidence: StateFieldWaterNormal::procMsgPcFieldWaterWarp (0x7100561cbc) builds it on the stack and
// GfComBehaviorPc::recieveMessage writes the id of the current state to the member at 0x8.
struct MsgPcGetState : fw::Message {
  MsgPcGetState() : fw::Message(MSG_PC_UNKNOWN_16777221, 0x40), unknown08(ai::INVALID_STATE_ID) {}

  u32 unknown08; // Inferred role: current state id; original member name unknown.
};

static_assert(offsetof(MsgPcGetState, unknown08) == 0x08, "");

// Layout evidence: GfGameRide::rideOn and getDown build it on the stack; GfComBehaviorPc::recieveMessage stores the
// transform in the property (or warps now when the member at 0x30 is set) and sets the member at 0x31.
struct MsgPcFieldWarp : fw::Message {
  MsgPcFieldWarp() : fw::Message(MSG_PC_UNKNOWN_16777241, 0x40), unknown30(true), unknown31(false) {}

  fw::Transform unknown10; // Inferred role: target transform; original member name unknown.
  bool unknown30;          // Inferred role: warp now; original member name unknown.
  bool unknown31;          // Inferred role: warp accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldWarp, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldWarp, unknown30) == 0x30, "");
static_assert(offsetof(MsgPcFieldWarp, unknown31) == 0x31, "");

// Layout evidence: GfGameRide::rideOn and getDown build it on the stack with the control mode in the member at 0x8.
struct MsgPcFieldChangeControlMode : fw::Message {
  explicit MsgPcFieldChangeControlMode(u32 mode) : fw::Message(MSG_PC_UNKNOWN_16777243, 0x40), unknown08(mode) {}

  u32 unknown08; // Inferred role: control mode; original member name unknown.
};

static_assert(offsetof(MsgPcFieldChangeControlMode, unknown08) == 0x08, "");

// Layout evidence: GfComBehaviorPc::recieveMessage and procMsgPcApplyFieldDamage pass the member at 0x8 as the damage rate to
// StateUtil::applyDamage; gmk::GmkDmgPhantomManager::update (0x710061f644) builds it on the stack with the id, the mask 0x40 and the rate.
struct MsgPcApplyFieldDamage : fw::Message {
  explicit MsgPcApplyFieldDamage(u8 rate) : fw::Message(MSG_PC_UNKNOWN_16777225, 0x40), unknown08(rate) {}

  u8 unknown08; // Inferred role: damage rate; original member name unknown.
};

static_assert(offsetof(MsgPcApplyFieldDamage, unknown08) == 0x08, "");

// Layout evidence: GfComBehaviorPc::procMsgPcFieldGetAccessTarget stores the object handle of the access plugin in the member at 0x8.
struct MsgPcFieldGetAccessTarget : fw::Message {
  GF_OBJ_HANDLE *unknown08; // Inferred role: access target; original member name unknown.
};

static_assert(offsetof(MsgPcFieldGetAccessTarget, unknown08) == 0x08, "");

class GfComBehaviorPc : public GfComBehavior {
public:
  class Listener {
  public:
    explicit Listener(GfComBehaviorPc *owner) : unknown08(owner) {}

    virtual void onWkStandbyLogout();

    GfComBehaviorPc *unknown08; // Inferred role: owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  GfComBehaviorPc();
  ~GfComBehaviorPc() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void update(const fw::UpdateInfo &info) override;
  void procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) override;
  void callbackBattle(GfComAsm *comAsm, const CallBackCache &cache);
  void callbackField(GfComAsm *comAsm, const CallBackCache &cache);
  void callbackSound(const fw::ResSoundData &data, fw::SoundResSourceManager::CustomInfo *info);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setEnableAgentField(bool isEnable);
  void setEnableAgentBattle(bool isEnable);
  void procMsgPcApplyFieldDamage(fw::MessageObject *sender, MsgPcApplyFieldDamage &message);
  void procMsgPcGetState(fw::MessageObject *sender, MsgPcGetState &message);
  void procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message);
  void procMsgPcResetState(fw::MessageObject *sender, MsgPcResetState &message);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  void procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgDebugNotifyReloadLookAtBdat(fw::MessageObject *sender, MsgDebugNotifyReloadLookAtBdat &message);
  void procMsgPcFieldNotifyWall(fw::MessageObject *sender, MsgPcFieldNotifyWall &message);
  void procMsgPcFieldNotifyHighJump(fw::MessageObject *sender, MsgPcFieldNotifyHighJump &message);
  void procMsgPcFieldNotifyWallJumpStart(fw::MessageObject *sender, MsgPcFieldNotifyWallJumpStart &message);
  void procMsgPcFieldNotifyWaterWarp(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarp &message);
  void procMsgPcFieldNotifyWaterWarpBuddy(fw::MessageObject *sender, MsgPcFieldNotifyWaterWarpBuddy &message);
  void procMsgPcFieldGetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldGetFallMaxHeight &message);
  void procMsgPcFieldSetFallMaxHeight(fw::MessageObject *sender, MsgPcFieldSetFallMaxHeight &message);
  void procMsgPcFieldGetAccessTarget(fw::MessageObject *sender, MsgPcFieldGetAccessTarget &message);
  void procMsgPcFieldReqFallDeadMotion(fw::MessageObject *sender, MsgPcFieldReqFallDeadMotion &message);
  void procMsgPcFieldWarp(fw::MessageObject *sender, MsgPcFieldWarp &message);
  void procMsgPcFieldElvWarp(fw::MessageObject *sender, MsgPcFieldElvWarp &message);
  void procMsgPcFieldChangeControlMode(fw::MessageObject *sender, MsgPcFieldChangeControlMode &message);
  void procMsgPcFieldDrawDebugAccess(fw::MessageObject *sender, MsgPcFieldDrawDebug &message);
  void procMsgGameChangeTarget(fw::MessageObject *sender, MsgGameChangeTarget &message);
  bool warp();
  bool warpNormal(GfComPropertyPc &property);
  bool warpWall(GfComPropertyPc &property);
  bool warpBattle(GfComPropertyPc &property);
  bool warpFallDead(GfComPropertyPc &property);
  bool warpExternal(GfComPropertyPc &property, const fw::Transform &transform);
  void onWarp(GfComPropertyPc &property);
  void onWarpNormal(GfComPropertyPc &property);
  void onWarpWall(GfComPropertyPc &property);
  void onWarpBattle(GfComPropertyPc &property);
  void onWarpFallDead(GfComPropertyPc &property);
  void onWarpBeforeTransform(GfComPropertyPc &property);
  void onWarpAfterTransform(GfComPropertyPc &property);
  void resetHeadColiPos(GfComPropertyPc &property);
  void resetHeadColPosition(const fw::Transform &transform);
  void calcHeadColiPos(f32 height, const fw::Transform &transform, mm::Vec3 *position);
  void detectHead(GfComPropertyPc &property, fw::ColiObject *coli, const mm::Vec3 &move, fw::Transform *transform);
  void notifyGround();
  void integrateMove(const fw::UpdateInfo &info);
  void integrateMoveNormal(const fw::UpdateInfo &info, GfComPropertyPc &property);
  void integrateMoveChildHeight(const fw::UpdateInfo &info, GfComPropertyPc &property);
  void integrateMoveWall(const fw::UpdateInfo &info, GfComPropertyPc &property);
  void cleanup();

  GfComPropertyPc *getProperty() const { return mm::mtl::dynamicCast<GfComPropertyPc>(unknown08->unknown38[GfComPropertyPc::COMPONENT_INDEX]); }

  mm::mtl::UniquePtr<pc::Agent> unknown98;              // Inferred role: agent, tested by setEnableAgentField; original member name unknown.
  ai::Hfsm unknowna0;                                   // Inferred role: state machine; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown128; // Inferred role: look point frame; original member name unknown.
  void *unknown130;                                     // Inferred role: viewer; original member name unknown.
  Listener unknown138;                                  // Inferred role: listener; original member name unknown.
};

static_assert(offsetof(GfComBehaviorPc, unknown98) == 0x98, "");
static_assert(offsetof(GfComBehaviorPc, unknowna0) == 0xa0, "");
static_assert(offsetof(GfComBehaviorPc, unknown128) == 0x128, "");
static_assert(offsetof(GfComBehaviorPc, unknown130) == 0x130, "");
static_assert(offsetof(GfComBehaviorPc, unknown138) == 0x138, "");
static_assert(sizeof(GfComBehaviorPc::Listener) == 0x10, "");
static_assert(sizeof(GfComBehaviorPc) == 0x148, "");

} // namespace gf
