#include "gf/menu/object/gf_menu_obj_main_menu2_bg.h"

#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_manager.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x60;
GfMenuObjMainMenu2BG::GfMenuObjMainMenu2BG(u32 handle) : GfMenuObject(handle), unknown24(0), unknown28(nullptr), unknown30(nullptr) {}

GfMenuObjMainMenu2BG::~GfMenuObjMainMenu2BG() {
  mm::mtl::safeRelease(unknown30);
  mm::mtl::safeRelease(unknown28);
}

void GfMenuObjMainMenu2BG::finalize() { GfMenuObject::finalize(); }

void GfMenuObjMainMenu2BG::setupMainMenuBG(ui::UIObjectAcc &) {}

void GfMenuObjMainMenu2BG::update() {
  for (u32 i = 0; i < unknown30->getSize(); i++) {
    ui::UIObjectAcc acc(unknown30->getObject(i));
    if (!acc.isStreaming()) {
      acc.setAlpha(1.0f);
      acc.startAnimationFromIndex(1, false);
      unknown30->delObject(acc.unknown10);
    }
  }
  GfMenuObject::update();
}

void GfMenuObjMainMenu2BG::move(GfMenuCallContext *, u32 index, const OpenMainMenuBg &param) {
  u32 handle = getAttachedObject(unknown001);
  if (ui::UIObjectAcc(handle).isValid()) {
    if (!ui::UIObjectAcc(handle).isTerm()) {
      ui::EventData event;
      event.unknown00 = 0x101;
      event.unknown08 = param.unknown00;
      event.unknown0c = param.unknown08;
      event.unknown10 = param.unknown04;
      event.unknown14 = index;
      ui::UIManager::get()->requestObjectEvent(handle, event, 0.0f);
    }
  }
}

} // namespace gf
