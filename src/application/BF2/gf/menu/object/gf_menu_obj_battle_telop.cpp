#include "gf/menu/object/gf_menu_obj_battle_telop.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x4e;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

void GfMenuObjBattleTelop::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBattleTelop::update() { GfMenuObject::update(); }

void GfMenuObjBattleTelop::close() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = GfMenuTypes::UI_EVENT_CLOSE;
    GfMenuObject::sendEvent(acc.searchChild("LAY_telop"), event, 0.0f);
  }
}

void GfMenuObjBattleTelop::closeUniteCombo() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    ui::EventData event;
    event.unknown00 = unknown002;
    GfMenuObject::sendEvent(acc.searchChild("LAY_fusion_combo"), event, 0.0f);
  }
}

} // namespace gf
