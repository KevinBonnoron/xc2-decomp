#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectDispPlugin;

class UIEventDispCondition : public UIEventCondition {
public:
  UIEventDispCondition(u32 event, u32 value);
  virtual ~UIEventDispCondition();
  static UIEventDispCondition *create(u32 event, u32 value, const UIObjectDispPlugin *plugin);
  virtual int update();

  const UIObjectDispPlugin *unknown20; // Inferred role: plugin; original member name unknown.
  bool unknown28;                      // Inferred role: disp; original member name unknown.
};

static_assert(offsetof(UIEventDispCondition, unknown20) == 0x20, "");
static_assert(offsetof(UIEventDispCondition, unknown28) == 0x28, "");
static_assert(sizeof(UIEventDispCondition) == 0x30, "");

} // namespace ui
