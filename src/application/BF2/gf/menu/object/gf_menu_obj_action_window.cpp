#include "gf/menu/object/gf_menu_obj_action_window.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/ui_manager.h"
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

void GfMenuObjActionWindow::close() {
  u32 handle = GfMenuObject::getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = unknown002;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
