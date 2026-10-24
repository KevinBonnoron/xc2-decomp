#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerResSecTexture {
public:
  LayerResSecTexture(const void *data);
  ~LayerResSecTexture();
  void update();

  u8 _00[0x10 - 0x00];
  u16 unknown10; // Inferred role: icon num; original member name unknown.
  u16 unknown12; // Inferred role: icon max; original member name unknown.
  f32 unknown14; // Inferred role: blend; original member name unknown.
  u8 _18[0x50 - 0x18];
};

static_assert(offsetof(LayerResSecTexture, unknown10) == 0x10, "");
static_assert(offsetof(LayerResSecTexture, unknown14) == 0x14, "");
static_assert(sizeof(LayerResSecTexture) == 0x50, "");

} // namespace layer
