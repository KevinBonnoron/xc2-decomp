#pragma once
#include <stddef.h>

#include "gf/object/gf_obj_handle.h"
#include "types.h"

namespace gf {

struct GF_OBJ_HANDLE;
class GfComAsm;

// Turns the object towards an angle with an asm command. The layout follows GfComBehaviorEnemy::execTurnCmd (0x7100517cb4),
// execTurnCmd with four angles (0x7100518150) and the offsets of GfComBehaviorEnemy, which holds one at 0x53f0 up to 0x5460.
template <typename T> class TFieldExecCmdTurn {
public:
  struct CreateInfo {
    CreateInfo() : unknown00(INVALID_HANDLE), unknown08(0.0f), unknown0c(0.0f), unknown10(1.5707964f), unknown14(1.0f), unknown18(0.0f) {}

    GF_OBJ_HANDLE *unknown00; // Inferred role: object; original member name unknown.
    f32 unknown08;            // Inferred role: target angle; original member name unknown.
    f32 unknown0c;            // Role and original member name unknown.
    f32 unknown10;            // Role and original member name unknown.
    f32 unknown14;            // Role and original member name unknown.
    f32 unknown18;            // Role and original member name unknown.
  };

  void create(const CreateInfo &info);

  u8 _00[0x6c];
  bool unknown6c; // Inferred role: turn command active; original member name unknown.
  u8 _6d[0x70 - 0x6d];
};

static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>::CreateInfo, unknown10) == 0x10, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>::CreateInfo, unknown18) == 0x18, "");
static_assert(offsetof(TFieldExecCmdTurn<GfComAsm>, unknown6c) == 0x6c, "");
static_assert(sizeof(TFieldExecCmdTurn<GfComAsm>) == 0x70, "");

} // namespace gf
