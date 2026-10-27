#pragma once
#include <stddef.h>

#include "layer/layer_obj.h"
#include "types.h"

namespace layer {

class LayerFilterObj;

class LayerObjTopFilter : public LayerObj {
public:
  LayerFilterObj *getFilterObj() const;
  u32 getFilterType() const;
  void createGaussianBlur(u32 width, u32 height);
  void setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum);
  void createFlowMap(u32 width, u32 height, const void *data);
  void setFlowMapParameter(f32 speed, f32 strength);
  void finalRender();

  u8 _250[0x270 - 0x250];
  LayerFilterObj *unknown270;    // Inferred role: first filter object; original member name unknown.
  LayerFilterObj *unknown278[2]; // Inferred role: filter object per buffer; original member name unknown.
};

static_assert(offsetof(LayerObjTopFilter, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopFilter, unknown278) == 0x278, "");

} // namespace layer
