#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlPostObjCapture {
public:
  void render();
  void release();
  void renderCaputre();
  void renderDef();

  DrMan *unknown00; // Inferred role: driver manager; original member name unknown.
  u8 _08[0x18 - 0x08];
  grlib::CGLibRenderTarget unknown18; // Inferred role: render target; original member name unknown.
  u32 unknown3e0;                     // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjCapture, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjCapture, unknown3e0) == 0x3e0, "");

} // namespace ml
