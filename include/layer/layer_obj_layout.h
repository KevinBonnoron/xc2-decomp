#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace grlib {
class CGLibRenderTarget;
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjLayout : public LayerActBase {
public:
  // Inferred layout of a render target entry; original type and member names unknown.
  struct unknown001 {
    u32 unknown00; // Inferred role: flags; original member name unknown.
    f32 unknown04; // Inferred role: x; original member name unknown.
    f32 unknown08; // Inferred role: y; original member name unknown.
    f32 unknown0c; // Inferred role: width; original member name unknown.
    f32 unknown10; // Inferred role: height; original member name unknown.
    u8 _14[0x18 - 0x14];
    grlib::CGLibRenderTarget *unknown18; // Inferred role: render target; original member name unknown.
    u8 _20[0x28 - 0x20];
    mm::Col4 unknown28; // Inferred role: clear color; original member name unknown.
  };

  static_assert(offsetof(unknown001, unknown18) == 0x18, "");
  static_assert(offsetof(unknown001, unknown28) == 0x28, "");
  static_assert(sizeof(unknown001) == 0x38, "");

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
  u8 _2ca[0x310 - 0x2ca];
  unknown001 unknown310[2]; // Inferred role: render targets; original member name unknown.
  u8 _380[0x3b8 - 0x380];
  unknown001 unknown3b8; // Inferred role: active render target; original member name unknown.
};

static_assert(offsetof(LayerObjLayout, unknown2b0) == 0x2b0, "");
static_assert(offsetof(LayerObjLayout, unknown2c0) == 0x2c0, "");
static_assert(offsetof(LayerObjLayout, unknown2c8) == 0x2c8, "");
static_assert(offsetof(LayerObjLayout, unknown310) == 0x310, "");
static_assert(offsetof(LayerObjLayout, unknown3b8) == 0x3b8, "");

} // namespace layer
