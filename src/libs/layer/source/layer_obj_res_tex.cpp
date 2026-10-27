#include "layer/layer_obj_res_tex.h"

#include "layer/layer_manager.h"
#include "mtl/alloc_handle.h"

namespace layer {

void LayerObjResTex::setAddTexture(grlib::CGLibTextureBuffer &texture, u32 index) {
  resetAddTexutre(index);
  LayerResAddTexObj *addTexture = new (LayerManager::get()->unknown28) LayerResAddTexObj(&texture, index);
  unknown18[LayerManager::s_nStkIdx].unknown002(addTexture);
}

} // namespace layer
