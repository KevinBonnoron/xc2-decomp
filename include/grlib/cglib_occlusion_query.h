#pragma once
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

  u8 _00[0x18 - 0x00];
};

static_assert(sizeof(CGLibOcclusionQuery) == 0x18, "");

} // namespace grlib
