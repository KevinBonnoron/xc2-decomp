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

  const UIObjectPosPlugin *unknown20; // Inferred role: plugin; original member name unknown.
  bool unknown28;                     // Inferred role: adjusting; original member name unknown.
};

static_assert(offsetof(UIEventPosCondition, unknown20) == 0x20, "");
static_assert(offsetof(UIEventPosCondition, unknown28) == 0x28, "");
static_assert(sizeof(UIEventPosCondition) == 0x30, "");

} // namespace ui
