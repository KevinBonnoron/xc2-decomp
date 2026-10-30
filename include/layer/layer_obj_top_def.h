#pragma once
#include "layer/layer_obj_work.h"

namespace layer {

class LayerObjTopDef : public LayerObjWork {
public:
  void updateResCheck();
  void alphaRender();
  void lastRender();
  void finalRender();
};

} // namespace layer
