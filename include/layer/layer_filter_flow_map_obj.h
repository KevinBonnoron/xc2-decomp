#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_filter_obj.h"
#include "types.h"

namespace layer {

class LayerTextureObj;

class LayerFilterFlowMapObj : public LayerFilterObj {
public:
  LayerFilterFlowMapObj(u32 width, u32 height, const void *data);
  ~LayerFilterFlowMapObj() override;
  void resourceInit() override;
  void update(const LayerResMatrix &matrix, const LayerResColor &color, const LayerRenderView *view, f32 time) override;
  void render() override;
  grlib::CGLibTextureBuffer *getTexture() override;
  void setParameter(f32 speed, f32 strength);

  grlib::CGLibRenderTarget unknown18;     // Inferred role: render target; original member name unknown.
  grlib::CGLibDblUniformBlock unknown3e0; // Inferred role: uniform block; original member name unknown.
  const void *unknown418;                 // Inferred role: flow map resource; original member name unknown.
  LayerTextureObj *unknown420;            // Inferred role: flow map texture; original member name unknown.
  u32 unknown428;                         // Inferred role: width; original member name unknown.
  u32 unknown42c;                         // Inferred role: height; original member name unknown.
  f32 unknown430;                         // Inferred role: speed; original member name unknown.
  f32 unknown434;                         // Inferred role: strength; original member name unknown.
  f32 unknown438;                         // Inferred role: scroll u; original member name unknown.
  f32 unknown43c;                         // Inferred role: scroll v; original member name unknown.
};

static_assert(offsetof(LayerFilterFlowMapObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerFilterFlowMapObj, unknown3e0) == 0x3e0, "");
static_assert(offsetof(LayerFilterFlowMapObj, unknown418) == 0x418, "");
static_assert(offsetof(LayerFilterFlowMapObj, unknown420) == 0x420, "");
static_assert(offsetof(LayerFilterFlowMapObj, unknown428) == 0x428, "");
static_assert(offsetof(LayerFilterFlowMapObj, unknown43c) == 0x43c, "");
static_assert(sizeof(LayerFilterFlowMapObj) == 0x440, "");

} // namespace layer
