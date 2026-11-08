#include "gf/menu/object/gf_menu_obj_item_list.h"

#include "gf/menu/gf_menu_reference_list.h"
#include "gf/menu/list/gf_menu_item_list.h"
#include "mm_mtl/reference_object.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h"
#include "ui/ctrl/ui_ctrl_slide_select.h"
#include "ui/list/ui_select_obj_list.h"

namespace gf {

GfMenuObjItemList::GfMenuObjItemList(u32 handle) : GfMenuObject(handle) {}

GfMenuObjItemList::~GfMenuObjItemList() {
  mm::mtl::safeRelease(unknown28);
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown38);
  mm::mtl::safeRelease(unknown40);
  for (int i = 0; i < 21; i++) {
    mm::mtl::safeRelease(unknown48[i]);
  }
  unknownf0 = nullptr;
}

void GfMenuObjItemList::finalize() { GfMenuObject::finalize(); }

void GfMenuObjItemList::update() { GfMenuObject::update(); }

} // namespace gf
