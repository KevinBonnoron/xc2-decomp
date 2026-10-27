#pragma once
#include <stddef.h>

#include "grlib/cglib_render_volume.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderVolume : public grlib::CGLibRenderVolume {
public:
  explicit DrPixlRenderVolume(DrMan *man);
  ~DrPixlRenderVolume();
  void setTextureInfo(f32 width, f32 height, f32 depth, GrlSurfaceFormat format, bool isResArea, u32 resArea);

  DrMan *unknown90; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderVolume, unknown90) == 0x90, "");

} // namespace ml
