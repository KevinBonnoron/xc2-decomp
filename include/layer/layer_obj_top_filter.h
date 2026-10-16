#pragma once
#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

class LayerObjTopFilter : public LayerObj {
public:
  u32 getFilterType() const;
  void createGaussianBlur(u32 width, u32 height);
  void setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum);
  void createFlowMap(u32 width, u32 height, const void *data);
  void setFlowMapParameter(f32 speed, f32 strength);
};

} // namespace layer
