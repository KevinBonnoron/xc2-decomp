#include "gf/menu/object/gf_menu_obj_blade_name.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x81;

void GfMenuObjBladeName::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjBladeName::finalize() { GfMenuObject::finalize(); }

} // namespace gf
