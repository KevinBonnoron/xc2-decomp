#pragma once
#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
class MessageObject;
} // namespace fw

namespace gf {

class GfComBehaviorPc;
struct MsgPcFieldHighJump;

namespace pc {

class StateFieldIdle : public GfStateBase {
  GF_STATE_CLASS(StateFieldIdle, GfComBehaviorPc)
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  bool checkSpace(GfComBehaviorPc *behavior) const;
  void procMsgPcFieldHighJump(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldHighJump &message);
};

static_assert(sizeof(StateFieldIdle) == 0x18, "");

} // namespace pc
} // namespace gf
