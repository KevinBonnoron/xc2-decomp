#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObj;

class LayerObjSortLayout : public LayerSortObj {
public:
  LayerObjSortLayout(LayerObj *obj) : LayerSortObj(obj) {}
  void finalRender() override;
};

} // namespace layer
