#include "layer/layer_obj_res_tex.h"

#include "layer/layer_manager.h"
#include "layer/layer_res_add_tex_obj.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerObjResTex::LayerObjResTex() {}

void LayerObjResTex::resetAddTexutre(u32 index) {
  for (LayerResAddTexObj *texture = unknown00.unknown00; texture != nullptr; texture = texture->unknown08) {
    if (texture->unknown20 == index) {
      texture->unknown22 |= 1 << LayerManager::s_nStkIdx;
    }
  }
}

void LayerObjResTex::setAddTexture(const void *data, u32 index) {
  resetAddTexutre(index);
  LayerResAddTexObj *addTexture = new (LayerManager::get()->unknown28) LayerResAddTexObj(data, index);
  unknown18[LayerManager::s_nStkIdx].unknown002(addTexture);
}

void LayerObjResTex::setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index) {
  resetAddTexutre(index);
  LayerResAddTexObj *addTexture = new (LayerManager::get()->unknown28) LayerResAddTexObj(&texture, index);
  unknown18[LayerManager::s_nStkIdx].unknown002(addTexture);
}

void LayerObjResTex::resetAddAllTexutre() {
  for (LayerResAddTexObj *texture = unknown00.unknown00; texture != nullptr; texture = texture->unknown08) {
    texture->unknown22 |= 1 << LayerManager::s_nStkIdx;
  }
}

void LayerObjResTex::clear() {
  unknown00.unknown003();
  unknown18[0].unknown003();
  unknown18[1].unknown003();
}

} // namespace layer
