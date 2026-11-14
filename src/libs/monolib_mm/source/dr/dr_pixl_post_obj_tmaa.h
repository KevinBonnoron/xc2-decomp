#pragma once
#include <stddef.h>

#include "dr/dr_pixl_post_obj.h"
#include "types.h"

namespace ml {

class DrMan;
class DrPixlMan;
class DrPixlPostMan;
class DrPixlRenderTarget;

class DrPixlPostObjTMAA : public DrPixlPostObj {
public:
  enum SHARPNESS_TYPE {
    SHARPNESS_TYPE_UNKNOWN_1 = 1,
    SHARPNESS_TYPE_UNKNOWN_2 = 2,
    SHARPNESS_TYPE_UNKNOWN_4 = 4,
  };

  DrPixlPostObjTMAA(DrMan *drMan, DrPixlMan *pixlMan, DrPixlPostMan *postMan);
  ~DrPixlPostObjTMAA();
  void render();
  void renderTMAA();
  void renderSharpness();
  void renderSharpnessImpl(SHARPNESS_TYPE type);
  void update();
  void debugRender();
  void releaseColorBuff();
  DrPixlRenderTarget *getBloomTexture();

  u32 unknown18; // Inferred role: flags; original member name unknown.
  u8 _1c[0x20 - 0x1c];
  DrPixlRenderTarget *unknown20[2]; // Inferred role: render targets; original member name unknown.
  DrPixlRenderTarget *m_bloomTexture[2];
};

static_assert(offsetof(DrPixlPostObjTMAA, unknown18) == 0x18, "");
static_assert(offsetof(DrPixlPostObjTMAA, unknown20) == 0x20, "");
static_assert(offsetof(DrPixlPostObjTMAA, m_bloomTexture) == 0x30, "");

} // namespace ml
