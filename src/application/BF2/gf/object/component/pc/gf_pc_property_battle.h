#pragma once
#include <stddef.h>

#include "framework/message/message_object.h"
#include "gf/object/component/pc/gf_pc_property_pc_interface.h"
#include "types.h"

namespace btl {
class CharacterParameter;
class PlayerParameter;
} // namespace btl

namespace gf {

enum {
  MSG_PC_BATTLE_UNKNOWN_16777226 = 0x100000a, // Inferred role: msg pc battle start; original name unknown.
  MSG_PC_BATTLE_UNKNOWN_16777227 = 0x100000b, // Inferred role: msg pc battle end; original name unknown.
};

// Layout evidence: StateField::procMsgObjectNotifyDamage (0x7100553740) builds it on the stack; the flags are left unset by
// StateField::procMsgObjectNotifyDead.
struct MsgPcBattleStart : fw::Message {
  explicit MsgPcBattleStart(u32 type) : fw::Message(MSG_PC_BATTLE_UNKNOWN_16777226, 0x40), unknown08(type) {}

  u32 unknown08; // Inferred role: start condition type, copied by GfPropertyBattle::SetStartCondition; original member name unknown.
  u32 unknown0c; // Inferred role: start condition flag; original member name unknown.
  u32 unknown10; // Inferred role: start condition flag; original member name unknown.
};

static_assert(offsetof(MsgPcBattleStart, unknown08) == 0x08, "");
static_assert(offsetof(MsgPcBattleStart, unknown0c) == 0x0c, "");
static_assert(offsetof(MsgPcBattleStart, unknown10) == 0x10, "");

struct MsgPcBattleEnd : fw::Message {};

namespace pc {

class GfPropertyBattle : public GfPropertyPcInterface {
public:
  GfPropertyBattle();
  void setup(const GfComPropertyPc &property) override;
  void cleanup(const GfComPropertyPc &property) override;
  void flush(const GfComPropertyPc &property) override;
  const btl::CharacterParameter *GetCharacterParameterConst() const;
  const btl::PlayerParameter *GetPlayerParameterConst() const;
  void SetStartCondition(MsgPcBattleStart &message);

  int unknown08;  // Inferred role: battle character id; original member name unknown.
  int unknown0c;  // Inferred role: parameter of the requested battle state; original member name unknown.
  f32 unknown10;  // Inferred role: rate reset to 1 by StateBattle::Leave; original member name unknown.
  u8 unknown14;   // Inferred role: start condition type; original member name unknown.
  u8 unknown15;   // Inferred role: start condition flag; original member name unknown.
  u8 unknown16;   // Inferred role: start condition flag; original member name unknown.
  bool unknown17; // Role and original member name unknown.
  bool unknown18; // Role and original member name unknown.
};

static_assert(offsetof(GfPropertyBattle, unknown08) == 0x08, "");
static_assert(offsetof(GfPropertyBattle, unknown0c) == 0x0c, "");
static_assert(offsetof(GfPropertyBattle, unknown10) == 0x10, "");
static_assert(offsetof(GfPropertyBattle, unknown14) == 0x14, "");
static_assert(offsetof(GfPropertyBattle, unknown17) == 0x17, "");
static_assert(offsetof(GfPropertyBattle, unknown18) == 0x18, "");
static_assert(sizeof(GfPropertyBattle) == 0x20, "");

} // namespace pc
} // namespace gf
