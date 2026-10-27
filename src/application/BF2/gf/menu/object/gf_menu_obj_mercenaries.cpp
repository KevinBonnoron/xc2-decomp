#include "gf/menu/object/gf_menu_obj_mercenaries.h"
#include "gf/menu/adapter/gf_menu_zone_adapter.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjMercenaries::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMercenaries::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

void GfMenuObjMercenaries::setupLocationSelect(ui::UIObjectAcc &acc) { GfMenuZoneAdapter::createFromReferenceZone(acc.searchChild("TXT_loc_select_name"), 0, false); }

} // namespace gf
