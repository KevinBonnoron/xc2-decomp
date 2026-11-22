#pragma once
#include <stddef.h>

#include "grlib/cglib_render_cube_map.h"

namespace ml {

class DrMan;

class DrPixlRenderCubeMap : public grlib::CGLibRenderCubeMap {
public:
  explicit DrPixlRenderCubeMap(DrMan *man);
  ~DrPixlRenderCubeMap();

  DrMan *m_drMan; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderCubeMap, m_drMan) == 0x208, "");

} // namespace ml
