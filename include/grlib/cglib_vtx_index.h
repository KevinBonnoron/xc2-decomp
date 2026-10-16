#pragma once
#include "types.h"

namespace grlib {

class CGLibVtxIndex {
public:
  void drawIndex();
  void drawInsIndex(int instanceCount);

  u8 _00[0x28 - 0x00];
};

static_assert(sizeof(CGLibVtxIndex) == 0x28, "");

} // namespace grlib
