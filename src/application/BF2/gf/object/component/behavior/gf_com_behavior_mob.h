#pragma once
#include <stddef.h>

#include "ai/ai_state_hfsm.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_local_steer.h"
#include "gf/field/gf_field_look_ik.h"
#include "gf/field/gf_field_move_speed.h"
#include "gf/game/gf_game_stuck_meter.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gmk/gmk_squad.h"
#include "mm_math/mm_quat.h"
#include "mm_math/mm_vec3.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace fw {
class ColiMoveObject;
class MessageObject;
} // namespace fw

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace navi {
class NvmshAcObj;
} // namespace navi

struct CBdatWrapper;

namespace gf {

struct MsgDebugActivateComponentWindow;
class GfComAsm;

namespace mob {

// The original enumerator names are unknown. The states registered by GfComBehaviorMob::createFsm are noted for each id.
enum STATE_ID {
  STATE_ID_UNKNOWN_0 = 0, // StateIdle
  STATE_ID_UNKNOWN_1 = 1, // StateMove
  STATE_ID_UNKNOWN_2 = 2, // npc::StateAreaMove
  STATE_ID_UNKNOWN_3 = 3, // StateSquadMember
  STATE_ID_UNKNOWN_4 = 4, // npc::StateReaction
  STATE_ID_UNKNOWN_5 = 5, // npc::StateBattle
};

} // namespace mob

// Layout from its constructor (0x710052b4c4), destructor and cleanup: the navi mesh object at 0xa8, the squad navi at 0xc0,
// the velocity at 0x100 read by recieveMessage, the state machine at 0x5328 and the listener at 0x53c0.
class GfComBehaviorMob : public GfComBehavior {
public:
  class Listener {
  public:
    Listener() : unknown08(nullptr) {}

    virtual void onWkStandbyLogout();

    GfComBehaviorMob *unknown08; // Inferred role: owner; original member name unknown.
  };

  struct BdatInfo {
    void create(const CBdatWrapper &bdat, int id);

    f32 unknown00; // Inferred role: squared reaction range; original member name unknown.
    u16 unknown04; // Inferred role: reaction percent; original member name unknown.
    u16 unknown06; // Inferred role: reaction motion; original member name unknown.
    u16 unknown08; // Inferred role: battle reaction; original member name unknown.
    u16 unknown0a; // Inferred role: battle motion; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  GfComBehaviorMob();
  ~GfComBehaviorMob() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void update(const fw::UpdateInfo &info) override;
  virtual const mm::Vec3 &getPos() const;
  virtual const mm::Quat &getRot() const;

  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  void setup();
  void cleanup();
  fw::ColiMoveObject *getColiObject() const;
  gmk::AGmkBase *getBindedGmkInst() const;
  bool isSquadMember() const;
  bool isMove() const;
  void initMoveSpeed(f32 time);
  void setStateId(mob::STATE_ID stateId);
  void disposeNaviMeshObj();
  void disposeFsm();
  void disposeSquadNavi();
  void setActivateCollison(bool isActivate);
  u32 getStateId() const;
  void createNaviMeshObj();
  void updateNaviMeshObj(f32 deltaTime);
  void createSquadNavi();
  void createFsm();
  void init(bool param1);
  bool isStateCondMatch(mob::STATE_ID stateId);
  void execTurnCmdToGoal();
  void execTurnCmdToPos(const mm::Vec3 &position);
  bool isArrivedToGoal() const;
  void moveToGoal(f32 deltaTime);

  // Inferred helper: rotation of the object kept by the reaction state; original name unknown.
  mm::Quat &unknown003() { return unknown120; }

  // Inferred helper: turn command; original name unknown.
  TFieldExecCmdTurn<GfComAsm> &unknown004() { return unknown250; }

  // Inferred helper: goal position; original name unknown.
  mm::Vec3 &unknown005() { return unknown110; }

  // Inferred helper: reaction motion; original name unknown.
  u16 unknown006() const { return unknown98.unknown06; }

  // Inferred helper: battle motion; original name unknown.
  u16 unknown007() const { return unknown98.unknown0a; }

  // Inferred helper: battle reaction; original name unknown.
  u16 unknown008() const { return unknown98.unknown08; }

  // Inferred helper: squad of the squad navi; original name unknown.
  gmk::GmkSquad *unknown009() const { return unknownc0.unknown10.unknown00; }

  BdatInfo unknown98; // Inferred role: bdat parameters; original member name unknown.
  u8 _a4[0xa8 - 0xa4];
  navi::NvmshAcObj *unknowna8; // Inferred role: navi mesh object; original member name unknown.
  u32 unknownb0;               // Inferred role: reset with the navi mesh object; original member name unknown.
  u8 _b4[0xb8 - 0xb4];
  void *unknownb8;                                                        // Role and original member name unknown.
  gmk::GmkSquadNavi unknownc0;                                            // Inferred role: squad navi; original member name unknown.
  mm::Vec3 unknown100;                                                    // Inferred role: velocity; original member name unknown.
  mm::Vec3 unknown110;                                                    // Inferred role: goal position; original member name unknown.
  mm::Quat unknown120;                                                    // Inferred role: rotation; original member name unknown.
  GfGameStuckMeter unknown130;                                            // Inferred role: stuck meter; original member name unknown.
  GfGameDepopMeter unknown190;                                            // Inferred role: depop meter; original member name unknown.
  GfFieldMoveSpeed unknown1e0;                                            // Inferred role: move speed; original member name unknown.
  GfFieldLookIk unknown210;                                               // Inferred role: look ik; original member name unknown.
  TFieldExecCmdTurn<GfComAsm> unknown250;                                 // Inferred role: turn command; original member name unknown.
  GfFieldLocalSteer unknown2c0;                                           // Inferred role: local steer; original member name unknown.
  GfFieldLocalSteer::TIsTargetNotSameSquad<GfComBehaviorMob> unknown5320; // Inferred role: predicate of the local steer; original member name unknown.
  ai::Hfsm unknown5328;                                                   // Inferred role: state machine; original member name unknown.
  bool unknown53b0;                                                       // Inferred role: state machine is not set up, true by default; original member name unknown.
  void *unknown53b8;                                                      // Inferred role: viewer; original member name unknown.
  Listener unknown53c0;                                                   // Inferred role: listener; original member name unknown.
  f32 unknown53d0;                                                        // Inferred role: squared distance to the player on the ground plane; original member name unknown.
  f32 unknown53d4;                                                        // Inferred role: squared height difference to the player; original member name unknown.
  bool unknown53d8;                                                       // Inferred role: reaction rolled while the player is in range; original member name unknown.
  u8 _53d9[0x53e0 - 0x53d9];
};

static_assert(sizeof(GfComBehaviorMob::Listener) == 0x10, "");
static_assert(offsetof(GfComBehaviorMob, unknowna8) == 0xa8, "");
static_assert(offsetof(GfComBehaviorMob, unknownb8) == 0xb8, "");
static_assert(offsetof(GfComBehaviorMob, unknownc0) == 0xc0, "");
static_assert(offsetof(GfComBehaviorMob, unknown100) == 0x100, "");
static_assert(offsetof(GfComBehaviorMob, unknown1e0) == 0x1e0, "");
static_assert(offsetof(GfComBehaviorMob, unknown110) == 0x110, "");
static_assert(sizeof(GfComBehaviorMob::BdatInfo) == 0x0c, "");
static_assert(offsetof(GfComBehaviorMob, unknown98) == 0x98, "");
static_assert(offsetof(GfComBehaviorMob, unknown120) == 0x120, "");
static_assert(offsetof(GfComBehaviorMob, unknown250) == 0x250, "");
static_assert(offsetof(GfComBehaviorMob, unknown2c0) == 0x2c0, "");
static_assert(offsetof(GfComBehaviorMob, unknown5320) == 0x5320, "");
static_assert(offsetof(GfComBehaviorMob, unknown5328) == 0x5328, "");
static_assert(offsetof(GfComBehaviorMob, unknown53b0) == 0x53b0, "");
static_assert(offsetof(GfComBehaviorMob, unknown53b8) == 0x53b8, "");
static_assert(offsetof(GfComBehaviorMob, unknown53c0) == 0x53c0, "");
static_assert(offsetof(GfComBehaviorMob, unknown53d0) == 0x53d0, "");
static_assert(offsetof(GfComBehaviorMob, unknown53d4) == 0x53d4, "");
static_assert(offsetof(GfComBehaviorMob, unknown53d8) == 0x53d8, "");
static_assert(sizeof(GfComBehaviorMob) == 0x53e0, "");

} // namespace gf
