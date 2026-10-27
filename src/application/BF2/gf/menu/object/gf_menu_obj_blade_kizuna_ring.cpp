#include "gf/menu/object/gf_menu_obj_blade_kizuna_ring.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjBladeKizunaRing::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeKizunaRing::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
