#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "types.h"

namespace gf {

enum {
  MSG_GAME_UNKNOWN_16777259 = 0x100002b, // Inferred role: msg game change target; original name unknown.
  MSG_GAME_UNKNOWN_16777260 = 0x100002c, // Inferred role: msg game debug target; original name unknown.
  MSG_GAME_UNKNOWN_16777261 = 0x100002d, // Inferred role: msg game talk action; original name unknown.
  MSG_GAME_UNKNOWN_16777262 = 0x100002e, // Inferred role: msg game lip action; original name unknown.
  MSG_GAME_UNKNOWN_16777263 = 0x100002f, // Inferred role: msg game set lip weight; original name unknown.
};

struct MsgGameDebugTarget : fw::Message {};

struct MsgGameTalkAction : fw::Message {
  MsgGameTalkAction(u32 action, bool isDirect) : fw::Message(MSG_GAME_UNKNOWN_16777261, 0x40), action(action), isDirect(isDirect), isSuccess(false) {}

  u32 action;
  bool isDirect;
  bool isSuccess;
};

struct MsgGameLipAction : fw::Message {
  MsgGameLipAction(u32 action) : fw::Message(MSG_GAME_UNKNOWN_16777262, 0x40), action(action) {}

  u32 action;
};

struct MsgGameSetLipWeight : fw::Message {
  f32 unknown08; // Inferred role: lip sync weight; original member name unknown.
};

static_assert(offsetof(MsgGameSetLipWeight, unknown08) == 0x08, "");

} // namespace gf
