#pragma once
#include <stddef.h>

#include "ai/ai_state_hfsm.h"
#include "framework/message/message_object.h"
#include "framework/object/updatable_object.h"
#include "gf/field/gf_field_dmg.h"
#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/field/gf_field_undulator.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "gf/object/component/enemy/gf_beh_field_owner.h"
#include "gf/object/component/enemy/gf_behavior_enemy_field.h"
#include "gf/object/component/enemy/gf_enemy_state_id.h"
#include "gf/object/component/gf_com_transform.h"
#include "mm_math/mm_vec3.h"
#include "mm_mtl/intrusive_ptr.h"
#include "types.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
struct Quat;
} // namespace mm

namespace fw {
class ColiMoveObject;
struct UpdateInfo;
class ReferenceFrame;
} // namespace fw

namespace gmk {
class AGmkBase;
} // namespace gmk

namespace gf {

class GfComAsm;
class GfMenuCallContext;
struct CallBackCache;
struct MsgDebugActivateComponentWindow;
struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;

enum {
  MSG_OBJECT_LURE = 0x1000041,
};

struct MsgObjectLure : fw::Message {};

// Layout evidence: the constructor at 0x7100514074 initializes the members below in this order, the allocation in
// GfObjFactory::createComponent is 0x5510 bytes with 16 byte alignment, and the vtable at 0x119bdd8 holds, after the
// GfComBehavior slots, getTransformToSearchPlayer, getTransform, getBdatId_CHR_EnArrange and getGmkBattleLockInfo followed
// by the IGfBehFieldOwner thunks (offset to the base 0x98).
class GfComBehaviorEnemy : public GfComBehavior, public IGfBehFieldOwner {
public:
  class Listener {
  public:
    Listener() : unknown08(nullptr) {}

    virtual void onWkStandbyLogout();

    GfComBehaviorEnemy *unknown08; // Inferred role: owner; original member name unknown.
  };

  static mm::mtl::RTTI m_rtti;

  GfComBehaviorEnemy();
  ~GfComBehaviorEnemy() override;
  const mm::mtl::RTTI *getRTTI() const override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void update(const fw::UpdateInfo &info) override;
  void procAnimCallback(GfComAsm *comAsm, const CallBackCache &cache) override;
  const fw::Transform &getTransformToSearchPlayer() const override;
  const fw::Transform &getTransform() const override;
  u32 getBdatId_CHR_EnArrange() const override;
  bool getGmkBattleLockInfo(int &param1, int &param2) const override;

  void procMsgObjectNotifyDead(fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgObjectNotifyDamage(fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgActivateComponentDebugWindow(fw::MessageObject *sender, MsgDebugActivateComponentWindow &message);
  void procMsgPcGetLookPoint(fw::MessageObject *sender, MsgPcGetLookPoint &message);
  void procMsgObjectLure(fw::MessageObject *sender, MsgObjectLure &message);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);
  void cleanup();
  gmk::AGmkBase *getBindedGmkInst() const;
  bool isFlyInsect() const;
  bool isFly() const;
  bool isFlyCircle() const;
  bool isWater() const;
  f32 getMoveSpeedDelta(GfBehaviorEnemyField::MoveSpeed moveSpeed) const;
  fw::ColiMoveObject *getColiObject() const;
  void callbackBattle(GfComAsm *comAsm, const CallBackCache &cache);
  void callbackField(GfComAsm *comAsm, const CallBackCache &cache);
  void updateField(const fw::UpdateInfo &info);
  void updateInvincible();
  void disposeMenuObj();
  void validateBattleLock(bool isLock);
  bool extractLoco();
  bool canChangeBattle() const;
  void setStateId(enemy::STATE_ID stateId);
  void updateWeapon();
  void setup();
  void createMenuObj();
  void createFsm();
  f32 getCollisionRadius() const;
  void createBehField();
  void setupWeapon();
  void disposeFsm();
  bool isStateCondMatch(enemy::STATE_ID stateId) const;
  template <typename T> void reqChangeBattleToOtherMember() const;
  void setActivateCollison(bool isActivate);
  void moveProc(mm::Vec3 &velocity);
  void rotProc(f32 angle);
  void rotProc(const mm::Quat &rotation);
  void execTurnCmd(f32 angle);
  void execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4);
  void execTurnCmdAccurately(f32 angle);
  void execTurnCmdToGoal();
  bool isOtherMemberBattle() const;
  template <typename T> bool isOtherMemberBattle() const;
  bool isOtherMemberHome() const;
  template <typename T> bool isOtherMemberHome() const;
  void reqChangeBattle();
  bool validatePopPos(const mm::Vec3 &position, const mm::Vec3 &rotation, bool param3, bool param4);
  void onPopped();
  enemy::STATE_ID getNextFieldStateId() const;
  u32 getStateId() const;

  // Inferred helper: the frame of the transform component, its child frame when there is one; original name unknown.
  const mm::mtl::IntrusivePtr<fw::ReferenceFrame> &unknown001() const {
    GfComTransform *transform = unknown08->getComponent<GfComTransform>();
    return transform->unknown18.get() == nullptr ? transform->unknown10 : transform->unknown18;
  }

  ai::Hfsm unknowna0;                                   // Inferred role: state machine; original member name unknown.
  bool unknown128;                                      // Inferred role: state machine is not set up, true by default; original member name unknown.
  GfMenuCallContext *unknown130;                        // Inferred role: target info menu context; original member name unknown.
  mm::mtl::IntrusivePtr<fw::ReferenceFrame> unknown138; // Inferred role: search base bone frame; original member name unknown.
  GfBehaviorEnemyField unknown140;                      // Inferred role: field behavior; original member name unknown.
  TFieldExecCmdTurn<GfComAsm> unknown53f0;              // Inferred role: turn command; original member name unknown.
  GfFieldUndulator unknown5460;                         // Inferred role: undulator; original member name unknown.
  GfFieldDmg unknown54a0;                               // Inferred role: field damage; original member name unknown.
  u8 _54c8[0x54d0 - 0x54c8];
  mm::Vec3 unknown54d0; // Inferred role: velocity; original member name unknown.
  bool unknown54e0;     // Inferred role: battle lock counted; original member name unknown.
  bool unknown54e1;     // Role and original member name unknown.
  bool unknown54e2;     // Inferred role: request to change to the battle state; original member name unknown.
  bool unknown54e3;     // Inferred role: request to change to the battle state from another squad member; original member name unknown.
  bool unknown54e4;     // Role and original member name unknown.
  u8 _54e5[0x54e8 - 0x54e5];
  void *unknown54e8;    // Inferred role: viewer; original member name unknown.
  Listener unknown54f0; // Inferred role: listener; original member name unknown.
  u8 unknown5500;       // Inferred role: weapon alpha requests; original member name unknown.
  u8 unknown5501;       // Inferred role: weapon alpha values; original member name unknown.
};

static_assert(offsetof(GfComBehaviorEnemy, unknowna0) == 0xa0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown128) == 0x128, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown130) == 0x130, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown138) == 0x138, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown140) == 0x140, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown53f0) == 0x53f0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown54a0) == 0x54a0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown54d0) == 0x54d0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown54e0) == 0x54e0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown54e8) == 0x54e8, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown54f0) == 0x54f0, "");
static_assert(offsetof(GfComBehaviorEnemy, unknown5500) == 0x5500, "");
static_assert(sizeof(GfComBehaviorEnemy::Listener) == 0x10, "");
static_assert(sizeof(GfComBehaviorEnemy) == 0x5510, "");

} // namespace gf
