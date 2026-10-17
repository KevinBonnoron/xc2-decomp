#pragma once
#include <stddef.h>

#include "ai/ai_state.h"

namespace btl {
class BattleCharacter;
}

namespace fw {
class MessageObject;
struct Message;
struct UpdateInfo;
} // namespace fw

namespace gf {

class GfComBehaviorEnemy;

class GfStateBase : public ai::State {
public:
  void onEvent(void *owner, void *event) override;
  virtual void recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message);
};

namespace enemy {

class StateBattleActionBase : public GfStateBase {
public:
  void recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  virtual bool Enter(GfComBehaviorEnemy *behavior, ai::State *previous) = 0;
  virtual void Leave(GfComBehaviorEnemy *behavior, ai::State *next) = 0;
  virtual void BeforeUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  virtual void Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) = 0;
  virtual void AfterUpdate(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info);
  virtual bool IsBattleActionState() const;

  void *mOwner;
  bool mIsEntered;
};

static_assert(offsetof(StateBattleActionBase, mOwner) == 0x18, "");
static_assert(offsetof(StateBattleActionBase, mIsEntered) == 0x20, "");

class StateBattle : public StateBattleActionBase {
public:
  ~StateBattle() override;
  const char *getName() const override;
  void onEnter(void *owner, ai::State *previous) override;
  void onLeave(void *owner, ai::State *next) override;
  void onStep(void *owner, const void *param) override;
  bool Enter(GfComBehaviorEnemy *behavior, ai::State *previous) override;
  void Leave(GfComBehaviorEnemy *behavior, ai::State *next) override;
  void Update(btl::BattleCharacter *character, GfComBehaviorEnemy *behavior, const fw::UpdateInfo &info) override;
};

} // namespace enemy
} // namespace gf
