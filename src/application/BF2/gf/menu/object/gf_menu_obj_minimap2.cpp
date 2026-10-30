#include "gf/menu/object/gf_menu_obj_minimap2.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x80;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x100;

void GfMenuObjMinimap2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMinimap2::enable() { GfMenuFlag::set1(0x1f, 0); }

void GfMenuObjMinimap2::disable() { GfMenuFlag::set1(0x1f, 1); }

void GfMenuObjMinimap2::changeMap() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.searchChild("LAY_map"), event, 0.0f);
  }
}

void GfMenuObjMinimap2::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjMinimap2::open() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_33;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
