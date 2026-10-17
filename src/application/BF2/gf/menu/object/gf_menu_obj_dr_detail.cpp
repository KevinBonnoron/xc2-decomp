#include "gf/menu/object/gf_menu_obj_dr_detail.h"

#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_DR_DETAIL = 81;

GfMenuObjDrDetail::GfMenuObjDrDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjDrDetail::~GfMenuObjDrDetail() { ; }

void GfMenuObjDrDetail::initialize() {
  ui::UIObjectAcc main(handle, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_DR_DETAIL, main.handle);
    GfMenuObject::initialize();
  }
}

void GfMenuObjDrDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrDetail::update() { GfMenuObject::update(); }

} // namespace gf
