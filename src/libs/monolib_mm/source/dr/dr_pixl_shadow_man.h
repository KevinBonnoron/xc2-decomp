#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class DrLightObj;
class DrPixlShadowObj;
class DrPixlShadowObjDir;

class DrPixlShadowMan {
public:
  void releaseShadow(DrPixlShadowObj *shadow);
  DrPixlShadowObj *createDirCacheShadow(DrLightObj *light, int index);
  void setAddShadowObj(DrPixlShadowObjDir *shadow);
  f32 getShadowTexSize(int index);

  u8 _0000[0x8918];
  DrPixlShadowObjDir *unknown8918; // Inferred role: additional shadow object; original member name unknown.
};

static_assert(offsetof(DrPixlShadowMan, unknown8918) == 0x8918, "");

} // namespace ml
