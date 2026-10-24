#include "layer/layer_obj_manager.h"

#include "layer/layer_sort_man.h"

namespace layer {

void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  unknown00 = info;
  unknown10->finalRender();
}

void LayerObjManager::end() {}

} // namespace layer
