#include "ui/ctrl/ui_ctrl_object.h"

#include "ui/ctrl/ui_ctrl_manager.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
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

u16 UICtrlObject::getEventCtrlObjID(const EventData &event) { return event.unknown08_u16; }

u16 UICtrlObject::getEventType(const EventData &event) { return event.unknown08 >> 16; }

void UICtrlObject::getEventParam(const EventData &event, u32 index, uiEventParam &param) { param.valueU32 = (&event.unknown08)[index]; }

void UICtrlObject::sendEvent(u16 type, const uiEventParam *param0, const uiEventParam *param1, const uiEventParam *param2) {
  UIEventManager *manager = UIEventManager::get();
  if (manager == nullptr || unknown24 == 0) {
    return;
  }
  EventData data;
  data.unknown00 = 0xe;
  data.unknown08_u16 = unknown28;
  data.unknown0a = type;
  data.unknown0c = param0 != nullptr ? param0->valueU32 : 0;
  data.unknown10 = param1 != nullptr ? param1->valueU32 : 0;
  data.unknown14 = param2 != nullptr ? param2->valueU32 : 0;
  UIEventManager::EventInfo info;
  info.unknown00 = unknown24;
  info.unknown08 = data;
  manager->pushObjectEvent(info);
}

} // namespace ui
