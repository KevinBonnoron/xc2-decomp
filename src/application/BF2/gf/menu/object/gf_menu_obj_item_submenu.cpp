#include "gf/menu/object/gf_menu_obj_item_submenu.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjItemSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemSubmenu::update() { GfMenuObject::update(); }

void GfMenuObjItemSubmenu::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
