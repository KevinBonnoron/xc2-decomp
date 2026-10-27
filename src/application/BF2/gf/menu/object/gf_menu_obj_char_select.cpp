#include "gf/menu/object/gf_menu_obj_char_select.h"
#include "gf/game/gf_game_util.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"

namespace gf {

void GfMenuObjCharSelect::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjCharSelect::seqSpHikariToHomura() {
  GfGameUtil::changeHikariCurrent(false);
  return true;
}

bool GfMenuObjCharSelect::seqSpHomuraToHikari() {
  GfGameUtil::changeHikariCurrent(true);
  return true;
}

void GfMenuObjCharSelect::sendEvent(u32 handle, u32 type, u32 param) {
  ui::EventData event;
  event.unknown08 = param;
  event.unknown0c = 0;
  event.unknown00 = type;
  ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
}

} // namespace gf
