#include "gf/menu/object/gf_menu_obj_common_list.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x24;

GfMenuObjCommonList::GfMenuObjCommonList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonList::~GfMenuObjCommonList() { ; }

void GfMenuObjCommonList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonList::update() { GfMenuObject::update(); }

void GfMenuObjCommonList::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::UI_EVENT_CLOSE;
      GfMenuObject::sendEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
