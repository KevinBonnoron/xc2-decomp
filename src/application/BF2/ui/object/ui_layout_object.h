#pragma once
#include <stddef.h>

#include "mm_math/mm_rect.h"
#include "types.h"
#include "ui/ui_object.h"

namespace mm {
namespace mtl {
class RTTI;
} // namespace mtl
} // namespace mm

namespace ui {

class UILayoutData;

class UILayoutObject : public UIObject {
public:
  static mm::mtl::RTTI m_rtti;

  u32 addChild(u32 parent, UIObject *child);
  u32 countChild(const char *name, u32 length) const;
  u32 countActiveChild() const;
  u32 searchChild(const char *name) const;
  u32 searchDuplicatedChild(const char *name, u16 index) const;
  void setViewport(const mm::Rect<s16> &viewport);
  void updateSize();

  u8 _108[0x110 - 0x108];
  UILayoutData *unknown110; // Inferred role: layout data; original member name unknown.
};

static_assert(offsetof(UILayoutObject, unknown110) == 0x110, "");

} // namespace ui
