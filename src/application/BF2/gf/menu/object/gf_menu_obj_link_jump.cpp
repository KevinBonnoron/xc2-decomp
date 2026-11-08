#include "gf/menu/object/gf_menu_obj_link_jump.h"

#include "gf/menu/gf_menu_reference.h"
#include "gf/menu/gf_menu_types.h"
#include "mm_mtl/reference_object.h"
#include "types.h"
#include "ui/ctrl/ui_ctrl_cursor_select.h" // IWYU pragma: keep
#include "ui/ctrl/ui_ctrl_object.h"
#include "ui/ctrl/ui_ctrl_revolve_select.h"
#include "ui/event/ui_event_data.h"
#include "ui/list/ui_list_info.h"
#include "ui/list/ui_select_obj_list.h"
#include "ui/ui_object_acc.h"

namespace gf {

// Inferred role: attached call id; original name unknown.
constexpr u32 unknown001 = 0x49;

GfMenuObjLinkJump::GfMenuObjLinkJump(u32 handle) : GfMenuObject(handle), unknown28(), unknown68(nullptr), unknown70(nullptr), unknown78(false) {}

GfMenuObjLinkJump::~GfMenuObjLinkJump() {
  for (int i = 0; i < 2; i++) {
    mm::mtl::safeRelease(unknown28[i].unknown18);
    mm::mtl::safeRelease(unknown28[i].unknown08);
    mm::mtl::safeRelease(unknown28[i].unknown10);
  }
  mm::mtl::safeRelease(unknown70);
  mm::mtl::safeRelease(unknown68);
}

void GfMenuObjLinkJump::finalize() {
  GfMenuReference::clearLinkList();
  GfMenuObject::finalize();
}

void GfMenuObjLinkJump::update() { GfMenuObject::update(); }

void GfMenuObjLinkJump::close() {}

void GfMenuObjLinkJump::changeCategory(int index) {
  ui::UIObjectAcc main(unknown18, "LAY_main");
  if (main.isValid()) {
    unknown68->setIndex(index);
    u32 selected = unknown68->getSelectObject();
    for (int i = 0; i < 2; i++) {
      if (unknown28[i].unknown08 != nullptr && unknown28[i].unknown00 == selected) {
        unknown28[i].unknown08->setIndex(0);
        setupInputSelectionFromList(main.unknown10, *unknown28[i].unknown08);
      }
    }
    migrateInput(main.unknown10, selected);
  }
}

void GfMenuObjLinkJump::listenerCategorySelect(const ui::EventData &event) {
  switch (ui::UICtrlObject::getEventType(event)) {
  case 2:
    if (unknown78) {
      ui::UIObjectAcc notify(unknown18, "LAY_notify");
      ui::EventData notifyEvent;
      notifyEvent.unknown00 = 0x22;
      sendEvent(notify.unknown10, notifyEvent, 0.0f);
    }
    break;
  case 3:
    if (!unknown78) {
      ui::UIObjectAcc notify(unknown18, "LAY_notify");
      ui::EventData notifyEvent;
      notifyEvent.unknown00 = 0x21;
      sendEvent(notify.unknown10, notifyEvent, 0.0f);
      ui::UIObjectAcc(unknown18).setDispChild(false, "LAY_main");
      ui::UIObjectAcc(unknown18).setDispChild(false, "IMG_bg");
    } else {
      ui::UIObjectAcc categoryList(unknown18, "LAY_category_list");
      if (categoryList.isValid()) {
        ui::UIObjectAcc main(unknown18, "LAY_main");
        if (main.isValid()) {
          enableInput(categoryList.unknown10);
          enableInput(main.unknown10);
        }
      }
    }
    break;
  }
}

void GfMenuObjLinkJump::open() { unknown143(unknown001, GfMenuTypes::unknown003_33); }

} // namespace gf
