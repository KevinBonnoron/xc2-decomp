#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

class CGLibDecShader;

// Layout from CGLibDecShdExtTbl::CGLibDecShdExtTbl() (clears 0x00, 0x08 and 0x10), setObj (stores
// its shader at 0x00, clears the table at 0x10 and the u32 at 0x08) and setTbl (stores at 0x10).
class CGLibDecShdExtTbl {
public:
  CGLibDecShdExtTbl();
  void setObj(CGLibDecShader *shader);
  void setTbl(u8 *table);
  void setDeclarationIdx(u32 offset, u32 index);

  CGLibDecShader *unknown00; // Inferred role: shader; original member name unknown.
  u32 unknown08;
  u8 *unknown10; // Inferred role: declaration table; original member name unknown.
};

static_assert(offsetof(CGLibDecShdExtTbl, unknown08) == 0x08, "");
static_assert(offsetof(CGLibDecShdExtTbl, unknown10) == 0x10, "");
static_assert(sizeof(CGLibDecShdExtTbl) == 0x18, "");

} // namespace grlib
