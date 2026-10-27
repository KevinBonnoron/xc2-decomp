#include "gf/menu/object/gf_menu_obj_party_status2.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjPartyStatus2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyStatus2::update() { GfMenuObject::update(); }

void GfMenuObjPartyStatus2::sendEvent(u32 handle, u32 type, u32 param) {
  if (handle != 0) {
    ui::EventData event;
    event.unknown08 = param;
    event.unknown0c = 0;
    event.unknown00 = type;
    ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
  }
}

} // namespace gf
