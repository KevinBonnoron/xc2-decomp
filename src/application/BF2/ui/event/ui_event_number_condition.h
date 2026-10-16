#pragma once
#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectNumberPlugin;

class UIEventNumberCondition : public UIEventCondition {
public:
  static UIEventNumberCondition *create(u32 event, u32 value, const UIObjectNumberPlugin *plugin);
  static UIEventNumberCondition *create(u32 event, u32 value, const UIObjectNumberPlugin *plugin, f32 time);
};

} // namespace ui
