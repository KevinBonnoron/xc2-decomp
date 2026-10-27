#include "gf/menu/object/gf_menu_obj_environment_info.h"
#include "gf/menu/gf_menu_flag.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x2a;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;

GfMenuObjEnvironmentInfo::GfMenuObjEnvironmentInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjEnvironmentInfo::~GfMenuObjEnvironmentInfo() { ; }

void GfMenuObjEnvironmentInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjEnvironmentInfo::update() { GfMenuObject::update(); }

void GfMenuObjEnvironmentInfo::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::UI_EVENT_CLOSE;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjEnvironmentInfo::open() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::UI_EVENT_OPEN;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjEnvironmentInfo::disable() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = unknown002;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      GfMenuFlag::set1(0x1e, 1);
    }
  }
}

void GfMenuObjEnvironmentInfo::enable() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = unknown003;
      GfMenuObject::sendEvent(handle, event, 0.0f);
      GfMenuFlag::set1(0x1e, 0);
    }
  }
}

} // namespace gf
