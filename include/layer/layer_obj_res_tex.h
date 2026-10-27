#pragma once
#include <stddef.h>

#include "layer/layer_link_list.h"
#include "layer/layer_manager.h"
#include "layer/layer_res_add_tex_obj.h"
#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerTextureObj;

class LayerObjResTex {
public:
  void setAddTexture(const void *data, u32 index);
  void setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index);

  void clear();
  bool updateTexutre(grlib::CGLibTextureBuffer **textures, LayerTextureObj *textureObj);

  void resetAddTexutre(u32 index) {
    for (LayerResAddTexObj *texture = unknown00.unknown00; texture != nullptr; texture = texture->unknown08) {
      if (texture->unknown20 == index) {
        texture->unknown22 |= 1 << LayerManager::s_nStkIdx;
      }
    }
  }

  void resetAddAllTexutre() {
    for (LayerResAddTexObj *texture = unknown00.unknown00; texture != nullptr; texture = texture->unknown08) {
      texture->unknown22 |= 1 << LayerManager::s_nStkIdx;
    }
  }

  LayerLinkList<LayerResAddTexObj> unknown00;    // Inferred role: active textures; original member name unknown.
  LayerLinkList<LayerResAddTexObj> unknown18[2]; // Inferred role: pending textures per buffer; original member name unknown.
};

static_assert(offsetof(LayerObjResTex, unknown18) == 0x18, "");
static_assert(sizeof(LayerObjResTex) == 0x48, "");

} // namespace layer
