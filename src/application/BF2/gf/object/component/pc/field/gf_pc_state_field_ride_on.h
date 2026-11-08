#pragma once
#include <stddef.h>

#include "gf/gf_state.h"
#include "gf/object/component/enemy/gf_enemy_state_battle.h"
#include "mm_mtl/fixed_queue.h"
#include "mm_mtl/fixstr.h"

namespace ai {
class State;
} // namespace ai

namespace fw {
struct UpdateInfo;
class MessageObject;
} // namespace fw

namespace gf {

class GfComAsm;
class GfComBehaviorPc;
struct MsgPcFieldNotifyRiderEvent;

namespace pc {

class StateFieldRideOn : public GfStateBase {
  GF_STATE_CLASS(StateFieldRideOn, GfComBehaviorPc)
  // Inferred role: motion kind of the vehicle or the rider state; original enum and enumerator names unknown.
  enum unknown001 {
    unknown001_0 = 0,
    unknown001_1 = 1,
    unknown001_2 = 2,
    unknown001_3 = 3,
    unknown001_4 = 4,
    unknown001_5 = 5,
    unknown001_6 = 6,
    unknown001_7 = 7,
    unknown001_8 = 8,
    unknown001_9 = 9,
    unknown001_10 = 10,
    unknown001_11 = 11,
    unknown001_12 = 12,
    unknown001_13 = 13,
  };

  void syncMotion(GfComBehaviorPc *behavior);
  unknown001 getVehicleMotType(GfComAsm &comAsm) const;
  unknown001 getRiderMotType(GfComAsm &comAsm) const;
  void enter(GfComBehaviorPc *behavior, ai::State *previous);
  void leave(GfComBehaviorPc *behavior, ai::State *next);
  void update(GfComBehaviorPc *behavior, const fw::UpdateInfo &info);
  bool recieveMessage(void *owner, fw::MessageObject *sender, fw::Message &message) override;
  void procMsgPcFieldNotifyRiderEvent(GfComBehaviorPc *behavior, fw::MessageObject *sender, MsgPcFieldNotifyRiderEvent &message);

  mm::mtl::FixedQueue<mm::mtl::FixStr<32>, 8> unknown18; // Inferred role: commands; original member name unknown.
};

static_assert(offsetof(StateFieldRideOn, unknown18) == 0x18, "");
static_assert(sizeof(StateFieldRideOn) == 0x148, "");

} // namespace pc
} // namespace gf
