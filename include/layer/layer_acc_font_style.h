#pragma once
#include <stddef.h>

#include "types.h"

namespace layer {

class LayerBase;
class LayerFontStyleObj;

// Inferred layout of a font style row; original type and member names unknown.
struct LyrFontStyleData {
  u8 _00[0x04];
  u32 unknown04; // Inferred role: style name offset; original member name unknown.
  u32 unknown08; // Inferred role: font name offset; original member name unknown.
  f32 unknown0c;
  f32 unknown10;
  u8 _14[0x28 - 0x14];
};

static_assert(offsetof(LyrFontStyleData, unknown04) == 0x04, "");
static_assert(offsetof(LyrFontStyleData, unknown08) == 0x08, "");
static_assert(sizeof(LyrFontStyleData) == 0x28, "");

// Inferred layout of the pair returned by LayerAccFontStyle::getStyleInfo; original type name unknown.
struct LayerStyleInfo {
  const void *unknown00;
  const LyrFontStyleData *unknown08;
};

class LayerAccFontStyle {
public:
  LayerAccFontStyle(LayerBase *layer);
  u32 getStyleDataMax() const;
  LayerStyleInfo getStyleInfo(u32 index) const;
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
