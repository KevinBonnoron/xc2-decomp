#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {

class CGLibRenderTargetBase : public CGLibTextureBuffer {
public:
  CGLibRenderTargetBase();
  void setColorInvalidate();
  u32 getImageSize() const;

  CGLibTextureBuffer *unknown70; // Inferred role: texture; original member name unknown.
};

static_assert(offsetof(CGLibRenderTargetBase, unknown70) == 0x70, "");
static_assert(sizeof(CGLibRenderTargetBase) == 0x78, "");

} // namespace grlib
