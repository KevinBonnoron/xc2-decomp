#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {

class UIEventCondition : public mm::mtl::ReferenceObject {
public:
  UIEventCondition(u32 event, u32 value) : unknown0c(event), unknown10(value) {}
  virtual int update() = 0;
  virtual u32 getArg() const;

  u32 unknown0c;               // Inferred role: event; original member name unknown.
  u32 unknown10;               // Inferred role: value; original member name unknown.
  UIEventCondition *unknown18; // Inferred role: next; original member name unknown.
};

static_assert(offsetof(UIEventCondition, unknown0c) == 0x0c, "");
static_assert(offsetof(UIEventCondition, unknown10) == 0x10, "");
static_assert(offsetof(UIEventCondition, unknown18) == 0x18, "");
static_assert(sizeof(UIEventCondition) == 0x20, "");

} // namespace ui
