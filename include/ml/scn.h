#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "mtl/alloc_handle.h"
#include "types.h"

namespace ml {

class ScnObj;
class ScnRenderDrSys;

class ScnObjCam {
public:
  struct RENDER_INFO {
    u8 _00[0x10];
    mm::Vec3 position;
  };

  u8 _00[0x78];
  RENDER_INFO *renderInfo;
};

class Scn : public mm::mtl::PtrSingleton<Scn> {
public:
  void releaseItem(ScnObj *obj);
  ScnObj *createLgt(const void *data, int screenID);
  ScnObjCam *getCam(int index);

  u8 _08[0x38 - 0x08];
  ScnRenderDrSys *renderDrSys;
  u8 _40[0x64 - 0x40];
  mtl::ALLOC_HANDLE allocHandle;
};

static_assert(offsetof(Scn, renderDrSys) == 0x38, "");
static_assert(offsetof(Scn, allocHandle) == 0x64, "");

} // namespace ml
