#pragma once
#include <stddef.h>

#include "grlib/cglib_texture_buffer.h"
#include "types.h"

namespace grlib {
class CGLibDepthBuffer;

class CGLibDepthTarget {
public:
  void setRenderTarget();
  void release();
  void clearDepth(bool isClear);
  void setTextureInfo(f32 width, f32 height, GrlDepthFormat format, bool isResArea, u32 resArea);
  void clearValDepth(float value, bool isClear);

  u32 unknown00; // Inferred role: width; original member name unknown.
  u32 unknown04; // Inferred role: height; original member name unknown.
  u8 _008[0x120 - 0x008];
  CGLibDepthBuffer *unknown120; // Inferred role: depth buffer; original member name unknown.
};

static_assert(offsetof(CGLibDepthTarget, unknown04) == 0x004, "");
static_assert(offsetof(CGLibDepthTarget, unknown120) == 0x120, "");

} // namespace grlib
