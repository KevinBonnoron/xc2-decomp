#pragma once
#include <stddef.h>

#include "grlib/cglib_render_cube_map.h"

namespace ml {

class DrMan;

class DrPixlRenderCubeMapMipMap : public grlib::CGLibRenderCubeMapMipMap {
public:
  explicit DrPixlRenderCubeMapMipMap(DrMan *man);
  ~DrPixlRenderCubeMapMipMap();

  DrMan *unknown1888; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderCubeMapMipMap, unknown1888) == 0x1888, "");

} // namespace ml
