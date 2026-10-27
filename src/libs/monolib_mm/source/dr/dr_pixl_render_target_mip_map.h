#pragma once
#include <stddef.h>

#include "grlib/cglib_render_target_mip_map.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderTargetMipMap : public grlib::CGLibRenderTargetMipMap {
public:
  explicit DrPixlRenderTargetMipMap(DrMan *man);
  ~DrPixlRenderTargetMipMap();
  void debugRender(int x, int y, int width, int height, bool isAlpha);
  void debugRenderCh(int x, int y, int width, int height, u32 channel);

  DrMan *unknown488; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderTargetMipMap, unknown488) == 0x488, "");

} // namespace ml
