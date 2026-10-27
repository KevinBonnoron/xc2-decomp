#pragma once
#include <stddef.h>

#include "types.h"

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

struct LayerRenderView;
struct LayerResColor;
struct LayerResMatrix;

class LayerFilterObj {
public:
  LayerFilterObj() : unknown08(0), unknown0c(3), m_filterType(0) {}
  virtual ~LayerFilterObj() {}
  virtual void resourceInit() = 0;
  virtual void update(const LayerResMatrix &matrix, const LayerResColor &color, const LayerRenderView *view, f32 time) = 0;
  virtual void render();
  virtual grlib::CGLibTextureBuffer *getTexture() = 0;
  void releaseCall();
  u32 isReleaseCall() const;
  void calcMatInvert(f32 *param, const LayerResMatrix &matrix);
  void calcMatRotParam(f32 *param, const LayerResMatrix &matrix);
  f32 gaussianDistribution(f32 x, f32 y, f32 rho) const;

  u32 unknown08; // Inferred role: release call bits per buffer; original member name unknown.
  u32 unknown0c; // Inferred role: initialized to 3; original member name unknown.
  s32 m_filterType;
};

static_assert(offsetof(LayerFilterObj, unknown08) == 0x08, "");
static_assert(offsetof(LayerFilterObj, m_filterType) == 0x10, "");

} // namespace layer
