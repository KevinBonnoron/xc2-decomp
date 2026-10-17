#include "layer/layer_obj_manager.h"

#include "layer/layer_sort_man.h"

namespace layer {

void LayerObjManager::finalRender(const ml::IDrDrawWorkInfo *info) {
  m_workInfo = info;
  m_sortMan->finalRender();
}

void LayerObjManager::end() {}

} // namespace layer
