#include "gf/menu/object/gf_menu_obj_special_gauge.h"

#include "gf/menu/gf_menu_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown004 = 0x100;

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x29;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x10a;

GfMenuObjSpecialGauge::GfMenuObjSpecialGauge(u32 handle) : GfMenuObject(handle) {}

GfMenuObjSpecialGauge::~GfMenuObjSpecialGauge() { ; }

void GfMenuObjSpecialGauge::push() { unknown144(unknown001, unknown002); }

void GfMenuObjSpecialGauge::finalize() { GfMenuObject::finalize(); }

void GfMenuObjSpecialGauge::update() {
  ui::UIObjectAcc(unknown18).setAlpha(1.0f);
  GfMenuObject::update();
}

void GfMenuObjSpecialGauge::close() { unknown145(unknown001, unknown003); }

void GfMenuObjSpecialGauge::open() { unknown145(unknown001, unknown004); }

void GfMenuObjSpecialGauge::reverse(bool isReverse) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid() && !acc.isTerm()) {
    ui::EventData event;
    event.unknown0c = 0;
    event.unknown00 = 0x10b;
    event.unknown08 = isReverse;
    ui::UIManager::get()->requestObjectEvent(acc.unknown10, event, 0.0f);
  }
}

} // namespace gf
