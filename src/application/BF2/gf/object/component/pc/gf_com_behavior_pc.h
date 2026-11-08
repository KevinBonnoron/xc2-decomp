#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "ai/ai_state_hfsm.h"
#include "framework/message/message_object.h"
#include "framework/object/component_object.h"
#include "framework/object/updatable_object.h"
#include "fw/fw_transform.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/pc/gf_com_property_pc.h"
#include "mm_mtl/intrusive_ptr.h"
#include "mm_mtl/rtti.h"
#include "mm_mtl/unique_ptr.h"
#include "types.h"

namespace fw {
class ReferenceFrame;
} // namespace fw

namespace gf {

struct MsgDebugActivateComponentWindow;
class GfComAsm;
namespace pc {
class Agent;
} // namespace pc
struct CallBackCache;

enum {
  MSG_PC_GET_STATE = 0x1000005,
  MSG_PC_FIELD_WARP = 0x1000019,
  MSG_PC_FIELD_CHANGE_CONTROL_MODE = 0x100001b,
};

// Layout evidence: StateFieldWaterNormal::procMsgPcFieldWaterWarp (0x7100561cbc) builds it on the stack and
// GfComBehaviorPc::recieveMessage writes the id of the current state to the member at 0x8.
struct MsgPcGetState : fw::Message {
  MsgPcGetState() : fw::Message(MSG_PC_GET_STATE, 0x40), unknown08(ai::INVALID_STATE_ID) {}

  u32 unknown08; // Inferred role: current state id; original member name unknown.
};

static_assert(offsetof(MsgPcGetState, unknown08) == 0x08, "");

// Layout evidence: GfGameRide::rideOn and getDown build it on the stack; GfComBehaviorPc::recieveMessage stores the
// transform in the property (or warps now when the member at 0x30 is set) and sets the member at 0x31.
struct MsgPcFieldWarp : fw::Message {
  MsgPcFieldWarp() : fw::Message(MSG_PC_FIELD_WARP, 0x40), unknown30(true), unknown31(false) {}

  fw::Transform unknown10; // Inferred role: target transform; original member name unknown.
  bool unknown30;          // Inferred role: warp now; original member name unknown.
  bool unknown31;          // Inferred role: warp accepted; original member name unknown.
};

static_assert(offsetof(MsgPcFieldWarp, unknown10) == 0x10, "");
static_assert(offsetof(MsgPcFieldWarp, unknown30) == 0x30, "");
static_assert(offsetof(MsgPcFieldWarp, unknown31) == 0x31, "");

// Layout evidence: GfGameRide::rideOn and getDown build it on the stack with the control mode in the member at 0x8.
struct MsgPcFieldChangeControlMode : fw::Message {
  explicit MsgPcFieldChangeControlMode(u32 mode) : fw::Message(MSG_PC_FIELD_CHANGE_CONTROL_MODE, 0x40), unknown08(mode) {}

  u32 unknown08; // Inferred role: control mode; original member name unknown.
};

static_assert(offsetof(MsgPcFieldChangeControlMode, unknown08) == 0x08, "");

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
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void setEnableAgentField(bool isEnable);
  void setEnableAgentBattle(bool isEnable);

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
