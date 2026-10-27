#include "gf/menu/object/gf_menu_obj_hana_parts_make.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

#include "gf/game/gf_game_util_hana.h"

namespace gf {

void GfMenuObjHanaPartsMake::finalize() { GfMenuObject::finalize(); }

void GfMenuObjHanaPartsMake::update() { GfMenuObject::update(); }

u32 GfMenuObjHanaPartsMake::getCrystalItemCount(u32 item) { return GfGameUtilHana::getConvertToEther(item); }

void GfMenuObjHanaPartsMake::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
