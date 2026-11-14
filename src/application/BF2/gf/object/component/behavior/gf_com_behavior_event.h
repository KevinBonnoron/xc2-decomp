#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd_turn.h"
#include "gf/object/component/behavior/gf_com_behavior.h"
#include "types.h"

namespace fw {
class MessageObject;
} // namespace fw

namespace mm {
struct Vec3;

namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace gf {

class GfComEvtAnim;

// Layout from its constructor (0x7100522174) and destructor: the flags at 0x98 and the turn command at 0xa0.
class GfComBehaviorEvent : public GfComBehavior {
public:
  static mm::mtl::RTTI m_rtti;

  GfComBehaviorEvent();
  const mm::mtl::RTTI *getRTTI() const override;
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void setup();
  void update(const fw::UpdateInfo &info) override;
  void cleanup();
  void setFootIK(bool isEnable);
  void setTarget(bool isEnable, f32 time, bool isLookOnly);
  void setTargetPos(const mm::Vec3 &position);
  void execTurnCmd(f32 angle, f32 param2, f32 param3, f32 param4);
  void procMsgObjectGetVelocity(fw::MessageObject *sender, MsgObjectGetVelocity &message);

  u32 unknown98;                             // Inferred role: flags, 1 foot IK set up, 2 target set; original member name unknown.
  TFieldExecCmdTurn<GfComEvtAnim> unknowna0; // Inferred role: turn command; original member name unknown.
};

static_assert(offsetof(GfComBehaviorEvent, unknown98) == 0x98, "");
static_assert(offsetof(GfComBehaviorEvent, unknowna0) == 0xa0, "");
static_assert(sizeof(GfComBehaviorEvent) == 0x110, "");

} // namespace gf
