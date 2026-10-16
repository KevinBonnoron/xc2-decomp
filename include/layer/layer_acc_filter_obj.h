#pragma once
#include "layer/layer_acc_obj_base.h"
#include "types.h"

namespace layer {

class LayerBase;

class LayerAccFilterObj : public LayerAccObjBase {
public:
  LayerAccFilterObj(LayerBase *layer);
  u32 getFilterType() const;
  void selectFilterOfGaussianBlur(u32 width, u32 height);
  void setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum);
  void selectFilterOfFlowMap(u32 width, u32 height, const void *data);
  void setFlowMapParameter(f32 speed, f32 strength);
};

} // namespace layer
