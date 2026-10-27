#pragma once
#include "types.h"

namespace gf {

struct MenuCommonWindowParam {
  MenuCommonWindowParam()
      : unknown00(nullptr), unknown08(0), unknown10(nullptr), unknown18(0), unknown20(nullptr), unknown28(0), unknown30(nullptr), unknown38(0), unknown3c(0), unknown40(0), unknown44(0), unknown48(0) {
  }

  u8 *unknown00; // Inferred role: title bdat; original member name unknown.
  u32 unknown08; // Inferred role: title row; original member name unknown.
  u8 *unknown10; // Inferred role: text bdat; original member name unknown.
  u32 unknown18; // Inferred role: text row; original member name unknown.
  u8 *unknown20; // Inferred role: ok text bdat; original member name unknown.
  u32 unknown28; // Inferred role: ok text row; original member name unknown.
  u8 *unknown30; // Inferred role: cancel text bdat; original member name unknown.
  u32 unknown38; // Inferred role: cancel text row; original member name unknown.
  u32 unknown3c; // Inferred role: type; original member name unknown.
  u32 unknown40; // Inferred role: select; original member name unknown.
  u32 unknown44; // Role and original member name unknown.
  u32 unknown48; // Role and original member name unknown.
};

static_assert(sizeof(MenuCommonWindowParam) == 0x50, "");

} // namespace gf
