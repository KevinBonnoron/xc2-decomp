#include "gf/menu/object/gf_menu_obj_other_cursor.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjOtherCursor::GfMenuObjOtherCursor(u32 handle) : GfMenuObject(handle), unknown24(0), unknown30(0) {}

GfMenuObjOtherCursor::~GfMenuObjOtherCursor() { ; }

void GfMenuObjOtherCursor::finalize() { GfMenuObject::finalize(); }

void GfMenuObjOtherCursor::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x13));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

} // namespace gf
