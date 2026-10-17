#include "ui/ctrl/ui_ctrl_object.h"

#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_util.h"

namespace ui {

UICtrlObject::UICtrlObject(u32 object) : object(object), eventHandler(0) {
  addRef();
  UICtrlManager::get()->addCtrlObject(this);
}

UICtrlObject::~UICtrlObject() { ; }

bool UICtrlObject::isTerm() {
  if (getRefCount() == 1) {
    return true;
  }
  return !UIUtil::isValid(object);
}

void UICtrlObject::setupEventHanding(u32 handler, u16 id) {
  eventHandler = handler;
  this->id = id;
}

u16 UICtrlObject::getEventType(const EventData &event) { return event.param0 >> 16; }

void UICtrlObject::getEventParam(const EventData &event, u32 index, uiEventParam &param) { param.valueU32 = (&event.param0)[index]; }

} // namespace ui
