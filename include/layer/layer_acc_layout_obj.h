#pragma once
#include "layer/layer_acc_obj_base.h"

namespace grlib {
class CGLibTextureBuffer;
}

namespace layer {

class LayerBase;

class LayerAccLayoutObj : public LayerAccObjBase {
public:
  LayerAccLayoutObj(LayerBase *layer);
  LayerBase *createObj(const void *data);
  LayerBase *createMaskObj(const void *data);
  LayerBase *createTexObj(const grlib::CGLibTextureBuffer &texture);
};

} // namespace layer
