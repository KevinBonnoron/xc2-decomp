#pragma once
#include <stddef.h>

#include "grlib/cglib_render_cube_map.h"

namespace ml {

class DrMan;

class DrPixlRenderCubeMapMipMap : public grlib::CGLibRenderCubeMapMipMap {
public:
  explicit DrPixlRenderCubeMapMipMap(DrMan *man);
  ~DrPixlRenderCubeMapMipMap();

  DrMan *m_drMan; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderCubeMapMipMap, m_drMan) == 0x1888, "");

} // namespace ml
