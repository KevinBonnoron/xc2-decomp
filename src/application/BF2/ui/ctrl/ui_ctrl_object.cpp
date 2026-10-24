#include "ui/ctrl/ui_ctrl_object.h"

#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_util.h"

namespace ui {

UICtrlObject::UICtrlObject(u32 object) : unknown20(object), unknown24(0) {
  addRef();
  UICtrlManager::get()->addCtrlObject(this);
}

UICtrlObject::~UICtrlObject() { ; }

bool UICtrlObject::isTerm() {
  if (getRefCount() == 1) {
    return true;
  }
  return !UIUtil::isValid(unknown20);
}

void UICtrlObject::setupEventHanding(u32 handler, u16 id) {
  unknown24 = handler;
  this->unknown28 = id;
}

u16 UICtrlObject::getEventType(const EventData &event) { return event.unknown08 >> 16; }

void UICtrlObject::getEventParam(const EventData &event, u32 index, uiEventParam &param) { param.valueU32 = (&event.unknown08)[index]; }

} // namespace ui
