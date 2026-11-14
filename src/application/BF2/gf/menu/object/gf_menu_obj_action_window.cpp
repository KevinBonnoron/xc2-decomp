#include "gf/menu/object/gf_menu_obj_action_window.h"

#include "gf/data/gf_bdat_id.h"
#include "gf/data/gf_data_bdat.h"
#include "gf/game/gf_game_util.h"
#include "gf/gf_allocator.h"
#include "gf/menu/adapter/gf_menu_game_adapter.h"
#include "gf/menu/gf_menu_bdat.h"
#include "gf/menu/object/gf_menu_obj_util.h"
#include "gf/object/gf_obj_handle.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/event/ui_event_manager.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"
#include "ui/ui_str.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0xb;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown002 = 0x101;
// Inferred role: ui event type; original name unknown.
constexpr u16 unknown003 = 0x100;

GfMenuObjActionWindow::GfMenuObjActionWindow(u32 handle) : GfMenuObject(handle) {}

GfMenuObjActionWindow::~GfMenuObjActionWindow() { ; }

void GfMenuObjActionWindow::initialize() {
  ui::UIObjectAcc acc(unknown18);
  if (acc.isValid()) {
    attachExternalCall(10, unknown18);
    u32 main = acc.searchChild("LAY_main");
    if (ui::UIObjectAcc(main).isValid()) {
      attachExternalCall(unknown001, main);
// __LINE__ must be 87 as in the original file: it is the line argument of operator new.
#line 87
      MainListener *listener = new (getAllocator(ALLOCATOR_UNKNOWN_0), __FILE__, __LINE__, 8) MainListener(this);
      listener->addRef();
      ui::UIEventManager::get()->registObjectListener(main, listener);
      if (listener != nullptr) {
        listener->release();
      }
    }
    GfMenuGameAdapter::create(acc.searchChild("LAY_contents"), 0x11, true);
    GfMenuObject::initialize();
  }
}

void GfMenuObjActionWindow::finalize() { GfMenuObject::finalize(); }

void GfMenuObjActionWindow::update() { GfMenuObject::update(); }

void GfMenuObjActionWindow::eventHudSceneChange(u32) {}

void GfMenuObjActionWindow::open(const OpenParam &param) {
  u32 object = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      GF_OBJ_HANDLE *target = param.unknown00;
      GfGameUtil::UiActionWindowInfo info;
      if (target != unknown020) {
        info.create(target);
      }
      u16 text = registString(ui::UIStr(info.unknown00, info.unknown08));
      ui::EventData event;
      event.unknown00 = unknown003;
      event.unknown08 = text;
      event.unknown0c = GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getBtnIconNumber(param.unknown08));
      ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
    }
  }
}

void GfMenuObjActionWindow::openBattle(const OpenParam &param) {
  u32 object = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(object).isValid()) {
    if (!ui::UIObjectAcc(object).isTerm()) {
      u16 text = registString(ui::UIStr(GfDataBdat::getFP(BDAT_FLD_ACTIONWINDOW), 5));
      ui::EventData event;
      event.unknown00 = unknown003;
      event.unknown08 = text;
      event.unknown0c = GfMenuBdat::getIconImageIndex(GfMenuObjUtil::getBtnIconNumber(param.unknown08));
      ui::UIManager::get()->requestObjectEvent(object, event, 0.0f);
    }
  }
}

void GfMenuObjActionWindow::close() { GF_MENU_REQUEST_EVENT(unknown001, unknown002); }

void GfMenuObjActionWindow::closeBattle() { close(); }

void GfMenuObjActionWindow::disp(bool disp) {
  ui::UIObjectAcc acc(GfMenuObject::getAttachedObject(10));
  if (acc.isValid()) {
    acc.setDisp(disp);
  }
}

void GfMenuObjActionWindow::MainListener::reciveEvent(const ui::EventData &event, u32 handle) {
  ui::UIObjectAcc acc(handle);
  switch (event.unknown00) {
  case 1:
  case unknown002:
    acc.setDisp(false);
    break;
  case unknown003: {
    {
      ui::UIObjectAcc text(acc.searchChild("TXT_content"));
      if (text.isValid()) {
        GfMenuObject::setText(text.unknown10, event.unknown08);
      }
    }
    if (event.unknown0c != 0xffffffff) {
      ui::UIObjectAcc button(handle, "IMG_btn");
      if (button.isValid()) {
        button.setImageIndex(event.unknown0c);
        button.setDisp(true);
      } else {
        button.setDisp(false);
      }
    }
    acc.setDisp(true);
    break;
  }
  default:
    ui::UIObjectListener::reciveEvent(event, handle);
    break;
  }
}

} // namespace gf
