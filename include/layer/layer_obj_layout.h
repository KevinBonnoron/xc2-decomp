#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjLayout : public LayerActBase {
public:
  void createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor);
  void releaseRenderTarget();
  grlib::CGLibTextureBuffer *getTexture();
  void setRender(bool render);
  bool isRender() const;

  u8 _258[0x2b0 - 0x258];
  f32 unknown2b0;    // Inferred role: view port x; original member name unknown.
  f32 unknown2b4;    // Inferred role: view port y; original member name unknown.
  f32 unknown2b8;    // Inferred role: view port width; original member name unknown.
  f32 unknown2bc;    // Inferred role: view port height; original member name unknown.
  u32 unknown2c0;    // Inferred role: auto anchor mode; original member name unknown.
  u16 unknown2c4[2]; // Inferred role: priority tbls; original member name unknown.
  u16 unknown2c8;    // Inferred role: priority tbl; original member name unknown.
};

static_assert(offsetof(LayerObjLayout, unknown2b0) == 0x2b0, "");
static_assert(offsetof(LayerObjLayout, unknown2c0) == 0x2c0, "");
static_assert(offsetof(LayerObjLayout, unknown2c8) == 0x2c8, "");

} // namespace layer
