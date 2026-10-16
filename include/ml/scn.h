#pragma once
#include <stddef.h>

#include "mm_math/mm_vec3.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace ml {

class ScnRenderDrSys;

class ScnCam {
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
  ScnCam *getCam(int index);

  u8 _08[0x38 - 0x08];
  ScnRenderDrSys *renderDrSys;
};

static_assert(offsetof(Scn, renderDrSys) == 0x38, "");

} // namespace ml
