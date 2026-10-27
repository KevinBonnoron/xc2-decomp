#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {

class CGLibOcclusionQuery {
public:
  CGLibOcclusionQuery();
  ~CGLibOcclusionQuery() { release(); }
  void release();
  void beginQuery();
  void endQuery();
  u32 getQueryPixel();

  u8 *unknown00; // Inferred role: report counter data; original member name unknown.
  u32 unknown08; // Inferred role: report buffer id; original member name unknown.
  u32 unknown0c; // Inferred role: report buffer offset; original member name unknown.
  u16 unknown10; // Inferred role: reported bits; original member name unknown.
  u8 unknown12;  // Inferred role: write index; original member name unknown.
  u8 unknown13;  // Inferred role: read index; original member name unknown.
  u8 _14[0x18 - 0x14];
};

static_assert(offsetof(CGLibOcclusionQuery, unknown08) == 0x08, "");
static_assert(sizeof(CGLibOcclusionQuery) == 0x18, "");

} // namespace grlib
