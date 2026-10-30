#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjSortTexObj : public LayerSortObj {
public:
  void finalRender() override;
};

} // namespace layer
