#pragma once
#include "types.h"
#include "ui/event/ui_event_condition.h"

namespace ui {

class UIObjectPosPlugin;

class UIEventPosCondition : public UIEventCondition {
public:
  static UIEventPosCondition *create(u32 event, u32 value, const UIObjectPosPlugin *plugin);
};

} // namespace ui
