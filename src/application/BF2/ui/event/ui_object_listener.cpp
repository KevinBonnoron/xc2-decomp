#include "ui/event/ui_object_listener.h"

#include "ui/event/ui_event_data.h"
#include "ui/ui_object.h"
#include "ui/ui_util.h"

namespace ui {

void UIObjectListener::reciveEvent(const EventData &event, u32 handle) {
  if (event.type == 2) {
    UIUtil::getObject(handle)->setTerm();
  }
}

} // namespace ui
