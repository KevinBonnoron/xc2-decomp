#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "layer/layer_obj.h"
#include "layer/layer_obj_sort_filter.h"
#include "types.h"

namespace layer {

class LayerFilterObj;

class LayerObjTopFilter : public LayerObj {
public:
  ~LayerObjTopFilter() override;
  LayerFilterObj *getFilterObj() const;
  u32 getFilterType() const;
  void createGaussianBlur(u32 width, u32 height);
  void setGaussianBlurParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum);
  void createFlowMap(u32 width, u32 height, const void *data);
  void setFlowMapParameter(f32 speed, f32 strength);
  void finalRender();
  void releaseWorkBuffer();
  void resourceInit() override;
  void applyPartsSetup() override;

  u8 _250[0x258 - 0x250];
  LayerObjSortFilter unknown258;          // Inferred role: sort object; original member name unknown.
  LayerFilterObj *unknown270;             // Inferred role: first filter object; original member name unknown.
  LayerFilterObj *unknown278[2];          // Inferred role: filter object per buffer; original member name unknown.
  LayerFilterObj *unknown288;             // Inferred role: filter object to release; original member name unknown.
  grlib::CGLibDblUniformBlock unknown290; // Inferred role: uniform block; original member name unknown.
};

static_assert(offsetof(LayerObjTopFilter, unknown258) == 0x258, "");
static_assert(offsetof(LayerObjTopFilter, unknown270) == 0x270, "");
static_assert(offsetof(LayerObjTopFilter, unknown278) == 0x278, "");
static_assert(offsetof(LayerObjTopFilter, unknown288) == 0x288, "");
static_assert(offsetof(LayerObjTopFilter, unknown290) == 0x290, "");

} // namespace layer
