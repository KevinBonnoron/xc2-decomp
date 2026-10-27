#include "gf/menu/object/gf_menu_obj_hana_parts_crystal.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/util/gf_item_util.h"

namespace gf {

void GfMenuObjHanaPartsCrystal::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsCrystal::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsCrystal::getCrystalItemCount(u32 item) { return GfItemUtil::getItemBoxCount(item); }

void GfMenuObjHanaPartsCrystal::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
