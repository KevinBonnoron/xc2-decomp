#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrMan;
class DrPixlRenderTarget;

class DrPixlPostObjRainDrop {
public:
  ~DrPixlPostObjRainDrop();
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
  u8 _1c[0x20 - 0x1c];
  DrPixlRenderTarget *unknown20; // Inferred role: depth render target; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjRainDrop, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlPostObjRainDrop, unknown20) == 0x20, "");

} // namespace ml
