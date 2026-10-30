#include "gf/menu/object/gf_menu_obj_party_gauge.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x55;

void GfMenuObjPartyGauge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjPartyGauge::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::UIObjectAcc child(acc.unknown10, "LAY_gauge");
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(child.unknown10, event, 0.0f);
  }
}

} // namespace gf
