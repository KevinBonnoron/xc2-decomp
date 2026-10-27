#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrResMdoLodObj {
public:
  ~DrResMdoLodObj();
  static void release(DrResMdoLodObj *&lodObj);

  void *unknown00; // Inferred role: lod groups; original member name unknown.
  void *unknown08; // Inferred role: lod parts; original member name unknown.
  void *unknown10; // Inferred role: lod work; original member name unknown.
  s32 unknown18;   // Inferred role: state; original member name unknown.
  f32 unknown1c;   // Inferred role: ratio; original member name unknown.
};

static_assert(offsetof(DrResMdoLodObj, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodObj, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoLodObj, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoLodObj, unknown1c) == 0x1c, "");

} // namespace ml
