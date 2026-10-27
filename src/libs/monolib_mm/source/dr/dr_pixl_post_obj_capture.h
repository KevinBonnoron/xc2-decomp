#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "grlib/cglib_render_target.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlMan;
class DrPixlPostMan;

class DrPixlPostObjCapture : public DrPixlPostObj {
public:
  enum Flag {
    FLAG_UNKNOWN_2 = 1 << 2,
    FLAG_UNKNOWN_3 = 1 << 3,
  };

  DrPixlPostObjCapture(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjCapture();
  void setup();
  void update();
  void render();
  void release();
  void renderCaputre();
  void renderDef();

  grlib::CGLibRenderTarget unknown18; // Inferred role: render target; original member name unknown.
  u32 unknown3e0;                     // Inferred role: state flags; original member name unknown.
};

static_assert(offsetof(DrPixlPostObjCapture, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjCapture, unknown3e0) == 0x3e0, "");

} // namespace ml
