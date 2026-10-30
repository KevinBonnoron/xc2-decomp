#pragma once
#include "layer/layer_sort_obj.h"

namespace layer {

class LayerObjSortFont : public LayerSortObj {
public:
  void finalRender() override;
};

} // namespace layer
