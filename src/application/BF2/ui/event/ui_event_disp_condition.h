#pragma once
#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectDispPlugin;

class UIEventDispCondition : public UIEventCondition {
public:
  static UIEventDispCondition *create(u32 event, u32 value, const UIObjectDispPlugin *plugin);
};

} // namespace ui
