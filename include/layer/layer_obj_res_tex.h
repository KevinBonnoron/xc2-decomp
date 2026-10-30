#pragma once
#include <stddef.h>

#include "layer/layer_link_list.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerTextureObj;
class LayerResAddTexObj;

class LayerObjResTex {
public:
  LayerObjResTex();
  void resetAddTexutre(u32 index);
  void setAddTexture(const void *data, u32 index);
  void setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index);
  void resetAddAllTexutre();
  void clear();
  bool updateTexutre(grlib::CGLibTextureBuffer **textures, LayerTextureObj *textureObj);

  LayerLinkList<LayerResAddTexObj> unknown00;    // Inferred role: active textures; original member name unknown.
  LayerLinkList<LayerResAddTexObj> unknown18[2]; // Inferred role: pending textures per buffer; original member name unknown.
};

static_assert(offsetof(LayerObjResTex, unknown18) == 0x18, "");
static_assert(sizeof(LayerObjResTex) == 0x48, "");

} // namespace layer
