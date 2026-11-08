#include "gf/menu/object/gf_menu_obj_main_menu2_bg.h"

#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjMainMenu2BG::GfMenuObjMainMenu2BG(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr) {}

GfMenuObjMainMenu2BG::~GfMenuObjMainMenu2BG() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjMainMenu2BG::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainMenu2BG::setupMainMenuBG(ui::UIObjectAcc &) {}

} // namespace gf
