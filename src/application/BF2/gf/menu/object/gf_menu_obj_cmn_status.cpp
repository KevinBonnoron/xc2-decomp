#include "gf/menu/object/gf_menu_obj_cmn_status.h"
#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x52;

bool GfMenuObjCmnStatus::s_DispFlag[2];

bool GfMenuObjCmnStatus::isOpenDrStatus() { return s_DispFlag[0]; }

bool GfMenuObjCmnStatus::isOpenBlStatus() { return s_DispFlag[1]; }

void GfMenuObjCmnStatus::update() { GfMenuObject::update(); }

void GfMenuObjCmnStatus::setInputDisable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::disableInput(acc.unknown10);
  }
}

void GfMenuObjCmnStatus::setInputEnable() {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(unknown001));
  if (acc.isValid()) {
    GfMenuObject::enableInput(acc.unknown10);
  }
}

} // namespace gf
