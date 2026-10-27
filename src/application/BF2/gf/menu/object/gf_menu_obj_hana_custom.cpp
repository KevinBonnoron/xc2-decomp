#include "gf/menu/object/gf_menu_obj_hana_custom.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjHanaCustom::finalize() { GfMenuObject::finalize(); }

u32 GfMenuObjHanaCustom::convPartsId(u32 partsId) {
  if (partsId > 0xf) {
    return partsId - 7;
  }
  return partsId;
}

bool GfMenuObjHanaCustom::isExpandParts(u32 partsId) { return partsId - 9 < 6; }

void GfMenuObjHanaCustom::refreshPlanLine(ui::UIObjectAcc &) {}

void GfMenuObjHanaCustom::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
