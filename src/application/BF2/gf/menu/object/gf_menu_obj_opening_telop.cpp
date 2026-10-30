#include "gf/menu/object/gf_menu_obj_opening_telop.h"

#include "gf/menu/gf_menu_object.h"
#include "gf/menu/gf_menu_types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x82;
// Inferred role: telop position; original name unknown.
constexpr u32 unknown002_0 = 0;
constexpr u32 unknown002_1 = 1;
constexpr u32 unknown002_2 = 2;

void GfMenuObjOpeningTelop::openCenter(u32 telop) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = unknown002_0;
    event.unknown0c = telop;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjOpeningTelop::closeCenter() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjOpeningTelop::openLeft(u32 telop) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = unknown002_1;
    event.unknown0c = telop;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjOpeningTelop::openRight(u32 telop) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    event.unknown08 = unknown002_2;
    event.unknown0c = telop;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjOpeningTelop::finalize() { GfMenuObject::finalize(); }

} // namespace gf
