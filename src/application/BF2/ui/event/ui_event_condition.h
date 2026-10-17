#pragma once
#include <stddef.h>

#include "mm_mtl/reference_object.h"
#include "types.h"

namespace ui {

class UIEventCondition : public mm::mtl::ReferenceObject {
public:
  UIEventCondition(u32 event, u32 value) : event(event), value(value) {}
  virtual int update() = 0;
  virtual u32 getArg() const;

  u32 event;
  u32 value;
  UIEventCondition *next;
};

static_assert(offsetof(UIEventCondition, event) == 0x0c, "");
static_assert(offsetof(UIEventCondition, value) == 0x10, "");
static_assert(offsetof(UIEventCondition, next) == 0x18, "");
static_assert(sizeof(UIEventCondition) == 0x20, "");

} // namespace ui
