#include "gf/menu/object/gf_menu_obj_common_detail.h"

#include "ui/ui_object_acc.h"

namespace gf {

constexpr u32 CALL_COMMON_DETAIL = 79;

GfMenuObjCommonDetail::GfMenuObjCommonDetail(u32 handle) : GfMenuObject(handle) {}

GfMenuObjCommonDetail::~GfMenuObjCommonDetail() { ; }

void GfMenuObjCommonDetail::initialize() {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    attachExternalCall(CALL_COMMON_DETAIL, main.unknown10);
    GfMenuObject::initialize();
  }
}

void GfMenuObjCommonDetail::finalize() { GfMenuObject::finalize(); }

void GfMenuObjCommonDetail::update() { GfMenuObject::update(); }

} // namespace gf
