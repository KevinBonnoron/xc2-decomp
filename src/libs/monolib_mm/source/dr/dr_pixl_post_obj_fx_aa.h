#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace ml {
class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjFxAA : public DrPixlPostObj {
public:
  DrPixlPostObjFxAA(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjFxAA();
  void releaseColorBuff();
  void update();
  void resetColorBuff();
  void render();
  void calcScale();
  void calcLuminosity();
  void debugRender();

  DrPixlRenderTarget *unknown18; // Inferred role: render target, a DrPixlRenderTarget the constructor allocates (0x71008571d0); original member name unknown.
  f32 unknown20;                 // Inferred role: screen width; original member name unknown.
  f32 unknown24;                 // Inferred role: screen height; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjFxAA, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjFxAA, unknown24) == 0x24, "");

} // namespace ml
