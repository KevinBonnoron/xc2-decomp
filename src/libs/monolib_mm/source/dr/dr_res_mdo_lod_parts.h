#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

struct MdsMdlLodData;

class DrResMdoLodParts {
public:
  DrResMdoLodParts();
  void setup(const MdsMdlLodData *lodData);

  u64 unknown00; // Inferred role: state; original member name unknown.
  u32 unknown08; // Inferred role: state; original member name unknown.
  u8 _0c[0x10 - 0x0c];
  f32 unknown10;                  // Inferred role: ratio; original member name unknown.
  u32 unknown14;                  // Inferred role: state; original member name unknown.
  const MdsMdlLodData *unknown18; // Inferred role: lod data; original member name unknown.
};

static_assert(offsetof(DrResMdoLodParts, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoLodParts, unknown10) == 0x10, "");
static_assert(offsetof(DrResMdoLodParts, unknown18) == 0x18, "");
static_assert(sizeof(DrResMdoLodParts) == 0x20, "");

} // namespace ml
