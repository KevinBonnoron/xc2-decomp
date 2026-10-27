#include "gf/menu/object/gf_menu_obj_main_submenu.h"

#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"

namespace gf {

void GfMenuObjMainSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainSubmenu::update() { GfMenuObject::update(); }

bool GfMenuObjMainSubmenu::isEnableSkipTime() {
  if (GfDataUtil::getScenarioFlag() > 0xfbc && GfDataUtil::getScenarioFlag() < 0xfc9 && GfGameManager::getMapID() == 10) {
    return false;
  }
  return true;
}

} // namespace gf
