#include "gf/menu/object/gf_menu_obj_action_window.h"

#include "types.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0xb;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;

GfMenuObjActionWindow::GfMenuObjActionWindow(u32 handle) : GfMenuObject(handle) {}

GfMenuObjActionWindow::~GfMenuObjActionWindow() { ; }

void GfMenuObjActionWindow::finalize() { GfMenuObject::finalize(); }

void GfMenuObjActionWindow::update() { GfMenuObject::update(); }

void GfMenuObjActionWindow::eventHudSceneChange(u32) {}

void GfMenuObjActionWindow::closeBattle() { close(); }

void GfMenuObjActionWindow::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(10));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjActionWindow::close() { unknown142(unknown001, unknown002); }

} // namespace gf
