#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoLodGrp {
public:
  DrResMdoLodGrp();

  void *unknown00; // Inferred role: lod parts; original member name unknown.
  s32 unknown08;   // Inferred role: lod parts count; original member name unknown.
  s32 unknown0c;   // Inferred role: cleared with the lod parts count; original member name unknown.
  u32 unknown10;   // Inferred role: flags; original member name unknown.
};

static_assert(offsetof(DrResMdoLodGrp, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodGrp, unknown10) == 0x10, "");

} // namespace ml
