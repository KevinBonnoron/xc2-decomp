#pragma once
#include "types.h"

namespace layer {

class LayerBase;
class LayerFontStyleObj;

class LayerAccFontStyle {
public:
  LayerAccFontStyle(LayerBase *layer);
  u32 getStyleDataMax() const;
  s32 getStyleIndex(const char *name) const;
  const char *getStyleName(u32 index) const;
  const char *getFontName(u32 index) const;
  void createColorInfo(u32 num);
  void releaseColorInfo();
  void *getColorInfo();
  void createIconInfo(u32 num);
  void releaseIconInfo();
  void *getIconInfo();
  f32 getRubyScale() const;
  void setRubyScale(f32 scale);

  LayerFontStyleObj *m_style;
};

} // namespace layer
