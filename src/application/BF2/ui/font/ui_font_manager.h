#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "mm_mtl/vector.h"
#include "types.h"

namespace layer {
class LayerBase;
}

namespace ui {

class UIResource;

class UIFontManager : public mm::mtl::PtrSingleton<UIFontManager> {
public:
  struct FontRes {
    u16 unknown00;               // Inferred role: id; original member name unknown.
    u32 unknown04;               // Inferred role: hash; original member name unknown.
    layer::LayerBase *unknown08; // Inferred role: res; original member name unknown.
  };

  struct StyleInfo {
    f32 unknown00; // Inferred role: offset x; original member name unknown.
    f32 unknown04; // Inferred role: offset y; original member name unknown.
  };

  struct FacePattern {
    u32 unknown00; // Inferred role: name hash; original member name unknown.
    u32 unknown04; // Inferred role: pattern index; original member name unknown.
  };

  FontRes *getFontRes(u16 id);
  FontRes *getFontRes(const char *name);
  FontRes *getFontStyle();
  FontRes *getFontResFromStyle(u16 style);
  bool isLoading() const;
  bool getFontStyleInfo(u16 style, StyleInfo &info);
  bool findFacePattern(const char *name, u32 &index);

  UIResource *unknown08;                      // Inferred role: resource; original member name unknown.
  mm::mtl::FixedVector<FontRes, 4> unknown10; // Inferred role: fonts; original member name unknown.
  FontRes m_fontStyle;
  u8 _68[0x70 - 0x68];
  mm::mtl::Vector<FacePattern> unknown70; // Inferred role: face patterns; original member name unknown.
  layer::LayerBase *unknown98;            // Inferred role: color map; original member name unknown.
  u8 _a0[0xa8 - 0xa0];
};

static_assert(sizeof(UIFontManager::FontRes) == 0x10, "");
static_assert(offsetof(UIFontManager, unknown08) == 0x08, "");
static_assert(offsetof(UIFontManager, unknown10) == 0x10, "");
static_assert(offsetof(UIFontManager, m_fontStyle) == 0x58, "");
static_assert(offsetof(UIFontManager, unknown70) == 0x70, "");
static_assert(offsetof(UIFontManager, unknown98) == 0x98, "");
static_assert(sizeof(UIFontManager) == 0xa8, "");

} // namespace ui
