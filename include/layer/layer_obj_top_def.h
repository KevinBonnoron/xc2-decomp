#pragma once
#include "layer/layer_obj_work.h"

namespace layer {

class LayerObjTopDef : public LayerObjWork {
public:
  void updateResCheck();
  void finalRender();
};

} // namespace layer
