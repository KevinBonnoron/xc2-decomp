#pragma once
#include <stddef.h>

#include "mm_math/mm_rect.h"
#include "mm_mtl/reference_object.h"
#include "types.h"

namespace mm {
namespace mtl {
class IAllocator;
} // namespace mtl
} // namespace mm

namespace ui {

class UIObject;

class UILayoutData : public mm::mtl::ReferenceObject {
public:
  UILayoutData(void *data);
  virtual ~UILayoutData();
  static UILayoutData *create(void *data, mm::mtl::IAllocator *allocator, const UILayoutData *parent);
  bool attachLayout(const char *name, UIObject *object) const;
  bool getLayoutRect(const char *name, mm::Rect<s16> &rect) const;

  void *unknown10;               // Inferred role: data; original member name unknown.
  const UILayoutData *unknown18; // Inferred role: parent; original member name unknown.
};

static_assert(offsetof(UILayoutData, unknown10) == 0x10, "");
static_assert(offsetof(UILayoutData, unknown18) == 0x18, "");
static_assert(sizeof(UILayoutData) == 0x20, "");

} // namespace ui
