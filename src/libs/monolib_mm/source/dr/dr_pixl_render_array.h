#pragma once
#include <stddef.h>

#include "grlib/cglib_render_array.h"
#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace ml {

class DrMan;

class DrPixlRenderArray : public grlib::CGLibRenderArray {
public:
  explicit DrPixlRenderArray(DrMan *man);
  ~DrPixlRenderArray();
  void setTextureInfo(f32 width, f32 height, u32 slice, GrlSurfaceFormat format, bool isResArea, u32 resArea);

  DrMan *m_drMan; // Inferred role: DrMan owner; original member name unknown.
};

static_assert(offsetof(DrPixlRenderArray, m_drMan) == 0x98, "");

} // namespace ml
