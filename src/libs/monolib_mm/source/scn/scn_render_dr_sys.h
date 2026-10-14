#pragma once
#include "../dr/dr_man.h"
#include "types.h"
#include <stddef.h>

namespace ml {

class ScnRenderDrSys {
public:
  u8 _00[0x10 - 0x00];
  DrMan *drMan;
};

static_assert(offsetof(ScnRenderDrSys, drMan) == 0x10, "");

class ScnRenderDrViewCtrl {
public:
  u8 _00[0x08 - 0x00];
  s32 viewId;
};

static_assert(offsetof(ScnRenderDrViewCtrl, viewId) == 0x08, "");

} // namespace ml
