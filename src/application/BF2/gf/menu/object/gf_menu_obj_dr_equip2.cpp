#include "gf/menu/object/gf_menu_obj_dr_equip2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjDrEquip2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrEquip2::update() { GfMenuObject::update(); }

void GfMenuObjDrEquip2::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
