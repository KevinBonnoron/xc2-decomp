#pragma once
#include "mm_math/mm_rect.h"
#include "types.h"

namespace ui {

class UIObject;

class UILayoutData {
public:
  void attachLayout(const char *name, UIObject *object) const;
  bool getLayoutRect(const char *name, mm::Rect<s16> &rect) const;
};

} // namespace ui
