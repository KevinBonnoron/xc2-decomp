#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

// Derives from DrPixlPostObj: the constructor (1.0.0: 0x71008378c4) calls the base constructor on this.
class DrPixlPostObjRainDrop : public DrPixlPostObj {
public:
  DrPixlPostObjRainDrop(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjRainDrop();
  void render();
  void resetColorBuff();
  void releaseColorBuff();
  void requestRebuildDepth();
  void requestUseLoadedDepth();
  void requestSaveDepth(const char *path);
  void update();

  u32 unknown18; // Inferred role: depth request; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  DrPixlRenderTarget *unknown20; // Inferred role: depth render target; original member name unknown.
  f32 unknown28;                 // Role and original member name unknown; the constructor stores 0.0f at 0x28 and 0.1f at 0x2c in one 64 bit store; render loads it as a float.
  f32 unknown2c;                 // Role and original member name unknown; render loads it as a float.
  f32 unknown30;                 // Role and original member name unknown; the constructor stores 0.2f; render loads it as a float.
};

static_assert(offsetof(DrPixlPostObjRainDrop, unknown00) == 0x00, "");
static_assert(offsetof(DrPixlPostObjRainDrop, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjRainDrop, unknown28) == 0x28, "");
static_assert(offsetof(DrPixlPostObjRainDrop, unknown30) == 0x30, "");

} // namespace ml
