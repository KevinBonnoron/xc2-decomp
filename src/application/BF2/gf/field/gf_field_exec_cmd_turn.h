#pragma once
#include <stddef.h>

#include "gf/field/gf_field_exec_cmd.h"
#include "gf/object/gf_obj_handle.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfComAsm;

// Turns the object towards an angle with an asm command. The layout follows GfComBehaviorEnemy::execTurnCmd (0x7100517cb4),
// execTurnCmd with four angles (0x7100518150), TFieldExecCmdTurn::create (0x7100517d54), the destructor (0x71005145a8) and the
// constructor inlined in GfComBehaviorEnemy::GfComBehaviorEnemy (0x7100514074), which holds one at 0x53f0 up to 0x5460.
template <typename T> class TFieldExecCmdTurn {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(INVALID_HANDLE), unknown08(0.0f), unknown0c(0.7853982f), unknown10(1.5707964f), unknown14(1.0f), unknown18(0.0f) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
    f32 unknown08;            // Inferred role: target angle; original member name unknown.
    f32 unknown0c;            // Inferred role: smallest angle that plays a turn command; original member name unknown.
    f32 unknown10;            // Inferred role: smallest angle that plays the large turn command; original member name unknown.
    f32 unknown14;            // Role and original member name unknown.
    f32 unknown18;            // Inferred role: turn time without a command; original member name unknown.
  };

  TFieldExecCmdTurn() : unknown58(0.0f), unknown5c(1.0f), unknown60(false), unknown64(0.0f), unknown68(0.0f), unknown6c(false) {}
  ~TFieldExecCmdTurn() { dispose(); }

  void dispose() {
    unknown6c = false;
    unknown60 = false;
    unknown64 = 0.0f;
    unknown20.dispose();
    unknown00 = CreateInfo();
  }

  void create(const CreateInfo &info);

  CreateInfo unknown00;       // Inferred role: create info; original member name unknown.
  TFieldExecCmd<T> unknown20; // Inferred role: turn command; original member name unknown.
  f32 unknown58;              // Inferred role: angle left to turn; original member name unknown.
  f32 unknown5c;              // Role and original member name unknown.
  bool unknown60;             // Role and original member name unknown.
  f32 unknown64;              // Inferred role: turn time without a command; original member name unknown.
  f32 unknown68;              // Inferred role: elapsed turn time; original member name unknown.
  bool unknown6c;             // Inferred role: turn command active; original member name unknown.
};

static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>::CreateInfo, unknown18) == 0x18, "");
static_assert(sizeof(TFieldExecCmdTurn<GfComAsm>::CreateInfo) == 0x20, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown20) == 0x20, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown58) == 0x58, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown60) == 0x60, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown64) == 0x64, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown6c) == 0x6c, "");
static_assert(sizeof(TFieldExecCmdTurn<GfComAsm>) == 0x70, "");

} // namespace gf
