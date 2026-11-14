#pragma once
#include <stddef.h>

#include "ai/ai_state_hfsm.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_look_ik.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/game/gf_game_stuck_meter.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {

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
struct MsgGameTalkAction;
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
    Listener() : unknown08(nullptr) {}
    virtual void onWkStandbyLogout();

    GfComBehaviorNpc *unknown08; // Inferred role: owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  struct BdatInfo {
    BdatInfo() : unknown00(0), unknown04(0.0f), unknown08(1.0f), unknown0c(0.0f), unknown10(0), unknown12(0), unknown14(0), unknown16(0), unknown18(0), unknown1a(false) {}
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

  GfComBehaviorNpc();
  ~GfComBehaviorNpc() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void update(const fw::UpdateInfo &info) override;
  virtual GfComAsm *getComAsm() const;

  void setup();
  void cleanup();

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgPcFieldNotifyAction(fw::MessageObject *sender, MsgPcFieldNotifyAction &message);
  void procMsgPcFieldGetAccessType(fw::MessageObject *sender, MsgPcFieldGetAccessType &message);
  void procMsgGameTalkAction(fw::MessageObject *sender, MsgGameTalkAction &message);
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
  void createMenuObj();
  u32 getStateId() const;
  void setStateId(npc::STATE_ID stateId);
  void initStateId(npc::STATE_ID stateId);
  void validateLocalSteer(npc::STATE_ID stateId);
  void setActivateCollison(bool isActivate);
  void createFsm();
  void createNaviMeshObj();
  void updateNaviMeshObj(f32 deltaTime);
  void init(bool param1);
  bool isStateCondMatch(npc::STATE_ID stateId);
  bool isArrivedToGoal() const;
  int getNexStateId();
  void execTurnCmd(f32 angle);
  void execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4);
  void execTurnCmdToGoal();
  void execTurnCmdToPos(const mm::Vec3 &position);
  void moveToGoal(f32 deltaTime);

  // Inferred helper: rotation of the object kept by the reaction state; original name unknown.
  mm::Quat &unknown003() { return unknownd0; }

  // Inferred helper: turn command; original name unknown.
  TFieldExecCmdTurn<GfComAsm> &unknown004() { return unknown2e0; }

  // Inferred helper: goal position; original name unknown.
  mm::Vec3 &unknown005() { return unknownc0; }

  // Inferred helper: reaction motion; original name unknown.
  u16 unknown006() const { return unknown98.unknown12; }

  // Inferred helper: battle motion; original name unknown.
  u16 unknown007() const { return unknown98.unknown16; }

  // Inferred helper: battle reaction; original name unknown.
  u16 unknown008() const { return unknown98.unknown14; }

  BdatInfo unknown98; // Inferred role: bdat parameters; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
  navi::NvmshAcObj *unknownb8; // Inferred role: navi mesh object; original member name unknown.
  mm::Vec3 unknownc0;          // Inferred role: goal position; original member name unknown.
  mm::Quat unknownd0;          // Inferred role: rotation; original member name unknown.
  f32 unknowne0;               // Inferred role: squared distance to the player on the ground plane; original member name unknown.
  f32 unknowne4;               // Inferred role: squared height difference to the player; original member name unknown.
  u8 _e8[0xf0 - 0xe8];
  mm::Vec3 unknownf0; // Inferred role: velocity; original member name unknown.
  bool unknown100;    // Role and original member name unknown.
  bool unknown101;    // Inferred role: reaction rolled flag, set by isStateCondMatch; original member name unknown.
  u8 _102[0x108 - 0x102];
  ai::Hfsm unknown108;                                  // Inferred role: state machine; original member name unknown.
  bool unknown190;                                      // Inferred role: state machine is not set up, true by default; original member name unknown.
  void *unknown198;                                     // Inferred role: viewer; original member name unknown.
  Listener unknown1a0;                                  // Inferred role: listener; original member name unknown.
  GfMenuCallContext *unknown1b0;                        // Inferred role: target info menu context; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown1b8; // Inferred role: look point frame; original member name unknown.
  GfGameStuckMeter unknown1c0;                          // Inferred role: stuck meter; original member name unknown.
  GfGameDepopMeter unknown220;                          // Inferred role: depop meter, its flag is cleared while the player talks to the npc; original member name unknown.
  GfFieldMoveSpeed unknown270;                          // Inferred role: move speed; original member name unknown.
  GfFieldLookIk unknown2a0;                             // Inferred role: look ik; original member name unknown.
  TFieldExecCmdTurn<GfComAsm> unknown2e0;               // Inferred role: turn command; original member name unknown.
  GfFieldLocalSteer unknown350;                         // Inferred role: local steer; original member name unknown.
  LocalSteerIsTargetNotPlayer unknown53b0;              // Inferred role: predicate of the local steer while approaching the player; original member name unknown.
};

static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown04) == 0x04, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown18) == 0x18, "");
static_assert(offsetof(GfComBehaviorNpc::BdatInfo, unknown1a) == 0x1a, "");
static_assert(sizeof(GfComBehaviorNpc::BdatInfo) == 0x1c, "");
static_assert(sizeof(GfComBehaviorNpc::Listener) == 0x10, "");
static_assert(offsetof(GfComBehaviorNpc, unknownb8) == 0xb8, "");
static_assert(offsetof(GfComBehaviorNpc, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorNpc, unknownd0) == 0xd0, "");
static_assert(offsetof(GfComBehaviorNpc, unknowne0) == 0xe0, "");
static_assert(offsetof(GfComBehaviorNpc, unknowne4) == 0xe4, "");
static_assert(offsetof(GfComBehaviorNpc, unknownf0) == 0xf0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown100) == 0x100, "");
static_assert(offsetof(GfComBehaviorNpc, unknown108) == 0x108, "");
static_assert(offsetof(GfComBehaviorNpc, unknown190) == 0x190, "");
static_assert(offsetof(GfComBehaviorNpc, unknown198) == 0x198, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1a0) == 0x1a0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1b0) == 0x1b0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1b8) == 0x1b8, "");
static_assert(offsetof(GfComBehaviorNpc, unknown1c0) == 0x1c0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown220) == 0x220, "");
static_assert(offsetof(GfComBehaviorNpc, unknown270) == 0x270, "");
static_assert(offsetof(GfComBehaviorNpc, unknown2a0) == 0x2a0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown2e0) == 0x2e0, "");
static_assert(offsetof(GfComBehaviorNpc, unknown350) == 0x350, "");
static_assert(offsetof(GfComBehaviorNpc, unknown53b0) == 0x53b0, "");

} // namespace gf
