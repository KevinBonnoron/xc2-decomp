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
  u16 m_iconNum;
  u16 m_iconMax;
  f32 m_blend;
  u8 _18[0x50 - 0x18];
};

static_assert(offsetof(LayerResSecTexture, m_iconNum) == 0x10, "");
static_assert(offsetof(LayerResSecTexture, m_blend) == 0x14, "");
static_assert(sizeof(LayerResSecTexture) == 0x50, "");

} // namespace layer
