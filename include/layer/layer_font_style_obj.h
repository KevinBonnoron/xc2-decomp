#pragma once
#include <stddef.h>

#include "layer/layer_base.h"
#include "types.h"

namespace layer {

class LayerFontStyleObj : public LayerBase {
public:
  void releaseColorInfo();
  void releaseIconInfo();
  s32 getStyleIndex(const char *name) const;
  const char *getStyleName(u32 index) const;
  const char *getFontName(u32 index) const;
  void createColorInfo(u32 num);
  void createIconInfo(u32 num);

  u8 _1c[0x28 - 0x1c];
  u32 m_styleDataMax;
  u8 _2c[0x40 - 0x2c];
  f32 m_rubyScale;
  u8 _44[0x48 - 0x44];
  void *m_colorInfo;
  void *m_iconInfo;
};

static_assert(offsetof(LayerFontStyleObj, m_styleDataMax) == 0x28, "");
static_assert(offsetof(LayerFontStyleObj, m_rubyScale) == 0x40, "");
static_assert(offsetof(LayerFontStyleObj, m_colorInfo) == 0x48, "");

} // namespace layer
