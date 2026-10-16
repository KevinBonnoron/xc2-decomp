#pragma once
#include <stddef.h>

#include "mm_math/mm_col3.h"
#include "mm_math/mm_col4.h"
#include "types.h"

namespace ui {

class UIDisplayInfo {
public:
  struct DefColor {
    mm::Col3 mulColor;
    mm::Col3 addColor;
  };

  UIDisplayInfo();
  UIDisplayInfo(const UIDisplayInfo &other);
  void saveDefColor();
  virtual ~UIDisplayInfo();
  void syncParent();
  void setParent(const UIDisplayInfo *parent);
  void setDisp(bool disp);
  void loadDefColor();
  void linkColor(const UIDisplayInfo *link);
  void setPixelWidth(u16 width);
  void setPixelHeight(u16 height);
  void operator=(const UIDisplayInfo &other);

  const UIDisplayInfo *getColorSource() const {
    const UIDisplayInfo *info = this;
    while (info->colorLink != nullptr) {
      info = info->colorLink;
    }
    return info;
  }

  const mm::Col4 &getMulColor() const { return getColorSource()->mulColor; }
  const mm::Col3 &getAddColor() const { return getColorSource()->addColor; }

  bool disp;
  u8 displayMode;
  u8 blendType;
  u16 priority;
  mm::Col4 mulColor;
  mm::Col3 addColor;
  u16 pixelWidth;
  u16 pixelHeight;
  bool dirty;
  DefColor *defColor;
  const UIDisplayInfo *colorLink;
};

static_assert(offsetof(UIDisplayInfo, disp) == 0x08, "");
static_assert(offsetof(UIDisplayInfo, displayMode) == 0x09, "");
static_assert(offsetof(UIDisplayInfo, blendType) == 0x0a, "");
static_assert(offsetof(UIDisplayInfo, priority) == 0x0c, "");
static_assert(offsetof(UIDisplayInfo, mulColor) == 0x10, "");
static_assert(offsetof(UIDisplayInfo, addColor) == 0x20, "");
static_assert(offsetof(UIDisplayInfo, pixelWidth) == 0x2c, "");
static_assert(offsetof(UIDisplayInfo, pixelHeight) == 0x2e, "");
static_assert(offsetof(UIDisplayInfo, dirty) == 0x30, "");
static_assert(offsetof(UIDisplayInfo, defColor) == 0x38, "");
static_assert(offsetof(UIDisplayInfo, colorLink) == 0x40, "");
static_assert(sizeof(UIDisplayInfo) == 0x48, "");

} // namespace ui
