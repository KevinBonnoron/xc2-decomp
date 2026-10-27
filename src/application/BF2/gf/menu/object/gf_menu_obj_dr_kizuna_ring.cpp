#include "gf/menu/object/gf_menu_obj_dr_kizuna_ring.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjDrKizunaRing::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjDrKizunaRing::isLockPos(int index) { return index % 6 == 0; }

bool GfMenuObjDrKizunaRing::isScreenLR(u32 screen) { return screen < 3; }

void GfMenuObjDrKizunaRing::setupCircle(ui::UIObjectAcc &, u32) {}

void GfMenuObjDrKizunaRing::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
