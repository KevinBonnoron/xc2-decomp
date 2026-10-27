#include "gf/menu/object/gf_menu_obj_target_info.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

GfMenuObjTargetInfo::GfMenuObjTargetInfo(u32 handle) : GfMenuObject(handle) {}

GfMenuObjTargetInfo::~GfMenuObjTargetInfo() { ; }

void GfMenuObjTargetInfo::finalize() { GfMenuObject::finalize(); }

void GfMenuObjTargetInfo::update() { GfMenuObject::update(); }

void GfMenuObjTargetInfo::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0x11));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllEnemy(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xc));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllOther(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xd));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjTargetInfo::dispAllSymbol(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(0xe));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

} // namespace gf
