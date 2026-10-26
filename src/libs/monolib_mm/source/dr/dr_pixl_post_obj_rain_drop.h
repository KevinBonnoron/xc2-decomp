#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMan;

class DrPixlPostObjRainDrop {
public:
  void render();
  void resetColorBuff();
  void releaseColorBuff();
  void requestRebuildDepth();
  void requestUseLoadedDepth();
  void requestSaveDepth(const char *path);
  void update();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  u32 unknown18; // Inferred role: depth request; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjRainDrop, unknown00) == 0x00, "");

} // namespace ml
