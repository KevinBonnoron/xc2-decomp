#pragma once

#include <stddef.h>

#include "types.h"

namespace ml {

class DrResUseQueryObj;

class DrPixlSkyDome {
public:
  ~DrPixlSkyDome();
  void baseRender();
  void godRayRender();
  void renderBackgroundCube();

  u8 _00[0x08];
  DrResUseQueryObj *unknown08; // Inferred role: occlusion query; original member name unknown.
};

static_assert(offsetof(DrPixlSkyDome, unknown08) == 0x08, "");

} // namespace ml
