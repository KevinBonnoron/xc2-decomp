#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace layer {

class LayerBase;

class LayerAccMemObj : public LayerAccObjBase {
public:
  LayerAccMemObj(LayerBase *layer);
  u16 getMemWidth() const;
  u16 getMemHeight() const;

  LayerBase *memObj;
};

} // namespace layer
