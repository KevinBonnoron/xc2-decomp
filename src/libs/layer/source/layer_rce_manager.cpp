#include "layer/layer_rce_manager.h"

#include "layer/layer_manager.h"
#include "layer/layer_rce_obj.h"

namespace layer {

LayerRceManager::~LayerRceManager() {}

void LayerRceManager::releaseObj(LayerRceObj *obj) { obj->unknown30 |= 1 << LayerManager::s_nStkIdx; }

} // namespace layer
