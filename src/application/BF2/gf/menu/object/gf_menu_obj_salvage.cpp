#include "gf/menu/object/gf_menu_obj_salvage.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjSalvage::finalize() { GfMenuObject::finalize(); }

bool GfMenuObjSalvage::seqResultEnd() {
  ui::UIObjectAcc acc(unknown18, "LAY_result");
  termCallContext(acc.unknown10);
  return true;
}

} // namespace gf
