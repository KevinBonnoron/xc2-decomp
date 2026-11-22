#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerTextureObj;

class LayerResSecTexture {
public:
  LayerResSecTexture(const void *data);
  ~LayerResSecTexture();
  void release();
  grlib::CGLibTextureBuffer *getTexture();
  void resourceInit();
  void update();

  const void *unknown00;                              // Inferred role: resource data; original member name unknown.
  LayerTextureObj *m_layerTextureObj;                 // Inferred role: texture object; original member name unknown.
  u16 unknown10;                                      // Inferred role: icon num; original member name unknown.
  u16 unknown12;                                      // Inferred role: icon max; original member name unknown.
  f32 unknown14;                                      // Inferred role: blend; original member name unknown.
  grlib::CGLibDblUniformBlock m_cGLibDblUniformBlock; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerResSecTexture, m_layerTextureObj) == 0x08, "");
static_assert(offsetof(LayerResSecTexture, unknown10) == 0x10, "");
static_assert(offsetof(LayerResSecTexture, unknown14) == 0x14, "");
static_assert(offsetof(LayerResSecTexture, m_cGLibDblUniformBlock) == 0x18, "");
static_assert(sizeof(LayerResSecTexture) == 0x50, "");

} // namespace layer
