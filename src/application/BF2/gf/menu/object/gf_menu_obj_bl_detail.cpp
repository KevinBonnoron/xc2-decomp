#include "gf/menu/object/gf_menu_obj_bl_detail.h"

#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_BL_DETAIL = 80;

GfMenuObjBlDetail::GfMenuObjBlDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjBlDetail::~GfMenuObjBlDetail() { ; }

void GfMenuObjBlDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_BL_DETAIL, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjBlDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjBlDetail::update() { GfMenuObject::update(); }

} // namespace gf
