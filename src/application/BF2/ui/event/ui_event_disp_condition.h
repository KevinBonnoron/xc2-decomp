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

  const UIObjectDispPlugin *plugin;
  bool disp;
};

static_assert(offsetof(UIEventDispCondition, plugin) == 0x20, "");
static_assert(offsetof(UIEventDispCondition, disp) == 0x28, "");
static_assert(sizeof(UIEventDispCondition) == 0x30, "");

} // namespace ui
