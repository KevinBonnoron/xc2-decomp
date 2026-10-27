#include "gf/menu/object/gf_menu_obj_combo_route.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x5e;

void GfMenuObjComboRoute::finalize() { GfMenuObject::finalize(); }

void GfMenuObjComboRoute::update() { GfMenuObject::update(); }

void GfMenuObjComboRoute::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::UI_EVENT_CLOSE;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

void GfMenuObjComboRoute::open() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::UI_EVENT_OPEN;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
