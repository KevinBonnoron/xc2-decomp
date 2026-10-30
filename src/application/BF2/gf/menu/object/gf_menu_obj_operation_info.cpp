#include "gf/menu/object/gf_menu_obj_operation_info.h"
#include "gf/menu/gf_menu_types.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x47;

void GfMenuObjOperationInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOperationInfo::update() { GfMenuObject::update(); }

void GfMenuObjOperationInfo::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = GfMenuTypes::unknown003_34;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
