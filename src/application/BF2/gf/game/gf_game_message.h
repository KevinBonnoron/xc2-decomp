#pragma once
#include "framework/message/message_object.h"
#include "types.h"

namespace gf {

struct MsgGameTalkAction : fw::Message {
  MsgGameTalkAction(u32 action, bool isDirect) : fw::Message(0x100002d, 0x40), action(action), isDirect(isDirect), isSuccess(false) {}

  u32 action;
  bool isDirect;
  bool isSuccess;
};

} // namespace gf
