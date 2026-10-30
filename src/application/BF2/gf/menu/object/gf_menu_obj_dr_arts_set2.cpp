#include "gf/menu/object/gf_menu_obj_dr_arts_set2.h"

#include "mm_math/mm_pnt.h"
#include "ui/ui_object_acc.h"

namespace gf {

void GfMenuObjDrArtsSet2::finalize() { GfMenuObject::finalize(); }

void GfMenuObjDrArtsSet2::sendEvent(u32 handle, u32 type, u32 param) { unknown140(handle, type, param, 0.0f); }

void GfMenuObjDrArtsSet2::moveRight(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x += 0x10;
  acc.setPos(pos);
}

void GfMenuObjDrArtsSet2::moveLeft(ui::UIObjectAcc &acc) {
  mm::Pnt<s16> pos;
  acc.getPos(pos);
  pos.x -= 0x10;
  acc.setPos(pos);
}

} // namespace gf
