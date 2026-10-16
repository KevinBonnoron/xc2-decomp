#pragma once
#include <stddef.h>

#include "types.h"

namespace ml {
class ScnObj;
class ScnObjCam;
class ScnRenderDrSys;

class Scn {
public:
  void releaseItem(ScnObj *obj);
  ScnObj *createLgt(const void *data, int screenID);
  ScnObjCam *getCam(int index);

  u8 _00[0x38 - 0x00];
  ScnRenderDrSys *renderDrSys;
};

static_assert(offsetof(Scn, renderDrSys) == 0x38, "");

} // namespace ml
