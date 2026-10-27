#pragma once
#include <stddef.h>

#include "ai/ai_state.h"
#include "gf/gf_state.h"
#include "types.h"

namespace btl {
class BattleCharacter;
class EnemyParameter;
} // namespace btl

namespace fw {
class MessageObject;
struct Message;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorEnemy;
class GfComPropertyEnemy;
struct MsgObjectNotifyAsmCallback;

namespace enemy {
class GfEnemyBattleProperty;
} // namespace enemy

class GfStateBase : public ai::State {
public:
  // Inferred type: the event that ai::Hfsm::execEvent passes to onEvent, forwarded to recieveMessage; original name unknown.
  struct unknown001 {
    fw::MessageObject *unknown00; // Inferred role: sender; original member name unknown.
    fw::Message *unknown08;       // Inferred role: message; original member name unknown.
  };

  bool onEvent(void *owner, void *event) override;
  virtual bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message);
};

namespace enemy {

class StateBattleBase : public GfStateBase {
public:
  StateBattleBase();
  void enter(GfComBehaviorEnemy *behavior, ai::State *previous);
  void leave(GfComBehaviorEnemy *behavior, ai::State *next);
  void update(GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  btl::BattleCharacter *GetBattleCharacter();
  GfComPropertyEnemy *GetProperty();
  const GfComPropertyEnemy *GetPropertyConst() const;
  GfEnemyBattleProperty *GetBattleProperty();
  const GfEnemyBattleProperty *GetBattlePropertyConst() const;
  const btl::EnemyParameter *GetEnemyParameter();
  const btl::EnemyParameter *GetEnemyParameterConst() const;
  bool IsDriver() const;
  bool IsBlade() const;
  virtual bool Enter(GfComBehaviorEnemy *behavior, ai::State *previous) { return true; }
  virtual void Leave(GfComBehaviorEnemy *behavior, ai::State *next) {}
  virtual void BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {}
  virtual void Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {}
  virtual void AfterUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) {}
  virtual bool IsBattleActionState() const { return false; }

  void *mOwner;
  bool mIsEntered;
};

static_assert(offsetof(StateBattleBase, mOwner) == 0x18, "");
static_assert(offsetof(StateBattleBase, mIsEntered) == 0x20, "");

class StateBattleActionBase : public StateBattleBase {
public:
  bool Enter(GfComBehaviorEnemy *behavior, ai::State *previous) override { return true; }
  void BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) override;
  void AfterUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) override;
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void ProcMessageAsmCallback(GfComBehaviorEnemy *behavior, fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message);
  bool IsBattleActionState() const override { return true; }
};

class StateBattle : public StateBattleActionBase {
  GF_STATE_CLASS(StateBattle, GfComBehaviorEnemy)
  bool Enter(GfComBehaviorEnemy *behavior, ai::State *previous) override;
  void Leave(GfComBehaviorEnemy *behavior, ai::State *next) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) override;
  void CheckInvalidTarget(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior);
  bool CheckReturnHome(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior);

  f32 unknown24; // Inferred role: system message timer; original member name unknown.
};

static_assert(offsetof(StateBattle, unknown24) == 0x24, "");

} // namespace enemy
} // namespace gf
