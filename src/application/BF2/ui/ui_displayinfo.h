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
    while (info->unknown40 != nullptr) {
      info = info->unknown40;
    }
    return info;
  }

  const mm::Col4 &getMulColor() const { return getColorSource()->unknown10; }
  const mm::Col3 &getAddColor() const { return getColorSource()->unknown20; }

  bool unknown08;                 // Inferred role: disp; original member name unknown.
  u8 unknown09;                   // Inferred role: display mode; original member name unknown.
  u8 unknown0a;                   // Inferred role: blend type; original member name unknown.
  u16 unknown0c;                  // Inferred role: priority; original member name unknown.
  mm::Col4 unknown10;             // Inferred role: mul color; original member name unknown.
  mm::Col3 unknown20;             // Inferred role: add color; original member name unknown.
  u16 unknown2c;                  // Inferred role: pixel width; original member name unknown.
  u16 unknown2e;                  // Inferred role: pixel height; original member name unknown.
  bool unknown30;                 // Inferred role: dirty; original member name unknown.
  DefColor *unknown38;            // Inferred role: def color; original member name unknown.
  const UIDisplayInfo *unknown40; // Inferred role: color link; original member name unknown.
};

static_assert(offsetof(UIDisplayInfo, unknown08) == 0x08, "");
static_assert(offsetof(UIDisplayInfo, unknown09) == 0x09, "");
static_assert(offsetof(UIDisplayInfo, unknown0a) == 0x0a, "");
static_assert(offsetof(UIDisplayInfo, unknown0c) == 0x0c, "");
static_assert(offsetof(UIDisplayInfo, unknown10) == 0x10, "");
static_assert(offsetof(UIDisplayInfo, unknown20) == 0x20, "");
static_assert(offsetof(UIDisplayInfo, unknown2c) == 0x2c, "");
static_assert(offsetof(UIDisplayInfo, unknown2e) == 0x2e, "");
static_assert(offsetof(UIDisplayInfo, unknown30) == 0x30, "");
static_assert(offsetof(UIDisplayInfo, unknown38) == 0x38, "");
static_assert(offsetof(UIDisplayInfo, unknown40) == 0x40, "");
static_assert(sizeof(UIDisplayInfo) == 0x48, "");

} // namespace ui
