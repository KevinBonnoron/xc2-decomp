#include "gf/menu/object/gf_menu_obj_special_gauge.h"

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x29;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

void GfMenuObjSpecialGauge::push() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjSpecialGauge::finalize() { GfMenuObject::finalize(); }

} // namespace gf
