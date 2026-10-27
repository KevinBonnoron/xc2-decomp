#include "gf/menu/object/gf_menu_obj_pouch.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjPouch::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPouch::update() { GfMenuObject::update(); }

void GfMenuObjPouch::setupPouch(ui::UIObjectAcc &) {}

void GfMenuObjPouch::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
