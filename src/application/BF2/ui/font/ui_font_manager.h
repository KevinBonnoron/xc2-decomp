#pragma once
#include <stddef.h>

#include "mm_mtl/fixed_vector.h"
#include "mm_mtl/singleton.h"
#include "types.h"

namespace layer {
class LayerBase;
}

namespace ui {

class UIFontManager : public mm::mtl::PtrSingleton<UIFontManager> {
public:
  struct FontRes {
    u8 _00[0x04 - 0x00];
    u32 unknown04;               // Inferred role: hash; original member name unknown.
    layer::LayerBase *unknown08; // Inferred role: res; original member name unknown.
  };

  struct StyleInfo {
    f32 unknown00; // Inferred role: offset x; original member name unknown.
    f32 unknown04; // Inferred role: offset y; original member name unknown.
  };

  FontRes *getFontResFromStyle(u16 style);
  bool getFontStyleInfo(u16 style, StyleInfo &info);
  bool findFacePattern(const char *name, u32 &index);

  u8 _08[0x10 - 0x08];
  mm::mtl::FixedVector<FontRes, 4> unknown10; // Inferred role: fonts; original member name unknown.
  u8 m_fontStyle[0x60 - 0x58];
  layer::LayerBase *unknown60; // Inferred role: font style; original member name unknown.
  u8 _68[0x98 - 0x68];
  layer::LayerBase *unknown98; // Inferred role: color map; original member name unknown.
  u8 _a0[0xa8 - 0xa0];
};

static_assert(sizeof(UIFontManager::FontRes) == 0x10, "");
static_assert(offsetof(UIFontManager, unknown10) == 0x10, "");
static_assert(offsetof(UIFontManager, unknown60) == 0x60, "");
static_assert(offsetof(UIFontManager, unknown98) == 0x98, "");
static_assert(sizeof(UIFontManager) == 0xa8, "");

} // namespace ui
