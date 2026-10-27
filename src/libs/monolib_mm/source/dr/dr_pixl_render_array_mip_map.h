#pragma once
#include <stddef.h>

#include "grlib/cglib_render_array.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderArrayMipMap : public grlib::CGLibRenderArray {
public:
  explicit DrPixlRenderArrayMipMap(DrMan *man);
  ~DrPixlRenderArrayMipMap();
  void setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea);

  DrMan *unknown98; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderArrayMipMap, unknown98) == 0x98, "");

} // namespace ml
