#include "layer/layer_rce_manager.h"

#include "layer/layer_manager.h"
#include "layer/layer_rce_obj.h"
#include "mtl/alloc_handle.h"

namespace layer {

LayerRceManager::~LayerRceManager() {}

LayerRceObj *LayerRceManager::createRceObj(const void *data, const char *name) {
  LayerRceObj *obj = new (unknown00->unknown28) LayerRceObj(data, name);
  unknown20[LayerManager::s_nStkIdx].unknown002(obj);
  return obj;
}

void LayerRceManager::releaseObj(LayerRceObj *obj) { obj->unknown30 |= 1 << LayerManager::s_nStkIdx; }

} // namespace layer
