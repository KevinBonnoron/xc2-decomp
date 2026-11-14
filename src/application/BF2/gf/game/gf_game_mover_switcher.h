#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/event/gf_event.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace gf {

struct GfSetupParam;

constexpr u32 MSG_UNKNOWN_16777265 = 0x1000031; // Inferred role: msg game switch control mover; original name unknown.

// Layout evidence: StateUtilField::requestBattleStart (0x710054e6a8) builds it with the id 0x1000031 and 1 in the member at 0x8;
// GfGameMoverSwitcher::recieveMessage compares that member with 1.
struct MsgGameSwitchControlMover : fw::Message {
  explicit MsgGameSwitchControlMover(u32 kind) : fw::Message(MSG_UNKNOWN_16777265, 0), unknown08(kind) {}

  u32 unknown08; // Inferred role: switch kind, 1 starts a battle; original member name unknown.
};

static_assert(offsetof(MsgGameSwitchControlMover, unknown08) == 0x08, "");

class GfGameMoverSwitcher : public mm::mtl::PtrSingleton<GfGameMoverSwitcher>, public fw::MessageObject, public IGfEvent {
public:
  GfGameMoverSwitcher();
  ~GfGameMoverSwitcher();
  static void build(const GfSetupParam &param);
  void setup();
  static void destroy();
  void cleanup();
  void switchMover();
  // The order of the overrides follows the game's vtable (0x710118a850).
  bool recieveMessage(fw::MessageObject *sender, fw::Message &message) override;
  void gevPartyMemberOK(bool isMemberOk) override;
  void gevPartyReturnFieldState(u32 state) override;
  void procMsgGameSwitchControlMover(fw::MessageObject *sender, MsgGameSwitchControlMover &message);

  bool unknown28; // Inferred role: mover switch enabled, set by gevPartyMemberOK; original member name unknown.
};

static_assert(offsetof(GfGameMoverSwitcher, unknown28) == 0x28, "");
static_assert(sizeof(GfGameMoverSwitcher) == 0x30, "");

} // namespace gf
