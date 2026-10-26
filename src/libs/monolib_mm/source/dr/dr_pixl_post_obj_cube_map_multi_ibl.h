#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrPixlPostObjCubeMapMultiIBL {
public:
  void render();
  void outputPremToDDS();
  void update();
  void debugRender() const;
  u32 getPremMipCount() const;

  u8 _00[0x5d8];
  u32 m_premMipCount;
};

static_assert(offsetof(DrPixlPostObjCubeMapMultiIBL, m_premMipCount) == 0x5d8, "");

} // namespace ml
