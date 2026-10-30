#include "gf/menu/object/gf_menu_obj_blade_change.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x3c;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x104;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x102;

void GfMenuObjBladeChange::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBladeChange::enableAwakening(bool) {}

void GfMenuObjBladeChange::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_34;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjBladeChange::exitChainAttack() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjBladeChange::open() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::unknown003_33;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjBladeChange::pushGroupUp() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown003;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
