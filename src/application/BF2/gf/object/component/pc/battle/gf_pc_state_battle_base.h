#pragma once
#include <stddef.h>

#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "gf/object/component/pc/gf_pc_state_id.h"

namespace ai {
class State;
} // namespace ai

namespace btl {
class BattleCharacter;
class PlayerParameter;
} // namespace btl

namespace fw {
class MessageObject;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorPc;
class GfComPropertyPc;
struct MsgObjectNotifyAsmCallback;
struct MsgObjectNotifyDamage;
struct MsgObjectNotifyDead;
struct MsgObjectNotifyHealHp;
struct MsgPcBattleEnd;

namespace pc {

class GfPropertyBattle;

class StateBattleBase : public GfStateBase {
public:
  StateBattleBase();
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  btl::BattleCharacter *GetBattleCharacter();
  void ChangeState(STATE_ID state, int param);
  GfPropertyBattle *GetBattleProperty();
  GfComPropertyPc *GetProperty();
  const GfComPropertyPc *GetPropertyConst() const;
  const GfPropertyBattle *GetBattlePropertyConst() const;
  btl::PlayerParameter *GetPlayerParameter();
  const btl::PlayerParameter *GetPlayerParameterConst() const;
  bool IsDriver() const;
  bool IsBlade() const;
  void recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgObjectNotifyDamage(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDamage &message);
  void procMsgObjectNotifyDead(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyDead &message);
  void procMsgObjectNotifyHealHp(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyHealHp &message);
  virtual bool Enter(GfComBehaviorPc *behavior, ai::State *previous) { return true; }
  virtual void Leave(GfComBehaviorPc *behavior, ai::State *next) {}
  virtual void BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}
  virtual void Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}
  virtual void AfterUpdate(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) {}
  virtual bool IsBattleActionState() const { return false; }

  GfComBehaviorPc *unknown18; // Inferred role: behavior; original member name unknown.
  bool unknown20;             // Inferred role: entered; original member name unknown.
  bool unknown21;             // Inferred role: state changed; original member name unknown.
};

static_assert(offsetof(StateBattleBase, unknown18) == 0x18, "");
static_assert(offsetof(StateBattleBase, unknown20) == 0x20, "");
static_assert(offsetof(StateBattleBase, unknown21) == 0x21, "");

class StateBattleActionBase : public StateBattleBase {
public:
  bool Enter(GfComBehaviorPc *behavior, ai::State *previous) override;
  void BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) override;
  void AfterUpdate(btl::BattleCharacter *character, GfComBehaviorPc *behavior, const fw::UpdateInfo &info) override;
  void recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void ProcMessageAsmCallback(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgObjectNotifyAsmCallback &message);
  void ProcMessageBattleEnd(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcBattleEnd &message);
  bool IsBattleActionState() const override { return true; }
};

} // namespace pc
} // namespace gf
