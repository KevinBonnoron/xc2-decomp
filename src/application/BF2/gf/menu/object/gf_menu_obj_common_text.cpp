#include "gf/menu/object/gf_menu_obj_common_text.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjCommonText::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonText::update() { GfMenuObject::update(); }

void GfMenuObjCommonText::sendEvent(u32 handle, u32 type, u32 param, f32 delay) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, delay);
}

} // namespace gf
