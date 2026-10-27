#pragma once
#include <stddef.h>

#include "grlib/cglib_dbl_uniform_block.h"
#include "grlib/cglib_render_target.h"
#include "layer/layer_filter_obj.h"
#include "types.h"

namespace layer {

class LayerFilterGsBlurObj : public LayerFilterObj {
public:
  LayerFilterGsBlurObj(u32 width, u32 height);
  ~LayerFilterGsBlurObj() override;
  void resourceInit() override;
  void update(const LayerResMatrix &matrix, const LayerResColor &color, const LayerRenderView *view, f32 time) override;
  void render() override;
  grlib::CGLibTextureBuffer *getTexture() override;
  void renderMain();
  void renderSub();
  void setParameter(f32 strength, f32 scale, u32 sampleNum, bool isHalf, u32 passNum);

  grlib::CGLibRenderTarget unknown18;     // Inferred role: render target; original member name unknown.
  grlib::CGLibRenderTarget unknown3e0;    // Inferred role: result render target; original member name unknown.
  grlib::CGLibDblUniformBlock unknown7a8; // Inferred role: uniform block; original member name unknown.
  u32 unknown7e0;                         // Inferred role: width; original member name unknown.
  u32 unknown7e4;                         // Inferred role: height; original member name unknown.
  f32 unknown7e8;                         // Inferred role: horizontal blur scale; original member name unknown.
  f32 unknown7ec;                         // Inferred role: vertical blur scale; original member name unknown.
  u32 unknown7f0;                         // Inferred role: sample num; original member name unknown.
  u32 unknown7f4;                         // Inferred role: pass num; original member name unknown.
  bool unknown7f8;                        // Inferred role: half size; original member name unknown.
  bool unknown7f9;                        // Inferred role: parameter changed; original member name unknown.
};

static_assert(offsetof(LayerFilterGsBlurObj, unknown18) == 0x18, "");
static_assert(offsetof(LayerFilterGsBlurObj, unknown3e0) == 0x3e0, "");
static_assert(offsetof(LayerFilterGsBlurObj, unknown7a8) == 0x7a8, "");
static_assert(offsetof(LayerFilterGsBlurObj, unknown7e0) == 0x7e0, "");
static_assert(offsetof(LayerFilterGsBlurObj, unknown7f8) == 0x7f8, "");
static_assert(sizeof(LayerFilterGsBlurObj) == 0x800, "");

} // namespace layer
