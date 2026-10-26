#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "types.h"

namespace ml {
class DrMan;

class DrFogObj {
public:
  DrFogObj(DrMan *man);
  virtual ~DrFogObj() {}
  virtual void update() {}

  DrFogObj *unknown08; // Inferred role: previous fog; original member name unknown.
  DrFogObj *unknown10; // Inferred role: next fog; original member name unknown.
  DrMan *unknown18;    // Inferred role: dr man; original member name unknown.
  mm::Col3 unknown20;  // Inferred role: color; original member name unknown.
  mm::Col3 unknown2c;  // Inferred role: side color; original member name unknown.
  mm::Col3 unknown38;  // Inferred role: sun color; original member name unknown.
  f32 unknown44;       // Inferred role: near; original member name unknown.
  f32 unknown48;       // Inferred role: far; original member name unknown.
  f32 unknown4c;       // Inferred role: str; original member name unknown.
  f32 unknown50;
  f32 unknown54; // Inferred role: pow; original member name unknown.
  f32 unknown58;
  f32 unknown5c;
  f32 unknown60;
  f32 unknown64;
};

static_assert(offsetof(DrFogObj, unknown08) == 0x08, "");
static_assert(offsetof(DrFogObj, unknown18) == 0x18, "");
static_assert(offsetof(DrFogObj, unknown20) == 0x20, "");
static_assert(offsetof(DrFogObj, unknown2c) == 0x2c, "");
static_assert(offsetof(DrFogObj, unknown38) == 0x38, "");
static_assert(offsetof(DrFogObj, unknown44) == 0x44, "");
static_assert(offsetof(DrFogObj, unknown64) == 0x64, "");

} // namespace ml
