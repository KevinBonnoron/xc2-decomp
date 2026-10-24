#pragma once
#include <stddef.h>

#include "mm_math/mm_col4.h"
#include "types.h"

namespace ml {

class DrResMdoMat {
public:
  DrResMdoMat &operator=(const DrResMdoMat &other);
  void setColor(f32 r, f32 g, f32 b, f32 a);
  void setAlpha(f32 alpha);
  void setName(const char *name);

  const char *m_name;
  mm::Col4 unknown08; // Inferred role: color; original member name unknown.
  u32 unknown18;      // Inferred role: param0; original member name unknown.
  u32 unknown1c;      // Inferred role: param1; original member name unknown.
};

static_assert(offsetof(DrResMdoMat, unknown08) == 0x08, "");
static_assert(offsetof(DrResMdoMat, unknown18) == 0x18, "");
static_assert(offsetof(DrResMdoMat, unknown1c) == 0x1c, "");

} // namespace ml
