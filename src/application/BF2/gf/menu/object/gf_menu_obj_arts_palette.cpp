#include "gf/menu/object/gf_menu_obj_arts_palette.h"
#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x10b;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown005 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x27;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

void GfMenuObjArtsPalette::finalize() { GfMenuObject::finalize(); }

void GfMenuObjArtsPalette::push(unsigned int slot) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown08 = slot;
    event.unknown0c = 0;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjArtsPalette::exitChainAttack() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown003;
    GfMenuObject::sendEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjArtsPalette::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown004;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

void GfMenuObjArtsPalette::open() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown00 = unknown005;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
