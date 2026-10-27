#pragma once
#include "grlib/cglib_render_array.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrPixlRenderCubeMapArrayMipMap : public grlib::CGLibRenderArrayCubeMap {
public:
  void setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea);
};

} // namespace ml
