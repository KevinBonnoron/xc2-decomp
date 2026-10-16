#pragma once
#include <stddef.h>

#include "layer/layer_act_base.h"
#include "types.h"

namespace mm {
struct Col4;
} // namespace mm

namespace grlib {
class CGLibTextureBuffer;
} // namespace grlib

namespace layer {

class LayerObjLayout : public LayerActBase {
public:
  void createRenderTarget(f32 x, f32 y, f32 width, f32 height, mm::Col4 clearColor);
  void releaseRenderTarget();
  grlib::CGLibTextureBuffer *getTexture();
  void setRender(bool render);
  bool isRender() const;

  u8 _258[0x2b0 - 0x258];
  f32 m_viewPortX;
  f32 m_viewPortY;
  f32 m_viewPortWidth;
  f32 m_viewPortHeight;
  u32 m_autoAnchorMode;
  u16 m_priorityTbls[2];
  u16 m_priorityTbl;
};

static_assert(offsetof(LayerObjLayout, m_viewPortX) == 0x2b0, "");
static_assert(offsetof(LayerObjLayout, m_autoAnchorMode) == 0x2c0, "");
static_assert(offsetof(LayerObjLayout, m_priorityTbl) == 0x2c8, "");

} // namespace layer
