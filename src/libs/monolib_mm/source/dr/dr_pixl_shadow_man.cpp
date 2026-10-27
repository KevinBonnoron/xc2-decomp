#include "dr/dr_pixl_shadow_man.h"

namespace ml {

// Inferred role: shadow texture sizes by quality level; original name unknown.
static const f32 unknown001[6] = {128.0f, 256.0f, 512.0f, 1024.0f, 1536.0f, 2048.0f};

f32 DrPixlShadowMan::getShadowTexSize(int index) {
  if (index >= 1 && index <= 6) {
    return unknown001[index - 1];
  }
  return 64.0f;
}

void DrPixlShadowMan::setAddShadowObj(DrPixlShadowObjDir *shadow) { unknown8918 = shadow; }

} // namespace ml
