#pragma once
#include <stddef.h>

#include "ai/ai_state_hfsm.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
struct Quat;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class ColiMoveObject;
class MessageObject;
class ReferenceFrame;
} // namespace fw

namespace gmk {
class AGmkBase;
class GmkRouteNavi;
} // namespace gmk

namespace navi {
class NvmshAcObj;
} // namespace navi

struct CBdatWrapper;

namespace gf {

class GfComAsm;
class GfMenuCallContext;
struct MsgDebugActivateComponentWindow;
struct MsgGameLipAction;
struct MsgGameSetLipWeight;

namespace npc {

// The original enumerator names are unknown. The states registered by GfComBehaviorNpc::createFsm are noted for each id.
enum STATE_ID {
  STATE_ID_UNKNOWN_0 = 0, // StateIdle
  STATE_ID_UNKNOWN_1 = 1, // StateWalk
  STATE_ID_UNKNOWN_2 = 2, // StateAreaMove
  STATE_ID_UNKNOWN_3 = 3, // StateApproachPc
  STATE_ID_UNKNOWN_4 = 4, // StateReaction
  STATE_ID_UNKNOWN_5 = 5, // StateBattle
  STATE_ID_UNKNOWN_6 = 6, // StateTalk
};

} // namespace npc

class GfComBehaviorNpc : public GfComBehavior {
public:
  class LocalSteerIsTargetNotPlayer : public unknown001 {
  public:
    bool operator()(const GfFieldLocalSteer &steer, GF_OBJ_HANDLE *handle) const override;
  };

  class Listener {
  public:
    virtual void onWkStandbyLogout();

    GfComBehaviorNpc *unknown08; // Inferred role: owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  struct BdatInfo {
    void create(const CBdatWrapper &bdat, int id, const GfComBehaviorNpc &npc);
    int getTalkBonusFlagId() const;
    bool isIconTalkBonus() const;
    void setTalkBonusFlag() const;
    static f32 getDistYThreshold();

    u16 unknown00;  // Inferred role: shop id; original member name unknown.
    f32 unknown04;  // Inferred role: squared close range; original member name unknown.
    f32 unknown08;  // Inferred role: move speed; original member name unknown.
    f32 unknown0c;  // Inferred role: squared reaction range; original member name unknown.
    u16 unknown10;  // Inferred role: reaction percent; original member name unknown.
    u16 unknown12;  // Inferred role: reaction motion; original member name unknown.
    u16 unknown14;  // Inferred role: battle reaction; original member name unknown.
    u16 unknown16;  // Inferred role: battle motion; original member name unknown.
    u16 unknown18;  // Inferred role: event id used as talk bonus; original member name unknown.
    bool unknown1a; // Inferred role: talk bonus enabled; original member name unknown.
  };

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgPcFieldNotifyAction(fw::MessageObject *sender, MsgPcFieldNotifyAction &message);
  void procMsgPcFieldGetAccessType(fw::MessageObject *sender, MsgPcFieldGetAccessType &message);
  void procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message);
  void procMsgGameLipAction(fw::MessageObject *sender, MsgGameLipAction &message);
  void procMsgGameSetLipWeight(fw::MessageObject *sender, MsgGameSetLipWeight &message);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  gmk::GmkRouteNavi *getGmkRouteNavi() const;
  const mm::Vec3 &getPos() const;
  const mm::Quat &getRot() const;
  void disposeNaviMeshObj();
  void validateBindedGmkInstInfo(bool param1);
  gmk::AGmkBase *getBindedGmkInst() const;
  void setGoalPos(const mm::Vec3 &position);
  bool isNullNpc() const;
  fw::ColiMoveObject *getColiObject() const;
  void disposeFsm();
  void disposeMenuObj();
  u32 getStateId() const;
  void setStateId(npc::STATE_ID stateId);
  void initStateId(npc::STATE_ID stateId);
  void validateLocalSteer(npc::STATE_ID stateId);
  void setActivateCollison(bool isActivate);
  GfComAsm *getComAsm() const;

  u8 _98[0xb8 - 0x98];
  navi::NvmshAcObj *unknownb8; // Inferred role: navi mesh object; original member name unknown.
  mm::Vec3 unknownc0;          // Inferred role: goal position; original member name unknown.
  u8 _d0[0xf0 - 0xd0];
  mm::Vec3 unknownf0; // Inferred role: velocity; original member name unknown.
  bool unknown100;    // Role and original member name unknown.
  u8 _101[0x108 - 0x101];
  ai::Hfsm unknown108;                                  // Inferred role: state machine; original member name unknown.
  bool unknown190;                                      // Inferred role: state machine is not set up, true by default; original member name unknown.
  void *unknown198;                                     // Inferred role: viewer; original member name unknown.
  Listener unknown1a0;                                  // Inferred role: listener; original member name unknown.
  GfMenuCallContext *unknown1b0;                        // Inferred role: target info menu context; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown1b8; // Inferred role: look point frame; original member name unknown.
  u8 _1c0[0x240 - 0x1c0];
  bool unknown240; // Inferred role: set when the talk access ends; original member name unknown.
  u8 _241[0x2e0 - 0x241];
  TFieldExecCmdTurn<GfComAsm> unknown2e0;  // Inferred role: turn command; original member name unknown.
  GfFieldLocalSteer unknown350;            // Inferred role: local steer; original member name unknown.
  LocalSteerIsTargetNotPlayer unknown53b0; // Inferred role: predicate of the local steer while approaching the player; original member name unknown.
};

static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown18) == 0x18, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown1a) == 0x1a, "");
static_assert(sizeof(GfComBehaviorNpc::BdatInfo) == 0x1c, "");
static_assert(sizeof(GfComBehaviorNpc::Listener) == 0x10, "");
static_assert(offsetof(GfComBehaviorNpc, unknownb8) == 0xb8, "");
static_assert(offsetof(GfComBehaviorNpc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorNpc, unknownf0) == 0xf0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown100) == 0x100, "");
static_assert(offsetof(GfComBehaviorNpc, unknown108) == 0x108, "");
static_assert(offsetof(GfComBehaviorNpc, unknown190) == 0x190, "");
static_assert(offsetof(GfComBehaviorNpc, unknown198) == 0x198, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1b0) == 0x1b0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GfComBehaviorNpc, unknown240) == 0x240, "");
static_assert(offsetof(GfComBehaviorNpc, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown350) == 0x350, "");
static_assert(offsetof(GfComBehaviorNpc, unknown53b0) == 0x53b0, "");

} // namespace gf
