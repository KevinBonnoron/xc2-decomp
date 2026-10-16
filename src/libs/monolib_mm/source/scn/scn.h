#pragma once
#include <stddef.h>

#include "mtl/alloc_handle.h"
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
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE allocHandle;
};

static_assert(offsetof(Scn, renderDrSys) == 0x38, "");
static_assert(offsetof(Scn, allocHandle) == 0x64, "");

} // namespace ml
