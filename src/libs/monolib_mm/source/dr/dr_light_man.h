#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {

class DrLightObjPnt;
class DrLightObjSpt;

class DrLightMan {
public:
  void render();
  void renderDir();
  void renderPnt();
  void renderSpt();
  void renderDebugDir();
  void releaseFastLight();
  DrLightObjPnt *createInstantPntLight();
  DrLightObjSpt *createInstantSptLight();
  void releaseInstantPntLight(DrLightObjPnt *light);
  void releaseInstantSptLight(DrLightObjSpt *light);

  u8 _000[0x108];
  s32 unknown108; // Inferred role: instant point light count; original member name unknown.
  s32 unknown10c; // Inferred role: instant spot light count; original member name unknown.
};

static_assert(offsetof(DrLightMan, unknown108) == 0x108, "");
static_assert(offsetof(DrLightMan, unknown10c) == 0x10c, "");

} // namespace ml
