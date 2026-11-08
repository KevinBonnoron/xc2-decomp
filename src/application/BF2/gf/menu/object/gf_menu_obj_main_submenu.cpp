#include "gf/menu/object/gf_menu_obj_main_submenu.h"

#include <string.h>

#include "gf/data/gf_data_util.h"
#include "gf/game/gf_game_manager.h"
#include "gf/menu/call/gf_menu_call_context.h"
#include "mm_mtl/reference_object.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjMainSubmenu::GfMenuObjMainSubmenu(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(0), unknown2c(0), unknown30(nullptr), unknown64(true), unknown68(nullptr), unknown70(-1) {
  memset(unknown74, 0xff, sizeof(unknown74));
}

GfMenuObjMainSubmenu::~GfMenuObjMainSubmenu() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjMainSubmenu::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainSubmenu::update() { GfMenuObject::update(); }

bool GfMenuObjMainSubmenu::isEnableSkipTime() {
  if (GfDataUtil::getScenarioFlag() > 0xfbc && GfDataUtil::getScenarioFlag() < 0xfc9 && GfGameManager::getMapID() == 10) {
    return false;
  }
  return true;
}

} // namespace gf
