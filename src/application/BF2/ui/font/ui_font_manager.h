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
    u32 hash;
    layer::LayerBase *res;
  };

  struct StyleInfo {
    f32 offsetX;
    f32 offsetY;
  };

  FontRes *getFontResFromStyle(u16 style);
  bool getFontStyleInfo(u16 style, StyleInfo &info);
  bool findFacePattern(const char *name, u32 &index);

  u8 _08[0x10 - 0x08];
  mm::mtl::FixedVector<FontRes, 4> fonts;
  u8 _58[0x60 - 0x58];
  layer::LayerBase *fontStyle;
  u8 _68[0x98 - 0x68];
  layer::LayerBase *colorMap;
  u8 _a0[0xa8 - 0xa0];
};

static_assert(sizeof(UIFontManager::FontRes) == 0x10, "");
static_assert(offsetof(UIFontManager, fonts) == 0x10, "");
static_assert(offsetof(UIFontManager, fontStyle) == 0x60, "");
static_assert(offsetof(UIFontManager, colorMap) == 0x98, "");
static_assert(sizeof(UIFontManager) == 0xa8, "");

} // namespace ui
