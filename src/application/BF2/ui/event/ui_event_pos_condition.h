#pragma once
#include <stddef.h>

#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectPosPlugin;

class UIEventPosCondition : public UIEventCondition {
public:
  UIEventPosCondition(u32 event, u32 value);
  virtual ~UIEventPosCondition();
  static UIEventPosCondition *create(u32 event, u32 value, const UIObjectPosPlugin *plugin);
  virtual int update();

  const UIObjectPosPlugin *plugin;
  bool adjusting;
};

static_assert(offsetof(UIEventPosCondition, plugin) == 0x20, "");
static_assert(offsetof(UIEventPosCondition, adjusting) == 0x28, "");
static_assert(sizeof(UIEventPosCondition) == 0x30, "");

} // namespace ui
